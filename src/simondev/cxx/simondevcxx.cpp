#include <iostream>
#include "simondevcxx.h"

namespace smn_info
{
    const str simon_version = VERSION;
}

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

void push(void* v, long s)
{
    char* c = static_cast<char *>(v);
    for (long i = 0; i < s; ++i)
    { push(c[i]); }
}

void* pop(long s)
{
    static char* c = static_cast<char *>(malloc(s));
    for (long i = s - 1; i >= 0; --i)
    { c[i] = pop(); }
    return c;
}
