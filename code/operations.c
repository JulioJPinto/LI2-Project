#include "logger.h"
#include "operations.h"

#include <math.h>

void operate_promoting_number_type(Stack *stack,
                                   void (*double_operation_function_pointer)(Stack *, double, double),
                                   void (*long_operation_function_pointer)(Stack *, long, long)) {
    StackElement x = pop(stack);
    StackElement y = pop(stack);

    ElementType x_type = x.type;
    ElementType y_type = y.type;

    if (x_type == DOUBLE_TYPE && y_type == DOUBLE_TYPE) {
        double_operation_function_pointer(stack, x.content.double_value, y.content.double_value);
    } else if (x_type == DOUBLE_TYPE && y_type == LONG_TYPE) {
        double_operation_function_pointer(stack, x.content.double_value, (double) y.content.long_value);
    } else if (x_type == LONG_TYPE && y_type == DOUBLE_TYPE) {
        double_operation_function_pointer(stack, (double) x.content.long_value, y.content.double_value);
    } else if (x_type == LONG_TYPE && y_type == LONG_TYPE) {
        long_operation_function_pointer(stack, x.content.long_value, y.content.long_value);
    } else {
        fprintf(stderr, "Trying to operate non number elements. (x_type: %d, y_type: %d)", x_type, y_type);
    }
}

void add_double_operation(Stack *stack, double a, double b) {
    push_double(stack, a + b);
}

void add_long_operation(Stack *stack, long a, long b) {
    push_long(stack, a + b);
}

void add_operation(Stack *stack) {
    operate_promoting_number_type(stack, add_double_operation, add_long_operation);
}

void minus_double_operation(Stack *stack, double a, double b) {
    push_double(stack, a - b);
}

void minus_long_operation(Stack *stack, long a, long b) {
    push_long(stack, a - b);
}

void minus_operation(Stack *stack) {
    operate_promoting_number_type(stack, minus_double_operation, minus_long_operation);
}

void mult_double_operation(Stack *stack, double a, double b) {
    push_double(stack, a * b);
}

void mult_long_operation(Stack *stack, long a, long b) {
    push_long(stack, a * b);
}

void mult_operation(Stack *stack) {
    operate_promoting_number_type(stack, mult_double_operation, mult_long_operation);
}

void div_double_operation(Stack *stack, double a, double b) {
    push_double(stack, a / b);
}

void div_long_operation(Stack *stack, long a, long b) {
    push_long(stack, a / b);
}

void div_operation(Stack *stack) {
    operate_promoting_number_type(stack, div_double_operation, div_long_operation);
}

void decrement_operation(Stack *stack) {
    StackElement element = pop(stack);

    if (element.type == DOUBLE_TYPE) {
        push_double(stack, element.content.double_value--);
    } else if (element.type == LONG_TYPE) {
        push_long(stack, element.content.long_value--);
    } else {
        fprintf(stderr, "Trying to decrement non number element. (type: %d)", element.type);
    }
}

void increment_operation(Stack *stack) {
    StackElement element = pop(stack);

    if (element.type == DOUBLE_TYPE) {
        push_double(stack, element.content.double_value++);
    } else if (element.type == LONG_TYPE) {
        push_long(stack, element.content.long_value++);
    } else {
        fprintf(stderr, "Trying to increment non number element. (type: %d)", element.type);
    }
}

void modulo_operation(Stack *stack) {
    long x = pop_long(stack);
    long y = pop_long(stack);

    push_long(stack, y % x);
}

void exponential_operation(Stack *stack) {
    StackElement x = pop(stack);
    StackElement y = pop(stack);

    ElementType x_type = x.type;
    ElementType y_type = y.type;

    if (x_type == DOUBLE_TYPE && y_type == DOUBLE_TYPE) {
        push_double(stack, pow(x.content.double_value, y.content.double_value));
    } else if (x_type == DOUBLE_TYPE && y_type == LONG_TYPE) {
        push_double(stack, pow(x.content.double_value, (double) y.content.long_value));
    } else if (x_type == LONG_TYPE && y_type == DOUBLE_TYPE) {
        push_long(stack, (long) pow((double) x.content.long_value, y.content.double_value));
    } else if (x_type == LONG_TYPE && y_type == LONG_TYPE) {
        push_long(stack, (long) pow((double) x.content.long_value, (double) y.content.long_value));
    } else {
        fprintf(stderr, "Trying to exp non number elements. (x_type: %d, y_type: %d)", x_type, y_type);
    }
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

void duplicate_operation(Stack *stack) {
    push(stack, peek(stack));
}

void pop_operation(Stack *stack) {
    pop(stack);
}

void swap_last_two_operation(Stack *stack) {
    StackElement x1 = pop(stack);
    StackElement x2 = pop(stack);

    push(stack, x1);
    push(stack, x2);
}

void rotate_last_three_operation(Stack *stack) {
    StackElement x1 = pop(stack);
    StackElement x2 = pop(stack);
    StackElement x3 = pop(stack);

    push(stack, x2);
    push(stack, x1);
    push(stack, x3);
}

void copy_nth_element_operation(Stack *stack) {
    long index = pop_long(stack);

    push(stack, get(stack, index));
}
