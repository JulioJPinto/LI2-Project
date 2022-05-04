#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conversions.h"
#include "logger.h"

#define MAX_CONVERT_TO_STRING_SIZE 100
/**
 * @brief Função que vai atribuir ao elemento da stack o respetivo tipo long.
 * @param word O elemento que vai ser transformado num long.
 * @param to O valor do elemento após ter sido transformado no tipo long.
 */
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
/**
 * @brief Função que vai atribuir ao elemento da stack o respetivo tipo double.
 * @param word O elemento que vai ser transformado num double.
 * @param to O valor do elemento após ter sido transformado no tipo double.
 */
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
/**
 * @brief Função que vai transformar um elemento na stack no tipo char.
 * Esta Função vai receber o @param{*stack_element} e vai transformá-lo num char, char este que é devolvido.
 */
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
        default: PANIC("Couldn't convert to long from type %d", (*stack_element).type)
    }
}

static void printf_array(char *str, Stack *array_stack){
    for(int i = 0; i < length(array_stack); i++){
        StackElement array_elem = array_stack->array[i];
        char dest[MAX_CONVERT_TO_STRING_SIZE];
        convert_element_to_string(&array_elem, dest);
        strcat(str, dest);
    }
}

/**
 * @brief Função que vai transformar um elemento na stack no tipo string.
 * Esta Função vai receber o @param{*stack_element} e vai transformá-lo num string, string este que é devolvido.
 */
void convert_element_to_string(StackElement *stack_element, char *dest) {
    switch ((*stack_element).type) {
        case DOUBLE_TYPE:
            sprintf(dest, "%g", (*stack_element).content.double_value);
            return;
        case LONG_TYPE:
            sprintf(dest, "%ld", (*stack_element).content.long_value);
            return;
        case CHAR_TYPE:
            sprintf(dest, "%c", (*stack_element).content.char_value);
            return;
        case STRING_TYPE:
            strcpy(dest, (*stack_element).content.string_value);
            return;
        case ARRAY_TYPE:
            printf_array(dest, (*stack_element).content.array_value);
          return;
        default: PANIC("Couldn't convert to string from type %d", (*stack_element).type)
    }
}

/**
 * @brief Esta função converte o último elemento da stack para o tipo char.
 */
void convert_last_element_to_char(Stack *stack) {
    StackElement stack_element = pop(stack);

    push_char(stack, convert_element_to_char(&stack_element));

    free_element(stack_element);
}
/**
 * @brief Esta função converte o último elemento da stack para o tipo double.
 */
void convert_last_element_to_double(Stack *stack) {
    StackElement stack_element = pop(stack);

    push_double(stack, convert_element_to_double(&stack_element));

    free_element(stack_element);
}
/**
 * @brief Esta função converte o último elemento da stack para o tipo long.
 */
void convert_last_element_to_long(Stack *stack) {
    StackElement stack_element = pop(stack);

    push_long(stack, convert_element_to_long(&stack_element));

    free_element(stack_element);
}
/*
void convert_array_to_string(struct stack list, char x[]){
    for(int i = 0; i < list.capacity; i++){
        char dest[MAX_CONVERT_TO_STRING_SIZE];
        convert_array_to_string(&(list.array[i]), dest);
        if (i == 0){
            strcpy(x, dest);
        } else {
            strcat(x,dest);
        }
    }
}
*/
/**
 * @brief Esta função converte o último elemento da stack para o tipo string.
 */
void convert_last_element_to_string(Stack *stack) {
    StackElement stack_element = pop(stack);

    char x[MAX_CONVERT_TO_STRING_SIZE];

    convert_element_to_string(&stack_element, x); 
    push_string(stack, x);

    free_element(stack_element);
}
