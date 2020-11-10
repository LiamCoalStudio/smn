#include "simon.h"
#include <iostream>
#include <generator.h>

bool comment_mode;

void parse_line(str str);

str current_function;

/**
 * Parses a smn file, and does stuff with it.
 */
void parse(std::istream *input)
{
    current_function = "";

    str obj;
    *input >> obj;
    if(obj.empty()) return;

    // Comments
    if(obj == "#[" && !comment_mode) comment_mode = true;
    if(obj == "]#" && comment_mode) comment_mode = false;
    if(obj == "#[" || obj == "]#" || (comment_mode && obj != "]#")) return;

    bool body = obj[obj.size() - 1] == ':';
    bool is_directive = obj[0] == '/';

    str match = ";";
    if(body) match = ":";
    if(is_directive) match = "/#";

    while(!obj.ends_with(match) && !input->eof())
    {
        obj += ' ';
        str add;
        *input >> add;
        obj += add;
    }

    parse_line(obj);

    // Flush outputs
    std::cout.flush();
    std::cerr.flush();
}

enum ParsePart
{Name, Arguments, Body, Finished};

void parse_line(str s)
{
#if TESTING == true
    print_info(s);
#endif

    auto generator = for_language(global.language);

    if(s == "/language: cpp/#")
    {
        global.language = Language::CPP;
    }

    if(s.substr(0, 6) == "/cpp/ ")
    {
        *global.output << generator->transform(CPP, s.substr(6, s.size() - 8)) << std::endl;
    }

    if(s.substr(0, 4) == "/c/ ")
    {
        *global.output << generator->transform(C, s.substr(4, s.size() - 8)) << std::endl;
    }

    if(s.substr(0, 6) == "/asm/ ")
    {
        *global.output << generator->transform(ASSEMBLY, s.substr(6, s.size() - 8)) << std::endl;
    }

    global.output->flush();

    if(s[0] == '/') return;

    std::list<str> args, lines;
    str name;

    str buf;
    ParsePart part = Name;
    bool started;
//    LanguageElement* element;
    char l = '\x00';

    int i = 0;
    while(true)
    {
        char c = 0;
        try {
            c = s.front();
            s = s.substr(1, s.size() - 1);
        }
        catch (std::out_of_range& e)
        {  }
        switch (part)
        {
            case Name:
                if(c == ' ')
                {
//                    element = get(name);
                    part = Arguments;
                }
                else if(c == ';')
                {
//                    element = get(name);
                    part = Finished;
                }
                else name += c;

                goto out_of_switch;

            case Arguments:
                if(c == ',')
                {
                    args.emplace_back(buf);
                    buf = "";
                    started = false;
                }
                else if(c == ';')
                {
                    args.emplace_back(buf);
                    part = Finished;
                    //lines.pop_back();
                }
                else if(c == ' ' && !started);
                else
                {
                    buf += c;
                    started = true;
                }

                goto out_of_switch;
        }
        out_of_switch:
            i++;
            if(part == Finished) break;
//            if(element == nullptr) return;
            l = c;
    }

//    if(element == nullptr)
//    {
//        print_error("invalid -> " << name);
//        return;
//    }

    if(name == "func")
    {
        // This is a function declaration.
        str type = args.front(); args.pop_front();
        str name = args.front(); args.pop_front();
        current_function = name;
        *global.output << generator->generate_function_start(type, name, nullptr, 0);
    }
    else if(name == "end")
    {
        str type = args.front(); args.pop_front();
        if(type == "func")
            *global.output << generator->generate_function_end();
    }
    else if(name == "return")
    {
        *global.output << generator->generate_function_return(args.front()); args.pop_front();
        *global.output << generator->generate_line_end();
    }
    else
    {
        str argsv[args.size()];
        int j = 0;
        for(auto& a : args)
        {
            argsv[j] = a;
            j++;
        }
        *global.output << generator->generate_function_call(name, argsv, args.size());
        *global.output << generator->generate_line_end();
    }
    global.output->flush();

    std::cout.flush();
    std::cerr.flush();
}
