#ifndef STACK_H
#define STACK_H

#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#define FUNCTION_INFO(stack)    do                                                              \
                                {                                                               \
                                    stack->func_info.number_line_stack_cpp = __LINE__ - 2;     \
                                    stack->func_info.name_function_stack_cpp = __FUNCTION__;   \
                                } while (0)                                                     

#define CHECK_ERROR(condition, error) (condition) ? error : 0

#define PRINT_ERROR(code_of_error_programm, error)  if (code_of_error_programm & error)                        \
                                                    {                                                          \
                                                        fprintf (stack->func_info.log_file, "%s\n", #error);  \
                                                    }                                                          

const size_t LEFT_CANARY  = 0xDEADBEEF;
const size_t RIGHT_CANARY = 0xABADBABE;
const size_t DTOR_VALUE   = 0xBABADEDA;

enum PROGRAMM_ERROR {
    GOOD_WORKING  = 0,
    ERROR_CALLOC  = 1,
    ERROR_REALLOC = 2,
};

enum STACK_ERROR {
    STACK_ERROR_POINTER_STRUCT_NULL        = 1 << 0,
    STACK_ERROR_POINTER_BUFFER_NULL        = 1 << 1,
    STACK_ERROR_SIZE_SMALLER_ZERO          = 1 << 2,
    STACK_ERROR_CAPACITY_SMALLER_ZERO      = 1 << 3,
    STACK_ERROR_SIZE_BIGGER_CAPACITY       = 1 << 4,
    STACK_ERROR_LEFT_CANARY_BUFFER_DEAD    = 1 << 5, 
    STACK_ERROR_RIGHT_CANARY_BUFFER_DEAD   = 1 << 6,
    STACK_ERROR_LEFT_CANARY_STRUCT_DEAD    = 1 << 7, 
    STACK_ERROR_RIGHT_CANARY_STRUCT_DEAD   = 1 << 8, 
};

struct function_info {
    FILE* log_file;
    const char* log_file_name;

    const char* name_stack;

    const char* name_function_stack_cpp; 
    size_t number_line_stack_name_main; 
    size_t number_line_stack_cpp;
};

struct stack_info {
    size_t left_struct_canary;
    Elem_t* data;
    size_t  size;
    size_t  capacity;
    unsigned int code_of_error;
    struct function_info func_info;
    size_t right_struct_canary;
};



int StackCtor (struct stack_info* stack, size_t capacity);

void StackPush (struct stack_info* stack, Elem_t value);

Elem_t StackPop (struct stack_info* stack);

void StackDtor (struct stack_info* stack);

int StackRealloc (struct stack_info* stack, size_t new_capacity);

void StackDump (struct stack_info* stack);

int StackError (struct stack_info* stack);

void DecoderStackError (struct stack_info* stack);

#endif // STACK_H