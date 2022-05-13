#include "array_operations.h"
#include "parser.h"
#include "logger.h"
#include "stack.h"
#include <string.h>

#define INITIAL_ARRAY_CAPACITY 5

int parse_array(Stack *stack, StackElement *variables, char *word) {
    size_t word_length = strlen(word);

    if (*word != '[' || word[word_length - 1] != ']') {
        return 0;
    }

    PRINT_DEBUG("Starting to parse array:\n")

    // remover brackets:
    word[word_length - 1] = '\0';
    word++;

    Stack *array = create_stack(INITIAL_ARRAY_CAPACITY);
    tokenize_and_parse(array, variables, word);

    push_array(stack, array);

    return 1;
}

/**
 * @brief A Função devolve um array com o range de elementos de 0 a @param{range}
 * A Função recebe um valor @param{range} e devolve num array todos os elementos de 0 a @param{range}
 * Estes valores são todos longs e são postos na stack em forma de array
 * @param stack A Stack para onde vamos devolver o range do elemento
 */
void create_range_array_operation(Stack *stack, long range) {
    Stack *array = create_stack(INITIAL_ARRAY_CAPACITY);
    for (int i = 0; i < range; i++) {
        push_long(array, (long) i);
    }
    push_array(stack, array);
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

void push_all_elements_from_array_operation(Stack *stack) {
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
 * @brief A função separa a string @param{string} em chars e da push para a @param{stack}
 * A função recebes uma stack @param{stack} e uma string @param{string} que vai separar em chars
 * e dar push aos mesmos para a stack 
 * @param stack A stack para onde vamos dar push aos chars que surgem da separação @param{string}
 * @param string A string que vamos separar em chars
 */
static void split_string_char_by_char(Stack *stack, char *string) {
    while (*string != 0) {
        char *temp_string = strdup(string);
        temp_string[1] = '\0';

        push_string(stack, temp_string);

        free(temp_string);

        string++;
    }
}

/**
 * @brief A função separa string @param{string} de acordo com um separador @param{delimiters}
 * A função separa a string @param{string} em substrings de acordo com um separador @param{delimiters} e da 
 * push a estas substrings para a @param{stack}
 * @param stack A stack que vai receber as substrings geradas pela função
 * @param string A string que irá será separada em substrings
 * @param delimiters O elemento que vai funcionar como separador
 */
static void split_string_by_multiple_delimiters(Stack *stack, char *string, const char *delimiters) {
    string = strtok(string, delimiters);
    while (string != NULL) {
        push_string(stack, string);
        string = strtok(NULL, delimiters);
    }
}

/**
 * @brief A função separa string @param{string} de acordo com uma substring que funciona como separador @param{delimeters}
 * A função separa a string @param{string} em substrings de acordo com a substring @param{delimiters} e
 * da push a estas substring, geradas pela @param{string}, para a @param{stack}
 * @param stack A stack que vai receber as substrings geradas pela função
 * @param string A string que irá será separada em substrings
 * @param delimiters O substring que vai funcionar como separador 
 */
static void split_string_by_substring(Stack *stack, char *string, const char *delimiters) {
    long substring_length = (long) strlen(delimiters);

    long current_index;
    while ((current_index = get_index_substring(string, delimiters)) != -1) {
        string[current_index] = '\0';
        push_string(stack, string);

        string += current_index + substring_length;
    }

    if (*string) {
        string[current_index] = '\0';
        push_string(stack, string);
    }
}

/**
 * @brief Separa os caracteres da string do topo da stack conforme a substring recebida e coloca o resultado numa array na stack
 * @param stack target
 * @param substring_string string para dar substring
 * @param multiple_delimiters 1 ou 0 se é para tratar a @param{substring_string} como multiplos delimitadores
 */
void separate_string_by_substring(Stack *stack, const char *substring_string, int multiple_delimiters) {
    StackElement target_element = pop(stack);
    char *target_string = target_element.content.string_value;

    Stack *result_array = create_stack(INITIAL_ARRAY_CAPACITY);

    if (multiple_delimiters) {
        split_string_by_multiple_delimiters(result_array, target_string, substring_string);
    } else if (*substring_string) {
        split_string_by_substring(result_array, target_string, substring_string);
    } else {
        split_string_char_by_char(result_array, target_string);
    }

    push_array(stack, result_array);
    free_element(target_element);
}

void separate_string_by_substring_operation(Stack *stack) {
    StackElement substring_element = pop(stack);

    separate_string_by_substring(stack, substring_element.content.string_value, 0);

    free_element(substring_element);
}

void separate_string_by_new_line_operation(Stack *stack) {
    separate_string_by_substring(stack, "\n", 0);
}

void separate_string_by_whitespace_operation(Stack *stack) {
    separate_string_by_substring(stack, " \n\t\v\f\r", 1);
}

static int min(int a, int b) {
    return a > b ? b : a;
}

void take_first_n_elements_from_array_operation(Stack *stack) {
    int number_of_elements = (int) pop_long(stack);
    StackElement array_element = pop(stack);
    Stack *array = array_element.content.array_value;

    Stack *new_array = create_stack(number_of_elements);
    int new_array_length = min(number_of_elements, length(array));

    for (int i = 0; i < new_array_length; i++) {
        push(new_array, duplicate_element(array->array[i]));
    }

    push(stack, create_array_element(new_array));

    free_element(array_element);
}

void take_first_n_elements_from_string_operation(Stack *stack) {
    long number_of_elements = pop_long(stack);
    StackElement string_element = pop(stack);

    char *string_value = string_element.content.string_value;
    int new_string_length = (int) strnlen(string_value, (size_t) number_of_elements);

    string_value[new_string_length] = '\0';

    push_string(stack, string_value);

    free_element(string_element);
}

void take_last_n_elements_from_array_operation(Stack *stack) {
    long number_of_elements = pop_long(stack);
    StackElement element = pop(stack);

    Stack *old_array = element.content.array_value;
    int old_array_length = length(old_array);

    Stack *new_array = create_stack((int) number_of_elements);

    for (long int i = old_array_length - number_of_elements; i < old_array_length; i++) {
        push(new_array, duplicate_element(old_array->array[i]));
    }

    push(stack, create_array_element(new_array));

    free_element(element);
}

void take_last_n_elements_from_string_operation(Stack *stack) {
    long number_of_elements = pop_long(stack);
    StackElement element = pop(stack);

    char *string = element.content.string_value;
    size_t string_length = strlen(string);

    long string_offset = (long) string_length - number_of_elements;

    if (number_of_elements > 0 && string_offset > 0) {
        string += string_offset;
    }

    push_string(stack, string);

    free_element(element);
}

void get_element_from_index_array_operation(Stack *stack) {
    long index = pop_long(stack);
    StackElement array_element = pop(stack);

    StackElement element_from_index = array_element.content.array_value->array[index];
    push(stack, duplicate_element(element_from_index));

    free_element(array_element);
}

void get_element_from_index_string_operation(Stack *stack) {
    long index = pop_long(stack);
    StackElement string_element = pop(stack);

    char char_from_index = string_element.content.string_value[index];
    push_char(stack, char_from_index);

    free_element(string_element);
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

    if (string_length <= 0) PANIC("Trying to remove last char from empty string")

    char last_element = string_value[string_length - 1];
    string_value[string_length - 1] = '\0';

    push_string(stack, string_value);
    push_char(stack, last_element);

    free_element(element);
}

void search_substring_in_string_operation(Stack *stack) {
    StackElement substring_element = pop(stack);
    StackElement string_element = pop(stack);

    char *string_value = string_element.content.string_value;
    char *substring_string = substring_element.content.string_value;

    long index = get_index_substring(string_value, substring_string);

    push_long(stack, index);

    free_element(substring_element);
    free_element(string_element);
}
