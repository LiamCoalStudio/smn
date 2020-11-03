//
// Created by liam on 11/1/20.
//

#ifndef SIMON_FUNCTIONS_H
#define SIMON_FUNCTIONS_H

#include <sstream>
#include <list>

class Function
{
private:
    std::list<std::string> input;
    bool locked = false;
public:
    Function();

    void add(const std::string& s);
    void exec();

    inline void lock() { locked = true; }
};

extern Function* find_func(const std::string& name);
extern void create_func(const std::string& name, Function* f);
extern void delete_func(const std::string& name);

#endif //SIMON_FUNCTIONS_H
