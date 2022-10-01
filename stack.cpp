#include "stack.h"

int StackCtor (struct stack_info* stack, size_t capacity)
{
    assert (stack);

    stack->left_struct_canary  = LEFT_CANARY;
    stack->right_struct_canary = RIGHT_CANARY;

    stack->data = (Elem_t*) calloc (1, capacity * sizeof(Elem_t) + 2 * sizeof (LEFT_CANARY));
    if (stack->data == nullptr)
    {
        return ERROR_CALLOC;
    }

    *((size_t*)(stack->data)) = LEFT_CANARY;
    stack->data = (Elem_t*)((size_t*)stack->data + 1);
    *((size_t*)(stack->data + capacity)) = RIGHT_CANARY;

    for (int i = 0; i < capacity; i++)
    {
        stack->data[i] = NULL_SPECIFIER;
    }

    stack->capacity = capacity;
    stack->size = 0;
    stack->code_of_error = 0;

    ASSERT_OK (stack);

    return GOOD_WORKING;
}

void StackPush (struct stack_info* stack, Elem_t value)
{   
    FUNCTION_INFO (stack);

    ASSERT_OK (stack);

    if (stack->size >= stack->capacity)
    {
        StackRealloc (stack, stack->capacity * 2);
        stack->capacity *= 2;
    }

    stack->data[stack->size++] = value;

    ASSERT_OK (stack);
}

Elem_t StackPop (struct stack_info* stack)
{
    ASSERT_OK (stack);

    Elem_t element_pop = stack->data[stack->size];
    stack->data[stack->size--] = NULL_SPECIFIER;

    if (stack->size <= ((stack->capacity/2) - 1))
    {
        StackRealloc (stack, stack->capacity/2);   
        stack->capacity /= 2;   
    }

    ASSERT_OK (stack);   

    return element_pop;
}

void StackDtor (struct stack_info* stack)
{
    ASSERT_OK (stack);

    for (int i = 0; i < stack->capacity; i++)
    {  
        stack->data[i] = NULL_SPECIFIER;
    }
    free (stack->data);

    stack->size = DTOR_VALUE;
    stack->capacity = DTOR_VALUE;
    stack->code_of_error = DTOR_VALUE;
    stack->left_struct_canary = DTOR_VALUE;
    stack->right_struct_canary = DTOR_VALUE;

    stack->func_info.log_file = nullptr;
    stack->func_info.log_file_name = nullptr;
    stack->func_info.name_stack = nullptr;
    stack->func_info.name_function_stack_cpp = nullptr;
    stack->func_info.number_line_stack_name_main = DTOR_VALUE;
    stack->func_info.number_line_stack_cpp = DTOR_VALUE;

}

int StackRealloc (struct stack_info* stack, size_t new_capacity)
{
    ASSERT_OK (stack);

    *((size_t*)(stack->data + stack->capacity)) = 0;

    stack->data = (Elem_t*) realloc ((char*)stack->data - sizeof(LEFT_CANARY), new_capacity * sizeof(Elem_t) + 2 * sizeof(LEFT_CANARY));
    
    if (stack->data == nullptr)
    {
        return ERROR_REALLOC;
    }
    
    *((size_t*)(stack->data)) = LEFT_CANARY;
    stack->data = (Elem_t*)((size_t*)stack->data + 1);
    *((size_t*)(stack->data + new_capacity)) = RIGHT_CANARY;

    for (int i = (stack->size); i < new_capacity; i++)
    {
        stack->data[i] = NULL_SPECIFIER;
    }

    ASSERT_OK (stack);

    return GOOD_WORKING;
}

