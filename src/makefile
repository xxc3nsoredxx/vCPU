OBJS = main.o vcpu.o
CC = gcc
COM = $(CC) -Wall -Wextra -std=c99 -pedantic-errors -c
BIN = ..\bin

$(BIN)\vcpu.exe: $(OBJS)
	$(CC) $(OBJS) -o $(BIN)\vcpu.exe

$(BIN)vcpu: $(OBJS)
	$(CC) $(OBJS) -o $(BIN)vcpu

main.o: main.c vcpu.h
	$(COM) main.c

vcpu.o: vcpu.c vcpu.h
	$(COM) vcpu.c

win: $(BIN)\vcpu.exe

linux: $(BIN)vcpu
