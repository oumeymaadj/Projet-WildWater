WildWater Analyse et Détection de Fuites

Prérequis :
Pour compiler et utiliser le projet, l’environnement suivant est requis :
GCC  compilateur C compatible C99
Make automatisation de la compilation
Gnuplot (recommandé)  génération automatique des graphiques
Compilation :
Le projet est entièrement géré par un Makefile.
Compiler le projet
make
(Génère l’exécutable wildwater)
Nettoyer le projet
make clean
(Supprime :
fichiers objets (.o)
l’exécutable
fichiers de résultats (.dat)
images générées (.png) )
Utilisation :
Script d’automatisation (recommandé)
Le script shell.sh permet de :
compiler le projet
exécuter le programme
générer automatiquement les graphiques avec Gnuplot
Rendre le script exécutable (une seule fois)
chmod +x shell.sh
Syntaxe
./shell.sh <fichier_donnees> <mode> <option>
Exemples
Détection de fuites
(Génère leaks_e.dat)
./shell.sh c-wildwater_v3.dat leaks "Unit #GV001308I"
Si l’identifiant contient un #, utilisez des guillemets.
Génération des statistiques et graphiques
./shell.sh c-wildwater_v3.dat histo all
Génère :
fichiers histo_*.dat
graphiques .png
Exécution manuelle
Le programme peut aussi être lancé directement :
./wildwater c-wildwater_v3.dat leaks "Unit#GV001308I"
Organisation des fichiers :
main.c	Point d’entrée du programme
leak.c / leak.h	Algorithmes récursifs de détection de fuites
histo.c / histo.h	Calcul des statistiques (min, max, moyenne)
fonction_base.c	Fonctions AVL (rotations, équilibrage, utilitaires)
shell.sh	Script d’automatisation + commandes Gnuplot
Makefile	Compilation et nettoyage complet
