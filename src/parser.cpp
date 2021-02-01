#include "simon.h"
#include <iostream>
#include <generator.h>
#include <fstream>

bool comment_mode;
void parse_line(str str);
str replace_all(str &basicString, char i, char i1);
str list_to_str(std::list<std::string> list, const char *delim);
extern std::list<std::string> libraries;

bool hasEnding(std::string const &fullString, std::string const &ending) {
    if (fullString.length() >= ending.length())
        return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
    else
        return false;
}

/**
 * Parses a smn file, and does stuff with it.
 */
void parse(std::istream *input) {
    global.line++;
    auto generator = for_language(global.language);
    str obj;
    char* ptr = new char[512];
    input->getline(ptr, 512);
    obj = str(ptr);
    if (obj.empty()) return;

    // Comments
    int i = 0;
    for (; obj[i] == ' ' || obj[i] == '\t'; ++i) {
        if(i >= obj.size()) return;
    }
    if (obj[i] == '#') {
        return;
    }
    bool is_directive = obj[i] == '/';
    str match = ";";
    if(is_directive) match = "/";
    if(!hasEnding(obj, match) && !is_directive) {
        print_error("at line " + current_line + ": missing semicolon");
        exit(1);
    }
    parse_line(str((char*)((long)ptr + i)));

    // Flush outputs
    std::cout.flush();
    std::cerr.flush();
}

enum ParsePart {
    Name, Arguments, Body, Finished
};

extern bool comments;
str** test_names = nullptr;
int test_index = 0;
std::list<str> stack;

