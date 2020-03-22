CC = gcc
EXEC = TicTacToe
CFLAGS = -Wall -Werror -ansi -pedantic -g -std=c89
OBJ = main.o LinkedList.o operation.o game.o display.o file.o logger.o myTime.o win.o


ifdef Secret
CFLAGS += -D Secret
Editor : clean $(EXEC)
endif


ifdef Editor
CFLAGS += -D Editor
Editor : clean $(EXEC)
endif


$(EXEC) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)

main.o : main.c operation.h file.h 
	$(CC) $(CFLAGS) main.c -c 

LinkedList.o : LinkedList.c LinkedList.h
	$(CC) $(CFLAGS) LinkedList.c -c

operation.o : operation.c LinkedList.h board.h file.h display.h game.h logger.h operation.h
	$(CC) $(CFLAGS) operation.c -c 

game.o : game.c LinkedList.h board.h display.h logger.h game.h win.h
	$(CC) $(CFLAGS) game.c -c 

display.o : display.c board.h
	$(CC) $(CFLAGS) display.c -c 

file.o : file.c myTime.h LinkedList.h board.h 
	$(CC) $(CFLAGS) file.c -c 

logger.o : logger.c board.h
	$(CC) $(CFLAGS) logger.c -c

myTime.o : myTime.c
	$(CC) $(CFLAGS) myTime.c -c 

win.o : win.c board.h win.h
	$(CC) $(CFLAGS) win.c -c 

clean :
	rm -f $(EXEC) $(OBJ)
