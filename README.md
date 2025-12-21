# Projet C-WildWater
Filière PréING2 – Année 2025–2026

## Auteurs
- Adjaimi Oumeyma
- Nabil
- Lina Porrinas

## Description générale
Ce projet a pour objectif de développer une application permettant d’analyser et de synthétiser des données massives issues d’un système de distribution d’eau potable.  
Les données sont fournies sous la forme d’un fichier CSV décrivant les différents acteurs du réseau (sources, usines de traitement, stockages, jonctions, raccordements et usagers), ainsi que les volumes d’eau et les pertes associées.

L’application repose sur deux parties principales :
- un programme en langage C, chargé des calculs lourds et du traitement des données,
- un script Shell, servant de point d’entrée utilisateur, assurant la vérification des arguments, la compilation, l’exécution du programme et la génération des graphiques.

## Organisation du projet
.
├── main.c              : programme principal
├── histo.c / histo.h   : gestion des histogrammes (AVL des usines)
├── fonction_base.c     : fonctions AVL et lecture du fichier CSV pour les histogrammes
├── leak.c / leak.h     : calcul des fuites (réseau aval et AVL des nœuds)
├── shell.sh            : script Shell (interface utilisateur)
├── Makefile            : compilation du projet
├── README.md           : documentation

## Compilation
La compilation du projet est entièrement gérée par le Makefile.

Commande de compilation :
make

Cette commande génère l’exécutable :
wildwater

Le script shell.sh est automatiquement rendu exécutable.

## Utilisation
Le script shell.sh constitue le point d’entrée unique de l’application.

### Histogrammes des usines
Commande :
./shell.sh <fichier_csv> histo <option>

Options possibles :
- max  : capacité maximale de traitement des usines
- src  : volume total capté par les sources
- real : volume réellement traité après pertes
- all  : histogramme cumulé des trois valeurs (option bonus)

Exemples :
./shell.sh data.csv histo max
./shell.sh data.csv histo src
./shell.sh data.csv histo real
./shell.sh data.csv histo all

Résultats :
- génération d’un fichier .dat contenant les données
- création d’images .png représentant les histogrammes via gnuplot

### Calcul des fuites d’une usine
Commande :
./shell.sh <fichier_csv> leaks "<identifiant_usine>"

Exemple :
./shell.sh c-wildwater_v0.csv leaks "Facility complex #RH400057F"

Résultats :
- ajout d’une ligne dans le fichier leaks_e.dat contenant l’identifiant de l’usine et le volume total de fuites
- si l’usine n’existe pas ou si aucun volume n’arrive à l’usine, la valeur -1 est enregistrée

## Choix techniques
- Utilisation de structures AVL pour garantir une complexité logarithmique lors des recherches et insertions.
- Lecture du fichier CSV ligne par ligne afin de limiter l’empreinte mémoire.
- Construction d’un réseau arborescent pour le calcul récursif des fuites en aval d’une usine.
- Libération systématique de la mémoire allouée avant la fin du programme.
- Séparation claire entre les calculs (programme C) et l’orchestration/visualisation (script Shell et gnuplot).

## Tests et résultats
Les fichiers .dat et les images .png générés lors des tests sont reproductibles à partir des commandes décrites ci-dessus, en utilisant le fichier CSV fourni.

## Nettoyage
Pour supprimer les fichiers générés (fichiers objets, exécutable, images et données) :
make clean

## Remarques
- Le programme est générique et peut fonctionner avec tout fichier CSV respectant la même structure.
- Les erreurs d’arguments ou de fichiers sont gérées par le script Shell avec des messages explicites.
- La durée totale d’exécution du script est affichée à la fin de chaque traitement.

