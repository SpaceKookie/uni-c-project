all:
	gcc container.c -Wall -o containers

clean:
	rm containers
	rm *.o *.out
