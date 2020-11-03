#ifndef SIMON_SET_VARIABLE_ELEMENT_H
#define SIMON_SET_VARIABLE_ELEMENT_H

#include "../language_element.h"

class SetVariableElement : public LanguageElement
{
public:
    bool matches(const std::string &line) override;

    Error execute(std::list<str> args, int64 len, global_t* global) override;
};


#endif //SIMON_SET_VARIABLE_ELEMENT_H
