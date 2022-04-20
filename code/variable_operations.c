#include "stack.h"

static int get_variable_index(const char key) {
    return key - 'A';
}

static int is_variable_key(const char variable) {
    return variable >= 'A' && variable <= 'Z';
}

void set_variable_element(Stack *stack, char key, StackElement element) {
    stack->variables[get_variable_index(key)] = element;
}

void set_long_variable(Stack *stack, char key, long value) {
    set_variable_element(stack, key, create_long_element(value));
}

void set_char_variable(Stack *stack, char key, char value) {
    set_variable_element(stack, key, create_char_element(value));
}

StackElement get_variable_value(Stack *stack, char key) {
    return stack->variables[get_variable_index(key)];
}

int parse_push_variable(Stack *stack, const char *input) {
    char variable = input[0];
    if (!is_variable_key(variable)) return 0;

    StackElement element = get_variable_value(stack, variable);
    // TODO: copy string pointer (fazer função de duplicar para elements de pointers)

    push(stack, element);
    return 1;
}

int parse_set_variable(Stack *stack, const char *input) {
    if (input[0] != ':') return 0;
    char variable = input[1];

    if (!is_variable_key(variable)) return 0;

    StackElement element = pop(stack);
    set_variable_element(stack, variable, element);
    // TODO: copy string pointer

    push(stack, element);
    return 1;
}
