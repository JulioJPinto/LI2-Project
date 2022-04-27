#pragma once

#include "stack.h"

void tokenize_and_parse(Stack *stack, char *input);

void parse_word(Stack *stack, char word[]);
