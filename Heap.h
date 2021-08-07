/**
 * @author Joseph Kawamura
 * 
 * Desc:
 *      contains prototype for heap class. 
 * 
 * Modified: April 26, 2021
 * Modified: April 28, 2021
 * Modified: April 29, 2021
 * Modified: May 4, 2021
 * Modified: May 6, 2021
 */

#include "Node.h"

#ifndef heap_defined
typedef struct {
    int count;
    node **data;
} heap;
#define heap_defined 1
#endif

heap* makeHeap(int size);

node* getMin(heap *heapIn);

void insert(heap *heapIn, node *input);

void swap(heap* heapIn, int index1, int index2);

int heapCompareValue(const node *p, const node *q);

void destroyHeap(heap *heapIn);
