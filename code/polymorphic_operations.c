#include "polymorphic_operations.h"
#include "operations.h"
#include "array_operations.h"

void plus_operation(Stack *stack) {
    ElementType type = get_last_element_type(stack);

    if (type == ARRAY_TYPE) {
        // TODO: meter aqui função de concatenar arrays
    } else {
        add_operation(stack);
    }
}

void asterisk_operation(Stack *stack) {
    ElementType left_element_type = get(stack, 1).type;

    if (left_element_type == ARRAY_TYPE) {
        repeat_array_operation(stack);
    } else if(left_element_type == STRING_TYPE) {
        repeat_string_operation(stack);
    } else {
        mult_operation(stack);
    }
}
