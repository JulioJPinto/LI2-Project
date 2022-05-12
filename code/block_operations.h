#pragma once

#include "stack.h"

int try_to_parse_block(Stack *stack, char *word);

StackElement execute_block(StackElement target_element, StackElement block_element, StackElement *variables);

void execute_block_operation(Stack *stack);

void map_block_array_operation(Stack *stack);
