#include <stdio.h>
#include "conversions.h"

void convert_last_element_to_char(Stack *stack) {
    StackElement stack_element = pop(stack);

    char x;

    switch (stack_element.type) {
        case LONG_TYPE:
            x = (char) stack_element.content.long_value;
            break;
        case CHAR_TYPE:
            x = stack_element.content.char_value;
            break;
        default:
            fprintf(stderr, "Couldn't convert to char from type %d", stack_element.type);
            return;
    }

    push_char(stack, x);
}