void parse_line(str s) {
#if TESTING == true
    print_info(current_line + " " + global.filename + " : " + s + " # " + list_to_str(stack, " -> "));
#endif
    auto generator = for_language(global.language);
    if (s == "/language: cpp/") {
        global.language = Language::CPP;
        return;
    }
    if (s == "/language: c/") {
        print_warning("at line " + current_line + ":");
        print_warning("c will not be supported in a future release. consider switching to c++:");
        print_warning("  * it has full support for classes");
        print_warning("  * you can use interfaces");
        print_warning("  * SIMONDEV is compatible");
        global.language = Language::C;
        return;
    }
    if (s == "/test/") {
        global.is_test = true;
        return;
    }
    if(global.language == NONE) {
        print_error("at line " + current_line + ": must have /language: .../ before code");
        exit(1);
    }
    if(comments) *global.output << generator->generate_comment("=> " + s, true);
    if (s.substr(0, 5) == "/cpp/") {
        *global.output << generator->transform(CPP, s.substr(5, s.size() - 7)) << std::endl;
    }
    if (s.substr(0, 3) == "/c/") {
        *global.output << generator->transform(C, s.substr(3, s.size() - 5)) << std::endl;
    }
    if (s.substr(0, 5) == "/asm/") {
        *global.output << generator->transform(ASSEMBLY, s.substr(5, s.size() - 7)) << std::endl;
    }
    if (s[0] == '/') return;
    std::list<str> args, lines;
    str name;
    str buf;
    ParsePart part = Name;
    bool started;
    char l = '\x00';
    int i = 0;
    bool interpret_next = true;
    if (s[0] == '#') return;
    while (true) {
        char c = 0;
        try {
            c = s.front();
            s = s.substr(1, s.size() - 1);
        }
        catch (std::out_of_range &e) {}
        switch (part) {
            case Name:
                if (c == ' ') {
                    part = Arguments;
                } else if (c == ';') {
                    part = Finished;
                } else name += c;
                goto out_of_switch;
            case Arguments:
                if (!interpret_next) {
                    buf += c;
                    started = true;
                    interpret_next = true;
                } else if (c == ',') {
                    args.emplace_back(buf);
                    buf = "";
                    started = false;
                } else if (c == ';') {
                    args.emplace_back(buf);
                    part = Finished;
                    //lines.pop_back();
                } else if (c == ' ' && !started);
                else if (c == '\\') {
                    interpret_next = false;
                }
                else {
                    buf += c;
                    started = true;
                }
                goto out_of_switch;
        }
        out_of_switch:
        i++;
        if (part == Finished) break;
        l = c;
    }

    if (name == "func") {
        str type = args.front();
        args.pop_front();
        str name = args.front();
        args.pop_front();
        str f_args[32];
        int f_arg_count = 0;
        for (auto& str : args) {
            f_args[f_arg_count] = str;
            f_arg_count++;
        }
        *global.output << generator->generate_function_start(type, name, f_args, f_arg_count);
        bool unimpl = false;
        for(auto& a : stack)
            unimpl = unimpl || a == "interface";
        if(!unimpl)
            stack.emplace_back("func");
    } else if (name == "main") {
        *global.output << generator->generate_function_start("int",
                                                             "main",
                                                             new str[2]{"int argc", "char** argv"},
                                                             2);
        stack.emplace_back("func");
    } else if (name == "end") {
        str type = stack.back();
        stack.pop_back();
        if (type == "func")
            *global.output << generator->generate_function_end();
        else if (type == "uses")
            *global.output << "#include <simondev.h>" << std::endl << std::endl;
        else if (type == "class")
            *global.output << generator->generate_class_end();
        else if (type == "interface")
            *global.output << generator->generate_interface_end();
        else if (type == "struct")
            *global.output << generator->generate_struct_end();
        else if (type == "if")
            *global.output << generator->generate_if_end();
        else if (type == "case")
            *global.output << generator->generate_switch_break();
        else if (type == "switch")
            *global.output << generator->generate_switch_end();
        else if (type == "for")
            *global.output << generator->generate_for_end();
        else if (type == "while")
            *global.output << generator->generate_while_end();
        else if (type == "postwhile")
            *global.output << generator->generate_postwhile_end(args.front());
        else if (type == "module" && global.language == CPP)
            *global.output << "#endif" << std::endl;
    } else if (name == "return") {
        *global.output << generator->generate_function_return(args.front());
        args.pop_front();
        *global.output << generator->generate_line_end();
    } else if (name == "newvar") {
        str type = args.front();
        args.pop_front();
        str name_ = args.front();
        args.pop_front();
        str value;
        if (!args.empty()) value = args.front();
        *global.output << generator->generate_variable_define(type, name_, value);
        *global.output << generator->generate_line_end();
    } else if (name == "newptr") {
        str type = args.front();
        args.pop_front();
        str name_ = args.front();
        args.pop_front();

        *global.output << generator->generate_variable_define("static " + type + '*',
                                                              name_,
                                                              "(" + type + "*)malloc(sizeof(" + type + "))");
        *global.output << generator->generate_line_end();
    } else if (name == "setvar") {
        str name_ = args.front();
        args.pop_front();
        str value = args.front();
        args.pop_front();
        *global.output << generator->generate_variable_set(name_, value);
        *global.output << generator->generate_line_end();
    } else if (name == "setptr") {
        str name_ = args.front();
        args.pop_front();
        str value = args.front();
        args.pop_front();
        *global.output << generator->generate_variable_set('*' + name_, value);
        *global.output << generator->generate_line_end();
    } else if (name == "uses") {
        str module = args.front();
        args.pop_front();
        str replaced = replace_all(module, '.', '$');
        *global.output << "#define MODULE_" << replaced << std::endl;
        if(stack.empty())
            stack.emplace_back("uses");
    } else if (name == "class") {
        str name_ = args.front();
        args.pop_front();
        std::list<str> bases;
        for (auto &a : args) {
            bases.emplace_back(a);
        }
        str basesv[args.size()];
        int j = 0;
        for (auto &a : bases) {
            basesv[j] = a;
            j++;
        }
        *global.output << generator->generate_class_start(name_, basesv, bases.size());
        stack.emplace_back("class");
    } else if (name == "interface") {
        *global.output << generator->generate_interface_start(args.front());
        args.pop_front();
        stack.emplace_back("interface");
    } else if (name == "struct") {
        *global.output << generator->generate_struct_start(args.front());
        args.pop_front();
        stack.emplace_back("struct");
    } else if (name == "enum") {
        *global.output << generator->generate_enum_start(args.front());
        args.pop_front();
        while (!args.empty()) {
            *global.output << generator->generate_enum_entry(args.front());
            args.pop_front();
        }
        *global.output << generator->generate_enum_end();
    } else if (name == "visibility") {
        *global.output << generator->generate_class_visibility(args.front());
        args.pop_front();
    } else if (name == "include") {
        *global.output << generator->generate_include(args.front(), false);
    } else if (name == "library") {
        libraries.emplace_back(args.front());
        *global.output << generator->generate_include(args.front(), true);
    } else if (name == "assert" && global.is_test) {
        str condition = args.front();
        args.pop_front();
        str name_ = args.front();
        args.pop_front();
        *global.output << generator->generate_assert_test(condition, name_);
    } else if (name == "if") {
        str condition = args.front();
        *global.output << generator->generate_if(condition);
        stack.emplace_back("if");
    } else if (name == "switch") {
        *global.output << generator->generate_switch(args.front());
        stack.emplace_back("switch");
    } else if (name == "case") {
        *global.output << generator->generate_switch_case(args.front());
        stack.emplace_back("case");
    } else if (name == "for") {
        str varname = args.front();
        args.pop_front();
        int from = std::stoi(args.front(), nullptr, 0);
        args.pop_front();
        int to = std::stoi(args.front(), nullptr, 0);
        *global.output << generator->generate_for_start(varname, from, to);
        stack.emplace_back("for");
    } else if (name == "while") {
        *global.output << generator->generate_while_start(args.front());
        stack.emplace_back("while");
    } else if (name == "postwhile") {
        *global.output << generator->generate_postwhile_start();
        stack.emplace_back("postwhile");
    } else if (name == "module" && global.language == Language::CPP) {
        str modName = args.front();
        str modDef = "MODULE_" + modName;
        for (int j = 0; j < modDef.size(); j++) {
            if (modDef[j] == '.' || modDef[j] == '@')
                modDef[j] = '$';
        }
        *global.output << "#ifdef " << modDef << std::endl;
        stack.emplace_back("module");
    } else if (name == "test" && global.language == Language::CPP && global.is_test) {
        *global.output << generator->generate_function_start("bool", args.front() + "_test", nullptr, 0);
        test_names = static_cast<str **>(reallocarray(test_names, test_index + 1, sizeof(str *)));
        test_names[test_index] = new str(args.front() + "_test");
        test_index++;
        stack.emplace_back("func");
    } else if (name == "run_tests" && global.language == Language::CPP && global.is_test) {
        bool in_func = false;
        for(auto& a : stack)
            in_func = in_func || a == "func";
        if(!in_func)
            *global.output << generator->generate_function_start("int", "main", nullptr, 0);
        for (int j = 0; j < test_index; ++j) {
            *global.output <<
                generator->generate_if("!" + *test_names[j] + "()") <<
                    generator->generate_function_call("eprintln", new str[1]{"\"! " + test_names[j]->substr(0, test_names[j]->length()-5) + "\""}, 1) <<
                    generator->generate_line_end() <<
                generator->generate_if_end();
        }
        if(!in_func)
            *global.output << generator->generate_function_end();
    } else if (name == ".include") {
        auto input = std::ifstream(args.front());
        auto linenum = global.line;
        auto filename = global.filename;
        global.line = 0;
        global.filename = args.front();
        while (!!input) ::parse(&input);
        global.line = linenum;
        global.filename = filename;
    } else {
        str argsv[args.size()];
        int j = 0;
        for (auto &a : args) {
            argsv[j] = a;
            j++;
        }
        *global.output << generator->generate_function_call(name, argsv, args.size());
        *global.output << generator->generate_line_end();
    }
    std::cout.flush();
    std::cerr.flush();
}

str list_to_str(std::list<std::string> list, const char* delim) {
    if(list.empty()) return "<global>";
    int size = list.size();
    str a[size];
    for (int i = 0; i < size; ++i) {
        a[i] = list.front();
        list.pop_front();
    }
    str r;
    for(int i = size-1; i >= 0; i--) {
        r += a[i] + (i == 0 ? "" : delim);
    }
    return r;
}

str replace_all(str &basicString, char i, char i1) {
    long loc;
    loc = basicString.find(i);
    while (loc < basicString.size()) {
        basicString.replace(loc, 1, str() + i1);
        loc = basicString.find(i);
    }
    return basicString;
}
