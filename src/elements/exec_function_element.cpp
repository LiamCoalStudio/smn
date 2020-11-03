//
// Created by liam on 11/1/20.
//

#include "exec_function_element.h"
#include "../functions/functions.h"

bool ExecFunctionElement::matches(const std::string &line)
{
    name = line;
    return find_func(line) != nullptr;
}

LanguageElement::Error ExecFunctionElement::execute(std::list<str> args, int64 len, global_t *global)
{
    find_func(name)->exec();
    return None;
}
