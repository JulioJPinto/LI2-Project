#include <ctype.h>
#include <string.h>
#include "parser.h"
#include "logger.h"
#include "conversions.h"
#include "variable_operations.h"
#include "operations_storage.h"
#include "string_operations.h"

/**
 * @brief Dá parse_word a uma word.
 * Transforma a word no seu devido tipo ou função correspondente.
 */

void parse_word(Stack *stack, char word[]) {
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
void tokenize_and_parse(Stack *stack, char *input) {
//    char p[] = " \t\r\n\f\v";
//
//    char *token = strtok(input, p);
//
//    while (token != NULL) {
//        parse_word(stack, token);
//
//        token = strtok(NULL, p);
//    }

    enum parseState {
        PARSING_NORMAL_TEXT,
        PARSING_INSIDE_QUOTE,
        PARSING_INSIDE_BRACKETS,
        PARSING_INSIDE_CURLY_BRACKETS
    };

    enum parseState state = PARSING_NORMAL_TEXT;

    size_t input_length = strlen(input);

    char word[input_length];

    int current_word_index = 0;

    for (size_t i = 0; i < input_length; ++i) {
        char current_char = input[i];

        if (state == PARSING_NORMAL_TEXT) {
            word[current_word_index++] = current_char;
            if (isspace(current_char)) {
                word[current_word_index - 1] = '\0';
                current_word_index = 0;

                if (*word) {
                    parse_word(stack, word);
                }
            } else if (current_char == '"') { // iniciar parse_word de string
                state = PARSING_INSIDE_QUOTE;
            }
        } else if (state == PARSING_INSIDE_QUOTE) {
            if (current_char == '"') { // fim do parse_word de string
                state = PARSING_NORMAL_TEXT;
            }
            word[current_word_index++] = current_char;
        }
    }
}
