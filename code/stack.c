#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

Stack *create_stack(int initial_capacity) {
    Stack *stack = malloc(sizeof(Stack));

    stack->capacity = initial_capacity;
    stack->current_index = -1;
    stack->array = calloc(initial_capacity, sizeof(int));

    return stack;
}

void free_stack(Stack *stack) {
    if (stack != NULL) {
        free(stack);
    }
}

void dump_stack(Stack *stack) {
    printf("Stack content is: ");
    for (int i = 0; i < length(stack); ++i) {
        printf("%d ", i);
    }
    printf("\n");
}

int length(Stack *stack) {
    return stack->current_index + 1;
}

int pop(Stack *stack) {
    int result = stack->array[stack->current_index];
    stack->current_index--;

    return result;
}

void push(Stack *stack, int x) {
    // TODO: resize array if no capacity

    stack->array[stack->current_index++] = x;
}