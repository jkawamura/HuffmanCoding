/**
 * @author Joseph Kawamura
 * 
 * Desc:
 *      Node class used to construct the huffman tree. Each node contains a character, that characters frequency
 *      within the given text file as well as pointers to left and right children that can be used to construct 
 *      a binary tree. 
 * 
 * Modified: April 26, 2021
 * Modified: April 28, 2021
 * Modified: April 29, 2021
 * Modified: May 4, 2021
 * Modified: May 6, 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include "Node.h"

/**
 * constructor for node class
 * @param c the character being stored in the node
 * @param freq the frequency at which that character occurs 
 * @param left pointer to left branch
 * @param right pointer to right branch
 */
node* makeNode(char c, int freq, node*left, node*right){
    node* output = malloc(sizeof(node));
    output->c = c;;
    output->freq = freq;
    output->left = left;
    output->right = right;
}

/**
 * destructor that frees memory for a given node and all of 
 * its children (ie a destructor for a binary tree)
 * @param root the root node
 */
void destroyNode(node* root){
    if(root->left == NULL && root->right == NULL){
        free(root);
        return;
    }
    destroyNode(root->left);
    destroyNode(root->right);
    free(root);
}
