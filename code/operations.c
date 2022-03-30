#include "stack.h"
#include <stdio.h>
#include <math.h>

void add_operation(Stack *stack) {
    int x = pop(stack);
    int y = pop(stack);

    push(stack, x + y);
}

void minus_operation(Stack *stack) {
    int x = pop(stack);
    int y = pop(stack);

    push(stack, y - x);
}

void mult_operation(Stack *stack) {
    int x = pop(stack);
    int y = pop(stack);

    push(stack, x * y);
}

void div_operation(Stack *stack) {
    int x = pop(stack);
    int y = pop(stack);

    push(stack, y / x);
}

void decrement_operation(Stack *stack) {
    int x = pop(stack);

    push(stack, x - 1);
}

void increment_operation(Stack *stack) {
    int x = pop(stack);

    push(stack, x + 1);
}

void modulo_operation(Stack *stack) {
    int x = pop(stack);
    int y = pop(stack);

    push(stack, y % x);
}

void exponential_operation(Stack *stack) {
    int x = pop(stack);
    int y = pop(stack);

    push(stack, (int) pow(y, x));
}

void and_bitwise_operation(Stack *stack) {
    int x = pop(stack);
    int y = pop(stack);

    push(stack, x & y);
}

void or_bitwise_operation(Stack *stack) {
    int x = pop(stack);
    int y = pop(stack);

    push(stack, x | y);
}

void xor_bitwise_operation(Stack *stack) {
    int x = pop(stack);
    int y = pop(stack);

    push(stack, x ^ y);
}

void not_bitwise_operation(Stack *stack) {
    int x = pop(stack);

    push(stack, ~x);
}