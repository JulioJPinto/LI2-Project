#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conversions.h"
#include "logger.h"

#define MAX_CONVERT_TO_STRING_SIZE 100

int parse_long(char word[], long *to) {
    char *remainder;
    long result = strtol(word, &remainder, 10);
    if (strlen(remainder) <= 0) {
        PRINT_DEBUG("Parsed %ld from '%s'\n", result, word)
        *to = result;
        return 1;
    }
    return 0;
}

int parse_double(char word[], double *to) {
    char *remainder;
    double result = strtod(word, &remainder);
    if (strlen(remainder) <= 0) {
        PRINT_DEBUG("Parsed %g from '%s'\n", result, word)
        *to = result;
        return 1;
    }
    return 0;
}

void convert_last_element_to_char(Stack *stack) {
    StackElement stack_element = pop(stack);

    char x;
    long l;

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
        case STRING_TYPE:
            if (parse_long(stack_element.content.string_value, &l)) {
                x = (char) l;
            } else {
                x = stack_element.content.string_value[0];
            }
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
        case STRING_TYPE:
            if (parse_double(stack_element.content.string_value, &x))
                break;
            fprintf(stderr, "Couldn't convert to double from string %s", stack_element.content.string_value);
            return;
        default:
            fprintf(stderr, "Couldn't convert to double from type %d", stack_element.type);
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
        case STRING_TYPE:
            if (parse_long(stack_element.content.string_value, &x))
                break;
            fprintf(stderr, "Couldn't convert to long from string %s", stack_element.content.string_value);
            return;
        default:
            fprintf(stderr, "Couldn't convert to long from type %d", stack_element.type);
            return;
    }

    push_long(stack, x);
}

void convert_last_element_to_string(Stack *stack) {
    StackElement stack_element = pop(stack);

    char x[MAX_CONVERT_TO_STRING_SIZE];

    switch (stack_element.type) {
        case DOUBLE_TYPE:
            sprintf(x, "%g", stack_element.content.double_value);
            break;
        case LONG_TYPE:
            sprintf(x, "%ld", stack_element.content.long_value);
            break;
        case CHAR_TYPE:
            sprintf(x, "%c", stack_element.content.char_value);
            break;
        case STRING_TYPE:
            strcpy(x, stack_element.content.string_value);
            break;
        default:
            fprintf(stderr, "Couldn't convert to string from type %d", stack_element.type);
            return;
    }

    push_string(stack, x);
}
