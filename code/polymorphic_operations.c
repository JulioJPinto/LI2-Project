#include "polymorphic_operations.h"
#include "operations.h"

void plus_operation(Stack *stack) {
    ElementType type = get_last_element_type(stack);

    if (type == ARRAY_TYPE) {
        // TODO: meter aqui função de concatenar arrays
    } else {
        add_operation(stack);
    }
}
