#include <stdio.h>
#include "simondevc.h"

const char* simon_version = VERSION;

void* _stack;
int _stack_pointer;

void start_stack()
{
    _stack = malloc(1 << 16);
    _stack_pointer = 0;
}

void end_stack()
{
    free(_stack);
}

void push(char c)
{
    ((char*)_stack)[_stack_pointer] = c;
    _stack_pointer++;
}

char pop()
{
    _stack_pointer--;
    return ((char*)_stack)[_stack_pointer];
}

void pushp(void* v, long s)
{
    char* c = (char*)v;
    for (long i = 0; i < s; ++i)
    { push(c[i]); }
}

void* popp(long s)
{
    char* c = NULL;
    c = (char*)malloc(s);
    for (long i = s - 1; i >= 0; --i)
    { c[i] = pop(); }
    return c;
}

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

void println(str text)
{ puts(text); }

void print(str text)
{ printf("%s", text); }
