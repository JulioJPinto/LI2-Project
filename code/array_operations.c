#include "array_operations.h"
#include "parser.h"
#include "logger.h"
#include <string.h>

#define INITIAL_ARRAY_CAPACITY 5

void create_range_array_operation(Stack *stack, long range);

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
        create_range_array_operation(stack, x.content.long_value);
    } else if (x_type == ARRAY_TYPE) {
        push_long(stack, (long) length(x.content.array_value));
    } else if (x_type == STRING_TYPE) {
        push_long(stack, (long) strlen(x.content.string_value));
    }

    free_element(x);
}

void create_range_array_operation(Stack *stack, long range) {
    Stack *array = create_stack(INITIAL_ARRAY_CAPACITY);
    for (int i = 0; i < range; i++) {
        push_long(array, (long) i);
    }
    push_array(stack, array);
}


void concat_x_times_string_or_array(Stack *stack) {
    long times = pop_long(stack);

    StackElement elements = pop(stack);
    ElementType element_type = elements.type;

    if (element_type == STRING_TYPE) {
        char *result = elements.content.string_value;
        char *copy = elements.content.string_value;

        for (int i = 0; i < times; ++i) {

            strcat(result, copy);
        }
        push_string(stack, result);
    }
    else if (element_type == ARRAY_TYPE){
        Stack *array = elements.content.array_value;

        long array_size = length(array);

        for (int i = 0; i < times; ++i) {
            for (int j = 0; j < array_size ; ++j) {
                push(array, duplicate_element(array->array[j]));
            }
        }
        push_array(stack, array);
    }

    free_element(elements);
}


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

void get_index(Stack *stack) {

    StackElement array = pop(stack);
    StackElement index = pop(stack);

    //push_long(stack, array.content.array_value[index.content.long_value]);

    free_element(array);
    free_element(index);
}

void prefix(Stack *stack){

    StackElement element = pop(stack); //string ou array
    StackElement range   = pop(stack); //quantos elementos o prefixo irá ter

    ElementType element_type = element.type;

    if (element_type == STRING_TYPE){

        char result [range.content.long_value];

        for (int i = 0; i < range.content.long_value; i++) {

            result [i] = element.content.string_value [i];
        }

        push_string(stack, result);

        free_element(element);
        free_element( range);

    }

    else {





    }




}




//void separate_string_by_substrings(Stack *stack) {
//
//}


