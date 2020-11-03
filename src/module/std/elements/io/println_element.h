#ifndef SIMON_PRINTLN_ELEMENT_H
#define SIMON_PRINTLN_ELEMENT_H

#include "../../../../language_element.h"

class PrintlnElement : public LanguageElement
{
public:
    bool matches(const std::string &line) override;
    Error execute(std::list<str> args, int64 len, global_t* global) override;
};


#endif //SIMON_PRINTLN_ELEMENT_H
