//
// Created by liam on 11/1/20.
//

#ifndef SIMON_EXEC_FUNCTION_ELEMENT_H
#define SIMON_EXEC_FUNCTION_ELEMENT_H

#include "../language_element.h"

class ExecFunctionElement : public LanguageElement
{
private:
    str name;
public:
    bool matches(const std::string &line) override;

    Error execute(std::list<str> args, int64 len, global_t *global) override;
};


#endif //SIMON_EXEC_FUNCTION_ELEMENT_H
