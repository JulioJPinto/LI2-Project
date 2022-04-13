#include <stdio.h>
#include "conversions.h"

void convert_last_element_to_char(Stack *stack) {
    StackElement stack_element = pop(stack);

    char x;

    switch (stack_element.type) {
        case DOUBLE_TYPE:
            x = (char) stack_element.content.double_value;
            break;
        case LONG_TYPE:
            x = (char) stack_element.content.long_value;
            break;
        case CHAR_TYPE:
            x = stack_element.content.char_value;
            break;
        default:
            fprintf(stderr, "Couldn't convert to char from type %d", stack_element.type);
            return;
    }

    push_char(stack, x);
}

void convert_last_element_to_double(Stack *stack) {
    StackElement stack_element = pop(stack);

    double x;

    switch (stack_element.type) {
        case DOUBLE_TYPE:
            x = stack_element.content.double_value;
            break;
        case LONG_TYPE:
            x = (double) stack_element.content.long_value;
            break;
        case CHAR_TYPE:
            x = (double) stack_element.content.char_value;
            break;
        default:
            fprintf(stderr, "Couldn't convert to char from type %d", stack_element.type);
            return;
    }

    push_double(stack, x);
}

void convert_last_element_to_long(Stack *stack) {
    StackElement stack_element = pop(stack);

    long x;

    switch (stack_element.type) {
        case DOUBLE_TYPE:
            x = (long) stack_element.content.double_value;
            break;
        case LONG_TYPE:
            x = stack_element.content.long_value;
            break;
        case CHAR_TYPE:
            x = (long) stack_element.content.char_value;
            break;
        default:
            fprintf(stderr, "Couldn't convert to char from type %d", stack_element.type);
            return;
    }

    push_long(stack, x);
}


