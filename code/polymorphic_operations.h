#pragma once

#include "stack.h"

void asterisk_operation(Stack *stack, StackElement *variables);

void tilde_operation(Stack *stack, StackElement *variables);

void lesser_than_symbol_operation(Stack *stack);

void bigger_than_symbol_operation(Stack *stack);

void open_parentheses_operation(Stack *stack);

void close_parentheses_operation(Stack *stack);

void equal_symbol_operation(Stack *stack);

void slash_symbol_operation(Stack *stack);

void hashtag_symbol_operation(Stack *stack);

void parentheses_symbol_operation(Stack *stack, StackElement *variables);

void comma_symbol_operation(Stack *stack, StackElement *variables);

void dollar_symbol_operation(Stack *stack, StackElement *variables);
