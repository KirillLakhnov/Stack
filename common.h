#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "common.h"

#define specifier_elem_t "%f"

typedef double Elem_t;
const Elem_t NULL_SPECIFIER = NAN;

#define ASSERT_OK(stack)    do                                      \
                            {                                       \
                                if (StackError (stack) != 0)        \
                                {                                   \
                                    DecoderStackError (stack);      \
                                    StackDump (stack);              \
                                    abort();                        \
                                }                                   \
                            }  while (0)

#endif // COMMON_H