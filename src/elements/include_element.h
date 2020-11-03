//
// Created by liam on 11/1/20.
//

#ifndef SIMON_INCLUDE_ELEMENT_H
#define SIMON_INCLUDE_ELEMENT_H

#include "../language_element.h"

class IncludeElement : public LanguageElement
{
public:
    bool matches(const std::string &line) override;

    Error execute(std::list<str> args, int64 len, global_t *global) override;
};


#endif //SIMON_INCLUDE_ELEMENT_H
