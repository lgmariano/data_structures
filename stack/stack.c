#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    struct node *next;
    void *data;
};

struct stack {
    struct node *top;
    unsigned int size;
    unsigned int data_size;
};

/**
 * Initializes a stack
 * @brief Initializes a stack
 * @param st -> stack object memory address
 * @param d_size -> data size (bytes) that each stack node will contain
 */

void stack_init(struct stack *st, int d_size)
{
    st->top = NULL;
    st->size = 0;
    st->data_size = d_size;
}

/**
 * 
 */

void stack_destroy(struct stack *st)
{
    struct node *aux = NULL;
    
    if (!st)
        return;
    
    aux = st->top;
    while (aux) {
        st->top = st->top->next;
    
        free(aux->data);
        free(aux);
        aux = st->top;
    }

    st->top = NULL;
    st->size = 0;
    st->data_size = 0;
}

/**
 * 
 */

int stack_push(struct stack *st, const void *data)
{
    struct node *aux = NULL;
    
    if (!st || !data)
        return -1;

    aux = malloc(sizeof(struct node));
    if (!aux)
        return -1;
    
    aux->data = malloc(st->data_size);
    if (!aux->data) {
        free(aux);
        return -1;
    }
    
    if (!st->top) {
        st->top = aux;
        st->top->next = NULL;
    } else {
        aux->next = st->top;
        st->top = aux;
    }
    
    memcpy(st->top->data, data, st->data_size);
    st->size++;
    
    return 0;
}

/**
 * 
 */

int stack_pop(struct stack *st, void *buff)
{
    struct node *aux;

    if (!st || !buff || !st->top)
        return -1;
    
    memcpy(buff, st->top->data, st->data_size);
    
    aux = st->top;
    st->top = st->top->next;
    
    free(aux->data);
    free(aux);
    st->size--;

    return 0;
}

/**
 * 
 */

unsigned int stack_get_size(struct stack *st)
{
    if (!st)
        return 0;
 
    return st->size;
}


int test_1()
{
    int size = 10000;
    int max = 50000;
    int i, j, aux;
    int val[size];
    struct stack st;
    
    printf("Test 1: %d integers...", size);
    
    for (i = 0; i < size; i++) {
        val[i] = (rand() % max) + 1;
    }
    
    stack_init(&st, sizeof(int));
    
    for (i = 0; i < size; i++) {
        if (stack_push(&st, &val[i]) < 0) {
            printf("error: push\n");
            return -1;
        }
    }
    
    for (j = size - 1; j >= 0; j--) {
        
        if (stack_get_size(&st) == 0) {
            printf("error: size should not be 0\n");
            return -1;
        }
        
        if (stack_pop(&st, &aux) < 0) {
            printf("error: pop\n");
            return -1;
        }
        
        if (aux != val[j]) {
            printf("error: aux (%d) != val[%d] (%d)\n", aux, j, val[j]);
            return -1;
        }
    }
    
    if (stack_get_size(&st) != 0) {
        printf("size %d\n", stack_get_size(&st));
        printf("error: size should be 0\n");
        return -1;
    }
    
    printf(" OK!\n");
    return 0;
}

int test_2()
{
    int size = 10000;
    int max = 50000;
    int i, j;
    float aux;
    float val[size];
    struct stack st;
    
    printf("Test 2: %d floats...", size);
    
    for (i = 0; i < size; i++) {
        val[i] = (float)((rand() % max) + 1);
    }
    
    stack_init(&st, sizeof(float));
    
    for (i = 0; i < size; i++) {
        if (stack_push(&st, &val[i]) < 0) {
            printf("error: push\n");
            return -1;
        }
    }
    
    for (j = size - 1; j >= 0; j--) {
        
        if (stack_get_size(&st) == 0) {
            printf("error: size should not be 0\n");
            return -1;
        }
        
        if (stack_pop(&st, &aux) < 0) {
            printf("error: pop\n");
            return -1;
        }
        
        if (aux != val[j]) {
            printf("error: aux (%f) != val[%d] (%f)\n", aux, j, val[j]);
            return -1;
        }
    }
    
    if (stack_get_size(&st) != 0) {
        printf("size %d\n", stack_get_size(&st));
        printf("error: size should be 0\n");
        return -1;
    }
    
    printf(" OK!\n");
    return 0;
}

int test_3()
{
    int size = 10000;
    int max = 50000;
    int i;
    float val[size];
    struct stack st;
    
    printf("Test 3: %d floats and destroy...", size);
    
    for (i = 0; i < size; i++) {
        val[i] = (float)((rand() % max) + 1);
    }
    
    stack_init(&st, sizeof(float));
    
    for (i = 0; i < size; i++) {
        if (stack_push(&st, &val[i]) < 0) {
            printf("error: push\n");
            return -1;
        }
    }
    
    stack_destroy(&st);

    if (stack_get_size(&st) != 0) {
        printf("size %d\n", stack_get_size(&st));
        printf("error: size should be 0\n");
        return -1;
    }

    printf(" OK!\n");
    return 0;
}

int main()
{
    struct stack st;
    int i;
    float x = 1.48;
    float y;
    int val = 100;
    
    stack_init(&st, sizeof(float));

    for (i = 0; i < 10; i++) {
        stack_push(&st, &x);
        x++;
    }

    while (stack_get_size(&st)) {
        stack_pop(&st, &y);
        printf("%f\n", y);
    }
    
    for (i = 0; i < 10; i++) {
        stack_push(&st, &x);
        x++;
    }

    while (stack_get_size(&st)) {
        stack_pop(&st, &y);
        printf("%f\n", y);
    }

    stack_destroy(&st);

    stack_init(&st, sizeof(int));

    for (i = 0; i < 10; i++) {
        stack_push(&st, &val);
        val++;
    }

    while (stack_get_size(&st)) {
        stack_pop(&st, &val);
        printf("%d\n", val);
    }

    test_1();
    test_2();
    test_3();

    return 0;
}



