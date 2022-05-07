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

    if (times > 0) {
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


void push_all_elements_from_array(Stack *stack) {
    StackElement element = pop(stack);

    Stack *array = element.content.array_value;

    long array_size = length(array);

    for (int i = 0; i < array_size; ++i) {
        push(stack, duplicate_element(array->array[i]));
    }

    free_element(element);
}

long get_index_substring(char *string, const char *substring) {
    char *result = strstr(string, substring);
    if (result == NULL) return -1;

    return result - string;
}

/**
 * @brief Separa uma string por caractere e coloca na stack uma string com esse caractere
 * @param stack target
 * @param string string
 */
static void split_string_by_char(Stack *stack, char *string) {
    while (*string != 0) {
        char *temp_string = strdup(string);
        temp_string[1] = '\0';

        push_string(stack, temp_string);

        free(temp_string);

        string++;
    }
}

/**
 * Separa uma string por delimitador e coloca na stack essa string
 * @param stack stack
 * @param string string
 * @param substring_string substring
 */
static void split_string_by_delimiter(Stack *stack, char *string, const char *substring_string) {
    long substring_length = (long) strlen(substring_string);

    long current_index;
    while ((current_index = get_index_substring(string, substring_string)) != -1) {
        string[current_index] = '\0';
        push_string(stack, string);

        string += current_index + substring_length;
    }

    string[current_index] = '\0';
    push_string(stack, string);
}

void separate_string_by_substring(Stack *stack, const char *substring_string) {
    StackElement target_element = pop(stack);
    char *target_string = target_element.content.string_value;

    Stack *result_array = create_stack(INITIAL_ARRAY_CAPACITY);

    if (*substring_string) {
        split_string_by_delimiter(result_array, target_string, substring_string);
    } else {
        split_string_by_char(result_array, target_string);
    }

    push_array(stack, result_array);
    free_element(target_element);
}

void separate_string_by_substring_operation(Stack *stack) {
    StackElement substring_element = pop(stack);

    separate_string_by_substring(stack, substring_element.content.string_value);

    free_element(substring_element);
}

void separate_string_by_new_line_operation(Stack *stack) {
    separate_string_by_substring(stack, "\n");
}

void separate_string_by_whitespace_operation(Stack *stack) {
    separate_string_by_substring(stack, " ");
}

void take_first_n_elements_from_array(Stack *stack, StackElement *list_element, long x) {
    Stack *new_array = create_stack((int) x);

    for (long int i = x; i < length(list_element->content.array_value); i++) {
        push(new_array, list_element->content.array_value->array[i]);
    }

    push(stack, create_array_element(new_array));
}

void take_first_n_elements_from_string(Stack *stack, StackElement *list_element, long x) {
    int lenght_string = (int) strlen(list_element->content.string_value);
    char old_str[lenght_string + 1];
    strcpy(old_str, list_element->content.string_value);
    char new_str[lenght_string - x + 1];

    for (long int i = x; i < lenght_string; i++) {
        new_str[i - x] = old_str[i];
    }

    push_string(stack, new_str);
}

void take_first_n_elements_operation(Stack *stack) {
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
    StackElement new_array = duplicate_array(*list_element);

    for (int i = 0; i < x; i++) {
        pop(new_array.content.array_value);
    }

    push(stack, new_array);
}

void take_last_n_elements_from_string(Stack *stack, StackElement *list_element, long x) {
    char *string = list_element->content.string_value;

    int string_length = (int) strlen(string);
    char new_str[string_length];
    strcpy(new_str, string);

    new_str[(long) string_length - x] = '\0';

    push_string(stack, new_str);
}

void take_last_n_elements_operation(Stack *stack) {
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

    if (element_type == ARRAY_TYPE) {
        elem_index_array_elements(stack, &element, x);
    } else if (element_type == STRING_TYPE) {
        elem_index_string_elements(stack, &element, x);
    }
}

void remove_first_element_from_array_operation(Stack *stack) {
    StackElement element = pop(stack);
    Stack *old_array = element.content.array_value;

    Stack *new_array = create_stack(length(old_array) - 1);

    StackElement first_element = old_array->array[0];
    for (int i = 1; i < length(old_array); i++) {
        push(new_array, old_array->array[i]);
    }

    push_array(stack, new_array);
    push(stack, first_element);
}

void remove_first_element_from_string_operation(Stack *stack) {
    StackElement element = pop(stack);

    char *string_value = element.content.string_value;

    char first_char = string_value[0];

    string_value++;

    push_string(stack, string_value);
    push_char(stack, first_char);

    free_element(element);
}

void remove_last_element_from_array_operation(Stack *stack) {
    StackElement element = pop(stack);
    StackElement last_element = pop(element.content.array_value);

    push(stack, element);
    push(stack, last_element);
}

void remove_last_element_from_string_operation(Stack *stack) {
    StackElement element = pop(stack);

    char *string_value = element.content.string_value;
    size_t string_length = strlen(string_value);

    if(string_length <= 0) PANIC("Trying to remove last char from empty string")

    char last_element = string_value[string_length - 1];
    string_value[string_length - 1] = '\0';

    push_string(stack, string_value);
    push_char(stack, last_element);

    free_element(element);
}
