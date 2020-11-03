//
// Created by liam on 11/3/20.
//

#include "add_element.h"
#include "../../str.h"

bool AddElement::matches(const std::string &line)
{
    return line == "add";
}

LanguageElement::Error AddElement::execute(std::list<str> args, int64 len, global_t *global)
{
    if(len < 3) { argerr; }
    str out = args.front(); args.pop_front();
    double result = 0.0;

    while(!args.empty())
    {
        result += double_from(args.front(), global); args.pop_front();
    }

    global->variable_context[out] = std::to_string(result);
    return None;
}
