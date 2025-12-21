# WildWater – Analyse et Détection de Fuites

Une application console en **C** dédiée à l’analyse de données hydrauliques et à la **détection automatique de fuites d’eau**, avec génération de statistiques et de graphiques.

- Code final : projet informatique  
- Analyse de fichiers de données hydrauliques  
- Détection de fuites par algorithmes récursifs  
- Calcul de statistiques (min, max, moyenne)  
- Génération automatique de graphiques via **Gnuplot**  
- Automatisation complète via **Makefile** et **script shell**

---

## Descriptif des fichiers

### main.c
Point d’entrée principal du programme.  
Gère l’analyse des arguments, l’appel des modules de détection ou de statistiques, et le lancement des traitements.

### leak.c
Implémente les algorithmes récursifs de détection de fuites à partir des données d’entrée.

### leak.h
Contient les prototypes des fonctions de détection de fuites et les structures associées.

### histo.c
Calcule les statistiques sur les données (minimum, maximum, moyenne)  
et prépare les fichiers nécessaires à la génération des graphiques.

### histo.h
Déclarations des fonctions de calcul statistique.

### fonction_base.c
Implémente les fonctions AVL : rotations, équilibrage et fonctions utilitaires liées aux arbres.

### shell.sh
Script d’automatisation permettant de compiler le projet, exécuter le programme  
et générer automatiquement les graphiques avec Gnuplot.

### Makefile
Fichier d’automatisation de la compilation.  
Permet de compiler le projet, générer l’exécutable `wildwater`  
et nettoyer tous les fichiers générés.

---

## Prérequis

Pour compiler et utiliser le projet, l’environnement suivant est requis :

- GCC (compilateur C compatible C99)  
- Make  
- Gnuplot (recommandé)  
- Shell Bash  

---

## Compilation

Le projet est entièrement géré par un Makefile.

Compiler le projet :
make

Nettoyer le projet :
make clean

Supprime les fichiers objets (.o), l’exécutable `wildwater`,  
les fichiers de résultats (.dat) et les images générées (.png).

---

## Utilisation

Méthode recommandée : script d’automatisation.

Rendre le script exécutable (une seule fois) :
chmod +x shell.sh

Syntaxe générale :
./shell.sh <fichier_donnees> <mode> <parametres>

---

## Exemples

### Détection de fuites
./shell.sh c-wildwater_v3.dat leaks "Unit #GV001308I"

Génère le fichier `leaks_e.dat`.  
Si l’identifiant contient un `#`, utilisez des guillemets.

### Génération des statistiques et graphiques
./shell.sh c-wildwater_v3.dat histo all

Génère les fichiers `histo_*.dat` et les graphiques `.png`.

---

## Exécution manuelle (optionnel)

./wildwater c-wildwater_v3.dat leaks "Unit#GV001308I"

---

## Organisation du projet

.
├── main.c  
├── leak.c  
├── leak.h  
├── histo.c  
├── histo.h  
├── fonction_base.c  
├── shell.sh  
├── Makefile  
├── *.dat  
└── *.png  

---

## Auteurs

Nabil Touat  
oumeyma  lina



