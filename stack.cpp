#include "stack.h"

void StackCtor (struct stack_info* stack, size_t capacity)
{
    assert (stack);

    stack->data = (Elem_t*) calloc (capacity, sizeof(Elem_t));

    stack->capacity = capacity;
    stack->size = 0;
    stack->code_of_error = 0;

}

void StackPush (struct stack_info* stack, Elem_t value)
{   

    if (stack->size >= stack->capacity)
    {
        stack->capacity *= 2;
        StackRealloc (stack, stack->capacity);
    }

    stack->data[stack->size++] = value;
}

Elem_t StackPop (struct stack_info* stack)
{
    Elem_t element_pop = stack->data[stack->size];
    stack->data[stack->size--] = NULL_SPECIFIER;

    if (stack->size <= ((stack->capacity/2) - 1))
    {
        StackRealloc (stack, stack->capacity);       
    }   

    return element_pop;
}

void StackDtor (struct stack_info* stack)
{
    for (int i = 0; i < stack->capacity; i++)
    {  
        stack->capacity /= 2;
        StackRealloc (stack, stack->capacity);
    }

    free (stack->data);
}

void StackRealloc (struct stack_info* stack, size_t new_capacity)
{
    stack->data = (Elem_t*) realloc (stack->data, new_capacity * sizeof(Elem_t));

    for (int i = (stack->size); i < new_capacity; i++)
    {
        stack->data[i] = NULL_SPECIFIER;
    }
}

void StackDump (struct stack_info* stack, struct function_info* func_info)
{
    FILE* dump_text = fopen(func_info->log_file_name, "ab");

    fprintf (dump_text, "-----------------------------------------------\n");

    fprintf (dump_text, "StackPush () at stack.cpp (%d):\n"
                        "Stack[%p] (%s) \"%s\" at main () at main.cpp (%d)\n", 
                        func_info->number_line_stack_cpp, stack, (stack->code_of_error > 0) ? "ERROR" : "OK", func_info->name_stack, func_info->number_line_stack_name_main);

    fprintf (dump_text, "{\n\tsize          = %lu\n"
                           "\tcapacity      = %lu\n" 
                           "\tcode of error = %d\n"
                           "\tdata[%p]\n\t{\n", stack->size, stack->capacity, stack->code_of_error, stack->data); 
    for (int i = 0; i < stack->capacity; i++)
    {
        fprintf (dump_text, "\t\t%c [%d] = " specifier_elem_t "\n", 
                           (stack->data[i] == NULL_SPECIFIER || stack->data[i] != stack->data[i]) ? ' ' : '*', i, stack->data[i]);
    }
    
    fprintf (dump_text, "\t}\n}\n");


    fprintf (dump_text, "-----------------------------------------------\n");

    fclose (dump_text);
}

int StackError (struct stack_info* stack)
{
    ;
}
