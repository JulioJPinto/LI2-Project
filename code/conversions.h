#include "stack.h"

int parse_long(char word[], long *to);

int parse_double(char word[], double *to);

void convert_last_element_to_char(Stack *stack);

void convert_last_element_to_double(Stack *stack);

void convert_last_element_to_long(Stack *stack);

void convert_last_element_to_string(Stack *stack);
