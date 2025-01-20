CC = gcc
objects := sapermain.o plansze.o funkcjaf.o polecenia.o top.o

all: $(objects)
	$(CC) $^ -o saper
	echo $^

sapermain.o: sapermain.c 
	$(CC) -c sapermain.c -o sapermain.o

plansze.o: plansze.c 
	$(CC) -c plansze.c -o plansze.o 

funkcjaf.o: funkcjaf.c 
	$(CC) -c funkcjaf.c -o funkcjaf.o 

polecenia.o: polecenia.c 
	$(CC) -c polecenia.c -o polecenia.o 

top.o: top.c 
	$(CC) -c top.c -o top.o 

test: all
	./saper

clean:
	rm -f *.o saper