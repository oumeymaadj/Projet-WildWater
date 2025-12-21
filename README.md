# :droplet: Projet C-WildWater (Projet CY-Tech PréING2)

Une application en C et Shell permettant d’analyser un réseau de distribution d’eau potable :
- traitement de données massives issues d’un fichier CSV  
- analyse des volumes captés, traités et réellement distribués  
- calcul des pertes d’eau sur l’ensemble du réseau aval d’une usine  
- génération d’histogrammes via gnuplot  
- gestion efficace des données grâce aux structures AVL  

---

## :file_folder: Descriptif des fichiers

### main.c
Point d’entrée principal du programme.  
Gère le choix du mode de fonctionnement (histogrammes ou calcul des fuites) et appelle les fonctions adaptées selon les arguments fournis.

### histo.c / histo.h
Gère la création et la manipulation d’un AVL d’usines.  
Implémente le calcul des capacités maximales, des volumes captés par les sources et des volumes réellement traités.  
Permet la génération des fichiers de données nécessaires aux histogrammes.

### fonction_base.c
Contient les fonctions de base liées aux AVL utilisés pour les histogrammes :  
création, insertion, recherche, équilibrage et libération de la mémoire, ainsi que la lecture et le traitement du fichier CSV.

### leak.c / leak.h
Implémente le calcul des fuites d’eau pour une usine donnée.  
Construit un réseau arborescent représentant l’aval de l’usine à l’aide d’un AVL de nœuds et de listes chaînées.  
Effectue un calcul récursif des pertes en tenant compte de la répartition équitable des volumes et des pourcentages de fuite.

### shell.sh
Script Shell servant de point d’entrée utilisateur.  
Vérifie la validité des arguments, compile le projet si nécessaire, lance le programme C et génère les histogrammes au format PNG à l’aide de gnuplot.  
Affiche également la durée totale d’exécution.

### Makefile
Automatise la compilation du projet et la génération de l’exécutable `wildwater`.  
Le Makefile ajoute également les droits d’exécution au script `shell.sh` afin de permettre son lancement direct depuis le terminal.  
Contient aussi une règle `clean` permettant de supprimer les fichiers générés.

---

## :arrow_forward: Compilation & exécution

1. Ouvrez un terminal à la racine du projet.  
2. Compilez le projet :
   ```
   make
   ```
   Cette commande compile le programme C et attribue automatiquement les droits d’exécution au script `shell.sh`.

3. Utilisez le script Shell pour lancer l’application.

### :bar_chart: Génération des histogrammes
```
./shell.sh <fichier_csv> histo <option>
```

Options disponibles :
- `max`  : capacité maximale de traitement des usines  
- `src`  : volume total capté par les sources  
- `real` : volume réellement traité après pertes  
- `all`  : histogramme cumulé des trois valeurs  

### :abacus: Calcul des fuites d’une usine
```
./shell.sh <fichier_csv> leaks "<identifiant_usine>"
```

Les résultats sont enregistrés dans des fichiers `.dat` et les graphiques sont générés au format `.png`.

---

## :broom: Nettoyage

Pour supprimer les fichiers générés (fichiers objets, exécutable, images PNG et fichiers `.dat`) :
```
make clean
```

---

## :busts_in_silhouette: Groupe

Oumeyma Adjaimi  
Nabil Touat  
Lina Porrinas  



