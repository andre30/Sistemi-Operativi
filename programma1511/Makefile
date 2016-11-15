all: start

start: analizzatore generatore elaboratore
	gcc -o start start.c

analizzatore:
	gcc -o analizzatore analizzatore.c procedure.c

generatore:
	gcc -o generatore generatore.c procedure.c

elaboratore:
	gcc -o elaboratore elaboratore.c procedure.c

