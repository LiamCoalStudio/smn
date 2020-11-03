#ifndef SIMON_FUNCTION_ELEMENT_H
#define SIMON_FUNCTION_ELEMENT_H

#include "../language_element.h"

class FunctionElement : public LanguageElement
{
private:
    str name;
public:
    bool matches(const std::string &line) override;

    bool has_body() override;

    Error execute(std::list<str> args, int64 len, global_t *global, const std::list<str> &body) override;
};


#endif //SIMON_FUNCTION_ELEMENT_H
