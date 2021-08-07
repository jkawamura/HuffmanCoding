/**
 * @author Joseph Kawamura
 *      
 * Desc:
 *      Contains the prototype for the node class. 
 * 
 * Modified: April 26, 2021
 * Modified: April 28, 2021
 * Modified: April 29, 2021
 * Modified: May 4, 2021
 * Modified: May 6, 2021
 */

#ifndef node_defined
typedef struct node { 
    int freq;
    char c;
    struct node* left;
    struct node* right;
} node;
#define node_defined 1
#endif

node* makeNode(char c, int freq, node*left, node*right);

void destroyNode(node* nodeIn);