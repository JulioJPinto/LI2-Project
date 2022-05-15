#pragma once

#include "stack.h"

/**
 * @brief Função que recebe a stack e caso encontre '"' insere no @param{*word} a string.
 */
int parse_string(Stack *, char *);

/**
 * @brief Função que compara se duas strings são iguais, caso sejam devolve 1, caso não devolve 0
 * @param stack A Stack onde vamos buscar os elementos para comparar
 */
void string_compare_equal_operation(Stack *stack);

/**
 * @brief Função que compara se a string a esquerda é menor (a nível lexicográfico) que a string a direita, caso seja devolve 1, caso não devolve 0
 * @param stack A Stack onde vamos buscar os elementos para comparar
 */
void string_compare_smaller_operation(Stack *stack);

/**
 * @brief Função que compara se a string a esquerda é maior (a nível lexicográfico) que a string a direita, caso seja devolve 1, caso não devolve 0
 * @param stack A Stack onde vamos buscar os elementos para comparar
 */
void string_compare_bigger_operation(Stack *stack);

/**
 * @brief Função que compara se a string a esquerda é menor (a nível lexicográfico) que a string a direita e devolve a menor das duas
 * @param stack A Stack onde vamos buscar os elementos para comparar
 */
void string_compare_smaller_value_operation(Stack *stack);

/**
 * @brief Função que compara se a string a esquerda é maior (a nível lexicográfico) que a string a direita e devolve a maior das duas
 * @param stack A Stack onde vamos buscar os elementos para comparar
 */
void string_compare_bigger_value_operation(Stack *stack);


void search_substring_in_string_operation(Stack *stack);
