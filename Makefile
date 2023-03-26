CC=gcc
BIN=SMS
OBJ=main.o system.o tools.o principle.o student.o teacher.o 
FLAG=-Wall -Werror

all:$(OBJ)
	$(CC) -o $(BIN) $(OBJ)
main.o:main.c tools.h system.h principle.h student.h teacher.h
	$(CC) -c main.c $(FLAG)
system.o:system.c tools.h system.h principle.h student.h teacher.h
	$(CC) -c system.c $(FLAG)
tools.o:tools.c tools.h 
	$(CC) -c tools.c $(FLAG)
principle.o:principle.c tools.h principle.h student.h teacher.h system.h
	$(CC) -c principle.c $(FLAG)
student.o:student.c tools.h principle.h student.h teacher.h system.h
	$(CC) -c student.c $(FLAG)
teacher.o:teacher.c tools.h system.h principle.h student.h teacher.h
	$(CC) -c teacher.c $(FLAG)

clean:
	rm $(BIN) $(OBJ)
