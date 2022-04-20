#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "operations.h"
#include "logica.h"
#include "conversions.h"
#include "logger.h"
#include "operations_storage.h"
#include "variable_operations.h"

#define INPUT_BUFFER_SIZE 1000
#define MAX_WORD_SIZE 50
#define INITIAL_STACK_CAPACITY 1000

void parse_input(Stack *stack, char *input);

/**
 * \brief A função que faz a stack funcionar.
 */
int main() {
    char input[INPUT_BUFFER_SIZE];

    if (fgets(input, INPUT_BUFFER_SIZE, stdin) != input) {
        return EXIT_FAILURE;
    }

    Stack *stack = create_stack(INITIAL_STACK_CAPACITY);

    parse_input(stack, input);

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

    if (parse_push_variable(stack, word)) {
        PRINT_DEBUG("Pushing variable '%s'\n", word)
        return;
    }

    if (parse_set_variable(stack, word)) {
        PRINT_DEBUG("Setting variable '%s'\n", word)
        return;
    }

    PRINT_DEBUG("Parsed symbol: %s\n", word)

    StackOperationFunction operation_function = get_operation(word);

    if (operation_function != NULL) {
        operation_function(stack);
    } else {
        PANIC("Couldn't find operator operation_function for '%s'\n", word)
    }
}

void parse_input(Stack *stack, char *input) {
    char *token;
    char p[] = " \t\r\n\f\v";

    token = strtok(input, p);

    while (token != NULL) {
        parse(stack, token);

        token = strtok(NULL, p);
    }
}
