GNU = gcc

all: 
	$(GNU) main.c my_top.c -o my_top -Wall -pedantic -lncurses

run: 
	./my_top

test: all run

clean:
	rm my_top;
	