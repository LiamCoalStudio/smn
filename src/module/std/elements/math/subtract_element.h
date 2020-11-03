//
// Created by liam on 11/3/20.
//

#ifndef SIMON_SUBTRACT_ELEMENT_H
#define SIMON_SUBTRACT_ELEMENT_H

#include "../../../../language_element.h"

class SubtractElement : public LanguageElement
{
public:
    bool matches(const std::string &line) override;

    Error execute(std::list<str> args, int64 len, global_t *global) override;
};


#endif //SIMON_SUBTRACT_ELEMENT_H
