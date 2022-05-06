#include "array_operations.h"
#include "parser.h"
#include "logger.h"
#include "stack.h"
#include <string.h>

#define INITIAL_ARRAY_CAPACITY 5
#define MAX_STR_ARRAY 100

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
    int length_array = length(array.content.array_value);

    Stack *new_array = create_stack(length_array - 1);
    for (int i = 0; i < length_array; i++) {
        new_array->array[i] = array.content.array_value->array[i + 1];
    }
    create_array_element(new_array);
    push_array(stack, new_array);

    free_element(array);

}

void remove_last_from_array(Stack *stack){
        StackElement array = pop(stack);

        if (array.type == ARRAY_TYPE) {
            pop(array.content.array_value);
        }
        push (stack,array);
}
/*
int search_substring (Stack *stack, char *string, char *result, char *x) {
    result = strstr(string, x);
    if (result == NULL) return -1;
    int position = *result - *string;
    
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

void separate_string_by_whitespaces (Stack *stack) {
    StackElement str = pop(stack);

    if (str.type == STRING_TYPE) {
        for(int i = 0; str.content.string_value; i++){
            char old_string[MAX_STR_ARRAY];
            strcpy(old_string, str.content.string_value);

        }
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
*/

void take_first_n_elements_from_array(Stack *stack, StackElement *list_element, long x) {
    Stack *new_array = create_stack((int) x);
    
    for(int i = 0; i < x; i++){
        push(new_array, list_element->content.array_value->array[i]);
    }

    free_element(*list_element);
    push(stack, create_array_element(new_array));
}

void take_first_n_elements_from_string(Stack *stack, StackElement *list_element, long x) {
    size_t lenght_string = strlen(list_element->content.string_value);
    char new_str[lenght_string];
    strcpy(new_str, list_element->content.string_value);

    for(size_t i = lenght_string ; i >= (size_t) x; i--) {
        new_str[i] = '\0';
    }

    free_element(*list_element);
    push_string(stack, new_str);
}

void take_first_n_elements_operation(Stack *stack){
    long x = pop_long(stack);
    StackElement element = pop(stack);
    ElementType element_type = element.type;

    if (element_type == ARRAY_TYPE) {
       take_first_n_elements_from_array(stack, &element, x);
   } else if (element_type == STRING_TYPE) {
       take_first_n_elements_from_string(stack, &element, x);
   }
}

void take_last_n_elements_from_array(Stack *stack, StackElement *list_element, long x) {
    Stack *new_array = create_stack((int) x);

    for(size_t i = (size_t) x; i < (size_t) length(list_element->content.array_value); i++) {
        push(new_array, list_element->content.array_value->array[i]);                
    }

    free_element(*list_element);
    push(stack, create_array_element(new_array));
}

void take_last_n_elements_from_string(Stack *stack, StackElement *list_element, long x) {
    size_t lenght_string = strlen(list_element->content.string_value);
    char new_str[lenght_string];
    strcpy(new_str, list_element->content.string_value);

    for(size_t i = 0, j = lenght_string - (size_t) x ; j <= (size_t) x; i++, j++) {
        new_str[i] = new_str[j];
    }

    free_element(*list_element);
    push_string(stack, new_str);
    
}

void take_last_n_elements_operation(Stack *stack){
    long x = pop_long(stack);
    StackElement element = pop(stack);
    ElementType element_type = element.type;

   if (element_type == ARRAY_TYPE) {
       take_last_n_elements_from_array(stack, &element, x);
   } else if (element_type == STRING_TYPE) {
       take_last_n_elements_from_string(stack, &element, x);
   }
}

void elem_index_array_elements(Stack *stack, StackElement *list_element, long x) {
    push(stack, list_element->content.array_value->array[x]);
}

void elem_index_string_elements(Stack *stack, StackElement *list_element, long x) { 
    push_char(stack, list_element->content.string_value[x]);
}

void elem_index_operation(Stack *stack) {
    long x = pop_long(stack);
    StackElement element = pop(stack);
    ElementType element_type = element.type;

    if ( element_type == ARRAY_TYPE) {
        elem_index_array_elements(stack, &element, x);

    } else if (element_type == STRING_TYPE) {
        elem_index_string_elements(stack, &element, x);
    }
}

void remove_first_element_from_array(Stack *stack, StackElement element) {
    Stack *new_array = create_stack(element.content.array_value->capacity);

    for(int i = 1; i < element.content.array_value->capacity; i++){
        push(new_array, element.content.array_value->array[i]);
    }

    free_element(element);
    push(stack, create_array_element(new_array));
    push(stack,element.content.array_value->array[0]);
}

void remove_first_element_from_string(Stack *stack, StackElement element) {
    char new_str[MAX_STR_ARRAY];
    strcpy(new_str,element.content.string_value);

    for(size_t i = 0; i < strlen(new_str); i++) {
        new_str[i] = new_str[i+1];
    }

    free_element(element);
    push_string(stack, new_str);
}

void remove_first_element_operation(Stack *stack){
    StackElement element = pop(stack);
    ElementType element_type = element.type;

    if (element_type == ARRAY_TYPE) {
        remove_first_element_from_array(stack, element);
    } else if (element_type == STRING_TYPE) {
        remove_first_element_from_string(stack, element);
    }

}

void remove_last_element_from_array(Stack *stack, StackElement element) {
    StackElement last_element = pop(element.content.array_value);
    free_element(last_element);

    push_array(stack, element.content.array_value);
}

void remove_last_element_from_string(Stack *stack, StackElement element) {
    char new_string[MAX_STR_ARRAY];
    strcpy(new_string, element.content.string_value);
    size_t lenght_str = strlen(new_string);

    new_string[lenght_str - 1] = '\0';

    free_element(element);
    push_string(stack, new_string);
}


void remove_last_element_operation(Stack *stack) {
    StackElement element = pop(stack);
    ElementType element_type = element.type;

    if (element_type == ARRAY_TYPE) {
        remove_last_element_from_array(stack, element);
    } else if (element_type == STRING_TYPE) {
        remove_last_element_from_string(stack, element);
    }
}
