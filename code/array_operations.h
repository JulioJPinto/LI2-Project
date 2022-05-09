#include "stack.h"

/**
 * @brief Tenta dar parse a uma array que está em string no @param{word} e dá push para a stack
 * A função tenta dar parse a @param{word} para o tipo array, caso consiga esta devolve 1
 * e da push ao novo array @param{stack}, levando também em conta o @param{variables}
 * @returns 1 caso a word é uma array, 0 caso contrário
 */
int parse_array(Stack *stack, StackElement *variables, char *word);
/**
 * @brief A Função devolve o tamanho da string/array ou um array com todos os elementos até esta caso seja um long
 * Dependendo do valor de @param{x}, elemento no topo da Stack, está função realizará diferentes operações
 * Caso @param{x} seja do tipo long esta realizará a função create_range_array_operation para este
 * e devolve um array com a range até ao elemento. Caso esta seja do tipo array/string irá devolver
 * o seu tamanho 
 * @param stack A Stack onde vamos buscar os elemento para a função
 */
void size_range_operation(Stack *stack);

/**
 * @brief A função copia a string @param{times} e da push a todas as cópias para a @param{stack}
 */
void repeat_string_operation(Stack *stack);

/**
 * @brief A função copia a string @param{string_element} @param{times} vezes e da push a todas as cópias para a @param{stack}
 * @param stack A Stack onde vamos buscar os elemento para a função e recebe as cópias de @param{string_element}
 */
void repeat_array_operation(Stack *stack);

/**
 * @brief A função da push para @param{stack} de todos os elementos guardados no array @param{element}
 * A função retira do array @param{element} e da push para @param{stack} de todos os elementos encontrados
 * no array
 * @param stack A Stack para onde vamos devolver os elementos do array
 */
void push_all_elements_from_array(Stack *stack);

void separate_string_by_substring_operation(Stack *stack);

void separate_string_by_new_line_operation(Stack *stack);

void separate_string_by_whitespace_operation(Stack *stack);

void take_first_n_elements_from_array_operation(Stack *stack);

void take_first_n_elements_from_string_operation(Stack *stack);

void take_last_n_elements_from_array_operation(Stack *stack);

void take_last_n_elements_from_string_operation(Stack *stack);

void get_element_from_index_array_operation(Stack *stack);

void get_element_from_index_string_operation(Stack *stack);

void remove_first_element_from_array_operation(Stack *stack);

void remove_first_element_from_string_operation(Stack *stack);

void remove_last_element_from_array_operation(Stack *stack);

void remove_last_element_from_string_operation(Stack *stack);

