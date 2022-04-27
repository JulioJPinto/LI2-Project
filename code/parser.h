#pragma once

#include "stack.h"

void tokenize_and_parse(Stack *stack, StackElement *variables, char *input);

void parse_word(Stack *stack, StackElement *variables, char word[]);
