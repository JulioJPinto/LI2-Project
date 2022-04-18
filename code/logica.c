#include "logger.h"
#include "operations.h"
#include "conversions.h"
#include "stack.h"

void lesser_than_long_operation(Stack *stack, long a, long b) {
    push_long(stack, a < b);
}

void lesser_than_double_operation(Stack *stack, double a, double b) {
    push_long(stack, a < b);
}

void lesser_than_operation(Stack *stack) {
    operate_promoting_number_type(stack, lesser_than_double_operation, lesser_than_long_operation);
}

void bigger_than_long_operation(Stack *stack, long a, long b) {
    push_long(stack, a > b);
}

void bigger_than_double_operation(Stack *stack, double a, double b) {
    push_long(stack, a > b);
}

void bigger_than_operation(Stack *stack) {
    operate_promoting_number_type(stack, bigger_than_double_operation, bigger_than_long_operation);
}

void is_equal_long_operation(Stack *stack, long a, long b) {
    push_long(stack, a == b);
}

void is_equal_double_operation(Stack *stack, double a, double b) {
    push_long(stack, a == b);
}

void is_equal_operation(Stack *stack) {
    operate_promoting_number_type(stack, is_equal_double_operation, is_equal_long_operation);
}

void and_long_operation(Stack *stack, long a, long b) {
    push_long(stack, a && b ? b : 0);
}

void and_double_operation(Stack *stack, double a, double b) {
    push_double(stack, a != 0 && b != 0 ? b : 0);
}

void and_operation(Stack *stack) {
    operate_promoting_number_type(stack, and_double_operation, and_long_operation);
}

void or_long_operation(Stack *stack, long a, long b) {
    push_long(stack, a ? a : b);
}

void or_double_operation(Stack *stack, double a, double b) {
    push_double(stack, a != 0 ? a : b);
}

void or_operation(Stack *stack) {
    operate_promoting_number_type(stack, or_double_operation, or_long_operation);
}

void lesser_value_long_operation(Stack *stack, long a, long b) {
    push_long(stack, a < b ? b : a);
}

void lesser_value_double_operation(Stack *stack, double a, double b) {
    push_double(stack, a < b ? b : a);
}

void lesser_value_operation(Stack *stack) {
    operate_promoting_number_type(stack, lesser_value_double_operation, lesser_value_long_operation);
}

void bigger_value_long_operation(Stack *stack, long a, long b) {
    push_long(stack, a > b ? b : a);
}

void bigger_value_double_operation(Stack *stack, double a, double b) {
    push_double(stack, a > b ? b : a);
}

void bigger_value_operation(Stack *stack) {
    operate_promoting_number_type(stack, bigger_value_double_operation, bigger_value_long_operation);
}

void if_then_else_operation(Stack *stack) {
    StackElement c = pop(stack);
    StackElement b = pop(stack);
    StackElement a = pop(stack);

    int cond = is_truthy(&a);

    push(stack, cond ? b : c);
}
