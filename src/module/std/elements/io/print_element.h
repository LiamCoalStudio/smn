#ifndef SIMON_PRINT_ELEMENT_H
#define SIMON_PRINT_ELEMENT_H

#include "../../../../language_element.h"

class PrintElement : public LanguageElement
{
public:
    bool matches(const std::string &line) override;
    Error execute(std::list<str> args, int64 len, global_t* glbl) override;
};


#endif //SIMON_PRINT_ELEMENT_H
