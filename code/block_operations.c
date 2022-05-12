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

void execute_block_operation(Stack *stack) {
    StackElement block_element = pop(stack);
    StackElement target_element = pop(stack);

    // TODO: fix variables
    push(stack, execute_block(target_element, block_element, NULL));
}

void map_block_array_operation(Stack *stack) {
    StackElement block_element = pop(stack);
    StackElement array_element = pop(stack);

    Stack *array_target = array_element.content.array_value;
    int array_target_length = length(array_target);

    Stack *array_result = create_stack(array_target_length);

    for (int i = 0; i < array_target_length; ++i) {
        StackElement result = execute_block(duplicate_element(array_target->array[i]), block_element, NULL);
        push(array_result, result);
    }

    push_array(stack, array_result);

    free_element(block_element);
    free_element(array_element);
}

