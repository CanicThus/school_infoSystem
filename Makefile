CC=gcc
BIN=SMS
OBJ=main.o principle.o student.o teacher.o system.o tools.o
FLAG=-Wall -Werror

all:$(OBJ)
	$(CC) -o $(BIN) $(OBJ)
main.o:main.c tools.h principle.h student.h teacher.h system.h
	$(CC) -c main.c $(FLAG)
principle.o:principle.c tools.h principle.h student.h teacher.h system.h
	$(CC) -c principle.c $(FLAG)
student.o:student.c tools.h principle.h student.h teacher.h system.h
	$(CC) -c student.c $(FLAG)
system.o:system.c tools.h principle.h student.h teacher.h system.h
	$(CC) -c system.c $(FLAG)
teacher.o:teacher.c tools.h principle.h student.h teacher.h system.h
	$(CC) -c teacher.c $(FLAG)
tools.o:tools.c tools.h 
	$(CC) -c tools.c $(FLAG)

clean:
	rm $(BIN) $(OBJ)
