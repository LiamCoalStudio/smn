//
// Created by liam on 10/30/20.
//

#ifndef SIMON_SIMON_H
#define SIMON_SIMON_H

#include <unordered_map>
#include <list>
#include <iostream>
#include "languages.h"

#define col_clear "\u001b[0m"
#define col_red "\u001b[31m"
#define col_yellow "\u001b[33m"
#define col_blue "\u001b[34m"

#define print_error(str) std::cerr << col_red << "error: " << str << col_clear << std::endl
#define print_warning(str) std::cerr << col_yellow << "warning: " << str << col_clear << std::endl
#define print_info(str) std::cerr << col_blue << "info: " << str << col_clear << std::endl

#define argerr  print_error("not enough arguments"); \
                return Err

#define simon_version "0.0.1"

// If TESTING is undefined, define it.
#ifndef TESTING
#define TESTING false
#endif

typedef std::string str;

typedef signed char int8;
typedef signed short int16;
typedef signed int int32;
typedef signed long long int64;

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

typedef std::unordered_map<str, str> var_context_t;

struct global_t
{
    var_context_t variable_context;
    Language language;
    std::iostream* output;
};

extern global_t global;

#endif //SIMON_SIMON_H
