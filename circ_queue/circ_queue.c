#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
        front                     back
        ____         ____         ____
       |    |       |    |       |    |
  |--->|    | ----> |    | ----> |    | ----|
  |    |____|       |____|       |____|     |
  |                                         |
  |-----------------------------------------|
*/

struct node {
    struct node *next;
    void *data;
};

struct queue {
    struct node *front;
    struct node *back;
    unsigned int size;
    unsigned int max_size;
    int data_size;
};

struct my_data {
    char name[100];
    float val;
    int other_val[50];
};

/**
 *
 */

void queue_init(struct queue *q, int d_size, unsigned int m_size)
{
    q->front = NULL;
    q->back = NULL;
    q->size = 0;
    q->max_size = m_size;
    q->data_size = d_size;
}

/**
 *
 */

void set_max_size(struct queue *q, unsigned int size)
{
    struct node *aux;

    q->max_size = size;

    /* if necessary, removes oldest data to fit new size */
    while(q->size > q->max_size) {
        aux = q->front;
        q->front = q->front->next;
        q->back->next = q->front;

        free(aux->data);
        free(aux);
        q->size--;
    }
}

/**
 *
 */

void destroy_c_queue(struct queue *q)
{
    struct node *aux;

    while(q->size > 0) {
        aux = q->front;
        q->front = q->front->next;
        q->back->next = q->front;

        free(aux->data);
        free(aux);
        q->size--;
    }
}

/**
 *
 *
 */

int pop_front(struct queue *q, void *data)
{
    struct node *aux;

    if (!q || !data || !q->size)
        return -1;

    memcpy(data, q->front->data, (size_t) q->data_size);

    aux = q->front;
    q->front = q->front->next;
    q->back->next = q->front;

    free(aux->data);
    free(aux);
    q->size--;

    return 0;
}

/**
 *
 *
 */

int push_back(struct queue *q, const void *data)
{
    struct node *aux;

    if (!q || !data)
        return -1;

    if (q->size == q->max_size) {   /* overwrites oldest data */
        q->back = q->front;
        q->front = q->front->next;
    } else {
        aux = (struct node *) malloc(sizeof(struct node));
        if (!aux)
            return -1;

        aux->data = malloc(q->data_size);
        if (!aux->data) {
            free(aux);
            return -1;
        }

        if (q->size == 0)
            q->front = aux;
        else
            q->back->next = aux;

        q->back = aux;
        q->back->next = q->front;
        q->size++;
    }

    memcpy(q->back->data, data, (size_t) q->data_size);
    printf("size %d max size %d\n", q->size, q->max_size);

    return 0;
}

/**
 *
 */

unsigned int get_size(struct queue *q)
{
    if (!q)
        return 0;

    return q->size;
}

/**
 *
 */

unsigned int get_max_size(struct queue *q)
{
    if (!q)
        return 0;

    return q->max_size;
}

int main()
{
    struct queue Q;
    int value = 1;
    int val = 0;
    struct my_data data;

    queue_init(&Q, sizeof(int), 50);

    for (value = 1; value < 51; value++)
        push_back(&Q, &value);

    set_max_size(&Q, 10);

    for (value = 0; value < 10; value++) {
        pop_front(&Q, &val);
        printf("%d\n", val);
    }

    destroy_c_queue(&Q);

    queue_init(&Q, sizeof(struct my_data), 150);

    for (value = 0; value < 200; value++)
        push_back(&Q, &data);

    printf("%d\n", get_size(&Q));

    set_max_size(&Q, 10);

    printf("%d\n", get_size(&Q));

    return 0;
}








