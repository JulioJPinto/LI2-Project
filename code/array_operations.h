#include "stack.h"

/**
 * @brief Tenta dar parse a uma array que está em string no @param{word} e dá push para a stack
 * @returns 1 caso a word é uma array, 0 caso contrário
 */
int parse_array(Stack *stack, StackElement *variables, char *word);

void size_range_operation(Stack *stack);

/**
 * @brief Operação de repetir string x vezes
 * @param stack target
 */
void repeat_string_operation(Stack *stack);

/**
 * @brief Operação de repetir array x vezes
 * @param stack target
 */
void repeat_array_operation(Stack *stack);

/**
 * @brief Operação de colocar todos os elementos do array na stack
 * @param stack target
 */
void push_all_elements_from_array(Stack *stack);
