#ifndef SIMON_USE_ELEMENT_H
#define SIMON_USE_ELEMENT_H

#include "../language_element.h"

class UseElement : public LanguageElement
{
public:
    bool matches(const std::string &line) override;

    Error execute(std::list<str> args, int64 len, global_t* global) override;
};


#endif //SIMON_USE_ELEMENT_H
