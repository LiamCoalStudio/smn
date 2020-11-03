#include "function_element.h"
#include "../functions/functions.h"

bool FunctionElement::matches(const std::string &line)
{
    name = line.substr(0, line.size() - 1);
    return line.ends_with(':');
}

LanguageElement::Error FunctionElement::execute(std::list<str> args, int64 len, global_t *global, const std::list<str> &body)
{
    static auto* f = new Function;
    for(auto& a : body) f->add(a);
    f->lock();
    create_func(name, f);

    return None;
}

bool FunctionElement::has_body()
{
    return true;
}
