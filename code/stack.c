#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logger.h"
#include "variable_operations.h"

#define VARIABLE_COUNT 26

void init_variables(Stack *stack) {
    set_long_variable(stack, 'A', 10);
    set_long_variable(stack, 'B', 11);
    set_long_variable(stack, 'C', 12);
    set_long_variable(stack, 'D', 13);
    set_long_variable(stack, 'E', 14);
    set_long_variable(stack, 'F', 15);
    set_char_variable(stack, 'N', '\n');
    set_char_variable(stack, 'S', ' ');
    set_long_variable(stack, 'X', 0);
    set_long_variable(stack, 'Y', 1);
    set_long_variable(stack, 'Z', 2);
}

/**
 * @brief Create a stack object
 * @param initial_capacity capacidade inicial da stack
 * @return Pointer para a stack criada
 */
Stack *create_stack(int initial_capacity) {
    Stack *stack = malloc(sizeof(Stack));

    stack->capacity = initial_capacity;
    stack->current_index = -1;
    stack->array = calloc((unsigned long) initial_capacity, sizeof(StackElement));

    stack->variables = calloc(VARIABLE_COUNT, sizeof(StackElement));

    init_variables(stack);

    return stack;
}

/**
 * @brief Dá free à memória alocada pela stack
 * @param stack target
 */
void free_stack(Stack *stack) {
    free(stack->array);
    free(stack->variables);
    free(stack);
}

void dump_element(StackElement *element) {
    switch ((*element).type) {
        case LONG_TYPE:
            printf("%ld", (*element).content.long_value);
            return;
        case CHAR_TYPE:
            printf("%c", (*element).content.char_value);
            return;
        case DOUBLE_TYPE:
            printf("%g", (*element).content.double_value);
            return;
        case STRING_TYPE:
            printf("%s", (*element).content.string_value);
            return;
        default: PANIC("Couldn't match type for %c when dumping\n", (*element).content.char_value)
    }
}

/**
 * @brief Imprime todos os valores da stack
 * @param stack target
 */
void dump_stack(Stack *stack) {
    for (int i = 0; i < length(stack); ++i) {
        dump_element(&stack->array[i]);
    }
    printf("\n");
}

/**
 * @brief Devolve o tamanho da stack.
 * @param stack target
 * @return tamanho da stack
 */
int length(Stack *stack) {
    return stack->current_index + 1;
}

/**
 * @brief Retira o elemento que se encontra no topo da stack
 * @param stack target
 * @return StackElement 
 */
StackElement pop(Stack *stack) {
    StackElement result = stack->array[stack->current_index];
    stack->current_index--;

    return result;
}

/**
 * @brief Retira o elemento que se encontra no topo da stack e acessa o valor long dele
 * @param stack target
 * @return valor long acessado
 */
long pop_long(Stack *stack) {
    return pop(stack).content.long_value;
}

/**
 * @brief Põem no topo da stack o elemento da x
 * @param stack target
 * @param x O elemento que vamos inserir no topo da stack
 */
void push(Stack *stack, StackElement x) {
    if (length(stack) >= stack->capacity) {
        stack->capacity *= 2;
        stack->array = realloc(stack, (unsigned long) stack->capacity);
        PRINT_DEBUG("REALLOCATED STACK (new capacity = %d)", stack->capacity)
    }

    stack->array[++(stack->current_index)] = x;
}

/**
 * @brief Push para tipos double
 */
void push_double(Stack *stack, double value) {
    push(stack, create_double_element(value));
}

/**
 * @brief Push para tipos long
 */
void push_long(Stack *stack, long value) {
    push(stack, create_long_element(value));
}

/**
 * @brief Push para tipos char
 */
void push_char(Stack *stack, char value) {
    push(stack, create_char_element(value));
}

void push_string(Stack *stack, char *value) {
    push(stack, create_string_element(value));
}

/**
 * @brief Cria um elemento do tipo double
 * @param value o valor do elemento
 * @return StackElement criado
 */
StackElement create_double_element(double value) {
    StackElement element;
    element.type = DOUBLE_TYPE;
    element.content.double_value = value;

    return element;
}

/**
 * @brief Cria um elemento do tipo long
 * @param value o valor do elemento
 * @return StackElement criado
 */
StackElement create_long_element(long value) {
    StackElement element;
    element.type = LONG_TYPE;
    element.content.long_value = value;

    return element;
}

/**
 * @brief Cria um elemento do tipo cbar
 * @param value o valor do elemento
 * @return StackElement criado
 */
StackElement create_char_element(char value) {
    StackElement element;
    element.type = CHAR_TYPE;
    element.content.char_value = value;

    return element;
}

/**
 * @brief Cria um elemento do tipo string
 * @param value o valor do elemento
 * @return StackElement criado
 */
StackElement create_string_element(char *value) {
    StackElement element;
    element.type = STRING_TYPE;

    unsigned long length = strlen(value) + 1;
    char *copied_string = calloc(length, sizeof(char));
    strcpy(copied_string, value);

    element.content.string_value = copied_string;

    return element;
}

StackElement peek(Stack *stack) {
    return stack->array[stack->current_index];
}

/**
 * @brief 
 * @param stack 
 * @param index 
 * @return StackElement 
 */
StackElement get(Stack *stack, long index) {
    return stack->array[stack->current_index - index];
}

int is_truthy(StackElement *a) {
    switch (a->type) {
        case LONG_TYPE:
            return a->content.long_value != 0;
        case CHAR_TYPE:
            return a->content.char_value != '\0';
        case STRING_TYPE:
            return strlen(a->content.string_value) != 0;
        case DOUBLE_TYPE:
            return a->content.double_value != .0;
        default: PANIC("Couldn't retrieve truthy value from type %d\n", a->type)
    }
}
