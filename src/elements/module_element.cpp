#include "module_element.h"
#include "../simon.h"
#include "../module.h"

bool ModuleElement::matches(const std::string &line)
{
    return line == "module";
}

LanguageElement::Error ModuleElement::execute(std::list<str> args, int64 len, global_t*)
{
    if(len < 1) { argerr; }
    str name = args.front();
    load(name);
    return None;
}
