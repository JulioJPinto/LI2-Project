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

    PRINT_DEBUG("Starting to execute block {%s}:", block_element.content.block_value)
    tokenize_and_parse(temp_stack, variables, block_element.content.block_value);

    if (length(temp_stack) == 1) PANIC("Block execution result is empty or has more than 1 element")

    StackElement result = pop(temp_stack);

    free_stack(temp_stack);

    return result;
}
