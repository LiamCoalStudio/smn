//
// Created by liam on 11/1/20.
//

#include "exec_function_element.h"
#include <functions.h>
#include <generator.h>

bool ExecFunctionElement::matches(const std::string &line)
{
    name = line;
    return true;
}

LanguageElement::Error ExecFunctionElement::execute(std::list<str> args, int64 len, global_t *global)
{
    auto gen = for_language(global->language);

    str strs[len];
    for (int i = 0; i < len; ++i)
    {
        strs[i] = args.front(); args.pop_front();
    }

    *global->output << gen->generate_function_call(name, strs, len);
    *global->output << gen->generate_line_end();
    global->output->flush();
    return None;
}
