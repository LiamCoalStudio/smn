#include "use.h"
#include "elements/module_element.h"
#include "elements/function_element.h"
#include <algorithm>
#include <exec_function_element.h>

/// Elements part of `use core`
LanguageElement* core[] = {
    new SetVariableElement,
    new ModuleElement,
    new FunctionElement
};

std::list<str> used;
std::unordered_map<str, std::list<LanguageElement*>> usable;

std::list<LanguageElement*> to_list(LanguageElement* a[], int size)
{
    std::list<LanguageElement*> r;
    for (int i = 0; i < size; i++)
    {
        r.emplace_back(a[i]);
    }
    return r;
}

/**
 * Initializes `use` by adding core to the usable map.
 */
void use_init()
{
    usable["core"] = to_list(core, 3);
}

/**
 * Adds all @c elements to @c all_elements, allowing
 * them to be parsed.
 * @param name Name of the usable.
 * @param elements Elements of the usable.
 */
void use(const str& name, std::list<LanguageElement*> elements)
{
    all_elements.pop_back();
    if(std::find(used.begin(), used.end(), name) != used.end()) return;
    for(auto& a : elements)
    {
        all_elements.emplace_back(a);
    }
    all_elements.emplace_back(new ExecFunctionElement);
    used.emplace_back(name);
}

/**
 * Adds all @c elements to @c all_elements, allowing
 * them to be parsed.
 * @param name Name of the usable.
 * @throws UseNotFound is thrown if @c name doesn't exist
 */
void use(const str& name)
{
    if(usable.contains(name))
        use(name, usable[name]);
    else
        throw UseNotFound();
}
