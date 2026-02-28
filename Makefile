pypour-bin: pypour.c
	gcc -std=c99 -O2 -o pypour-bin pypour.c

clean:
	rm -f pypour-bin
