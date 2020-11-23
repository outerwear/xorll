/*
 * xorll.h
 */
#ifndef _XORLL_
#define _XORLL_

typedef struct xnode_t {
    int data;
    struct xnode_t *link;
} xnode;

typedef struct xnode_l {
    xnode *front;
    xnode *end;
} xmanager;


xnode* initX (int new, xnode *p, xnode *n);
xnode* nextX (xnode *c, xnode *p);
void insertX (int data);
void appendX (int data);
void addNodeX (int data, xnode *c, xnode *p);
void searchX (int data, xnode **f, xnode **p);
void deleteX (int data);
void printList ();

#endif
