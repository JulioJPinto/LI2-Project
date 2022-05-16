#include "stack.h"

#define MAX_CONVERT_TO_STRING_SIZE 100


/**
 * @brief Tenta converter a string num inteiro e coloca-o no @param[to}. @returns retorna 1 se conseguiu converter 0 caso contrario
 * @param word O elemento que vai ser transformado num inteiro
 * @param to Resultado da função
 */
int parse_long(char word[], long *to);

/**
 * @brief Tenta converter a string num double e coloca-o no @param[to}. @returns retorna 1 se conseguiu converter 0 caso contrario
 * @param word O elemento que vai ser transformado num double
 * @param to Resultado da função
 */
int parse_double(char word[], double *to);

/**
* @brief Converte o topo da stack para caractere
* @param stack target
*/
void convert_last_element_to_char(Stack *stack);

/**
* @brief Converte o topo da stack num double
* @param stack target
*/
void convert_last_element_to_double(Stack *stack);

/**
* @brief Converte o topo da stack num inteiro
* @param stack target
*/
void convert_last_element_to_long(Stack *stack);

/**
* @brief Executa a conversão do topo da stack para string
* @param stack target
*/
void convert_last_element_to_string(Stack *stack);

/**
* @brief Converte um elemento da stack numa string
* @param stack target
*/
void convert_element_to_string(StackElement *stack_element, char *dest);

/**
 * @brief Converte um elemento da stack no tipo char.
 * @param stack_element target
 */
char convert_element_to_char(StackElement *stack_element);
