CC=gcc
CFLAGS=-O2

dnsrelay: main.o
	gcc main.o -o dnsrelay

clean:
	${RM} *.o dnsrelay

