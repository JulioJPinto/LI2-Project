#pragma once

#include "stack.h"

int try_to_parse_block(Stack *stack, char *word);

Stack *execute_block(StackElement target_element, StackElement block_element, StackElement *variables);

void execute_block_operation(Stack *stack, StackElement *variables);

void map_block_array_operation(Stack *stack, StackElement *variables);

void map_block_string_operation(Stack *stack, StackElement *variables);

void filter_block_array_operation(Stack *stack, StackElement *variables);

void filter_block_string_operation(Stack *stack, StackElement *variables);
