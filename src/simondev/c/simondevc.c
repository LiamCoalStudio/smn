#include <stdio.h>
#include "simondevc.h"

const char* simon_version = "0.1.2";

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
