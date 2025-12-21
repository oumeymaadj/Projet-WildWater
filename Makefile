EXEC = wildwater
CC = gcc
# Warnings, standard C99 et mode debug
CFLAGS = -Wall -Wextra -std=c99 -g

SRC = main.c leak.c histo.c fonction_base.c
# génère automatiquement la liste des .o à partir des .c
OBJ = $(SRC:.c=.o)

all: $(EXEC)

# édition de liens, création de l'exécutable final
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

# compilation, chaque .c devient un .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# nettoyage du projet
clean:
	rm -f $(OBJ) $(EXEC)
