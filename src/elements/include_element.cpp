//
// Created by liam on 11/1/20.
//

#include <fstream>
#include "include_element.h"
#include "../str.h"

extern void parse(std::istream *input);

bool IncludeElement::matches(const std::string &line)
{
    return line == ".include";
}

LanguageElement::Error IncludeElement::execute(std::list<str> args, int64 len, global_t *global)
{
    for (int i = 0; i < len; ++i)
    {
        str path = string_from(args.front()); args.pop_front();
        std::ifstream in(path);
        while(!!in) parse(&in);
    }
    return None;
}
