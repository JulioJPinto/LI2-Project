#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_BUFFER_SIZE 100
#define MAX_WORD_SIZE 50

void parse(char word[]) {
    printf("'%s'", word);
}

int main() {
    char input[INPUT_BUFFER_SIZE];

    if (fgets(input, INPUT_BUFFER_SIZE, stdin) != input) {
        return EXIT_FAILURE;
    }

    int length = (int) strlen(input);

    char current_word[MAX_WORD_SIZE];
    int current_word_index = 0;

    for (int i = 0; i < length; ++i) {
        char current_char = input[i];

        if (current_char != ' ' && current_char != '\0' && current_char != '\n') {
            current_word[current_word_index++] = current_char;
        } else if (current_word_index != 0) {
            current_word[current_word_index] = '\0';
            parse(current_word);
            current_word_index = 0;
        }
    }

    return 0;
}
