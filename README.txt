NAME:
=====
Joseph Kawamura

Program Files:
===============

    Heap.c
    Heap.h
    Main.c
    Node.c
    Node.h
	
How to Compile:
===============

    "make huff" (Equivalent to "gcc -o huff main.c Heap.c Node.c Tree.c")
  
How to Run:
===========

    To compress:
        "./heap 1 input.txt output.cmp" (Where input.txt is any text file using only characters in the ASCII set, 
                                        output.cmp is the file the compressed output will be written to)
    
    To Decompress:
        "./heap 2 output.cmp output.txt" (Where output.cmp is any compressed file that has been encoded by this program
                                        and output.txt is the text file the decompressed output will be written to)

Reflection:
===========

    Overall, the lab went fairly smoothly. I had been expecting the heap and tree creation to pose some difficulty,
    however, they worked fine after my first compile. Most of the difficulty I faced came from figuring out how 
    to write and read bits properly as mistakes were easy to make, especially when dealing with the incomplete bytes
    at the end of files. When I first tested my decompression method, I found that it was reading the bits backwards
    as I had failed to account for the fact that bits are read right-left from bytes while the huffman codes are read
    left-right.

    Additionally, I had some confusion over the endianness of the lab computers as when I used hexdump to display the contents
    of compressed files, every two bytes would be swapped. This turned out to not be an issue with decompressing, and 
    I found I could display the contents of the compressed file in a more readable manner using hexdump -C.

I Worked With:
==============
N/A

Approximate Hours worked:
=========================
10

Special Instructions to the grader:
===================================
None

Known Bugs or Limitations:
==========================
N/A

Other comments:
===============
N/A