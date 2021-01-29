#ifndef SMN_SIMONDEVC_H
#define SMN_SIMONDEV_H
#include <string>
#include <cstdlib>
#include <iostream>

#define MODULE_simon
#define MODULE_simon$io
#define MODULE_simon$math
#define MODULE_simon$io$fs
#define allocate(p, s) p = static_cast<typeof(p)>(malloc(s))
#define declare(type, name) type name()
typedef std::string str;
#ifdef MODULE_simon
extern void *_stack;
extern int  _stack_pointer;
void start_stack();
void end_stack();
void push(char c);
char pop();
void push(void *v, long s);
void *pop(long s);
#endif
#ifdef MODULE_simon$io$fs
#define MODULE_simon$io
#include <fstream>

typedef std::ifstream ifile;
typedef std::ofstream ofile;
typedef std::fstream  iofile;

inline ifile open_in(const str &name)
{ return ifile(name); }

inline ofile open_out(const str &name)
{ return ofile(name); }

inline iofile open_io(const str &name)
{ return iofile(name); }

template<typename T>
inline void write(ofile &out, T t)
{ out<<t; }

template<typename T>
inline T read(ifile &in)
{
    T t;
    in>>t;
    return t;
}

template<class T>
inline void close(T &stream)
{ stream.close(); }

template<class T>
inline void flush(T &stream)
{ stream.flush(); }

#endif
#ifdef MODULE_simon$io
typedef std::istream  istr;
typedef std::ostream  ostr;
typedef std::iostream iostr;

template<typename T>
void println(const T &text)
{ std::cout<<text<<std::endl; }

template<typename T>
void print(const T &text)
{ std::cout<<text; }

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
#define add(a, b) a += b
#define subtract(a, b) a -= b
#define multiply(a, b) a *= b;
#define divide(a, b) a /= b;
#endif //SMN_SIMONDEVC_H
