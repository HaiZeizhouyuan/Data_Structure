all = ./src/main.o ./src/decompression.o ./src/compress.o ./src/huffman.o

Huffman:$(all)
	gcc -o Huffman $(all)

./src/main.o: ./zhiyi/main.c ./include/head.h
	gcc -c -I ./ -o src/main.o  ./zhiyi/main.c
./src/huffman.o: ./zhiyi/huffman.c ./include/head.h
	gcc -c -I ./ -o src/huffman.o ./zhiyi/huffman.c
./src/compress.o: ./zhiyi/compress.c ./include/head.h
	gcc -c  -I ./ -o src/compress.o ./zhiyi/compress.c
./src/decompression.o: ./zhiyi/decompression.c ./include/head.h
	gcc -c -I ./ -o src/decompression.o ./zhiyi/decompression.c

.PHONY:clean
clean:
	rm $(all)
	rm Huffman
