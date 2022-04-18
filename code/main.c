#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "operations.h"
#include "logica.h"
#include "conversions.h"
#include "logger.h"
#include "operations_storage.h"

#define INPUT_BUFFER_SIZE 1000
#define MAX_WORD_SIZE 50
#define INITIAL_STACK_CAPACITY 1000

void parse_input(Stack *stack, const char *input, int input_length);

/**
 * \brief A função que faz a stack funcionar.
 */
int main() {
    char input[INPUT_BUFFER_SIZE];

    if (fgets(input, INPUT_BUFFER_SIZE, stdin) != input) {
        return EXIT_FAILURE;
    }

    int length = (int) strlen(input);

    Stack *stack = create_stack(INITIAL_STACK_CAPACITY);

    parse_input(stack, input, length);

    dump_stack(stack);
    free_stack(stack);

    return 0;
}

/**
 * \brief Dá parse a uma word.
 * Transforma a word no seu devido tipo ou função correspondente.
 */
void parse(Stack *stack, char word[]) {
    PRINT_DEBUG("Parsing: '%s'\n", word)

    long l;
    double d;


    if (parse_long(word, &l)) {
        PRINT_DEBUG("Pushing long: %ld\n", l)
        push_long(stack, l);
        return;
    }

    if (parse_double(word, &d)) {
        PRINT_DEBUG("Pushing double: %g\n", d)
        push_double(stack, d);
        return;

    }
    PRINT_DEBUG("Parsed symbol: %s\n", word)

    StackOperationFunction operation_function = get_operation(word);

    if (operation_function != NULL) {
        operation_function(stack);
    } else {
        PANIC("Couldn't find operator operation_function for %s\n", word)
    }
}

void parse_input(Stack *stack, const char *input, int input_length) {
    char current_word[MAX_WORD_SIZE];
    int current_word_index = 0;

    for (int i = 0; i < input_length; ++i) {
        char current_char = input[i];

        if (current_char != ' ' && current_char != '\0' && current_char != '\n') {
            current_word[current_word_index++] = current_char;
        } else if (current_word_index != 0) {
            current_word[current_word_index] = '\0';
            parse(stack, current_word);
            current_word_index = 0;
        }
    }
}