void StackDump (struct stack_info* stack)
{
    stack->func_info.log_file = fopen (stack->func_info.log_file_name, "ab");

    fprintf (stack->func_info.log_file, "-----------------------------------------------\n");

    fprintf (stack->func_info.log_file, "%s () at stack.cpp (%ld):\n"
                        "Stack[%p] (%s) \"%s\" at main () at main.cpp (%ld)\n", 
                        stack->func_info.name_function_stack_cpp, stack->func_info.number_line_stack_cpp, stack, (stack->code_of_error > 0) ? "ERROR" : "OK", stack->func_info.name_stack, stack->func_info.number_line_stack_name_main);

    fprintf (stack->func_info.log_file, "{\n\tsize          = %lu\n"
                                            "\tcapacity      = %lu\n" 
                                            "\tcode of error = %d\n"
                                            "\tdata[%p]\n\t{\n", stack->size, stack->capacity, stack->code_of_error, stack->data); 
    for (int i = 0; i < stack->capacity; i++)
    {
        fprintf (stack->func_info.log_file, "\t\t%c [%d] = " specifier_elem_t "\n", 
                           (stack->data[i] == NULL_SPECIFIER || stack->data[i] != stack->data[i]) ? ' ' : '*', i, stack->data[i]);
    }
    
    fprintf (stack->func_info.log_file, "\t}\n}\n");

    fprintf (stack->func_info.log_file, "-----------------------------------------------\n");

    fclose (stack->func_info.log_file);
}

int StackError (struct stack_info* stack)
{
    int pointer_stack_check_null = ((!stack) ? STACK_ERROR_POINTER_STRUCT_NULL : 0);

    if (pointer_stack_check_null != 0)
    {

    }
    else 
    {
        stack->code_of_error |= CHECK_ERROR (!stack->data, STACK_ERROR_POINTER_BUFFER_NULL);
        stack->code_of_error |= CHECK_ERROR (stack->size < 0, STACK_ERROR_SIZE_SMALLER_ZERO);
        stack->code_of_error |= CHECK_ERROR (stack->capacity < 0, STACK_ERROR_CAPACITY_SMALLER_ZERO);
        stack->code_of_error |= CHECK_ERROR (stack->size > stack->capacity, STACK_ERROR_SIZE_BIGGER_CAPACITY);
        stack->code_of_error |= CHECK_ERROR (stack->left_struct_canary != LEFT_CANARY, STACK_ERROR_LEFT_CANARY_STRUCT_DEAD);
        stack->code_of_error |= CHECK_ERROR (stack->right_struct_canary != RIGHT_CANARY, STACK_ERROR_RIGHT_CANARY_STRUCT_DEAD);

        if (stack->code_of_error & STACK_ERROR_POINTER_BUFFER_NULL)
        {
            stack->code_of_error |= CHECK_ERROR (*((size_t*)stack->data - 1) != LEFT_CANARY, STACK_ERROR_LEFT_CANARY_BUFFER_DEAD);
            stack->code_of_error |= CHECK_ERROR (*((size_t*)(stack->data + stack->capacity)) != RIGHT_CANARY, STACK_ERROR_LEFT_CANARY_BUFFER_DEAD);
        }
    }

    return stack->code_of_error;
}

void DecoderStackError (struct stack_info* stack)
{
    stack->func_info.log_file = fopen (stack->func_info.log_file_name, "ab");

    PRINT_ERROR (stack->code_of_error, STACK_ERROR_POINTER_BUFFER_NULL);
    PRINT_ERROR (stack->code_of_error, STACK_ERROR_SIZE_SMALLER_ZERO);
    PRINT_ERROR (stack->code_of_error, STACK_ERROR_CAPACITY_SMALLER_ZERO);
    PRINT_ERROR (stack->code_of_error, STACK_ERROR_SIZE_BIGGER_CAPACITY);
    PRINT_ERROR (stack->code_of_error, STACK_ERROR_LEFT_CANARY_BUFFER_DEAD);
    PRINT_ERROR (stack->code_of_error, STACK_ERROR_RIGHT_CANARY_BUFFER_DEAD);
    PRINT_ERROR (stack->code_of_error, STACK_ERROR_LEFT_CANARY_STRUCT_DEAD);
    PRINT_ERROR (stack->code_of_error, STACK_ERROR_RIGHT_CANARY_STRUCT_DEAD);

    fclose (stack->func_info.log_file);
}
