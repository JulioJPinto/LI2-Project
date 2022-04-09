typedef enum elementType {LongType, CharType} ElementType;

typedef struct {
    enum elementType type;
    union {
        long long_value;
        char char_value;
    } content;
} StackElement;

typedef struct {
    int capacity;
    int current_index;
    StackElement *array;
} Stack;

Stack *create_stack(int initial_capacity);

void free_stack(Stack *stack);

void dump_stack(Stack *stack);

int length(Stack *stack);

StackElement pop(Stack *stack);

long pop_long(Stack *stack);

void push(Stack *stack, StackElement x);

void push_long(Stack *stack, long value);

StackElement create_long_element(long value);

StackElement create_char_element(char value);