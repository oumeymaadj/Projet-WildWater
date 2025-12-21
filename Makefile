EXEC = wildwater
CC = gcc
# Warnings, Standard C99 et mode Debug
CFLAGS = -Wall -Wextra -std=c99 -g

SRC = main.c leak.c histo.c fonction_base.c
# génère automatiquement la liste des .o à partir des .c
OBJ = $(SRC:.c=.o)

all: $(EXEC)

# Édition de liens, création de l'exécutable final
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

# compilation, chaque .c devient un .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# nettoyage du projet
clean:
	rm -f $(OBJ) $(EXEC)
