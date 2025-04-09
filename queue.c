#include <stdio.h>
#include "queue.h"
// Conta o numero de elementos na fila
// Retorno: numero de elementos na fila

int queue_size (queue_t *queue) {
    if (queue == NULL)
        return 0;
    queue_t * q = queue->next;
    int size = 1;

    while (q != queue) {
        q = q->next;
        size++;
    }
    return size;
}

//------------------------------------------------------------------------------
// Percorre a fila e imprime na tela seu conteúdo. A impressão de cada
// elemento é feita por uma função externa, definida pelo programa que
// usa a biblioteca. Essa função deve ter o seguinte protótipo:
//
// void print_elem (void *ptr) ; // ptr aponta para o elemento a imprimir

void queue_print (char *name, queue_t *queue, void print_elem (void*) ) {
    printf("%s", name);
    if (queue == NULL)
        return;

    print_elem(queue);
    queue_t * q = queue->next;

    while (q != queue) {
        print_elem(q);
        q = q->next;
    }
}

//------------------------------------------------------------------------------
// Insere um elemento no final da fila.
// Condicoes a verificar, gerando msgs de erro:
// - a fila deve existir
// - o elemento deve existir
// - o elemento nao deve estar em outra fila
// Retorno: 0 se sucesso, <0 se ocorreu algum erro

int queue_append (queue_t **queue, queue_t *elem) {
    if (queue == NULL) {
        printf("Erro: a fila não existe.\n");
        return -1;
    }
    if (elem == NULL) {
        printf("Erro: o elemento não existe.\n");
        return -2;
    }
    if (elem->next != NULL || elem->prev != NULL) {
        printf("Erro: o elemento já está em uma fila.\n");
        return -3;
    }
    if (*queue == NULL) {
        *queue = elem;
        elem->next = elem;
        elem->prev = elem;
    }
    else {
        elem->next = *queue;
        elem->prev = (*queue)->prev;
        (*queue)->prev->next = elem;
        (*queue)->prev = elem;
    }
    return 0;
}

//------------------------------------------------------------------------------
// Remove o elemento indicado da fila, sem o destruir.
// Condicoes a verificar, gerando msgs de erro:
// - a fila deve existir
// - a fila nao deve estar vazia
// - o elemento deve existir
// - o elemento deve pertencer a fila indicada
// Retorno: 0 se sucesso, <0 se ocorreu algum erro

int queue_remove (queue_t **queue, queue_t *elem) {
    if (queue == NULL) {
        printf("Erro: a fila não existe.\n");
        return -1;
    }
    if (elem == NULL) {
        printf("Erro: o elemento não existe.\n");
        return -2;
    }
    if (elem->next == NULL || elem->prev == NULL) {
        printf("Erro: o elemento não está em uma fila.\n");
        return -3;
    }
    if (elem->next == elem && elem->prev == elem) {
        elem->next = NULL;
        elem->prev = NULL;
        (*queue) = NULL;
        return 0;
    }
    queue_t *q = *queue;
    do {
        if (q == elem) {
            q->prev->next = q->next;
            q->next->prev = q->prev;
            q = elem->next;
            elem->next = NULL;
            elem->prev = NULL;
        } else {
            q = q->next;
        }
    } while (q != *queue);
    return 0;
}