/*
 * xorll.h
 */
#ifndef _XORLL_
#define _XORLL_

typedef struct xnode_t {
    unsigned char *data;
    size_t data_sz;
    struct xnode_t *link;
} xnode;

typedef struct xnode_l {
    xnode *front;
    xnode *end;
} xmanager;

#define nextX(c, p) (xnode *)((uint64_t)(c)->link ^ (uint64_t)(p));

xnode* initX (unsigned char *new, size_t size, xnode *p, xnode *n);
void insertX (unsigned char *data, size_t size);
void appendX (unsigned char *data, size_t size);
void addNodeX (unsigned char *data, size_t size, xnode *c, xnode *p);
void searchX (unsigned char *data, size_t size, xnode **f, xnode **p);
void deleteX (unsigned char *data, size_t size);

#endif
