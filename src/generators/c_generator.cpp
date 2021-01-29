#include "generator.h"

#define class_error "this type of class is not supported"

str C_Generator::generate_function_call(const str &name, str *args, long arg_count) {
    str out = indent();
    str newname = name;
    for (auto &c : newname) {
        if (c == '.')
            c = '$';
    }
    out += newname;
    out += '(';
    for (int i = 0; i < arg_count; ++i) {
        out += args[i];
        if (i < arg_count - 1)
            out += ", ";
    }
    out += ")";
    return out;
}

str C_Generator::generate_function_start(const str &type, const str &name, str *args, long arg_count) {
    str out = "\n" + indent();
    out += type + ' ';
    out += generate_function_call(name, args, arg_count);
    out += " {\n";
    _indent++;
    return out;
}

str C_Generator::generate_function_end() {
    _indent--;
    return indent() + "}\n";
}

str C_Generator::generate_function_return(const str &value) {
    return indent() + "return(" + value + ");";
}

str C_Generator::generate_variable_define(const str &type, const str &name, const str &value) {
    str out = indent();
    out += type + ' ' + name;
    if (!value.empty()) {
        out += " = " + value;
    }
    return out;
}

str C_Generator::generate_variable_set(const str &name, const str &value) {
    str out = indent();
    out += name;
    out += " = " + value;
    return out;
}

str C_Generator::generate_line_end() { return ";\n"; }

str C_Generator::generate_if(const str &condition) {
    str out = indent() + "if(" + condition + ") {\n";
    _indent++;
    return out;
}

str C_Generator::generate_if_end() {
    _indent--;
    return indent() + "}\n";
}

str C_Generator::generate_switch(const str &value) {
    return indent() + "switch(" + value + ") {\n";
}

str C_Generator::generate_switch_case(const str &value) {
    str out = indent() + "case " + value + ":\n";
    _indent++;
    return out;
}

str C_Generator::generate_switch_break() {
    str out = indent() + "break;\n";
    _indent--;
    return out;
}

str C_Generator::generate_switch_end() {
    return indent() + "}\n";
}

str C_Generator::generate_class_visibility(const str &vis) unsupported(class_error)

str C_Generator::generate_class_start(const str &name, str *bases, long count) {
    if (count > 0) unsupported("cannot have base classes")
    return generate_struct_start(name);
}

str C_Generator::generate_class_end() { return generate_struct_end(); }

str C_Generator::generate_interface_start(const str &name) unsupported(class_error)

str C_Generator::generate_interface_end() unsupported(class_error)

str C_Generator::generate_struct_start(const str &name) {
    str out = indent() + "struct " + name + " {\n";
    _indent++;
    return out;
}

str C_Generator::generate_struct_end() {
    _indent--;
    return indent() + "};\n";
}

str C_Generator::generate_enum_start(const str &name) {
    str out = indent() + "enum " + name + " {\n";
    _indent++;
    return out;
}

str C_Generator::generate_enum_entry(const str &entry) {
    return indent() + entry + ",\n";
}

str C_Generator::generate_enum_end() {
    _indent--;
    return indent() + "}\n";
}

str C_Generator::transform(Language other, const str &string) {
    switch (other) {
        case C:
            return string;
        case ASSEMBLY:
            return "asm(\"" + string + "\");\n";
        default:
            print_error(global.filename + " at line " + current_line + ": incompatible language used");
            exit(1);
    }
}

void C_Generator::compile(str input_file, str output_file) {
    if (system(("gcc -x c -o " + output_file + " " + input_file + " -lsimondevc").c_str()) > 0)
        exit(1);
}

str C_Generator::generate_assert_test(str c, str name) {
    str out;
    out += generate_if("!(" + c + ")");
    out += generate_function_call("println", new str[1]{"\"Test failed: \"" + name}, 1);
    out += generate_line_end();
    out += generate_function_return("1");
    out += generate_line_end();
    out += generate_if_end();
    return out;
}

str C_Generator::generate_comment(str text, bool indent_) {
    return (indent_ ? indent() : "") + "// " + text + "\n";
}

str C_Generator::generate_include(str file, bool library) {
    return "#include \"" + file + (library ? ".h" : "") + "\"\n";
}

str C_Generator::comment_str() {
    return indent() + "// # ";
}

str C_Generator::name() {
    return "c";
}

str C_Generator::generate_for_start(const str &v, int f, int t) {
    if(t < f) {
        print_error(global.filename + " at line " + current_line + ": [for] <to> (" + std::to_string(t) + ") cannot be less than <from> (" + std::to_string(f) + ")");
        exit(1);
    }
    if(t == f) {
        print_warning(global.filename + " at line " + current_line + ": dead code");
    }
    str s = indent() + "for(int " + v + " = " + std::to_string(f) + "; " + v + " < " + std::to_string(t) + "; " + v +
            "++) {\n";
    _indent++;
    return s;
}

str C_Generator::generate_for_end() {
    _indent--;
    return indent() + "}\n";
}

str C_Generator::generate_while_start(const str &condition) {
    if(condition == "true") {
        print_warning(global.filename + " at line " + current_line + ": infinite loop");
    }
    if(condition == "false") {
        print_warning(global.filename + " at line " + current_line + ": dead code");
    }
    str s = indent() + "while(" + condition + ") {\n";
    _indent++;
    return s;
}

str C_Generator::generate_while_end() {
    _indent--;
    return indent() + "}\n";
}

str C_Generator::generate_postwhile_start() {
    str s = indent() + "do {\n";
    _indent++;
    return s;
}

str C_Generator::generate_postwhile_end(const str &condition) {
    if(condition == "true") {
        print_warning(global.filename + " at line " + current_line + ": infinite loop");
    }
    if(condition == "false") {
        print_warning(global.filename + " at line " + current_line + ": single run postwhile (consider removing postwhile loop here)");
    }
    _indent--;
    return indent() + "} while(" + condition + ");\n";
}
