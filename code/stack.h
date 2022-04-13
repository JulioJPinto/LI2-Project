#pragma once

typedef enum {
    DOUBLE_TYPE, LONG_TYPE, CHAR_TYPE
} ElementType;

typedef struct {
    ElementType type;
    union {
        double double_value;
        long long_value;
        char char_value;
    } content;
} StackElement;

typedef struct {
    int capacity;
    int current_index;
    StackElement *array;
} Stack;

/**
 * Cria e aloca uma stack na memória
 * @param initial_capacity capacidade incial
 * @return Um pointer para a stack
 */
Stack *create_stack(int initial_capacity);

/**
 * Libera a memória ocupada pela stack
 * @param stack
 */
void free_stack(Stack *stack);

/**
 * Faz print do conteúdo do stack conforme o tipo dos elementos
 * @param stack
 */
void dump_stack(Stack *stack);

/**
 * Calcula o tamanho do stack
 * @param stack target
 * @return tamanho
 */
int length(Stack *stack);

/**
 * Remove e retorna o último elemento adicionado à stack
 * @param stack target
 * @return O elemento da stack
 */
StackElement pop(Stack *stack);

/**
 * Faz pop da stack e converte o valor para long
 * @param stack target
 * @return O valor do long
 */
long pop_long(Stack *stack);

/**
 * Faz push a um StackElement para a @param{stack}
 * @param stack target
 * @param x StackElement para adicionar
 */
void push(Stack *stack, StackElement x);

/**
 * Faz push de um double para a @param{stack}
 * @param stack target
 * @param value valor double
 */
void push_double(Stack *stack, double value);

/**
 * Faz push de um long para a @param{stack}
 * @param stack target
 * @param value valor long
 */
void push_long(Stack *stack, long value);

/**
 * Faz push de um char para a @param{stack}
 * @param stack target
 * @param value valor char
 */
void push_char(Stack *stack, char value);

/**
 * @param stack target
 * @return O ultimo elemento adicionado à stack sem o remover
 */
StackElement peek(Stack *stack);

/**
 * Retorna o elemento da stack que está no indice @param{index}
 * O indice 0 é o ultimo elemento adicionado.
 * @param stack target
 * @param index indice
 * @return O elemento do indice
 */
StackElement get(Stack *stack, long index);

/**
 * Cria um elemento do tipo double.
 * @param value double
 * @return O elemento criado
 */
StackElement create_double_element(double value);

/**
 * Cria um elemento do tipo long.
 * @param value long
 * @return O elemento criado
 */
StackElement create_long_element(long value);

/**
 * Cria um elemento do tipo char.
 * @param value char
 * @return O elemento criado
 */
StackElement create_char_element(char value);
