#pragma once

#include "stack.h"

int try_to_parse_block(Stack *stack, char *word);

StackElement execute_block(StackElement target_element, StackElement block_element, StackElement *variables);
