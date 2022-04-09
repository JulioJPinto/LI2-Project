#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operations.h"
#include "logger.h"

#define INPUT_BUFFER_SIZE 1000
#define MAX_WORD_SIZE 50
#define INITIAL_STACK_CAPACITY 1000

/*
 * Tenta converter uma array de char word[] para *to.
 * Retorna 1 se conseguiu converter, 0 se não.
 */
int parse_number(char word[], long *to) {
    return sscanf(word, "%ld", to) == 1;
}

void (*handle_operation(char operation))(Stack *) {
    switch (operation) {
        case '+':
            return add_operation;
        case '-':
            return minus_operation;
        case '*':
            return mult_operation;
        case '/':
            return div_operation;
        case '(':
            return decrement_operation;
        case ')':
            return increment_operation;
        case '%':
            return modulo_operation;
        case '#':
            return exponential_operation;
        case '&':
            return and_bitwise_operation;
        case '|':
            return or_bitwise_operation;
        case '^':
            return xor_bitwise_operation;
        case '~':
            return not_bitwise_operation;
        case '_':
            return duplicate_operation;
        case ';':
            return pop_operation;
        case '\\':
            return swap_last_two_operation;
        case '@':
            return rotate_last_three_operation;
        case '$':
            return copy_nth_element_operation;
        default:
            return NULL;
    }
}

void parse(Stack *stack, char word[]) {
    PRINT_DEBUG("Parsing: '%s'\n", word);

    long i;
    if (parse_number(word, &i)) {
        PRINT_DEBUG("Pushing number: %ld\n", i);
        push_long(stack, i);
    } else {
        PRINT_DEBUG("Parsed symbol: %s\n", word);

        char function_name = word[0];

        void (*function)(Stack *) = handle_operation(function_name);
        if (function != NULL) {
            function(stack);
        } else {
            PRINT_DEBUG("Couldn't find operator function for %c\n", function_name);
        }
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
