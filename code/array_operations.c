#include "array_operations.h"
#include <string.h>

void size_range_operation(Stack *stack) {
    StackElement x = pop(stack);
    ElementType x_type = x.type;

    if (x_type == LONG_TYPE) {
        int array[x.content.long_value - 1];
        for (int i = 0; i != x.content.long_value; i++) {
            array[i] = i;
        }
        //push_array(stack, array);
    }
    //else fazer push do tamanho do array
    free_element(x);
}

void concat_x_times_string(Stack *stack) {
    StackElement string_element = pop(stack);

    char *result = string_element.content.string_value;

    long times = pop_long(stack);

    for (int i = 0; i < times; ++i) {
        strcat(result, result) ;    //se a strcat não resultar para arrays, falta fazer a concatenação para arrays
    }

    push_string(stack, result);

    free_element(string_element);
}

void create_string(Stack *stack){
    StackElement new_string = pop(stack);

    char *result = new_string.content.string_value;

    push_string(stack, result);

    free_element(new_string);
}

void create_array(Stack *stack){
    StackElement new_array = pop(stack);


     /* int *result = new_array.content.array_value; fazer array_value

     push_array(stack, result);

    free_element(new_array); */
}

void concat(Stack *stack){
    StackElement x = pop(stack);
    StackElement y = pop(stack);

    ElementType x_type = x.type;
    ElementType y_type = y.type;

    if ( x_type == STRING_TYPE || y_type == STRING_TYPE){

        char *result = x.content.string_value;
        strcat(result, y.content.string_value);

        push_string(stack, result);

        free_element(x);
        free_element(y);
    }
    /* criar array_value
     * else{
        int elements_array_x,elements_array_y;

        elements_array_x = sizeof(x.content.array_value) / sizeof(x.content.array_value[0]);
        elements_array_y = sizeof(y.content.array_value) / sizeof(y.content.array_value[0]);

        int *result;

        for(int i = 0; i < elements_array_x; i++){

            result[i]= x.content.array_value[i];
        }

        for(int i = elements_array_x; i < elements_array_x + elements_array_y; i++){

            result[i]= y.content.array_value[i];
        }

        push_array(stack, result);

        free_element(x);
        free_element(y);
    }*/
}



void separate_string_by_substrings(Stack *stack) {

}


