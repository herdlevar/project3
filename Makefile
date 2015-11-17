project3: main.c sub.c queue.c io.c cpu.c
	gcc -Wall -O3 main.c sub.c queue.c io.c cpu.c

clean:
	rm -rf *o project3
