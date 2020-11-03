#include "println_element.h"
#include "../../str.h"
#include <iostream>

bool PrintlnElement::matches(const std::string &line)
{
    return line == "println";
}

LanguageElement::Error PrintlnElement::execute(std::list<str> args, int64 len, global_t* glbl)
{
    if(len < 1) { argerr; }
    str st = args.front();
    str s = string_from(st, glbl);
    std::cout << s << std::endl;
    return None;
}
