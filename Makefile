all: start

start: generatore analizzatore elaboratore
	gcc -g -o start start.c

generatore:
	gcc -o generatore generatore.c generatore.c 

analizzatore:
	gcc -o analizzatore analizzatore.c analizzatore.c 

elaboratore:
	gcc -o elaboratore elaboratore.c elaboratore.c 


clean:
	rm -f*.o
	rm -f*./start ./generatore ./analizzatore ./elaboratore


