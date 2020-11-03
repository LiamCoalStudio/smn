#include "functions.h"
#include <unordered_map>

std::unordered_map<std::string, Function*> funcs;

Function* find_func(const std::string& name)
{
    if(!funcs.contains(name))
        return nullptr;
    else
        return funcs[name];
}

void create_func(const std::string& name, Function* f)
{
    funcs[name] = f;
}

void delete_func(const std::string& name)
{
    funcs[name] = nullptr;
}
