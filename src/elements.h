#ifndef SIMON_ELEMENTS_H
#define SIMON_ELEMENTS_H

#include "language_element.h"
#include "elements/set_variable_element.h"
#include "simon.h"
#include <list>

extern std::list<LanguageElement*> all_elements;

LanguageElement* get(const str& string);

#endif //SIMON_ELEMENTS_H
