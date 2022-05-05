#include "polymorphic_operations.h"
#include "operations.h"
#include "array_operations.h"

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
