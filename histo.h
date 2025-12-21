#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>

/* 
 * Structure représentant une usine.
 * Elle regroupe les informations nécessaires au suivi des capacités
 * et des volumes traités par une usine donnée.
 */
typedef struct{
    char *id_usine;
    double cap_max_trait;
    double volume_total_capte;
    double volume_reel_traite;
}Usine;

/*
 * Structure d’un nœud d’arbre AVL.
 * Chaque nœud contient une usine ainsi que les pointeurs vers
 * ses sous-arbres gauche et droit, et son facteur d’équilibrage.
 */
typedef struct avl{
    Usine us;
    struct avl *fg;
    struct avl *fd;
    int equilibre;
}Avl;



Avl * creerAVL(Usine r);
int estVide(Avl * a);
int existeFilsDroit(Avl * a);
int existeFilsGauche(Avl * a);
int min(int a, int b);
int max(int a, int b);
int min3(int a, int b, int c);
int max3(int a, int b, int c);
Avl* rotationDroite(Avl* a);
Avl * rotationGauche(Avl* a);
Avl* doubleRotationGauche(Avl* a);
Avl* doubleRotationDroite(Avl* a);
Avl* equilibrerAVL(Avl* a);
int comparer_chaine(char *s1,char *s2);
Avl* insertionAVL(Avl* a, Usine e, int *h);
Avl* rechercheAVL(Avl *a, char *id_usn);
void libererAVL(Avl* a);
Avl* traiter_ligne_usine(Avl* racine, char *id, double capacite);
Avl * traiter_ligne_source(Avl* racine, char *id, double volume, double fuite);
int recupereLigne(FILE * nomFichier, char *id_us,char *id_amont,char *id_aval,double *cap, double *fuite);
Avl * ajouterVal(char *nom_fichier);
void ajouterFichierMAX(FILE *fichier, Avl *a);
void ajouterFichierREAL(FILE *fichier, Avl *a);
void ajouterFichierSRC(FILE *fichier, Avl *a);
void ajouterFichierALL(FILE *fichier, Avl *a);
int creationFichier(char *choix, char *nom_fichier);

