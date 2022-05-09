#include "logger.h"
#include "operations.h"
#include "conversions.h"
#include "stack.h"
#include "logica.h"
#include "string_operations.h"
#include "array_operations.h"

/**
 * @brief Função lesser_than_operation para longs.
 */
void bigger_than_long_operation(Stack *stack, long a, long b) {
    push_long(stack, a > b);
}
/**
 * @brief Função lesser_than_operation para doubles.
 */
void bigger_than_double_operation(Stack *stack, double a, double b) {
    push_long(stack, a > b);
}
/**
 * @brief Função que vê se o último valor da stack é maior do que o penúltimo e devolve 1 ou 0 
 * A Função vê se o último valor da stack é maior que o penúltimo e devolve 1 ou 0 caso este seja verdadeiro ou falso.
 */
void bigger_than_operation(Stack *stack) {
    ElementType left_element_type = get(stack, 1).type;
    ElementType element_type = peek(stack).type;

    if (element_type == STRING_TYPE && left_element_type == STRING_TYPE) {
        string_compare_bigger_operation(stack);
    } else {
        operate_promoting_number_type(stack, bigger_than_double_operation, bigger_than_long_operation);
    }
}
/**
 * @brief Função bigger_than_operation para doubles.
 */
void lesser_than_long_operation(Stack *stack, long a, long b) {
    push_long(stack, a < b);
}
/**
 * @brief Função bigger_than_operation para doubles.
 */
void lesser_than_double_operation(Stack *stack, double a, double b) {
    push_long(stack, a < b);
}
/**
 * @brief Função que vê se o último valor da stack é menor do que o penúltimo e devolve 1 ou 0.
 * A Função vê se o último valor da stack é menor que o penúltimo e devolve 1 ou 0 caso este seja verdadeiro ou falso.
 */
void lesser_than_operation(Stack *stack) {
    ElementType left_element_type = get(stack, 1).type;
    ElementType element_type = peek(stack).type;
    
    if (element_type == STRING_TYPE && left_element_type == STRING_TYPE) {
        string_compare_smaller_operation(stack);
    } else {
        operate_promoting_number_type(stack, lesser_than_double_operation, lesser_than_long_operation);
    }
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
 * @brief Função que vê se o último valor da stack é igual ao penúltimo e devolve 1 ou 0.
 * A Função vê se o último valor da stack é igual ao penúltimo e devolve 1 ou 0 caso este seja verdadeiro ou falso.
 */
void is_equal_operation(Stack *stack) {
    ElementType left_element_type = get(stack, 1).type;
    ElementType element_type = peek(stack).type;
    
    if (element_type == STRING_TYPE && left_element_type == STRING_TYPE) {
        string_compare_equal_operation(stack);
    } else {
        operate_promoting_number_type(stack, is_equal_double_operation, is_equal_long_operation);
    }
    
}
/**
 * @brief Função and_operation para longs.
 */
void and_long_operation(Stack *stack, long a, long b) {
    push_long(stack, a && b ? b : 0);
}
/**
 * @brief Função and_operation para doubles.
 */
void and_double_operation(Stack *stack, double a, double b) {
    push_double(stack, a != 0 && b != 0 ? b : 0);
}
/**
 * @brief Função que vê a interseção dos últimos dois valores da stack e devolve 1 ou 0 
 * A Função que vê se ambos os valores não são do tipo falsy caso nenhum seja devolve o último valor que testa, 
 * caso um destes seja devolve o valor falsy.
 */
void and_operation(Stack *stack) {
    operate_promoting_number_type(stack, and_double_operation, and_long_operation);
}
/**
 * @brief Função or_operation para longs.
 */
void or_long_operation(Stack *stack, long a, long b) {
    push_long(stack, a ? a : b);
}
/**
 * @brief Função or_operation para doubles.
 */
void or_double_operation(Stack *stack, double a, double b) {
    push_double(stack, a != 0 ? a : b);
}
/**
 * @brief Função que vê a união dos últimos dois valores da stack 
 * A Função que vê se existe pelo menos um valor do tipo truthy, caso exista devolve o primeiro que se encontra nesse tipo,
 * caso nao exista devolve o valor falsy
 */
void or_operation(Stack *stack) {
    operate_promoting_number_type(stack, or_double_operation, or_long_operation);
}
/**
 * @brief Função que transforma um valor na sua negação.
 * A Função que caso o valor seja truthy devove um falsy, caso este seja falsy devolve um valor qualquer do tipo truthy.
 */
void not_operation(Stack *stack) {
    StackElement element = pop(stack);

    int truthy = is_truthy(&element);
    free_element(element);
    push_long(stack, !truthy);
}
/**
 * @brief Função lesser_value_operation para longs.
 */
void lesser_value_long_operation(Stack *stack, long a, long b) {
    push_long(stack, a < b ? b : a);
}
/**
 * @brief Função lesser_value_operation para doubles.
 */
void lesser_value_double_operation(Stack *stack, double a, double b) {
    push_double(stack, a < b ? b : a);
}
/**
 * @brief Esta função realiza o mesmo que a função lesser_then_operation porém devolve o maior valor.
 * A Função compara os últimos dois elementos que se encontram na stack e devolve o maior deste dois.
 */
void lesser_value_operation(Stack *stack) {
    ElementType left_element_type = get(stack, 1).type;
    ElementType element_type = peek(stack).type;
    
    if (element_type == STRING_TYPE && left_element_type == STRING_TYPE) {
        string_compare_smaller_value_operation(stack);
    } else {
        operate_promoting_number_type(stack, lesser_value_double_operation, lesser_value_long_operation);
    }
}
/**
 * @brief Função bigger_value_operation para longs.
 */
void bigger_value_long_operation(Stack *stack, long a, long b) {
    push_long(stack, a > b ? b : a);
}
/**
 * @brief Função bigger_value_operation para doubles.
 */
void bigger_value_double_operation(Stack *stack, double a, double b) {
    push_double(stack, a > b ? b : a);
}
/**
 * @brief Esta função realiza o mesmo que a função bigger_then_operation porém devolve o maior valor.
 * A Função compara os últimos dois elementos que se encontram na stack e devolve o menor deste dois.
 */
void bigger_value_operation(Stack *stack) {
    ElementType left_element_type = get(stack, 1).type;
    ElementType element_type = peek(stack).type;
    
    if (element_type == STRING_TYPE && left_element_type == STRING_TYPE) {
        string_compare_bigger_value_operation(stack);
    } else {
        operate_promoting_number_type(stack, bigger_value_double_operation, bigger_value_long_operation);
    }
}
/**
 * @brief Esta função dependendo no antepenúltimo elemento da stack ser truthy ou falsy devolve o penúltimo ou último elemento desta.
 * A Função vê se o antepenúltimo elemenento da stack é truthy ou falsy, caso este seja falsy esta vai retornar o último valor da stack,
 * caso este seja truthy esta vai devolver o penúltimo valor da stack.
 */
void if_then_else_operation(Stack *stack) {
    StackElement c = pop(stack);
    StackElement b = pop(stack);
    StackElement a = pop(stack);

    int cond = is_truthy(&a);
    push(stack, cond ? b : c);

    free_element(a);
    free_element(!cond ? b : c);
}
