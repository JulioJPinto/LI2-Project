#include "stack.h"
#include "logger.h"
#include <math.h>

void add_operation(Stack *stack) {
    long x = pop_long(stack);
    long y = pop_long(stack);

    push_long(stack, x + y);
}

void minus_operation(Stack *stack) {
    long x = pop_long(stack);
    long y = pop_long(stack);

    push_long(stack, y - x);
}

void mult_operation(Stack *stack) {
    long x = pop_long(stack);
    long y = pop_long(stack);

    push_long(stack, x * y);
}

void div_operation(Stack *stack) {
    long x = pop_long(stack);
    long y = pop_long(stack);

    push_long(stack, y / x);
}

void decrement_operation(Stack *stack) {
    long x = pop_long(stack);

    push_long(stack, x - 1);
}

void increment_operation(Stack *stack) {
    long x = pop_long(stack);

    push_long(stack, x + 1);
}

void modulo_operation(Stack *stack) {
    long x = pop_long(stack);
    long y = pop_long(stack);

    push_long(stack, y % x);
}

void exponential_operation(Stack *stack) {
    long x = pop_long(stack);
    long y = pop_long(stack);

    push_long(stack, (long) pow((double) y, (double) x));
}

void and_bitwise_operation(Stack *stack) {
    long x = pop_long(stack);
    long y = pop_long(stack);

    push_long(stack, x & y);
}

void or_bitwise_operation(Stack *stack) {
    long x = pop_long(stack);
    long y = pop_long(stack);

    push_long(stack, x | y);
}

void xor_bitwise_operation(Stack *stack) {
    long x = pop_long(stack);
    long y = pop_long(stack);

    push_long(stack, x ^ y);
}

void not_bitwise_operation(Stack *stack) {
    long x = pop_long(stack);

    push_long(stack, ~x);
}