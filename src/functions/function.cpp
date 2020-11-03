//
// Created by liam on 11/1/20.
//

#include "functions.h"

Function::Function()
{
    input = std::list<std::string>();
}

void Function::add(const std::string& s)
{
    if (locked) return;
    input.emplace_back(s);
}

extern void parse_line(const std::string& s);

void Function::exec()
{
    for(auto& a : input) parse_line(a);
}
