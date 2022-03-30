#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operations.h"

#define INPUT_BUFFER_SIZE 100
#define MAX_WORD_SIZE 50
#define INITIAL_STACK_CAPACITY 100

/*
 * Tenta converter uma array de char word[] para *to.
 * Retorna 1 se conseguiu converter, 0 se não.
 */
int parse_number(char word[], int *to) {
    return sscanf(word, "%d", to) == 1;
}

void (*handle_operation(char operation))(Stack *) {
    switch (operation) {
        case '+':
            return add_operation;
        default:
            return NULL;
    }
}

void parse(Stack *stack, char word[]) {
    printf("Parsing: '%s'\n", word);

    int i;
    if (parse_number(word, &i)) {
        printf("Pushing number: %d\n", i);
        push(stack, i);
    } else {
        printf("Parsed symbol: %s\n", word);

        void (*function)(Stack *) = handle_operation(word[0]);
        function(stack);
    }
}

int main() {
    char input[INPUT_BUFFER_SIZE];

    if (fgets(input, INPUT_BUFFER_SIZE, stdin) != input) {
        return EXIT_FAILURE;
    }

    int length = (int) strlen(input);

    Stack *stack = create_stack(INITIAL_STACK_CAPACITY);

    char current_word[MAX_WORD_SIZE];
    int current_word_index = 0;

    for (int i = 0; i < length; ++i) {
        char current_char = input[i];

        if (current_char != ' ' && current_char != '\0' && current_char != '\n') {
            current_word[current_word_index++] = current_char;
        } else if (current_word_index != 0) {
            current_word[current_word_index] = '\0';
            parse(stack, current_word);
            current_word_index = 0;
        }
    }

    dump_stack(stack);
    free_stack(stack);

    return 0;
}
