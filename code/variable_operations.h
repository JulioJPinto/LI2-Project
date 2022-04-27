#pragma once

#include "stack.h"

StackElement *create_variable_array();

int parse_push_variable(Stack *stack, StackElement *variables, const char *input);

int parse_set_variable(Stack *stack, StackElement *variables, const char *input);
