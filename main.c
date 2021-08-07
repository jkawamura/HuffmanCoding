/**
 * @author Joseph Kawamura
 * 
 * Desc:
 *      The main program file for running the huffman coding. This file contains methods
 *      to compress and decompress the files. Additionally, there is a method for traversing
 *      huffman trees in order to record the codings. 
 *      
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
#include "Heap.h"

//global dictionary of huffman codes
int huffCodes[128][129];


/**
 * traverses a huffman tree and records the codes into the global dictionary
 * of codes. 
 * @param root the current node 
 * @param arr a temporary array used to record the path the method takes through the tree
 * @param index used to record location in arr
 */
void traverseTree(node *root, int arr[], int index){

    //case if leaf node is reached
    if(root->left == NULL && root->right == NULL){

        //ends the code with a -1
        arr[index] = -1;
        
        //records the codes into the huffCodes dictionary
        for(int i = 0; i <= index; i++){
            huffCodes[root->c][i] = arr[i];
        }
        return;
    }

    //records left movement and recurses into left node
    arr[index] = 0;
    traverseTree(root->left, arr, index+1);

    //record right movement and recurses into right node
    arr[index] = 1;
    traverseTree(root->right, arr, index+1);
}


/**
 * Takes an input file and finds the frequency of all the letters it contains. The frequencies
 * are then used to construct a huffman tree. The tree is then used to generate codes for each character. 
 * The text is then translated into bits and written to an output file specified by the user.
 * @param argv command line arguments
 */
void compress(char*argv[]){

    FILE* file = fopen(argv[2], "r");
    //table to store the ascii frequencies 128 length to allow for simple indexing 
    //while also storing the data necessary for constructing a header
    int freqTable[128];

    //zeros the frequency table
    for(int i = 0; i < 128; i++){
        freqTable[i] = 0;
    }

    //reads in each character from the text file and adds to the corresponding index
    //in the frequency table
    int charIn;
    while(1){
        charIn = fgetc(file);
 
        if (feof(file))
            break ;
        
        freqTable[charIn]++;
    }

    //creates a heap
    heap *frequencies = makeHeap(128);

    //creates a node for each character present in the given file
    //and inserts each node into the heap
    for(int i = 0; i < 128; i++){
        if(freqTable[i] > 0){
            node* temp = makeNode(i, freqTable[i], NULL, NULL);
            insert(frequencies, temp);
        }
    }


    //builds the huffman tree. The two smallest nodes are removed and made the children of a 
    //parent node that is reinserted into the heap. 
    int neg = -1;
    while(frequencies->count > 1){
        node *left = getMin(frequencies);
        node *right = getMin(frequencies);
        node *combined = makeNode(neg, left->freq+right->freq, left, right);
        insert(frequencies, combined);
        neg--;
    } 

    //array to temporarily store huffman codes
    int arr[129];

    //uses the traverse method to get and store all the codes
    traverseTree(frequencies->data[0], arr, 0);
    
    //resets the file pointer and opens the output file to write to
    fseek(file, 0, SEEK_SET);
    FILE*write_out=fopen(argv[3], "w");

    //writes the frequencies into the header
    fwrite(freqTable, 4, 128, write_out);

    //a char to hold 8 bits before being written. Acts as a buffer.
    unsigned char write = 0;

    //keeps track of how many bits have been written to the buffer
    int byteLimit = 0;
    while(1){

        //gets a new character to be transcoded
        charIn = fgetc(file);
        if (feof(file))
            break ;
        int index = 0;
        
        //loops until the end of the huffcode is reached.
        while(1){
            
            //checks if the byte limit is reached. If it is, the contents of the buffer is written
            //to the file and the buffer is reset to 0
            if(byteLimit >= 8){
                fwrite(&write, 1, 1, write_out);
                write = 0;
                byteLimit = 0;

            //checks if the end of the current huffcode is reached and breaks the loop so that 
            //a new character can be read from the input file and its code can be added.
            } if(huffCodes[charIn][index] != 0 && huffCodes[charIn][index] != 1){
                break;
            }

            write <<= 1;

            //adds a 1 to the buffer
            if(huffCodes[charIn][index] == 1){
                write |= 1;
            }
            byteLimit++;
            index++;
        }
    }

    //shifts the remaining bits so that the last bits are 0, then writes the last contents of the buffer
    write<<=(8-byteLimit);
    fwrite(&write, 1, 1, write_out);

    //closes streams and frees memory
    destroyHeap(frequencies);
    fclose(file);
    fclose(write_out);
}

