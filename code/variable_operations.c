#include <stdlib.h>
#include "stack.h"
#include "variable_operations.h"

#define VARIABLE_COUNT 26

static int get_variable_index(const char key) {
    return key - 'A';
}

static int is_variable_key(const char variable) {
    return variable >= 'A' && variable <= 'Z';
}

void set_variable_element(StackElement *variables, char key, StackElement element) {
    variables[get_variable_index(key)] = element;
}

void set_long_variable(StackElement *variables, char key, long value) {
    set_variable_element(variables, key, create_long_element(value));
}

void set_char_variable(StackElement *variables, char key, char value) {
    set_variable_element(variables, key, create_char_element(value));
}

StackElement get_variable_value(StackElement *variables, char key) {
    return variables[get_variable_index(key)];
}

int parse_push_variable(Stack *stack, StackElement *variables, const char *input) {
    char variable = input[0];
    if (!is_variable_key(variable)) return 0;

    StackElement element = get_variable_value(variables, variable);

    push(stack, duplicate_element(element));
    return 1;
}

int parse_set_variable(Stack *stack, StackElement *variables, const char *input) {
    if (input[0] != ':') return 0;
    char variable = input[1];

    if (!is_variable_key(variable)) return 0;

    StackElement element = pop(stack);
    set_variable_element(variables, variable, element);

    push(stack, duplicate_element(element));
    return 1;
}

/**
 * @brief Declaração de variáveis e dos seus respetivos valores por omissão
 * @param stack A Stack onde poderemos encontrar estas variáveis
 */
static void init_variables(StackElement *variables) {
    set_long_variable(variables, 'A', 10);
    set_long_variable(variables, 'B', 11);
    set_long_variable(variables, 'C', 12);
    set_long_variable(variables, 'D', 13);
    set_long_variable(variables, 'E', 14);
    set_long_variable(variables, 'F', 15);
    set_char_variable(variables, 'N', '\n');
    set_char_variable(variables, 'S', ' ');
    set_long_variable(variables, 'X', 0);
    set_long_variable(variables, 'Y', 1);
    set_long_variable(variables, 'Z', 2);
}

StackElement *create_variable_array() {
    StackElement *variables = calloc(VARIABLE_COUNT, sizeof(StackElement));

    init_variables(variables);

    return variables;
}
