#ifndef SMN_GENERATOR_H
#define SMN_GENERATOR_H

#include <simon.h>

#define unsupported(str) \
{ throw UnsupportedFeatureException("classes not supported in C"); }

class UnsupportedFeatureException : public std::exception {
private:
    str _what;
public:
    explicit UnsupportedFeatureException(str what);
    const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
};

class Generator {
public:
    // Functions
    virtual str generate_function_call(const str &name, str *args, long arg_count) = 0;
    virtual str generate_function_start(const str &type, const str &name, str *args, long arg_count) = 0;
    virtual str generate_function_end() = 0;
    virtual str generate_function_return(const str &value) = 0;
    // Variables
    virtual str generate_variable_define(const str &type, const str &name, const str &value) = 0;
    virtual str generate_variable_set(const str &name, const str &value) = 0;
    // `if`
    virtual str generate_if(const str &condition) = 0;
    virtual str generate_if_end() = 0;
    // `switch`
    virtual str generate_switch(const str &value) = 0;
    virtual str generate_switch_case(const str &value) = 0;
    virtual str generate_switch_break() = 0;
    virtual str generate_switch_end() = 0;
    // `class`
    virtual str generate_class_visibility(const str &vis) = 0;
    virtual str generate_class_start(const str &name, str *bases, long count) = 0;
    virtual str generate_class_end() = 0;
    // `interface`
    virtual str generate_interface_start(const str &name) = 0;
    virtual str generate_interface_end() = 0;
    // `struct`
    virtual str generate_struct_start(const str &name) = 0;
    virtual str generate_struct_end() = 0;
    // `enum`
    virtual str generate_enum_start(const str &name) = 0;
    virtual str generate_enum_entry(const str &entry) = 0;
    virtual str generate_enum_end() = 0;
    // `for`
    virtual str generate_for_start(const str &variable_name, int from, int to) = 0;
    virtual str generate_for_end() = 0;
    // `while`
    virtual str generate_while_start(const str &condition) = 0;
    virtual str generate_while_end() = 0;
    // `postwhile`
    virtual str generate_postwhile_start() = 0;
    virtual str generate_postwhile_end(const str &condition) = 0;
    // Magic
    virtual str transform(Language other, const str &string) = 0;
    virtual void compile(str input_file, str output_file) = 0;
    // Everything else
    virtual str generate_comment(str text, bool indent) = 0;
    virtual str generate_include(str file, bool library) = 0;
    virtual str generate_assert_test(str condtition, str name) = 0;
    virtual str generate_line_end() = 0;
    virtual str comment_str() = 0;
    virtual str name() = 0;
};

class CPP_Generator : public Generator {
public:
    str generate_function_call(const str &name, str *args, long arg_count) override;
    str generate_function_start(const str &type, const str &name, str *args, long arg_count) override;
    str generate_function_end() override;
    str generate_variable_define(const str &type, const str &name, const str &value) override;
    str generate_variable_set(const str &name, const str &value) override;
    str generate_line_end() override;
    str generate_if(const str &condition) override;
    str generate_if_end() override;
    str generate_switch(const str &value) override;
    str generate_enum_entry(const str &entry) override;
    str generate_switch_case(const str &value) override;
    str generate_switch_break() override;
    str generate_switch_end() override;
    str generate_class_visibility(const str &vis) override;
    str generate_class_start(const str &name, str *bases, long count) override;
    str generate_class_end() override;
    str generate_interface_start(const str &name) override;
    str generate_interface_end() override;
    str generate_struct_start(const str &name) override;
    str generate_struct_end() override;
    str generate_enum_start(const str &name) override;
    str generate_function_return(const str &value) override;
    str generate_enum_end() override;
    str generate_include(str file, bool library) override;
    str generate_comment(str text, bool indent) override;
    str transform(Language other, const str &string) override;
    str name() override;
    str generate_assert_test(str condtition, str name) override;
    str comment_str() override;
    void compile(str input_file, str output_file) override;
    str generate_for_start(const str &v, int f, int t) override;
    str generate_for_end() override;
    str generate_while_start(const str &condition) override;
    str generate_while_end() override;
    str generate_postwhile_start() override;
    str generate_postwhile_end(const str &condition) override;
};

class C_Generator : public Generator {
public:
    str generate_function_call(const str &name, str *args, long arg_count) override;
    str generate_function_start(const str &type, const str &name, str *args, long arg_count) override;
    str generate_function_end() override;
    str generate_function_return(const str &value) override;
    str generate_variable_define(const str &type, const str &name, const str &value) override;
    str generate_variable_set(const str &name, const str &value) override;
    str generate_line_end() override;
    str generate_if(const str &condition) override;
    str generate_if_end() override;
    str generate_switch(const str &value) override;
    str generate_switch_case(const str &value) override;
    str generate_switch_break() override;
    str generate_switch_end() override;
    str generate_class_visibility(const str &vis) override;
    str generate_class_start(const str &name, str *bases, long count) override;
    str generate_class_end() override;
    str generate_interface_start(const str &name) override;
    str generate_interface_end() override;
    str generate_struct_start(const str &name) override;
    str generate_struct_end() override;
    str generate_enum_start(const str &name) override;
    str generate_enum_entry(const str &entry) override;
    str generate_enum_end() override;
    str generate_comment(str text, bool indent) override;
    str generate_include(str file, bool library) override;
    str transform(Language other, const str &string) override;
    str name() override;
    str generate_assert_test(str condition, str name) override;
    str comment_str() override;
    void compile(str input_file, str output_file) override;
    str generate_for_start(const str &v, int f, int t) override;
    str generate_for_end() override;
    str generate_while_start(const str &condition) override;
    str generate_while_end() override;
    str generate_postwhile_start() override;
    str generate_postwhile_end(const str &condition) override;
};

inline Generator *for_language(Language l) {
    switch (l) {
        case CPP:
            return new CPP_Generator;
        case C:
            return new C_Generator;
        case ASSEMBLY:
            break;
    }
    return nullptr;
}

extern int _indent;
extern str indent();
struct class_info_t {
    bool _class;
    bool _unimpl;
};
extern class_info_t class_info;
#endif //SMN_GENERATOR_H
