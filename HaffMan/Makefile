zhiyi.o = main.o compress.o decompression.o
zhiyi.o += huffman.o
Huffman:$(zhiyi.o)
	gcc -o Huffman $(zhiyi.o)
%.o:%.c
	gcc -c $<
.PHONY:clean
clean:
	rm *.o
	rm Huffman
