#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Stack {
    Elem_t* data;
    size_t  size;
    size_t  capacity;
};

void StackCtor (struct Stack* stack1, size_t capacity);

void StackPush (struct Stack* stack1, Elem_t value);

Elem_t StackPop (struct Stack* stack1);

void StackDtor (struct Stack* stack1);

#endif // STACK_H