#include "logger.h"
#include "operations.h"
#include "conversions.h"
#include "stack.h"
#include <math.h>

int look_for_give(StackElement *array){
    int cont = 0;
    for(int i = 0; array != ':'; array++, i++) cont = i;
    return cont;
}

void give_value_to_operation(Stack *stack){
    int idx_op = look_for_give(stack->array);
}