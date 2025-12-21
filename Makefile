# Compile le programme et rend le script exécutable
all: wildwater script


# Compilation du fichier main.c
main.o: main.c
	gcc -c main.c -o main.o

# Compilation du fichier leak.c (dépend de leak.h)
leak.o: leak.c leak.h
	gcc -c leak.c -o leak.o

# Compilation du fichier histo.c (dépend de histo.h)
histo.o: histo.c histo.h
	gcc -c histo.c -o histo.o

# Compilation du fichier fonction_base.c (utilise histo.h)
fonction_base.o: fonction_base.c histo.h
	gcc -c fonction_base.c -o fonction_base.o


# Création de l'exécutable final à partir des fichiers .o
wildwater: main.o leak.o histo.o fonction_base.o
	gcc main.o leak.o histo.o fonction_base.o -o wildwater


# Rend le script shell exécutable
.PHONY: script
script:
	chmod +x shell.sh


# Nettoyage du projet :
# supprime les fichiers objets, l'exécutable et les fichiers générés
clean:
	rm -f *.o
	rm -f wildwater
	rm -f *.png
	rm -f *_e.dat


