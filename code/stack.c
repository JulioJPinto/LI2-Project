#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "logger.h"

Stack *create_stack(int initial_capacity) {
    Stack *stack = malloc(sizeof(Stack));

    stack->capacity = initial_capacity;
    stack->current_index = -1;
    stack->array = calloc((unsigned long) initial_capacity, sizeof(StackElement));

    return stack;
}

void free_stack(Stack *stack) {
    if (stack != NULL) {
        free(stack);
    }
}

void dump_stack(Stack *stack) {
    for (int i = 0; i < length(stack); ++i) {
        StackElement element = stack->array[i];

        switch (element.type) {
            case LONG_TYPE:
                printf("%ld", element.content.long_value);
                break;
            case CHAR_TYPE:
                printf("%c", element.content.char_value);
                break;
            case DOUBLE_TYPE:
                printf("%g", element.content.double_value);
                break;
            case STRING_TYPE:
                printf("%s", element.content.string_value);
                break;
        }
    }
    printf("\n");
}

int length(Stack *stack) {
    return stack->current_index + 1;
}

StackElement pop(Stack *stack) {
    StackElement result = stack->array[stack->current_index];
    stack->current_index--;

    return result;
}

long pop_long(Stack *stack) {
    return pop(stack).content.long_value;
}

void push(Stack *stack, StackElement x) {
    if (length(stack) >= stack->capacity) {
        stack->capacity *= 2;
        stack->array = realloc(stack, (unsigned long) stack->capacity);
        PRINT_DEBUG("REALLOCATED STACK (new capacity = %d)", stack->capacity)
    }

    stack->array[++(stack->current_index)] = x;
}

void push_double(Stack *stack, double value) {
    push(stack, create_double_element(value));
}

void push_long(Stack *stack, long value) {
    push(stack, create_long_element(value));
}

void push_char(Stack *stack, char value) {
    push(stack, create_char_element(value));
}

void push_string(Stack *stack, char *value) {
    push(stack, create_string_element(value));
}

StackElement create_double_element(double value) {
    StackElement element;
    element.type = DOUBLE_TYPE;
    element.content.double_value = value;

    return element;
}

StackElement create_long_element(long value) {
    StackElement element;
    element.type = LONG_TYPE;
    element.content.long_value = value;

    return element;
}

StackElement create_char_element(char value) {
    StackElement element;
    element.type = CHAR_TYPE;
    element.content.char_value = value;

    return element;
}

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

StackElement get(Stack *stack, long index) {
    return stack->array[stack->current_index - index];
}
