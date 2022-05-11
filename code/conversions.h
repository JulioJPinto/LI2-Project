#include "stack.h"

#define MAX_CONVERT_TO_STRING_SIZE 100

int parse_long(char word[], long *to);

int parse_double(char word[], double *to);

void convert_last_element_to_char(Stack *stack);

void convert_last_element_to_double(Stack *stack);

void convert_last_element_to_long(Stack *stack);

void convert_last_element_to_string(Stack *stack);

void convert_element_to_string(StackElement *stack_element, char *dest);

/**
 * @brief Função que vai transformar um elemento na stack no tipo char.
 * Esta Função vai receber o @param{*stack_element} e vai transformá-lo num char, char este que é devolvido.
 */
char convert_element_to_char(StackElement *stack_element);
