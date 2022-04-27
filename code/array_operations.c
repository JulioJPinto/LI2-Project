#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conversions.h"
#include "logger.h"
#include "operations.h"
#include <math.h>


void size_range_operation(Stack *stack){
    StackElement x = pop(stack);
    ElementType x_type = x.type;

    if (x_type == LONG_TYPE){
        int array[x.content.long_value-1];
        for (int i=0;i!= x.content.long_value; i++){
            array[i]=i;
        }
        //push_array(stack, array);
    }
    //else fazer push do tamanho do array
}

void concat_x_times_string(Stack *stack){
    StackElement y = pop(stack);
    ElementType y_type = y.type;

    StackElement x = pop(stack);
    ElementType x_type = y.type;


}

