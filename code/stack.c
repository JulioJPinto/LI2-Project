#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logger.h"
/**
 * @brief Create a stack object
 * @param initial_capacity tamanho da string que recebemos
 * @return Stack* Cria uma stack com a capacidade necessária para guardar os conteudos da string
 */
Stack *create_stack(int initial_capacity) {
    Stack *stack = malloc(sizeof(Stack));

    stack->capacity = initial_capacity;
    stack->current_index = -1;
    stack->array = calloc((unsigned long) initial_capacity, sizeof(StackElement));

    return stack;
}
/**
 * @brief Dá free a todos os conteudos da stack.
 * @param stack A stack que contem os valores/operadores.
 */
void free_stack(Stack *stack) {
    if (stack != NULL) {
        free(stack);
    }
}
/**
 * @brief 
 * @param stack A stack que contem os valores/operadores.
 */
void dump_stack(Stack *stack) {
    for (int i = 0; i < length(stack); ++i) {
        StackElement element = stack->array[i];

        switch (element.type) {
            case LONG_TYPE:
                printf("%ld", element.content.long_value);
                break;
            case CHAR_TYPE:
                printf("%c", element.content.char_value);
                break;
            case DOUBLE_TYPE:
                printf("%g", element.content.double_value);
                break;
            case STRING_TYPE:
                printf("%s", element.content.string_value);
                break;
            default:
                fprintf(stderr,"Couldn't match type for %c\n", element.content.char_value);            
        }
    }
    printf("\n");
}
/**
 * @brief 
 * @param stack A stack que contem os valores/operadores.
 * @return int Devolve o tamanho da stack.
 */
int length(Stack *stack) {
    return stack->current_index + 1;
}
/**
 * @brief Dá pop a stack 
 * @param stack A stack que contem os valores/operadores.
 * @return StackElement 
 */
StackElement pop(Stack *stack) {
    StackElement result = stack->array[stack->current_index];
    stack->current_index--;

    return result;
}
/**
 * @brief Retira os elementos que se encontram no topo da stack
 * @param stack A stack que contem os valores/operadores.
 * @return long 
 */
long pop_long(Stack *stack) {
    return pop(stack).content.long_value;
}
/**
 * @brief Põem no topo da stack o elemento da x
 * @param stack A stack que contem os valores/operadores.
 * @param x O elemento que vamos inserir no topo da stack
 */
void push(Stack *stack, StackElement x) {
    if (length(stack) >= stack->capacity) {
        stack->capacity *= 2;
        stack->array = realloc(stack, (unsigned long) stack->capacity);
        PRINT_DEBUG("REALLOCATED STACK (new capacity = %d)", stack->capacity)
    }

    stack->array[++(stack->current_index)] = x;
}
/**
 * @brief Realiza o mesmo que a função push porém para tipos long 
 */

void push_double(Stack *stack, double value) {
    push(stack, create_double_element(value));
}

void push_long(Stack *stack, long value) {
    push(stack, create_long_element(value));
}
/**
 * @brief Realiza o mesmo que a função push porém para tipos char 
 */
void push_char(Stack *stack, char value) {
    push(stack, create_char_element(value));
}
/**
 * @brief Cria um elemento do tipo long consoante o elemento inserido
 * @param value O elemento que será transformado no tipo long
 * @return StackElement O elemento após ser transformdo no tipo long
 */

void push_string(Stack *stack, char *value) {
    push(stack, create_string_element(value));
}

StackElement create_double_element(double value) {
    StackElement element;
    element.type = DOUBLE_TYPE;
    element.content.double_value = value;

    return element;
}

StackElement create_long_element(long value) {
    StackElement element;
    element.type = LONG_TYPE;
    element.content.long_value = value;

    return element;
}
/**
 * @brief Cria um elemento do tipo char consoante o elemento inserido
 * @param value O elemento que será transformado no tipo char
 * @return StackElement O elemento após ser transformdo no tipo char
 */
StackElement create_char_element(char value) {
    StackElement element;
    element.type = CHAR_TYPE;
    element.content.char_value = value;

    return element;
}
/**
 * @brief 
 * @param stack 
 * @return StackElement 
 */

StackElement create_string_element(char *value) {
    StackElement element;
    element.type = STRING_TYPE;

    unsigned long length = strlen(value) + 1;
    char *copied_string = calloc(length, sizeof(char));
    strcpy(copied_string, value);

    element.content.string_value = copied_string;

    return element;
}

StackElement peek(Stack *stack) {
    return stack->array[stack->current_index];
}
/**
 * @brief 
 * @param stack 
 * @param index 
 * @return StackElement 
 */
StackElement get(Stack *stack, long index) {
    return stack->array[stack->current_index - index];
}

int is_truthy(StackElement* a){
    switch (a->type){
        case LONG_TYPE:
            return a->content.long_value != 0;
        case CHAR_TYPE:
            return a->content.char_value != '\0';
        case STRING_TYPE:
            return strlen(a->content.string_value) != 0;
        case DOUBLE_TYPE:
            return a->content.double_value != .0;
        default:
            fprintf(stderr,"Invalid Element Type\n");
            return 0;
    }
}
