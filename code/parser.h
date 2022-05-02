#pragma once

#include "stack.h"

void tokenize_and_parse(Stack *stack, StackElement *variables, char *input);

/**
 * @brief Dá parse_word a uma word.
 * Transforma a word no seu devido tipo e coloca-o na stack.
 */
void parse_word(Stack *stack, StackElement *variables, char word[]);
