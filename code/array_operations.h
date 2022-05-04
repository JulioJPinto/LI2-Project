#include "stack.h"

/**
 * @brief Tenta dar parse a uma array que está em string no @param{word} e dá push para a stack
 * @returns 1 caso a word é uma array, 0 caso contrário
 */
int parse_array(Stack *stack, StackElement *variables, char *word);

void size_range_operation(Stack *stack);

void concat_x_times_string_or_array(Stack *stack);
