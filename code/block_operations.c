#include <string.h>
#include "block_operations.h"
#include "logger.h"

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
