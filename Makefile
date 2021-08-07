huff: main.c Heap.c Node.c
	gcc -o huff main.c Heap.c Node.c

clean:
	find -type f -iname '*.o' -delete
	rm huff 
