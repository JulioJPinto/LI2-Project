#include "logger.h"
#include "operations.h"
#include "conversions.h"
#include "stack.h"
#include <math.h>
#include <string.h>


void lesser_then_long_operation(Stack *stack, long a, long b){
    push_long(stack, a > b ? 1 : 0);
}

void lesser_then_double_operation(Stack *stack, double a, double b){
    push_long(stack, a > b ? 1 : 0);
}

void lesser_then_operation(Stack *stack){
    operate_promoting_number_type( stack, lesser_then_double_operation, lesser_then_long_operation);
}

void bigger_then_long_operation(Stack *stack, long a, long b){
    push_long(stack, a < b ? 1 : 0);
}
void bigger_then_double_operation(Stack *stack, double a, double b){
    push_long(stack, a < b ? 1 : 0);
}

void bigger_then_operation(Stack *stack){
    operate_promoting_number_type( stack, bigger_then_double_operation, bigger_then_long_operation);
}

void equal_long_operation(Stack *stack, long a, long b){
    push_long(stack, a == b ? 1 : 0);
}
void equal_double_operation(Stack *stack, double a, double b){
    push_long(stack, a == b ? 1 : 0);
}

void equal_operation(Stack *stack){
    operate_promoting_number_type( stack, equal_double_operation, equal_long_operation);
}

void e_long_operation(Stack *stack, long a, long b){
    push_long(stack, a && b ? b : 0);
}

void e_double_operation(Stack *stack, double a, double b){
    push_double(stack, a && b ? b : 0);
}

void e_operation(Stack *stack){
    operate_promoting_number_type(stack, e_double_operation, e_long_operation);
}

void ou_long_operation(Stack *stack, long a, long b){
    push_long(stack, a ? a : b);
}

void ou_double_operation(Stack *stack, double a, double b){
    push_double(stack, a ? a : b);
}

void ou_operation(Stack *stack){
    operate_promoting_number_type( stack, ou_double_operation, ou_long_operation);
}

void lesser_value_long_operation(Stack *stack, long a, long b){
    push_long(stack, a > b ? b : a);
}

void lesser_value_double_operation(Stack *stack, double a, double b){
    push_double(stack, a > b ? b : a);
}

void lesser_value_operation(Stack *stack){
    operate_promoting_number_type(stack, lesser_then_double_operation, lesser_then_long_operation);
}

void bigger_value_long_operation(Stack *stack, long a, long b){
    push_long(stack, a < b ? b : a);
}

void bigger_value_double_operation(Stack *stack, double a, double b){
    push_double(stack, a < b ? b : a);
}

void bigger_value_operation(Stack *stack){
    operate_promoting_number_type(stack, bigger_then_double_operation, bigger_then_long_operation);
}

void if_then_else_long_operation(Stack *stack, long a, long b, long c){
    push_long(stack, a ? b : c);
}

void if_then_else_double_operation(Stack *stack, double a, double b, double c){
    
}
