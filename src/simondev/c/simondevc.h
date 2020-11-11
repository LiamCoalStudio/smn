#ifndef SMN_SIMONDEVC_H
#define SMN_SIMONDEVC_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MODULE_simon
#define MODULE_simon$io
#define MODULE_simon$math
#define MODULE_simon$io$fs

#define allocate(p, s) p = static_cast<typeof(p)>(malloc(s))
#define declare(type, name) type name()

typedef char *str;

#ifdef MODULE_simon
extern void *_stack;
extern int _stack_pointer;

void start_stack();
void end_stack();
void push(char c);
char pop();
void pushp(void *v, long s);
void *popp(long s);
#endif

#ifdef MODULE_simon$io$fs
#define MODULE_simon$io

typedef FILE* file;
typedef file ifile;
typedef file ofile;
typedef file iofile;

#define MODE_READ "r"
#define MODE_WRITE "w"
#define MODE_READ_WRITE "r+"
#define MODE_APPEND "a"
#define MODE_READ_BIN MODE_READ"b"
#define MODE_WRITE_BIN MODE_WRITE"b"
#define MODE_READ_WRITE_BIN MODE_READ_WRITE"b"
#define MODE_APPEND_BIN MODE_APPEND"b"

file open(str name, str mode)
{ return fopen(name, mode); }

void write(file out, void *t, int size)
{ fwrite(t, 1, size, out); }

void* read(file in, int size)
{
    void* t = malloc(size);
    fread(t, 1, size, in);
    return t;
}

void close_in(file f)
{ fclose(f); }

void flush(file f)
{ fflush(f); }
#endif

#ifdef MODULE_simon$io
void println(str text)
{ puts(text); }

void print(str text)
{ printf("%s", text); }
#endif

#ifdef MODULE_simon$math
#include <math.h>
#define pi M_PI
#define e M_E
#endif

extern const char* simon_version;

#ifdef __cplusplus
}
#endif

#endif //SMN_SIMONDEVC_H
