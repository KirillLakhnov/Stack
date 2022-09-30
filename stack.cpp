#include "common.h"
#include "stack.h"

void StackCtor (struct Stack* stack1, size_t capacity)
{
    Stack* stack1 = (struct Stack*) calloc (1, sizeof(Stack));
    stack1->capacity = capacity;

    stack1->data = (Elem_t*) calloc (stack1->capacity, sizeof(Elem_t));
}

void StackPush (struct Stack* stack1, Elem_t value)
{
    StackRealloc (stack1);
    stack1->data[stack1->size++];
}

Elem_t StackPop (struct Stack* stack1)
{
    Elem_t element_pop = stack1->data[stack1->size];
    stack1->data[stack1->size--] = NAN;

    if (stack1->size <= ((stack1->capacity/2) - 1))
    {
        stack1->capacity /= 2;
        StackRealloc (stack1);        
    }

    return element_pop;
}

void StackDtor (struct Stack* stack1)
{
    for (int i = 0; i < stack1->capacity; i++)
    {
        stack1->data[i] = NAN;
    }

    stack1->data = nullptr;
    stack1 = nullptr;
    stack1->size = NULL;
    stack1->capacity = NULL;

    free (stack1);
}
