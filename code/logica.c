#include "logger.h"
#include "operations.h"
#include "conversions.h"
#include "stack.h"
#include <math.h>
#include <string.h>


void lesser_then_long_operation(Stack *stack, long a, long b){
    if (a < b){
        push_long(stack, (long) 1);
    }
    else{
        push_long(stack, (long) 0);
    }
}
void lesser_then_double_operation(Stack *stack, double a, double b){
    if (a < b){
        push_long(stack, (long) 1);
    }
    else{
        push_long(stack, (long) 0);
    }
}

void lesser_then_operation(Stack *stack){
    operate_promoting_number_type( stack, lesser_then_long_operation, lesser_then_double_operation);
}

void bigger_then_long_operation(Stack *stack, long a, long b){
    if (a > b){
        push_long(stack, (long) 1);
    }
    else{
        push_long(stack, (long) 0);
    }
}
void bigger_then_double_operation(Stack *stack, double a, double b){
    if (a > b){
        push_long(stack, (long) 1);
    }
    else{
        push_long(stack, (long) 0);
    }
}

void bigger_then_operation(Stack *stack){
    operate_promoting_number_type( stack, bigger_then_long_operation, bigger_then_double_operation);
}

void equal_long_operation(Stack *stack, long a, long b){
    if (a = b){
        push_long(stack, (long) 1);
    }
    else{
        push_long(stack, (long) 0);
    }
}
void equal_double_operation(Stack *stack, double a, double b){
    if (a = b){
        push_long(stack, (long) 1);
    }
    else{
        push_long(stack, (long) 0);
    }
}

void equal_operation(Stack *stack){
    operate_promoting_number_type( stack, equal_long_operation, equal_double_operation);
}

void e_long_operation(Stack *stack, long a, long b){
    if (a && b){
        push_long(stack, a);
    } else if (a){
        push_long(stack,b);
    } else{
        push_long(stack,a);
    }
}