/**
 * Takes a compressed file and reads in the letter frequencies. The frequencies are then used
 * to generate a huffman tree. It then reads the rest of the bits into an array and uses those 
 * bits to traverse the huffman tree and get the corresponding letters.
 * @param argv the command line arguments
 */
void decompress(char*argv[]){

    //compressed file to be read
    FILE* fileIn = fopen(argv[2], "r");

    //table storing all the letter frequencies
    int freqTable[128];

    //reads in the frequencies from the file
    fread(freqTable, sizeof(int), 128, fileIn);


    //creates a node for each character present in the given file
    //and inserts each node into the heap
    heap *frequencies = makeHeap(128);
    for(int i = 0; i < 128; i++){
        if(freqTable[i] > 0){
            node* temp = makeNode(i, freqTable[i], NULL, NULL);
            insert(frequencies, temp);
        }
    }

    //builds the huffman tree. The two smallest nodes are removed and made the children of a 
    //parent node that is reinserted into the heap. 
    int neg = -1;
    while(frequencies->count > 1){
        node *left = getMin(frequencies);
        node *right = getMin(frequencies);
        node *combined = makeNode(neg, left->freq+right->freq, left, right);
        insert(frequencies, combined);
        neg--;
    }

    //opens the file being written to
    FILE*writeOut=fopen(argv[3], "w");
    
    int byteCount;
    //resets to the beginning of the inputs file and counts the number of bytes
    fseek(fileIn, 0, SEEK_SET);
    for(byteCount = -512; getc(fileIn) != EOF; ++byteCount);

    //creates an array to store all the bits from the file.
    int bitList[byteCount*8];

    //jumps past the header
    fseek(fileIn, 512, SEEK_SET);
    
    //loops through each byte and adds its contents to 
    //the bitList. Since bytes are read right to left,
    //the bits are written right to left in byte sized
    //chunks
    unsigned char byteIn;
    for(int i = 0; i < byteCount; i++){
        byteIn = fgetc(fileIn);
        for(int j = 7 + 8*i; j >= 0 + 8*i; j--){
            if(byteIn%2 == 1){
                bitList[j] = 1;
            } else{
                bitList[j] = 0;
            }
            byteIn/=2;
        }
    } 
    
    //keeps track of location within the bitList
    int bufferIndex = 0;

    //root of huffman tree
    node *root = frequencies->data[0];
    while(1){

        //stops reading once 
        if(bufferIndex == byteCount*8){
            break;
        }

        //checks if a leaf is reached
        if(root->c > -1){

            //ensures that any tail-bits are ignored by counting down the 
            //frequencies of each letter. Any additional letters that come as 
            //the result of extra bits are discarded.
            if(--freqTable[root->c] < 0)
                break;
            
            //writes the contents of the leaf to the file and resets to the root of the tree
            fputc(root->c, writeOut);
            root = frequencies->data[0];

        //moves to the right child if a 1 is the next bit
        //and to the left child if a 0 is the next bit
        } if(bitList[bufferIndex] == 1){
            root = root->right;
            bufferIndex++;
        } else if(bitList[bufferIndex] == 0){
            root = root->left;
            bufferIndex++;
        }
    }

    //closes streams and frees allocated memory
    destroyHeap(frequencies);
    fclose(writeOut);
    fclose(fileIn);   
}

/**
 * main method. Allows for switching between compressing and decompressing.
 * @param argv command line arguments
 */
void main(int argc, char *argv[]){ 
    
    char *encode = argv[1];

    switch(*encode){
        case '1':
            compress(argv);
            break;
        case '2':
            decompress(argv);
            break;
    }    
}



