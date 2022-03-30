typedef struct stack {
    int capacity;
    int current_index;
    int *array;
} Stack;

Stack *create_stack(int initial_capacity);

void free_stack(Stack *stack);

void dump_stack(Stack *stack);

int length(Stack *stack);

int pop(Stack *stack);

void push(Stack *stack, int x);