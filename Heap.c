/**
 * @author Joseph Kawamura
 * 
 * Desc:
 *      Class containing methods and struct for a heap. 
 * 
 * Modified: April 26, 2021
 * Modified: April 28, 2021
 * Modified: April 29, 2021
 * Modified: May 4, 2021
 * Modified: May 6, 2021
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Heap.h"
#include "Node.h"

/**
 * constructor for a heap
 * @param size the size of the heap
 * @return pointer to the beginning of the heap
 */
heap* makeHeap(int size){
    heap *output = malloc(1 * sizeof(heap));
    output->count = 0;
    output->data = malloc(size * sizeof(node*));
    return output;
}

/**
 * Gets the smallest node from the heap
 * @param heapIn the heap being used
 * @return the address of the smallest node
 */
node* getMin(heap *heapIn){

    //gets the smallest node
    node *output = heapIn->data[0];
    
    //swaps the old node with the last node
    //heapIn->data[0] = 0;
    swap(heapIn, 0, heapIn->count - 1);
    heapIn->count--;
    
    //bubbles the swapped node down to the correct location 
    int index = 0;
    while(1){
        int left = 2*index + 1;
        int right = 2*index + 2;
        
        //checks if the children of the current node are within the heap bounds and swaps the 
        //current node with a child if it is larger than that child
        if(left < heapIn->count && heapCompareValue(heapIn->data[index], heapIn->data[left]) > 0){
            swap(heapIn, index, left);
            index = left;
            continue;
        } else if(right < heapIn->count && heapCompareValue(heapIn->data[index], heapIn->data[right]) > 0){
            swap(heapIn, index, right);
            index = right;
            continue;
        } else {
            break;
        }
    }
    return output;
}

/**
 * inserts a node into the heap
 * @param heapIn the heap being used
 * @param input the node to be added
 */
void insert(heap *heapIn, node *input){

    //inserts the new node at the end of the heap
    int index = heapIn->count;
    heapIn->data[index] = input;
    heapIn->count++;

    //bubbles the new node up until it is larger than its parent
    while(index > 0){
        int parent = (index - 1)/2;
        if(heapCompareValue(heapIn->data[index], heapIn->data[parent]) < 0){
            swap(heapIn, index, parent);
            index = parent;
        } else{
            break;
        }
    }
}

/**
 * swaps two nodes in a heap
 * @param heapIn the heap being used
 * @param index1 the index of the first element
 * @param index2 the index of the second element being swapped
 */
void swap(heap* heapIn, int index1, int index2){
    node *temp = heapIn->data[index1];
    heapIn->data[index1] = heapIn->data[index2];
    heapIn->data[index2] = temp;
}

/**
 * compares the value of two nodes for the purpose of sorting the heap.
 * Compares the frequencies contained in two nodes or, in the case of 
 * a tie, compares their stored characters.
 * @param p the first node being compared
 * @param q the second node being compared
 * @return <0 if first value is less than second
 *         >0 if first value is greater than second
 */
int heapCompareValue(const node *p, const node *q){
    if(p->freq == q->freq){
        return p->c - q->c;
    } else if(p->freq > q->freq){
        return 1;
    } else{
        return -1;
    }
}

/**
 * Destroys the memory allocated for the heap and destroys the nodes for
 * the huffman tree contained within the heap.
 * @param heapIn the heap to be destroyed
 */
void destroyHeap(heap* heapIn){
    destroyNode(heapIn->data[0]);
    free(heapIn->data);
    free(heapIn);
}