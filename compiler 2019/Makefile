CC = gcc
CFLAGS = -Wall
EXEC_NAME = main
INCLUDES =
LIBS =
OBJ_FILES = asm.o data.o hash.o list.o split.o

all: $(EXEC_NAME)

clean:
	rm 	$(EXEC_NAME) $(OBJ_FILES) test.o

test: test.o
	$(CC) -o test $(OBJ_FILES) test.o $(LIBS)

$(EXEC_NAME) : $(OBJ_FILES) main.o
	$(CC) -o $(EXEC_NAME) $(OBJ_FILES) main.o $(LIBS)

%.o: %.c
	gcc $(CFLAGS) $(INCLUDES) -o $@ -c $<