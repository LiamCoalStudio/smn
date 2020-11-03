#include "../../str.h"

str string_from(const str& str, global_t* glbl)
{
    if (str.starts_with('"') && str.ends_with('"'))
        return str.substr(1, str.size() - 2);
    else if(glbl->variable_context.contains(str))
        return string_from(glbl->variable_context[str], glbl);
    else
        return str;
}

double double_from(const str& str, global_t* glbl)
{
    if(glbl->variable_context.contains(str))
        return double_from(glbl->variable_context[str], glbl);
    else
        return strtod(str.c_str(), (char **) (str.c_str() + str.size()));
}
