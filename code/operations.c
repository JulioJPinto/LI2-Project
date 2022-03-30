#include "stack.h"
#include <stdio.h>

void add_operation(Stack *stack) {
    int x = pop(stack);
    int y = pop(stack);

    push(stack, x + y);
}