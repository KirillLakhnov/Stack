#ifndef STACK_H
#define STACK_H

#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

enum STACK_ERROR {

};

struct stack_info {
    Elem_t* data;
    size_t  size;
    size_t  capacity;
    unsigned int code_of_error;
    struct function_info* func_info;
};

struct function_info {
    const char* log_file_name;
    const char* name_stack;
    const char* name_function_stack_cpp; //+++
    size_t number_line_stack_name_main; 
    size_t number_line_stack_cpp; //+++
};

void StackCtor (struct stack_info* stack, size_t capacity);

void StackPush (struct stack_info* stack, Elem_t value);

Elem_t StackPop (struct stack_info* stack);

void StackDtor (struct stack_info* stack);

void StackRealloc (struct stack_info* stack, size_t new_capacity);

void StackDump (struct stack_info* stack);

void StackDump (struct stack_info* stack, struct function_info* func_info);

#endif // STACK_H