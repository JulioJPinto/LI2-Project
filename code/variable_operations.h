#pragma once

#include "stack.h"

void set_long_variable(Stack *stack, char key, long value);

void set_char_variable(Stack *stack, char key, char value);

int parse_push_variable(Stack *stack, const char *input);

int parse_set_variable(Stack *stack, const char *input);
