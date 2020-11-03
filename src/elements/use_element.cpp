#include "use_element.h"
#include "../use.h"
#include "../module.h"

bool UseElement::matches(const std::string &line)
{
    return line == "use";
}

LanguageElement::Error UseElement::execute(std::list<str> args, int64 len, global_t*)
{
    if(len < 1) { argerr; }
    str name = args.front(); args.pop_front();
    if(len == 2)
    {
        str mod = name;
        name = args.front();
        use(mod, name);
    }
    else
        use(name);
    return None;
}
