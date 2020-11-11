#include "generator.h"

str CPP_Generator::generate_function_call(const str &name, str *args, long arg_count)
{
    str out = indent();
    out += name;
    out += '(';
    for (int i = 0; i < arg_count; ++i)
    {
        out += args[i];
        if(i < arg_count - 1)
            out += ", ";
    }
    out += ")";
    return out;
}
str CPP_Generator::generate_function_start(const str& type, const str &name, str *args, long arg_count)
{
    str out = (class_info._unimpl ? "" : "\n") + indent();
    if(class_info._class)
        out += "virtual ";
    out += type + ' ';
    out += generate_function_call(name, args, arg_count);
    if(class_info._unimpl)
        out += " = 0;\n";
    else
    {
        out += " {\n";
        _indent++;
    }
    return out;
}
str CPP_Generator::generate_function_end()
{
    _indent--;
    return indent() + (class_info._unimpl ? ";\n" : "}\n");
}

str CPP_Generator::generate_variable_define(const str &type, const str &name, const str &value)
{
    str out = indent();
    out += type + ' ' + name;
    if(!value.empty())
    {
        out += " = " + value;
    }
    return out;
}
str CPP_Generator::generate_variable_set(const str &name, const str &value)
{
    str out = indent();
    out += name;
    out += " = " + value;
    return out;
}

str CPP_Generator::generate_line_end()
{ return ";\n"; }

str CPP_Generator::generate_if(const str &condition)
{
    str out = indent() + "if(" + condition + ") {\n";
    _indent++;
    return out;
}
str CPP_Generator::generate_if_end()
{
    _indent--;
    return indent() + "}\n";
}

str CPP_Generator::generate_switch(const str &value)
{
    return indent() + "switch(" + value + ") {\n";
}
str CPP_Generator::generate_switch_case(const str &value)
{
    str out = indent() + "case " + value + ":\n";
    _indent++;
    return out;
}
str CPP_Generator::generate_switch_break()
{
    str out = indent() + "break";
    _indent--;
    return out;
}
str CPP_Generator::generate_switch_end()
{
    return indent() + "}\n";
}

str CPP_Generator::generate_class_visibility(const str &vis)
{
    return indent() + vis + ":\n";
}
str CPP_Generator::generate_class_start(const str &name, str *bases, long count)
{
    str out = "\n" + indent() + "class " + name;
    if(count > 0)
    {
        out += "\n: ";
        for (int i = 0; i < count; ++i)
        {
            out += "public ";
            out += bases[i];
            if(i < count - 1)
                out += ", ";
        }
    }
    out += " {\n";
    class_info._class = true;
    _indent++;
    return out;
}
str CPP_Generator::generate_class_end()
{
    class_info = {false,
                  false};
    _indent--;
    return indent() + "};\n";
}

str CPP_Generator::generate_interface_start(const str &name)
{
    class_info = {true,
                  true};
    str out = indent() + "class " + name + " {\n";
    _indent++;
    return out;
}
str CPP_Generator::generate_interface_end()
{
    class_info = {false,
                  false};
    _indent--;
    return indent() + "};";
}

str CPP_Generator::generate_struct_start(const str &name)
{
    str out = generate_class_start(name, nullptr, 0);
    return out.replace(out.find("class"), 5, "struct");
}
str CPP_Generator::generate_struct_end()
{
    return generate_class_end();
}

str CPP_Generator::generate_enum_start(const str &name)
{
    str out = indent() + "enum " + name + " {\n";
    _indent++;
    return out;
}
str CPP_Generator::generate_enum_entry(const str &entry)
{
    return indent() + entry + ",\n";
}
str CPP_Generator::generate_enum_end()
{
    _indent--;
    return indent() + "};\n";
}

str CPP_Generator::transform(Language other, const str &string)
{
    switch (other)
    {
        case CPP:
        case C:
            return string;
        case ASSEMBLY:
            return "asm(\"" + string + "\");\n";
        default:
            return "/*\n * An incompatible language was used here:\n * > " + string + "\n */";
    }
}

str CPP_Generator::generate_function_return(const str &value)
{
    return indent() + "return " + value;
}

void CPP_Generator::compile(str input_file, str output_file)
{
    if(system(("g++ -x c++ -o " + output_file + " " + input_file + " -lsimondevcxx").c_str()) > 0)
        exit(1);
}

str CPP_Generator::name()
{ return "cxx"; }

str CPP_Generator::generate_assert_test(str c, str name)
{
    str out;
    out += generate_if("!(" + c + ")");
    out += generate_function_call("println", new str[1] {"\"Test failed: \"" + name}, 1);
    out += generate_line_end();
    out += generate_function_return("1");
    out += generate_line_end();
    out += generate_if_end();
    return out;
}

