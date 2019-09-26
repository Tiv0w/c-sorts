default: radix_lsd

radix_lsd.o: radix_lsd.c
	gcc -c radix_lsd.c -o radix_lsd.o

radix_lsd: radix_lsd.o
	gcc radix_lsd.o -o radix_lsd

debug: radix_lsd-debug.o
	gcc radix_lsd-debug.o -o radix_lsd-debug

radix_lsd-debug.o: clean
	gcc -g -c radix_lsd.c -o radix_lsd-debug.o

clean:
	-rm -f radix_lsd.o
	-rm -f radix_lsd
