OBJS = main.o vcpu.o
CC = gcc
COM = $(CC) -Wall -Wextra -std=c99 -pedantic-errors -c
BINW = ..\bin
BINL = ../bin

$(BINW)\vcpu.exe: $(OBJS)
	$(CC) $(OBJS) -o $(BINW)\vcpu.exe

$(BINL)/vcpu: $(OBJS)
	$(CC) $(OBJS) -o $(BINL)/vcpu

main.o: main.c vcpu.h
	$(COM) main.c

vcpu.o: vcpu.c vcpu.h
	$(COM) vcpu.c

win: $(BINW)\vcpu.exe

linux: $(BINL)/vcpu
