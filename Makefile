EXEC = wildwater
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

SRC = main.c leak.c histo.c fonction_base.c
OBJ = $(SRC:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
