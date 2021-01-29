//
// Created by liam on 10/30/20.
//

#ifndef SIMON_SIMON_H
#define SIMON_SIMON_H

#include <unordered_map>
#include <list>
#include <iostream>
#include <string>
#include "languages.h"

#define col_clear "\u001b[0m"
#define col_red "\u001b[31m"
#define col_yellow "\u001b[33m"
#define col_blue "\u001b[34m"
#define print_error(str) std::cerr << col_red << "error: " << str << col_clear << std::endl
#define print_warning(str) std::cerr << col_yellow << "warning: " << str << col_clear << std::endl
#define print_info(str) std::cerr << col_blue << "info: " << str << col_clear << std::endl

// If TESTING is undefined, define it.
#ifndef TESTING
#define TESTING false
#endif

typedef std::string str;

struct global_t {
    Language language;
    std::iostream *output;
    bool is_test;
    long line;
    str filename;
};
extern global_t global;

#define current_line std::to_string(global.line)

#endif //SIMON_SIMON_H
