#include <ctype.h>
#include <string.h>
#include "parser.h"
#include "logger.h"
#include "conversions.h"
#include "variable_operations.h"
#include "operations_storage.h"
#include "string_operations.h"

enum parseState {
    PARSING_NORMAL_TEXT,
    PARSING_INSIDE_QUOTE,
    PARSING_INSIDE_BRACKETS,
    PARSING_INSIDE_CURLY_BRACKETS
};

/**
 * @brief Dá parse_word a uma word.
 * Transforma a word no seu devido tipo ou função correspondente.
 */
void parse_word(Stack *stack, StackElement *variables, char word[]) {
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

    if (parse_push_variable(stack, variables, word)) {
        PRINT_DEBUG("Pushing variable '%s'\n", word)
        return;
    }

    if (parse_set_variable(stack, variables, word)) {
        PRINT_DEBUG("Setting variable '%s'\n", word)
        return;
    }

    if (parse_string(stack, word)) {
        PRINT_DEBUG("Pushing string '%s'\n", word + 1)
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

/**
 * @brief 
 */
void tokenize_and_parse(Stack *stack, StackElement *variables, char *input) {
    enum parseState state = PARSING_NORMAL_TEXT;

    size_t input_length = strlen(input);

    char word[input_length];

    int current_word_index = 0;

    int bracket_count = 0;

    for (size_t i = 0; i < input_length; ++i) {
        char current_char = input[i];

        word[current_word_index++] = current_char;

        if (state == PARSING_NORMAL_TEXT) {
            if (isspace(current_char)) {
                word[current_word_index - 1] = '\0';
                current_word_index = 0;

                if (*word) {
                    parse_word(stack, variables, word);
                }
            } else if (current_char == '"') { // iniciar parse_word de string
                state = PARSING_INSIDE_QUOTE;
            } else if (current_char == '[') { // iniciar parse de arrays
                state = PARSING_INSIDE_BRACKETS;
                bracket_count++;
            } else if (current_char == '{') { // iniciar parse de blocos
                state = PARSING_INSIDE_CURLY_BRACKETS;
                bracket_count++;
            }
        } else if (state == PARSING_INSIDE_QUOTE) {
            if (current_char == '"') { // fim do parse_word de string
                state = PARSING_NORMAL_TEXT;
            }
        } else if (state == PARSING_INSIDE_BRACKETS) {
            if (current_char == '[') { // encontrou array dentro de array
                bracket_count++;
            } else if (current_char == ']') { // fechou array
                bracket_count--;
            }

            if (bracket_count <= 0) {
                state = PARSING_NORMAL_TEXT;
            }
        } else /* if (state == PARSING_INSIDE_CURLY_BRACKETS) */ {
            if (current_char == '{') { // encontrou bloco dentro de bloco
                bracket_count++;
            } else if (current_char == '}') { // fechou bloco
                bracket_count--;
            }

            if (bracket_count <= 0) {
                state = PARSING_NORMAL_TEXT;
            }
        }
    }
}
