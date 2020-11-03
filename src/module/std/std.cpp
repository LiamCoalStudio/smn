#include <unordered_map>
#include <list>
#include "../../language_element.h"
#include "elements/io/print_element.h"
#include "elements/io/println_element.h"

#define u (*usable)
#define add emplace_back

// use module std io
extern "C" void module_use_io(std::unordered_map<std::string, std::list<LanguageElement*>>* usable)
{
    u["io"] = std::list<LanguageElement*>();
    u["io"].add(new PrintElement);
    u["io"].add(new PrintlnElement);
}
