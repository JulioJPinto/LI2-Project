#include "stack.h"

/**
 * @brief A soma dos dois úlitmos dois valores da stack.
 * @param stack A stack que contem os valores/operadores.
 */
void add_operation(Stack *stack);
/**
 * @brief A diferença dos dois úlitmos dois valores da stack.
 * @param stack A stack que contem os valores/operadores.
 */
void minus_operation(Stack *stack);
/**
 * @brief O produto dos dois úlitmos dois valores da stack.
 * @param stack A stack que contem os valores/operadores.
 */
void mult_operation(Stack *stack);
/**
 * @brief A divisão do úlitmo valor da stack pelo penúltimo valor da stack.
 * @param stack A stack que contem os valores/operadores.
 */
void div_operation(Stack *stack);
/**
 * @brief Retira um ao ultimo valor da stack.
 * @param stack A stack que contem os valores/operadores.
 */
void decrement_operation(Stack *stack);
/**
 * @brief Adiciona um ao ultimo valor da stack.
 * @param stack A stack que contem os valores/operadores.
 */
void increment_operation(Stack *stack);
/**
 * @brief Faz o módulo um ao ultimo valor da stack.
 * @param stack A stack que contem os valores/operadores.
 */
void modulo_operation(Stack *stack);
/**
 * @brief Eleva o úlitmo valor da stack pelo penúltimo valor da stack.
 * @param stack A stack que contem os valores/operadores.
 */
void exponential_operation(Stack *stack);
/**
 * @brief Compara os bits dos últimos dois números da stack e retorna o coincidente a disjunção deste bits
 * @param stack A stack que contem os valores/operadores.
 */
void and_bitwise_operation(Stack *stack);
/**
 * @brief Compara os bits dos últimos dois números da stack e retorna o coincidente a conjunção deste bits
 * @param stack A stack que contem os valores/operadores.
 */
void or_bitwise_operation(Stack *stack);
/**
 * @brief Compara os bits dos últimos dois números da stack e retorna o coincidente a xor (negação da implicação) deste bits
 * @param stack A stack que contem os valores/operadores.
 */
void xor_bitwise_operation(Stack *stack);
/**
 * @brief Analisa os bits do último número da stack e retorna o coincidente a negação deste bits
 * @param stack A stack que contem os valores/operadores.
 */
void not_bitwise_operation(Stack *stack);
/**
 * @brief Duplica os conteudos da stack
 * @param stack A stack que contem os valores/operadores.
 */
void duplicate_operation(Stack *stack);
/**
 * @brief Dá pop aos conteudos no topo da stack
 * Retira os conteudos que se encontram no topo da stack do topo
 * @param stack A stack que contem os valores/operadores.
 */
void pop_operation(Stack *stack);
/**
 * @brief Troca a ordem dos ultimos dois elementos da stack
 * @param stack A stack que contem os valores/operadores.
 */
void swap_last_two_operation(Stack *stack);
/**
 * @brief Troca a ordem dos ultimos tres elementos da stack
 * @param stack A stack que contem os valores/operadores.
 */
void rotate_last_three_operation(Stack *stack);
/**
 * @brief Copia o elemento n da stack e retorna o
 * @param stack A stack que contem os valores/operadores.
 */
void copy_nth_element_operation(Stack *stack);
/**
 * @brief Converte o ultimo elemento da stack para um tipo char
 * @param stack A stack que contem os valores/operadores.
 */
void convert_last_to_char_operation(Stack *stack);
