

# Program Files
- Heap.c
- Heap.h
- Main.c
- Node.c
- Node.h
	
# How to Compile:

    *make huff* (Equivalent to *gcc -o huff main.c Heap.c Node.c Tree.c*)
  
# How to Run:

To compress:

	`./heap 1 input.txt output.cmp` 
	
Where input.txt is any text file using only characters in the ASCII set, output.cmp is the file the compressed output will be written to
    
    To Decompress:
        "./heap 2 output.cmp output.txt" (Where output.cmp is any compressed file that has been encoded by this program
                                        and output.txt is the text file the decompressed output will be written to)
