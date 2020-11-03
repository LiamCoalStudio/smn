#include "elements.h"
#include <list>

std::list<LanguageElement*> all_elements;

/**
 * Gets an element by match.
 * @param s Line to match.
 * @return Pointer to a @c LanguageElement, or
 * @c nullptr if it doesn't exist
 */
LanguageElement* get(const str& s)
{
    for(auto & element : all_elements)
    {
        if(element->matches(s)) return element;
    }
    return nullptr;
}
