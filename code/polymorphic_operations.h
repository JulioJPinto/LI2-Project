#pragma once

#include "stack.h"

/**
 * @brief a função verifica o "type" do elemento do @param{stack} a ser tratado para fazer a correspondente operação a esse específico tipo associada ao sinal gráfico asterisco '*'
 * caso o tipo seja "BLOCK_TYPE" realizará a operacão sobre as @param{variables}
 * @param stack, onde vamos buscar o elemento para saber qual o seu tipo
 */
void asterisk_operation(Stack *stack, StackElement *variables);

/**
 * @brief a função verifica o "type" do elemento do @param{stack} a ser tratado para fazer a correspondente operação a esse específico tipo associada ao sinal gráfico til '~'
 * caso o tipo seja "BLOCK_TYPE" realizará a operacão sobre as @param{variables}
 * @param stack, onde vamos buscar o elemento para saber qual o seu tipo
 */
void tilde_operation(Stack *stack, StackElement *variables);

/**
 * @brief a função verifica o "type" do elemento do @param{stack} a ser tratado para fazer a correspondente operação a esse específico tipo associada ao sinal gráfico menor do que '<'
 * @param stack, onde vamos buscar o elemento para saber qual o seu tipo
 */
void lesser_than_symbol_operation(Stack *stack);
/**
 * @brief a função verifica o "type" do elemento do @param{stack} a ser tratado para fazer a correspondente operação a esse específico tipo associada ao sinal gráfico maior do que '>'
 * @param stack, onde vamos buscar o elemento para saber qual o seu tipo
 */
void bigger_than_symbol_operation(Stack *stack);
/**
 * @brief a função verifica o "type" do elemento do @param{stack} a ser tratado para fazer a correspondente operação a esse específico tipo associada ao sinal gráfico percentagem '%',
 * caso o tipo seja "BLOCK_TYPE" realizará a operacão sobre as @param{variables}
 * @param stack, onde vamos buscar o elemento para saber qual o seu tipo
 */
/**
 * @brief a função verifica o "type" do elemento do @param{stack} a ser tratado para fazer a correspondente operação a esse específico tipo associada ao sinal gráfico parênteses do lado esquerdo '('
 * @param stack, onde vamos buscar o elemento para saber qual o seu tipo
 */
void open_parentheses_operation(Stack *stack);

/**
 * @brief a função verifica o "type" do elemento do @param{stack} a ser tratado para fazer a correspondente operação a esse específico tipo associada ao sinal gráfico parênteses do lado direito ')'
 * @param stack, onde vamos buscar o elemento para saber qual o seu tipo
 */
void close_parentheses_operation(Stack *stack);

/**
 * @brief a função verifica o "type" do elemento do @param{stack} a ser tratado para fazer a correspondente operação a esse específico tipo associada ao sinal gráfico igual '='
 * @param stack, onde vamos buscar o elemento para saber qual o seu tipo
 */
void equal_symbol_operation(Stack *stack);

/**
 * @brief a função verifica o "type" do elemento do @param{stack} a ser tratado para fazer a correspondente operação a esse específico tipo associada ao sinal gráfico barra '/'
 * @param stack, onde vamos buscar o elemento para saber qual o seu tipo
 */
void slash_symbol_operation(Stack *stack);

/**
 * @brief a função verifica o "type" do elemento do @param{stack} a ser tratado para fazer a correspondente operação a esse específico tipo associada ao sinal gráfico cardinal '#'
 * @param stack, onde vamos buscar o elemento para saber qual o seu tipo
 */
void hashtag_symbol_operation(Stack *stack);

/**
 * @brief a função verifica o "type" do elemento do @param{stack} a ser tratado para fazer a correspondente operação a esse específico tipo associada ao sinal gráfico percentagem '%'
 * caso o tipo seja "BLOCK_TYPE" realizará a operacão sobre as @param{variables}
 * @param stack, onde vamos buscar o elemento para saber qual o seu tipo
 */
void parentheses_symbol_operation(Stack *stack, StackElement *variables);

/**
 * @brief a função verifica o "type" do elemento do @param{stack} a ser tratado para fazer a correspondente operação a esse específico tipo associada ao sinal gráfico vírgula ','
 * caso o tipo seja "BLOCK_TYPE" realizará a operacão sobre as @param{variables}
 * @param stack, onde vamos buscar o elemento para saber qual o seu tipo
 */
void comma_symbol_operation(Stack *stack, StackElement *variables);

/**
 * @brief a função verifica o "type" do elemento do @param{stack} a ser tratado para fazer a correspondente operação a esse específico tipo associada ao sinal gráfico dólar '$',
 * caso o tipo seja "BLOCK_TYPE" realizará a operacão sobre as @param{variables}
 * @param stack, onde vamos buscar o elemento para saber qual o seu tipo
 */
void dollar_symbol_operation(Stack *stack, StackElement *variables);
