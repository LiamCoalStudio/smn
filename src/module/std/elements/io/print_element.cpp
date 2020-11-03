#include "print_element.h"
#include "../../str.h"
#include <iostream>

bool PrintElement::matches(const std::string &line)
{
    return line == "print";
}

LanguageElement::Error PrintElement::execute(std::list<str> args, int64 len, global_t* glbl)
{
    if(len < 1) { argerr; }
    str st = args.front();
    str s = string_from(st, glbl);
    std::cout << s;
    return None;
}
