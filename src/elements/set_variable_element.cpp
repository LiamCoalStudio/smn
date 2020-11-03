#include "set_variable_element.h"
#include "../simon.h"
#include "../str.h"

bool SetVariableElement::matches(const std::string &line)
{
    return line == "set";
}

LanguageElement::Error SetVariableElement::execute(std::list<str> args, int64 len, global_t*)
{
    if(len < 2) { argerr; }
    str var_name = args.front(); args.pop_front();
    str var_value = args.front();
    if(var_name.starts_with('@'))
    {
        print_warning("unable to set variables with name starting with @");
        return Warn;
    }
    global.variable_context[var_name] =  var_value;
    return None;
}
