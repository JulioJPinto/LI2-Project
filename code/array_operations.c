#include "array_operations.h"

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
    free_element(x);
}

void concat_x_times_string(Stack *stack) {
    StackElement string_element = pop(stack);

    char *result = string_element.content.string_value;

    long times = pop_long(stack);

    for (int i = 0; i < times; ++i) {
        strcat(result, result);
    }

    push_string(stack, result);

    free_element(string_element);
}

void separate_string_by_substrings(Stack *stack) {

}


