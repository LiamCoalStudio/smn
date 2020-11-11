#ifndef SMN_SIMONDEV_H
#define SMN_SIMONDEV_H

#include <string>
#include <cstdlib>
#include <iostream>

//#ifdef TESTING
//#define MODULE_simon
//#define MODULE_simon$io
//#define MODULE_simon$math
//#endif

#define allocate(p, s) p = static_cast<typeof(p)>(malloc(s))
#define declare(type, name) type name()

typedef std::string str;
typedef std::ifstream ifile;
typedef std::ofstream ofile;
typedef std::fstream iofile;
typedef std::istream istr;
typedef std::ostream ostr;
typedef std::iostream iostr;

#ifdef MODULE_simon
extern void* _stack;
extern int _stack_pointer;

void start_stack();
void end_stack();
void push(char c);
char pop();
void push(void* v, long s);
void* pop(long s);
#endif

#ifdef MODULE_simon$io
template<typename T>
void println(const T& text)
{ std::cout << text << std::endl; }

template<typename T>
void print(const T& text)
{ std::cout << text; }
#endif

#ifdef MODULE_simon$math
#include <cmath>
#define pi M_PI
#define e M_E
#endif

namespace smn_info
{
    extern const str simon_version;
}

#endif //SMN_SIMONDEV_H
