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

Stack *execute_block(StackElement target_element, StackElement block_element, StackElement *variables) {
    if (block_element.type != BLOCK_TYPE) PANIC("Trying to execute a non-block_element type (%d).", block_element.type)

    Stack *result_stack = create_stack(10);
    push(result_stack, target_element);

    PRINT_DEBUG("Starting to execute block {%s}:\n", block_element.content.block_value)
    tokenize_and_parse(result_stack, variables, block_element.content.block_value);

    return result_stack;
}

void execute_block_operation(Stack *stack, StackElement *variables) {
    StackElement block_element = pop(stack);
    StackElement target_element = pop(stack);

    Stack *result_stack = execute_block(target_element, block_element, variables);
    push_all(stack, result_stack);

    free_stack(result_stack);
}

Stack *map_blocks(Stack *array, StackElement block_element, StackElement *variables) {
    int array_target_length = length(array);
    Stack *array_result = create_stack(array_target_length);

    for (int i = 0; i < array_target_length; ++i) {
        StackElement target = duplicate_element(array->array[i]);
        Stack *result = execute_block(target, block_element, variables);

        push_all(array_result, result);

        free_stack(result);
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
        Stack *current_element_result = execute_block(current_element, block_element, variables);

        if (length(current_element_result) > 0) {
            StackElement first_element = pop(current_element_result);
            if (is_truthy(&first_element)) {
                push(array_result, current_element);
            }
            free_element(first_element);
        }

        free_stack(current_element_result);
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
        Stack *current_element_result = execute_block(char_element, block_element, variables);

        if (length(current_element_result) > 0) {
            StackElement first_element = pop(current_element_result);
            if (is_truthy(&first_element)) {
                string_result[current_string_result_index] = current_char;
                current_string_result_index++;
            }
            free_element(first_element);
        }

        free_element(char_element);
        free_stack(current_element_result);
    }

    push_string(stack, string_result);

    free(string_result);
    free_element(block_element);
    free_element(string_element);
}

void while_top_truthy_operation(Stack *stack, StackElement *variables) {
    StackElement block_element = pop(stack);
    StackElement element = pop(stack);

    Stack *storage_stack = create_stack(stack->capacity);
    Stack *result_stack = create_stack(stack->capacity);

    int controller = 0;

    for(int i = 0; is_truthy(&element) && length(stack) >= 1; i++) {

        if ( i != 0 ) {
            element = pop(stack);
        }

        StackElement transformed_element = pop(execute_block(element, block_element, variables));
        push(storage_stack, transformed_element);
        
        controller = 1;
        
    }
    for(int i = 0; i < length(storage_stack) + 1; i++) {
        StackElement new_element = pop(storage_stack);
        if (is_truthy(&new_element)) push(result_stack, new_element);        
    }

    if (controller) push_all(stack, result_stack);


    free_element(block_element);
    free_element(element);
    free_stack(storage_stack);
    free_stack(result_stack);
    
}