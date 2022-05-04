#include "array_operations.h"
#include "parser.h"
#include "logger.h"
#include <string.h>

#define INITIAL_ARRAY_CAPACITY 5

int parse_array(Stack *stack, StackElement *variables, char *word) {
    size_t word_length = strlen(word);

    if (*word != '[' || word[word_length - 1] != ']') {
        return 0;
    }

    PRINT_DEBUG("Starting parsing array:\n")

    // remover brackets
    word[word_length - 1] = '\0';
    word++;

    Stack *array = create_stack(INITIAL_ARRAY_CAPACITY);
    tokenize_and_parse(array, variables, word);

    push_array(stack, array);

    return 1;
}

void size_range_operation(Stack *stack) {
    StackElement x = pop(stack);
    ElementType x_type = x.type;
    
    if (x_type == LONG_TYPE) {
        Stack *array = create_stack(INITIAL_ARRAY_CAPACITY);
        for (int i = 0; i < x.content.long_value; i++) {
            push_long(array, (long) i);
        }
        push_array(stack, array);

    } else if(x_type == ARRAY_TYPE) {
        push_long(stack, (long) length(x.content.array_value));

    } else {
        push_long(stack, (long) strlen(x.content.string_value));        
    }
    free_element(x);
}
/*
void concat_x_times_string(Stack *stack) {
    StackElement string_element = pop(stack);

    char *result = string_element.content.string_value;

    long times = pop_long(stack);

    for (int i = 0; i < times; ++i) {
        strcat(result, result);    //se a strcat não resultar para arrays, falta fazer a concatenação para arrays
    }

    push_string(stack, result);

    free_element(string_element);
}
*/

void create_string(Stack *stack) {
    StackElement new_string = pop(stack);

    char *result = new_string.content.string_value;

    push_string(stack, result);

    free_element(new_string);
}

//void create_array(Stack *stack){
//    StackElement new_array = pop(stack);
//
//
//     /* int *result = new_array.content.array_value; fazer array_value
//
//     push_array(stack, result);
//
//    free_element(new_array); */
//}

void concat(Stack *stack) {
    StackElement x = pop(stack);
    StackElement y = pop(stack);

    ElementType x_type = x.type;
    ElementType y_type = y.type;

    if (x_type == STRING_TYPE || y_type == STRING_TYPE) {

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

//void push_elements_array(Stack *stack){
//    StackElement array = pop(stack);
//
//    int elements_array;

    /* elements_array = sizeof(array.content.array_value) / sizeof(array.content.array_value[0]);

    for(int i = 0; i < elements_array; i++){

        push_long(stack, array.content.array_value[i]);
    }

    free_element(array);  */
//}

void get_index(Stack *stack){

    StackElement array = pop(stack);
    StackElement index = pop(stack);

    //push_long(stack, array.content.array_value[index.content.long_value]);

    free_element(array);
    free_element(index);
}



//void separate_string_by_substrings(Stack *stack) {
//
//}


