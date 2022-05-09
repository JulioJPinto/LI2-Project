#include <string.h>
#include "string_operations.h"

/**
 * @brief Função que recebe a stack e caso encontre '"' insere no @param{*word} a string.
 */
int parse_string(Stack *stack, char *word) {
    size_t word_length = strlen(word);

    if (*word != '"' || word[word_length - 1] != '"') {
        return 0;
    }

    // remover aspas
    word[word_length - 1] = '\0';
    word++;

    push_string(stack, word);

    return 1;
}

/**
 * @brief A função compara duas strings consoante a sua ordem lexicográfica e devolve a diferença entre estas.
 * @param stack A Stack onde vamos buscar os elementos para comparar
 * @return int a diferença entre os valores das strings
 */
int string_compare_base(Stack *stack) {

    StackElement fst_element = pop(stack);
    StackElement snd_element = pop(stack);

    int return_value = strcmp(snd_element.content.string_value, fst_element.content.string_value);

    free_element(fst_element);
    free_element(snd_element);
    
    return return_value;
}

/**
 * @brief Função que compara se duas strings são iguais, caso sejam devolve 1, caso não devolve 0
 * @param stack A Stack onde vamos buscar os elementos para comparar
 */
void string_compare_equal_operation(Stack *stack) {
    int return_value = string_compare_base(stack);

    push_long(stack, return_value == 0);
}
/**
 * @brief Função que compara se a string a esquerda é maior (a nível lexicográfico) que a string a direita, caso seja devolve 1, caso não devolve 0
 * @param stack A Stack onde vamos buscar os elementos para comparar
 */
void string_compare_bigger_operation(Stack *stack) {
    int return_value = string_compare_base(stack);

    push_long(stack, return_value > 0);

}
/**
 * @brief Função que compara se a string a esquerda é menor (a nível lexicográfico) que a string a direita, caso seja devolve 1, caso não devolve 0
 * @param stack A Stack onde vamos buscar os elementos para comparar
 */
void string_compare_smaller_operation(Stack *stack) {
    int return_value = string_compare_base(stack);

    push_long(stack, return_value < 0);
}
/**
 * @brief Função que compara se a string a esquerda é menor (a nível lexicográfico) que a string a direita e devolve a menor das duas
 * @param stack A Stack onde vamos buscar os elementos para comparar
 */
void string_compare_smaller_value_operation(Stack *stack) {
    StackElement fst_element = pop(stack);
    StackElement snd_element = pop(stack);

    int return_value = strcmp(snd_element.content.string_value, fst_element.content.string_value);

    push(stack, return_value < 0 ? fst_element : snd_element);
    return_value < 0 ? free_element(snd_element) : free_element(fst_element);
}

/**
 * @brief Função que compara se a string a esquerda é maior (a nível lexicográfico) que a string a direita e devolve a maior das duas
 * @param stack A Stack onde vamos buscar os elementos para comparar
 */
void string_compare_bigger_value_operation(Stack *stack) {
    StackElement fst_element = pop(stack);
    StackElement snd_element = pop(stack);

    int return_value = strcmp(snd_element.content.string_value, fst_element.content.string_value);

    push(stack, return_value > 0 ? fst_element : snd_element);
    return_value > 0 ? free_element(snd_element) : free_element(fst_element);
}
