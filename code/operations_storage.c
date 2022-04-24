#include "operations_storage.h"
#include "operations.h"
#include "conversions.h"
#include "logica.h"
#include <string.h>

/**
 * \brief Procura a correspondente operação StackOperationFunction do @param{op} operador.
 * Caso o operador não tenha correspondente operação esta devolverá NULL.
 */
StackOperationFunction get_operation(char op[]) {
    static const StackOperationTableEntry entries[] = {
            {"+",  add_operation},
            {"-",  minus_operation},
            {"*",  mult_operation},
            {"/",  div_operation},
            {"%",  modulo_operation},
            {"(",  decrement_operation},
            {")",  increment_operation},
            {"#",  exponential_operation},
            {"&",  and_bitwise_operation},
            {"|",  or_bitwise_operation},
            {"^",  xor_bitwise_operation},
            {"~",  not_bitwise_operation},
            {"_",  duplicate_operation},
            {";",  pop_operation},
            {"\\", swap_last_two_operation},
            {"@",  rotate_last_three_operation},
            {"$",  copy_nth_element_operation},
            {"c",  convert_last_element_to_char},
            {"i",  convert_last_element_to_long},
            {"f",  convert_last_element_to_double},
            {"l",  read_input_from_console_operation},
            {"s",  convert_last_element_to_string},
            {">",  lesser_than_operation},
            {"<",  bigger_than_operation},
            {"=",  is_equal_operation},
            {"e&", and_operation},
            {"e|", or_operation},
            {"e>", lesser_value_operation},
            {"e<", bigger_value_operation},
            {"?",  if_then_else_operation},
            {"!",  not_operation}
    };

    size_t size = sizeof(entries) / sizeof(StackOperationTableEntry);

    for (size_t i = 0; i < size; i++) {
        if (strcmp(entries[i].operator, op) == 0) {
            return entries[i].operation;
        }
    }
    return NULL;
}
