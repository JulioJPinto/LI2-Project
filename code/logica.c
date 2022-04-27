#include "logger.h"
#include "operations.h"
#include "conversions.h"
#include "stack.h"
#include "logica.h"
/**
 * @brief Função lesser_than_operation para longs.
 */
void lesser_than_long_operation(Stack *stack, long a, long b) {
    push_long(stack, a > b);
}
/**
 * @brief Função lesser_than_operation para doubles.
 */
void lesser_than_double_operation(Stack *stack, double a, double b) {
    push_long(stack, a > b);
}
/**
 * @brief Função que vê se o último valor da stack é maior do que o penúltimo.
 * A Função vê se o último valor da stack é maior que o penúltimo e devolve 1 ou 0 caso este seja verdadeiro ou falso.
 */
void lesser_than_operation(Stack *stack) {
    operate_promoting_number_type(stack, lesser_than_double_operation, lesser_than_long_operation);
}
/**
 * @brief Função bigger_than_operation para doubles.
 */
void bigger_than_long_operation(Stack *stack, long a, long b) {
    push_long(stack, a < b);
}
/**
 * @brief Função bigger_than_operation para doubles.
 */
void bigger_than_double_operation(Stack *stack, double a, double b) {
    push_long(stack, a < b);
}
/**
 * @brief Função que vê se o último valor da stack é menor do que o penúltimo.
 * A Função vê se o último valor da stack é menor que o penúltimo e devolve 1 ou 0 caso este seja verdadeiro ou falso.
 */
void bigger_than_operation(Stack *stack) {
    operate_promoting_number_type(stack, bigger_than_double_operation, bigger_than_long_operation);
}
/**
 * @brief Função is_equal_operation para longs.
 */
void is_equal_long_operation(Stack *stack, long a, long b) {
    push_long(stack, a == b);
}
/**
 * @brief Função is_equal_operation para doubles.
 */
void is_equal_double_operation(Stack *stack, double a, double b) {
    push_long(stack, a == b);
}
/**
 * @brief Função que vê se o último valor da stack é igual ao penúltimo.
 * A Função vê se o último valor da stack é igual ao penúltimo e devolve 1 ou 0 caso este seja verdadeiro ou falso.
 */
void is_equal_operation(Stack *stack) {
    operate_promoting_number_type(stack, is_equal_double_operation, is_equal_long_operation);
}

void and_long_operation(Stack *stack, long a, long b) {
    push_long(stack, a && b ? b : 0);
}
/**
 * @brief 
 */
void and_double_operation(Stack *stack, double a, double b) {
    push_double(stack, a != 0 && b != 0 ? b : 0);
}
/**
 * @brief Função que vê a interseção dos últimos dois valores da stack   
 * A Função que vê se ambos os valores não são do tipo falsy caso nenhum seja devolve o último valor que testa, 
 * caso um destes seja devolve o valor falsy.
 */
void and_operation(Stack *stack) {
    operate_promoting_number_type(stack, and_double_operation, and_long_operation);
}

void or_long_operation(Stack *stack, long a, long b) {
    push_long(stack, a ? a : b);
}

void or_double_operation(Stack *stack, double a, double b) {
    push_double(stack, a != 0 ? a : b);
}

void or_operation(Stack *stack) {
    operate_promoting_number_type(stack, or_double_operation, or_long_operation);
}

void not_operation(Stack *stack) {
    StackElement element = pop(stack);

    int truthy = is_truthy(&element);
    push_long(stack, !truthy);
}

void lesser_value_long_operation(Stack *stack, long a, long b) {
    push_long(stack, a < b ? b : a);
}

void lesser_value_double_operation(Stack *stack, double a, double b) {
    push_double(stack, a < b ? b : a);
}

void lesser_value_operation(Stack *stack) {
    operate_promoting_number_type(stack, lesser_value_double_operation, lesser_value_long_operation);
}

void bigger_value_long_operation(Stack *stack, long a, long b) {
    push_long(stack, a > b ? b : a);
}

void bigger_value_double_operation(Stack *stack, double a, double b) {
    push_double(stack, a > b ? b : a);
}

void bigger_value_operation(Stack *stack) {
    operate_promoting_number_type(stack, bigger_value_double_operation, bigger_value_long_operation);
}

void if_then_else_operation(Stack *stack) {
    StackElement c = pop(stack);
    StackElement b = pop(stack);
    StackElement a = pop(stack);

    int cond = is_truthy(&a);

    push(stack, cond ? b : c);
}
