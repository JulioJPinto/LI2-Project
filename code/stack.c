#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include "logger.h"

Stack *create_stack(int initial_capacity) {
    Stack *stack = malloc(sizeof(Stack));

    stack->capacity = initial_capacity;
    stack->current_index = -1;
    stack->array = calloc(initial_capacity, sizeof(StackElement));

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
            case LongType:
                printf("%ld", element.content.long_value);
                break;
            case CharType:
                printf("%c", element.content.char_value);
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
        stack->array = realloc(stack, stack->capacity);
        PRINT_DEBUG("REALLOCATED STACK (new capacity = %d)", stack->capacity)
    }

    stack->array[++(stack->current_index)] = x;
}

void push_long(Stack *stack, long value) {
    push(stack, create_long_element(value));
}

StackElement create_long_element(long value) {
    StackElement element;
    element.type = LongType;
    element.content.long_value = value;

    return element;
}

StackElement create_char_element(char value) {
    StackElement element;
    element.type = CharType;
    element.content.char_value = value;

    return element;
}

StackElement peek(Stack *stack) {
    return stack->array[stack->current_index];
}
