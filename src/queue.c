#include "../include/queue.h"

int queue_size(queue_t *queue)
{
    queue_t *p;
    int cont = 0;
    if (queue == NULL)
    {
        printf("%d", cont);
        return cont;
    }
    p = queue;
    do
    {
        p = p->next;
        cont++;
    } while (p != queue);
    return cont;
}

void queue_print(char *name, queue_t *queue, void print_elem(void *))
{
    printf("%s: ", name);
    if(queue == NULL) {
        printf("[]\n");
        return;
    }
    queue_t *p;
    p = queue;
    printf(" [ ");
    do
    {
        print_elem(p);
        printf(" ");
        p = p->next;
    } while (p != queue);
    printf("]\n");
}

int queue_append(queue_t **queue, queue_t *elem)
{
    if (queue == NULL)
    {
        printf("### Erro: a fila não existe\n");
        return -1;
    }
    if (elem == NULL)
    {
        printf("### Erro: o elemento não existe\n");
        return -1;
    }
    if (elem->next != NULL || elem->prev != NULL)
    {
        printf("### Erro: o elemento já está inserido em outra lista\n");
        return -1;
    }
    if (*queue == NULL) {
        // Fila vazia: o elemento é o único na fila, então ele aponta para si mesmo
        *queue = elem;
        elem->next = elem;
        elem->prev = elem;
    } else {
        // Fila não vazia: insere o elemento no final
        queue_t *last = (*queue)->prev;

        last->next = elem;
        elem->prev = last;
        elem->next = *queue;
        (*queue)->prev = elem;
    }
    return 0;
}

int queue_remove (queue_t **queue, queue_t *elem) {
    if (queue == NULL)
    {
        printf("### Erro: a fila não existe\n");
        return -1;
    }
    if (elem == NULL)
    {
        printf("### Erro: o elemento não existe\n");
        return -1;
    }
    if((*queue) == NULL) {
        printf("### Erro: a fila está vazia\n");
        return -1;
    }
    queue_t *p = (*queue);
    int logic = 0;
    do {
        if (p == elem)
        {
            logic = 1;
            break;
        }
        p = p->next;
    } while(p != *queue);
    if(logic == 0) {
        printf("### Erro: o elemento não faz parte da lista\n");
        return -1;
    }
    if (p->next == p && p->prev == p) *queue = NULL;
    if(p == *queue) *queue = p->next;
    p->prev->next = p->next;
    p->next->prev = p->prev;
    p->next = NULL;
    p->prev = NULL;
    
    return 0;
}