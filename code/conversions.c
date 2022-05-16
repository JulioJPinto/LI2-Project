#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conversions.h"
#include "logger.h"

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

char convert_element_to_char(StackElement *stack_element) {
    long l;

    switch ((*stack_element).type) {
        case DOUBLE_TYPE:
            return (char) (*stack_element).content.double_value;
        case LONG_TYPE:
            return (char) (*stack_element).content.long_value;
        case CHAR_TYPE:
            return (*stack_element).content.char_value;
        case STRING_TYPE:
            if (parse_long((*stack_element).content.string_value, &l)) {
                return (char) l;
            } else {
                return (*stack_element).content.string_value[0];
            }
        case ARRAY_TYPE:
        case BLOCK_TYPE:
        default: PANIC("Couldn't convert to char from type %d", (*stack_element).type)
    }
}

/**
 * @brief Função que vai transformar um elemento na stack no tipo double.
 * Esta Função vai receber o @param{*stack_element} e vai transformá-lo num double, double este que é devolvido.
 */
double convert_element_to_double(StackElement *stack_element) {
    double x;

    switch ((*stack_element).type) {
        case DOUBLE_TYPE:
            return (*stack_element).content.double_value;
        case LONG_TYPE:
            return (double) (*stack_element).content.long_value;
        case CHAR_TYPE:
            return (double) (*stack_element).content.char_value;
        case STRING_TYPE:
            if (parse_double((*stack_element).content.string_value, &x))
                return x;
            PANIC("Couldn't convert to double from string %s", (*stack_element).content.string_value)
        case ARRAY_TYPE:
        case BLOCK_TYPE:
        default: PANIC("Couldn't convert to double from type %d", (*stack_element).type)
    }
}

/**
 * @brief Função que vai transformar um elemento na stack no tipo long.
 * Esta Função vai receber o @param{*stack_element} e vai transformá-lo num long, long este que é devolvido.
 */
long convert_element_to_long(StackElement *stack_element) {
    long x;

    switch ((*stack_element).type) {
        case DOUBLE_TYPE:
            return (long) (*stack_element).content.double_value;
        case LONG_TYPE:
            return (*stack_element).content.long_value;
        case CHAR_TYPE:
            return (long) (*stack_element).content.char_value;
        case STRING_TYPE:
            if (parse_long((*stack_element).content.string_value, &x))
                return x;
            PANIC("Couldn't convert to long from string %s", (*stack_element).content.string_value)
        case ARRAY_TYPE:
        case BLOCK_TYPE:
        default: PANIC("Couldn't convert to long from type %d", (*stack_element).type)
    }
}

/**
 * @brief Converte um array para uma string
 */
static void convert_array_to_string(Stack *array_stack, char *dest) {
    *dest = '\0';

    int stack_length = length(array_stack);

    for (int i = 0; i < stack_length; i++) {
        StackElement array_elem = array_stack->array[i];

        char current_element_to_string[MAX_CONVERT_TO_STRING_SIZE];
        convert_element_to_string(&array_elem, current_element_to_string);

        strcat(dest, current_element_to_string);
    }
}

void convert_element_to_string(StackElement *stack_element, char *dest) {
    switch ((*stack_element).type) {
        case DOUBLE_TYPE:
            sprintf(dest, "%g", stack_element->content.double_value);
            return;
        case LONG_TYPE:
            sprintf(dest, "%ld", stack_element->content.long_value);
            return;
        case CHAR_TYPE:
            sprintf(dest, "%c", stack_element->content.char_value);
            return;
        case STRING_TYPE:
            strcpy(dest, stack_element->content.string_value);
            return;
        case ARRAY_TYPE:
            convert_array_to_string(stack_element->content.array_value, dest);
            return;
        case BLOCK_TYPE:
            strcpy(dest, stack_element->content.block_value);
            return;
        default: PANIC("Couldn't convert to string from type %d", (*stack_element).type)
    }
}

void convert_last_element_to_char(Stack *stack) {
    StackElement stack_element = pop(stack);

    push_char(stack, convert_element_to_char(&stack_element));

    free_element(stack_element);
}

void convert_last_element_to_double(Stack *stack) {
    StackElement stack_element = pop(stack);

    push_double(stack, convert_element_to_double(&stack_element));

    free_element(stack_element);
}

void convert_last_element_to_long(Stack *stack) {
    StackElement stack_element = pop(stack);

    push_long(stack, convert_element_to_long(&stack_element));

    free_element(stack_element);
}

void convert_last_element_to_string(Stack *stack) {
    StackElement stack_element = pop(stack);

    char x[MAX_CONVERT_TO_STRING_SIZE];

    convert_element_to_string(&stack_element, x);
    push_string(stack, x);

    free_element(stack_element);
}
