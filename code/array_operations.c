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

    // remover brackets:
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

void repeat_string_operation(Stack *stack) {
    long times = pop_long(stack);
    StackElement string_element = pop(stack);

    char *from = string_element.content.string_value;
    long from_length = (long) strlen(from);

    char *dest = calloc((unsigned long) (from_length * times), sizeof(char));

    if(times > 0) {
        int i;
        for (i = 0; i < times - 1; ++i) {
            memcpy(dest + i * from_length, from, (unsigned long) from_length);
        }
        memcpy(dest + i * from_length, from, (unsigned long) (from_length + 1));
    }

    push_string(stack, dest);

    free_element(string_element);
    free(dest);
}

void repeat_array_operation(Stack *stack) {
    long times = pop_long(stack) - 1;
    StackElement array_element = pop(stack);

    Stack *array = array_element.content.array_value;

    long array_size = length(array);

    for (int i = 0; i < times; ++i) {
        for (int j = 0; j < array_size; ++j) {
            push(array, duplicate_element(array->array[j]));
        }
    }

    push_array(stack, array);
}


void push_all_elements_from_array(Stack *stack){
    StackElement element = pop(stack);

    Stack *array = element.content.array_value;

    long array_size = length(array);

    for (int i = 0; i < array_size ; ++i) {
        push(stack,duplicate_element(array->array[i]));
    }

    free_element(element);
}

void remove_first_from_array(Stack *stack) {
    StackElement array = pop(stack);
    ElementType array_type = array.type;
    int length_array = length(array.content.array_value);

    for (int i = 0; i < length_array; i++) {
        Stack *new_array = create_stack(length_array - 1);
        new_array->array[i] = array.content.array_value->array[i + 1];
    }
    create_array_element (stack, new_array);
    push_array(stack, new_array);

    free_element(array);

}

void remove_last_from_array(Stack *stack){
        StackElement array = pop(stack);
        ElementType array_type = array.type;

        if (array_type == ARRAY_TYPE) {
            pop(array.content.array_value);
        }
        push (stack,array);
}

int search_substring (Stack *stack, char *string, char *result, char *x) {
    int position;

    result = strstr(string, x);
    if (result == NULL) return -1;
    position = *result - *string;
}

void separate_string_by_substrings (Stack *stack, int v[]) {

}

void separate_string_by_whitespaces (Stack *stack, int v[]) {
    char *buff = v;
    char *word = strtok(buff," ");
    return position;
    int x=0;
    while(word){
        puts(word);
        word = strtok(NULL, " ");
        x++;
    }
}

void separate_string_by_newlines (Stack *stack, int v[]){
    char *buff = v;
    char *word = strtok(buff,"\n");
    return position;
    int x=0;
    while(word){
    puts(word);
    word = strtok(NULL, "\n");
    x++;
    }

}

int elems_inicio (Stack *stack, int v[], int N, int x){
    int i;
    for (i=0; i<x; i++){
        return v[i];
    }
}

int elems_fim (Stack *stack, int v[], int N, int x){
    int i;
    for (i=N; i>x ;i--){
        return v[i];
    }

}

void elem_indice (Stack *stack, StackElement v[], int N, int x) {
        push(stack->array[x]);
}
