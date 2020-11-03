#ifndef SIMON_LANGUAGE_ELEMENT_H
#define SIMON_LANGUAGE_ELEMENT_H

#include <string>
#include <regex>
#include "simon.h"

/**
 * Base class of all language elements.
 */
class LanguageElement
{
protected:
    std::smatch smatch;
public:
    enum Error
    {Err, Warn, Info, None};
    virtual bool matches(const std::string& line) = 0;
    virtual Error execute(std::list<str> args, int64 len, global_t* global) { return Err; }
    virtual Error execute(std::list<str> args, int64 len, global_t* global, const std::list<str>& body) { return Err; }
    virtual bool has_body() { return false; }
};

#endif //SIMON_LANGUAGE_ELEMENT_H
