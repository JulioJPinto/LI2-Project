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

void take_first_n_elements_from_array(Stack *stack, StackElement *list_element, size_t x) {
    Stack *new_array = create_stack((int) x);
    
    for(size_t i = x; i < (size_t) length(list_element->content.array_value); i++){
        push(new_array, list_element->content.array_value->array[i]);
    }

    push(stack, create_array_element(new_array));
    free_element(*list_element);
}

void take_first_n_elements_from_string(Stack *stack, StackElement *list_element, size_t x) {
    size_t lenght_string = strlen(list_element->content.string_value);
    char old_str[lenght_string+1];
    strcpy(old_str, list_element->content.string_value);
    char new_str[lenght_string - x+1];

    for(size_t i = x; i < lenght_string; i++){
        new_str[i - x] = old_str[i];
    }

    push_string(stack, new_str);
    free_element(*list_element);
}

void take_first_n_elements_operation(Stack *stack){
    long x = pop_long(stack);
    StackElement element = pop(stack);
    ElementType element_type = element.type;

    if (element_type == ARRAY_TYPE) {
       take_first_n_elements_from_array(stack, &element, (size_t) x);
   } else if (element_type == STRING_TYPE) {
       take_first_n_elements_from_string(stack, &element, (size_t) x);
   }
}

void take_last_n_elements_from_array(Stack *stack, StackElement *list_element, size_t x) {
    StackElement new_array = duplicate_array(*list_element);

    for(size_t i = 0; i < x; i++) {
        pop(new_array.content.array_value);
    }

    push(stack, new_array);
    free_element(*list_element);
}

void take_last_n_elements_from_string(Stack *stack, StackElement *list_element, size_t x) {
    size_t lenght_string = strlen(list_element->content.string_value);
    char new_str[lenght_string];
    strcpy(new_str, list_element->content.string_value);

    new_str[lenght_string - (size_t) x] = '\0';

    push_string(stack, new_str);
    free_element(*list_element); 
}

void take_last_n_elements_operation(Stack *stack){
    long x = pop_long(stack);
    StackElement element = pop(stack);
    ElementType element_type = element.type;

   if (element_type == ARRAY_TYPE) {
       take_last_n_elements_from_array(stack, &element, (size_t) x);
   } else if (element_type == STRING_TYPE) {
       take_last_n_elements_from_string(stack, &element, (size_t) x);
   }
}

void elem_index_array_elements(Stack *stack, StackElement *list_element, long x) {
    push(stack, list_element->content.array_value->array[x]);
    free_element(*list_element);
}

void elem_index_string_elements(Stack *stack, StackElement *list_element, long x) { 
    push_char(stack, list_element->content.string_value[x]);
    free_element(*list_element);
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

void remove_first_element_from_array(Stack *stack, StackElement *element) {
    Stack *old_array = element->content.array_value;
    Stack *new_array = create_stack(length(old_array));

    StackElement first_element = old_array->array[0];
    for(int i = 1; i < length(old_array); i++) {
        push(new_array, old_array->array[i]);
    }

    push_array(stack, new_array);
    push(stack, first_element);
    free_element(*element);
}
    

void remove_first_element_from_string(Stack *stack, StackElement *element) {
    char new_str[MAX_STR_ARRAY];
    strcpy(new_str, element->content.string_value);

    char aux = new_str[0];

    for(size_t i = 0; i < strlen(new_str); i++){
        new_str[i] = new_str[i+1];
    }

    push_string(stack, new_str);
    push_char(stack, aux);
    free_element(*element);
}


void remove_first_element_operation(Stack *stack){
    StackElement element = pop(stack);
    ElementType element_type = element.type;

    if (element_type == ARRAY_TYPE) {
        remove_first_element_from_array(stack, &element);
    } else if (element_type == STRING_TYPE) {
        remove_first_element_from_string(stack, &element);
    }

}

void remove_last_element_from_array(Stack *stack, StackElement *element) {
    StackElement last_element = pop(element->content.array_value);

    push(stack, *element);
    push(stack, last_element);

}


void remove_last_element_from_string(Stack *stack, StackElement *element) {
    char new_str[MAX_STR_ARRAY];
    size_t length_str = strlen(element->content.string_value);
    strcpy(new_str, element->content.string_value);

    char last_element = new_str[length_str - 1];
    new_str[length_str - 1] = '\0';

    push_string(stack, new_str);
    push_char(stack, last_element);
    free_element(*element);

}


void remove_last_element_operation(Stack *stack) {
    StackElement element = pop(stack);
    ElementType element_type = element.type;

    if (element_type == ARRAY_TYPE) {
        remove_last_element_from_array(stack, &element);
    } else if (element_type == STRING_TYPE) {
        remove_last_element_from_string(stack, &element);
    }
 
}
