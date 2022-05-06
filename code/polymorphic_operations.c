#include "polymorphic_operations.h"
#include "operations.h"
#include "logica.h"
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

void tilde_operation(Stack *stack) {
    StackElement element= peek(stack);
    ElementType  element_type =element.type;

    if (element_type == ARRAY_TYPE) {
        push_all_elements_from_array(stack);
    }else {
        not_bitwise_operation(stack);
    }
}

void lesser_symbol_operation(Stack *stack) {
    ElementType left_element_type = get(stack, 1).type;

    if (left_element_type == ARRAY_TYPE || left_element_type == STRING_TYPE) {
        take_first_n_elements_operation(stack);
    } else {
        lesser_than_operation(stack);
    }
}

void bigger_symbol_operation(Stack *stack) {
    ElementType left_element_type = get(stack, 1).type;

    if (left_element_type == ARRAY_TYPE || left_element_type == STRING_TYPE) {
        take_last_n_elements_operation(stack);
    } else {
        bigger_than_operation(stack);
    }
}

void left_parentheses_operation(Stack *stack) {
    ElementType element_type = peek(stack).type;

    if (element_type == ARRAY_TYPE || element_type == STRING_TYPE) {
        remove_first_element_operation(stack);
    } else {
        decrement_operation(stack);
    }
}

void right_parentheses_operation(Stack *stack) {
    ElementType element_type = peek(stack).type;

    if (element_type == ARRAY_TYPE || element_type == STRING_TYPE) {
        remove_last_element_operation(stack);
    } else {
        increment_operation(stack);
    }
}

void equal_symbol_operation(Stack *stack) {
    ElementType left_element_type = get(stack, 1).type;

    if(left_element_type == ARRAY_TYPE || left_element_type == STRING_TYPE ) {
        elem_index_operation(stack);
    } else {
        is_equal_operation(stack);
    }

}
