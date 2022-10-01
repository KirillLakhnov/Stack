#include "common.h"
#include "stack.h"

int main ()
{
    struct stack_info stack = {};
    struct function_info func_info = {.log_file_name = "stack_dump.txt", .name_stack = "stack", .number_line_stack_name_main = __LINE__ - 1};

    StackCtor (&stack, 5);
    
    StackPush (&stack, 7);
    StackPush (&stack, 8.34);
    StackPush (&stack, 99.9934);
    StackPush (&stack, -45.78);
    StackPush (&stack, -4);
    StackPush (&stack, 23);
    StackPush (&stack, 87);

    StackDump (&stack, &func_info);

    return 0;
}