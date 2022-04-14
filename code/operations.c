#include "logger.h"
#include "operations.h"
#include <math.h>

/**
 * \brief Nesta função fazemos a soma dos dois números no topo da stack.
 */
void add_operation(Stack *stack) {
    long x = pop_long(stack);
    long y = pop_long(stack);

    push_long(stack, x + y);
}

/**
 * \brief Nesta função fazemos a diferença dos dois ultimos números na stack.
 */
void minus_operation(Stack *stack) {
    long x = pop_long(stack);
    long y = pop_long(stack);

    push_long(stack, y - x);
}

/**
 * \brief Nesta função fazemos o produto dos dois ultimos números na stack.
 */
void mult_operation(Stack *stack) {
    long x = pop_long(stack);
    long y = pop_long(stack);

    push_long(stack, x * y);
}

/**
 * \brief Nesta função fazemos a divisão do número último número da stack pelo penúltimo número da stack.
 */
void div_operation(Stack *stack) {
    long x = pop_long(stack);
    long y = pop_long(stack);

    push_long(stack, y / x);
}

/**
 * \brief Nesta função retiramos ao ultimo número da stack um.
 */
void decrement_operation(Stack *stack) {
    long x = pop_long(stack);

    push_long(stack, x - 1);
}

/**
 * \brief Nesta função adicionamos ao ultimo número da stack um.
 */
void increment_operation(Stack *stack) {
    long x = pop_long(stack);

    push_long(stack, x + 1);
}

/**
 * \brief Nesta função retornamos o módulo do ultimo número da stack.
 */
void modulo_operation(Stack *stack) {
    long x = pop_long(stack);
    long y = pop_long(stack);

    push_long(stack, y % x);
}

/**
 * \brief Nesta função retornamos o módulo do número no topo da stack um.
 */
void exponential_operation(Stack *stack) {
    long x = pop_long(stack);
    long y = pop_long(stack);

    push_long(stack, (long) pow((double) y, (double) x));
}

/**
 * \brief Nesta função devolvemos a disjunção dos dois últimos números da stack.
 */
void and_bitwise_operation(Stack *stack) {
    long x = pop_long(stack);
    long y = pop_long(stack);

    push_long(stack, x & y);
}

/**
 * \brief Nesta função devolvemos a conjunção dos dois últimos números da stack.
 */
void or_bitwise_operation(Stack *stack) {
    long x = pop_long(stack);
    long y = pop_long(stack);

    push_long(stack, x | y);
}

/**
 * \brief Nesta função devolvemos a realizamos o xor dos dois últimos números da stack.
 */
void xor_bitwise_operation(Stack *stack) {
    long x = pop_long(stack);
    long y = pop_long(stack);

    push_long(stack, x ^ y);
}

/**
 * \brief Nesta função devolvemos a negação do número no topo da stack.
 */
void not_bitwise_operation(Stack *stack) {
    long x = pop_long(stack);

    push_long(stack, ~x);
}

/**
 * \brief Nesta função duplicamos o que se encontra na stack.
 */
void duplicate_operation(Stack *stack) {
    push(stack, peek(stack));
}

/**
 * \brief Nesta função retiramos o valor que se encontra no topo da stack da mesma.
 */
void pop_operation(Stack *stack) {
    pop(stack);
}

/**
 * \brief Nesta função trocamos a ordem dos ultimos dois elementos da stack.
 */
void swap_last_two_operation(Stack *stack) {
    StackElement x1 = pop(stack);
    StackElement x2 = pop(stack);

    push(stack, x1);
    push(stack, x2);
}

/**
 * \brief Nesta função trocamos a ordem dos ultimos três elementos da stack.
 */
void rotate_last_three_operation(Stack *stack) {
    StackElement x1 = pop(stack);
    StackElement x2 = pop(stack);
    StackElement x3 = pop(stack);

    push(stack, x2);
    push(stack, x1);
    push(stack, x3);
}
/**
 * \brief Nesta função copiamos o valor da posição n para o topo da stack.
 */
void copy_nth_element_operation(Stack *stack) {
    long index = pop_long(stack);

    push(stack, get(stack, index));
}
/**
 * \brief Nesta função convertemos o ultimo elemento da stack num char.
 */
void convert_last_to_char_operation(Stack *stack) {
    long x = pop_long(stack);

    push(stack, create_char_element((char) x));
}
