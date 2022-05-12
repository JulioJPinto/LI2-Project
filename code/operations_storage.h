#include "stack.h"

typedef void (*StackOperationFunction)(Stack *);

typedef void (*StackOperationVariablesFunction)(Stack *, StackElement *);

typedef enum {
    SIMPLE_OPERATION, VARIABLES_OPERATION
} OperationType;

typedef struct {
    OperationType type;
    union {
        StackOperationFunction operation_function;
        StackOperationVariablesFunction variables_operation;
    };
} StackOperation;

typedef struct {
    char operator[5];
    StackOperation operation;
} StackOperationTableEntry;


/**
 * \brief Procura a correspondente operação StackOperation do @param{op} operador.
 * Caso o operador não tenha correspondente operação esta devolverá NULL.
 */
StackOperation get_operation(char op[]);

void execute_operation(StackOperation operation, Stack *stack, StackElement *variables);
