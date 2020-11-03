#ifndef SIMON_USE_H
#define SIMON_USE_H

#include "str.h"
#include "elements.h"
#include <exception>

class UseNotFound : public std::exception {};

extern std::list<str> used;

template<typename T>
struct array
{
    T* ptr;
    long size;
};

extern void use(const str& name, LanguageElement* elements[]);
extern void use(const str& name);

#endif //SIMON_USE_H
