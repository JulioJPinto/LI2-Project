#include <string.h>
#include "string_operations.h"

int parse_string(Stack *stack, char *word) {
    size_t word_length = strlen(word);

    if (*word != '"' || word[word_length - 1] != '"') {
        return 0;
    }

    // remover aspas
    word[word_length - 1] = '\0';
    word++;

    push_string(stack, word);

    return 1;
}
