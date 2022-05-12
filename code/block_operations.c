#include <string.h>
#include "block_operations.h"
#include "logger.h"
#include "parser.h"

int try_to_parse_block(Stack *stack, char *word) {
    size_t word_length = strlen(word);

    if (*word != '{' || word[word_length - 1] != '}') {
        return 0;
    }

    // remover brackets:
    word[word_length - 1] = '\0';
    word++;

    push_block(stack, word);

    return 1;
}

StackElement execute_block(StackElement target_element, StackElement block_element, StackElement *variables) {
    if (block_element.type != BLOCK_TYPE) PANIC("Trying to execute a non-block_element type (%d).", block_element.type)

    Stack *temp_stack = create_stack(10);
    push(temp_stack, target_element);

    PRINT_DEBUG("Starting to execute block {%s}:\n", block_element.content.block_value)
    tokenize_and_parse(temp_stack, variables, block_element.content.block_value);

    if (length(temp_stack) != 1) {
        printf("Temp stack: '");
        dump_stack(temp_stack);
        printf("'\n");
        PANIC("Block execution result ^ is empty or has more than 1 element")
    }

    StackElement result = pop(temp_stack);

    free_stack(temp_stack);

    return result;
}

void execute_block_operation(Stack *stack, StackElement *variables) {
    StackElement block_element = pop(stack);
    StackElement target_element = pop(stack);

    push(stack, execute_block(target_element, block_element, variables));
}

Stack *map_blocks(Stack *array, StackElement block_element, StackElement *variables) {
    int array_target_length = length(array);
    Stack *array_result = create_stack(array_target_length);

    for (int i = 0; i < array_target_length; ++i) {
        StackElement target = duplicate_element(array->array[i]);
        StackElement result = execute_block(target, block_element, variables);
        push(array_result, result);
    }

    return array_result;
}

void map_block_array_operation(Stack *stack, StackElement *variables) {
    StackElement block_element = pop(stack);
    StackElement array_element = pop(stack);

    Stack *array_target = array_element.content.array_value;

    Stack *map_result = map_blocks(array_target, block_element, variables);

    push_array(stack, map_result);

    free_element(block_element);
    free_element(array_element);
}

Stack *create_string_array(char *string) {
    int string_length = (int) strlen(string);
    Stack *result = create_stack(string_length);

    for (int i = 0; i < string_length; ++i) {
        push_char(result, string[i]);
    }

    return result;
}

int compute_string_length_from_stack_string_array(Stack *array) {
    int result = 0;
    for (int i = 0; i < length(array); ++i) {
        StackElement x = array->array[i];
        if (x.type == CHAR_TYPE) {
            result++;
        } else if (x.type == STRING_TYPE) {
            result += (int) strlen(x.content.string_value);
        }
    }
    return result;
}

char *convert_stack_array_to_string(Stack *array) {
    int string_length = compute_string_length_from_stack_string_array(array);
    int array_length = length(array);

    char *result = calloc((size_t) string_length + 1, sizeof(char));

    int current_index = 0;
    for (int i = 0; i < array_length; ++i) {
        StackElement current_element = array->array[i];
        if (current_element.type == CHAR_TYPE) {
            result[current_index] = current_element.content.char_value;
            current_index++;
        } else if (current_element.type == STRING_TYPE) {
            char *current_string = current_element.content.string_value;
            int current_string_length = (int) strlen(current_string);
            for (int j = 0; j < current_string_length; ++j) {
                result[current_index] = current_string[j];
                current_index++;
            }
        } else {
            PANIC("Converting string stack array back to char array contains non string/char element (type: %d).",
                  current_element.type)
        }
    }

    result[current_index] = '\0';

    return result;
}

void map_block_string_operation(Stack *stack, StackElement *variables) {
    StackElement block_element = pop(stack);
    StackElement string_element = pop(stack);

    char *string_target = string_element.content.string_value;

    Stack *string_array = create_string_array(string_target);

    Stack *map_result = map_blocks(string_array, block_element, variables);
    char *string_result = convert_stack_array_to_string(map_result);

    push_string(stack, string_result);

    free(string_result);
    free_stack(map_result);
    free_stack(string_array);
    free_element(block_element);
    free_element(string_element);
}

void filter_block_array_operation(Stack *stack, StackElement *variables) {
    StackElement block_element = pop(stack);
    StackElement array_element = pop(stack);

    Stack *target_array = array_element.content.array_value;
    int array_length = length(target_array);

    Stack *array_result = create_stack(array_length);
    for (int i = 0; i < array_length; ++i) {
        StackElement current_element = duplicate_element(target_array->array[i]);
        StackElement current_element_result = execute_block(current_element, block_element, variables);

        if (is_truthy(&current_element_result)) {
            push(array_result, current_element);
        }

        free_element(current_element_result);
    }

    push_array(stack, array_result);

    free_element(block_element);
    free_element(array_element);
}

void filter_block_string_operation(Stack *stack, StackElement *variables) {
    StackElement block_element = pop(stack);
    StackElement string_element = pop(stack);

    char *target_string = string_element.content.string_value;
    int string_length = (int) strlen(target_string);

    char *string_result = calloc((size_t) string_length + 1, sizeof(char));
    int current_string_result_index = 0;

    for (int i = 0; i < string_length; ++i) {
        char current_char = target_string[i];
        StackElement char_element = create_char_element(current_char);
        StackElement current_element_result = execute_block(char_element, block_element, variables);

        if (is_truthy(&current_element_result)) {
            string_result[current_string_result_index] = current_char;
            current_string_result_index++;
        }

        free_element(char_element);
        free_element(current_element_result);
    }

    push_string(stack, string_result);

    free(string_result);
    free_element(block_element);
    free_element(string_element);
}
