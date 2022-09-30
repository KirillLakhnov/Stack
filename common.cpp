#include "common.h"
#include "stack.h"

void StackRealloc (struct Stack* stack1)
{
    if (stack1->size >= stack1->capacity)
    {
        stack1->capacity *= 2;
        stack1->data = (Elem_t*) realloc (stack1->data, stack1->capacity);

        for (int i = (stack1->capacity)/2; i < stack1->capacity; i++)
        {
            stack1->data[i] = NAN;
        }
    }

    else if (stack1->size <= ((stack1->capacity/2) - 1))
    {
        stack1->capacity /= 2;   
        stack1->data = (Elem_t*) realloc (stack1->data, stack1->capacity);  

        for (int i = (stack1->capacity)*2; i > stack1->capacity; i++)
        {
            stack1->data[i] = NAN;
        }       
    }
}