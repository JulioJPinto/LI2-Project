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

void remove_first_from_array(Stack *stack);

void remove_last_from_array(Stack *stack);

int search_substring (Stack *stack, char *string, char *result, char *x);

void separate_string_by_substrings (Stack *stack, int v[]);

void separate_string_by_whitespaces (Stack *stack, int v[]);

void separate_string_by_newlines (Stack *stack, int v[]);

int elems_inicio (Stack *stack, int v[], int N, int x);

int elems_fim (Stack *stack, int v[], int N, int x);

void elem_indice (Stack *stack, StackElement v[], int N, int x);


