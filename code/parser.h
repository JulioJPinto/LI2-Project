#pragma once

#include "stack.h"

/**
 * @brief Separa a string de input em espaços, strings, arrays e blocos e executa função parse_word nessa word separada
 * @param stack target
 * @param variables variáveis
 * @param input input bruto
 */
void tokenize_and_parse(Stack *stack, StackElement *variables, char *input);

/**
 * Dá parse_word a uma word.
 * Transforma a word no seu devido tipo e coloca-o na stack.
 * @param stack target
 * @param variables variáveis
 * @param word word para transformar
 */
void parse_word(Stack *stack, StackElement *variables, char word[]);
