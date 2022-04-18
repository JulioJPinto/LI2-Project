#include "stack.h"

typedef void (*StackOperationFunction)(Stack *);

typedef struct {
    char operator[2];
    StackOperationFunction operation;
} StackOperationTableEntry;

/**
 * \brief Procura a correspondente operação StackOperationFunction do @param{op} operador.
 * Caso o operador não tenha correspondente operação esta devolverá NULL.
 */
StackOperationFunction get_operation(char op[]);
