#include "logger.h"
#include "operations.h"
#include <math.h>
#include <string.h>

#define READ_INPUT_FROM_CONSOLE_MAX_LENGTH 100

void operate_promoting_number_type(Stack *stack,
                                   void (*double_operation_function_pointer)(Stack *, double, double),
                                   void (*long_operation_function_pointer)(Stack *, long, long)) {
    StackElement y = pop(stack);
    StackElement x = pop(stack);

    ElementType x_type = x.type;
    ElementType y_type = y.type;

    if (x_type == DOUBLE_TYPE && y_type == DOUBLE_TYPE) {
        double_operation_function_pointer(stack, x.content.double_value, y.content.double_value);
    } else if (x_type == DOUBLE_TYPE && y_type == LONG_TYPE) {
        double_operation_function_pointer(stack, x.content.double_value, (double) y.content.long_value);
    } else if (x_type == LONG_TYPE && y_type == DOUBLE_TYPE) {
        double_operation_function_pointer(stack, (double) x.content.long_value, y.content.double_value);
    } else if (x_type == LONG_TYPE && y_type == LONG_TYPE) {
        long_operation_function_pointer(stack, x.content.long_value, y.content.long_value);
    } else {
        PANIC("Trying to operate non number elements. (x_type: %d, y_type: %d)", x_type, y_type)
    }
}

void add_double_operation(Stack *stack, double a, double b) {
    push_double(stack, a + b);
}

void add_long_operation(Stack *stack, long a, long b) {
    push_long(stack, a + b);
}

/**
 * \brief Nesta função fazemos a soma dos dois números no topo da stack.
 */
void add_operation(Stack *stack) {
    operate_promoting_number_type(stack, add_double_operation, add_long_operation);
}

void minus_double_operation(Stack *stack, double a, double b) {
    push_double(stack, a - b);
}

void minus_long_operation(Stack *stack, long a, long b) {
    push_long(stack, a - b);
}

/**
 * \brief Nesta função fazemos a diferença dos dois ultimos números na stack.
 */
void minus_operation(Stack *stack) {
    operate_promoting_number_type(stack, minus_double_operation, minus_long_operation);
}

void mult_double_operation(Stack *stack, double a, double b) {
    push_double(stack, a * b);
}

void mult_long_operation(Stack *stack, long a, long b) {
    push_long(stack, a * b);
}

/**
 * \brief Nesta função fazemos o produto dos dois ultimos números na stack.
 */
void mult_operation(Stack *stack) {
    operate_promoting_number_type(stack, mult_double_operation, mult_long_operation);
}

/**
 * \brief Nesta função fazemos a divisão do número último número da stack pelo penúltimo número da stack.
 */
void div_long_operation(Stack *stack, long a, long b) {
    push_long(stack, a / b);
}

void div_double_operation(Stack *stack, double a, double b) {
    push_double(stack, a / b);
}

void div_operation(Stack *stack) {
    operate_promoting_number_type(stack, div_double_operation, div_long_operation);
}

/**
 * \brief Nesta função retiramos ao ultimo número da stack um.
 */
void decrement_operation(Stack *stack) {
    StackElement element = pop(stack);

    if (element.type == DOUBLE_TYPE) {
        push_double(stack, element.content.double_value - 1);
    } else if (element.type == LONG_TYPE) {
        push_long(stack, element.content.long_value - 1);
    } else if (element.type == CHAR_TYPE) {
        push_char(stack, (char) (element.content.char_value - 1));
    } else {
        PANIC("Trying to decrement non number element. (type: %d)", element.type)
    }
}

/**
 * \brief Nesta função adicionamos ao ultimo número da stack um.
 */
void increment_operation(Stack *stack) {
    StackElement element = pop(stack);

    if (element.type == DOUBLE_TYPE) {
        push_double(stack, element.content.double_value + 1);
    } else if (element.type == LONG_TYPE) {
        push_long(stack, element.content.long_value + 1);
    } else if (element.type == CHAR_TYPE) {
        push_char(stack, (char) (element.content.char_value + 1));
    } else {
        PANIC("Trying to increment non number element. (type: %d)", element.type)
    }
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
void exponential_double_operation(Stack *stack, double a, double b) {
    push_double(stack, pow(a, b));
}

void exponential_long_operation(Stack *stack, long a, long b) {
    push_long(stack, (long) pow((double) a, (double) b));
}

void exponential_operation(Stack *stack) {
    operate_promoting_number_type(stack, exponential_double_operation, exponential_long_operation);
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

void read_input_from_console_operation(Stack *stack) {
    char input[READ_INPUT_FROM_CONSOLE_MAX_LENGTH];
    if (fgets(input, READ_INPUT_FROM_CONSOLE_MAX_LENGTH, stdin) == NULL) {
        PANIC("Couldn't read input operation from console: fgets returned null pointer\n")
    }

    // fgets returns string ending in \n\0
    // temos que filtrar o \n
    unsigned long length = strlen(input);
    if (length > 0 && input[length - 1] == '\n') {
        input[--length] = '\0';
    }
    push_string(stack, input);
}
