typedef struct stack_entry {
    char* data;
    struct stack_entry* next;
} stack_entry;

typedef struct stack_t {
    stack_entry* head;
    int stackSize;
} stack_t;

stack_t* create_stack(void);

void push(stack_t*, char* value);

char* top(stack_t*);

char* pop(stack_t*);

void clear(stack_t*);

void delete_stack(stack_t**);
