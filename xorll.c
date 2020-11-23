/*
 * XOR Linked List
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "xorll.h"

/* Global XORLL Manager */
xmanager xl;

xnode* initX (int new, xnode *p, xnode *n) {
    xnode *xn = malloc(sizeof(xnode));
    if (NULL == xn) {
        printf("ERROR: Not enough space to allocate new xnode\n");
    } else {
        xn->data = new;
        xn->link = (xnode *)((uint64_t)p ^ (uint64_t)n);
    }
    return xn;
}

xnode* nextX (xnode *c, xnode *p) {
    return (xnode *)((uint64_t)c->link ^ (uint64_t)p);
}

/* Insert/Append
 * If xl is empty then both front and end will be NULL. At no point should 
 * one be NULL and other have a value.
 */
void insertX (int data) {
    if (NULL == xl.front)
        xl.front = xl.end = initX(data, NULL, NULL);
    else {
        xnode *t = initX(data, NULL, xl.front);
        xl.front->link = (xnode *)((uint64_t)t ^ (uint64_t)xl.front->link);
        xl.front = t;
    }
}

void appendX (int data) {
    if (NULL == xl.end)
        xl.end = xl.front = initX(data, NULL, NULL);
    else {
        xnode *t = initX(data, xl.end, NULL);
        xl.end->link = (xnode *)((uint64_t)t ^ (uint64_t)xl.end->link);
        xl.end = t;
    }
}

/* AddNode (data, current node, previous node)
 * This is different from insert/append because it adds a node anywhere in
 * the list. It's purpose is to init and update link
 */
void addNodeX (int data, xnode *c, xnode *p) {
    xnode *t = initX(data, p, c);

    /* p link update */
    p->link = (xnode *)(((uint64_t)p->link ^ (uint64_t)c) ^ (uint64_t)t);

    /* c link update */
    c->link = (xnode *)(((uint64_t)c->link ^ (uint64_t)p) ^ (uint64_t)t);
}

/* Search (search data, found node, prev node)
 * Traverse through the list until target is found. Found node is returned
 * as a passed parameter with the previous node as well.
 */
void searchX (int data, xnode **f, xnode **p) {
    *f = xl.front;
    while (NULL != *f) {
        if (data == (*f)->data)
            break;

        if (*f == xl.front) {
            *f = (*f)->link;
            *p = xl.front;
        }
        else {
            xnode *curr = *f;
            *f = nextX(*f, *p);
            *p = curr;
        }
    }
}

/* Delete
 * Search for node in list, update the surrounding links, free the delete node
 */
void deleteX (int data) {
    xnode *d, *p, *n;
    d = p = NULL;

    searchX(data, &d, &p);

    if (NULL == d) return;

    n = nextX(d, p);

    if (d == xl.front)
        xl.front = n;
    else if (d == xl.end)
        xl.end = p;

    /* p link update */
    if (NULL != p)
        p->link = (xnode *)(((uint64_t)p->link ^ (uint64_t)d) ^ (uint64_t)n);

    /* n link update */
    if (NULL != n)
        n->link = (xnode *)(((uint64_t)n->link ^ (uint64_t)d) ^ (uint64_t)p);

    free(d);
}

void printList () {
    xnode *T = xl.front, *P = NULL;

    printf("XORLL : ");
    while (NULL != T) {
        printf("%d", T->data);
        if (T == xl.front) {
            T = T->link;
            P = xl.front;
        }
        else if (T == xl.end) {
            break;
        }
        else {
            xnode *curr = T;
            T = nextX(T, P);
            P = curr;
        }
        printf(", ");
    }
    printf("\n");
}

