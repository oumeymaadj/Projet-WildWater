#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>

typedef struct{
    char *id_usine;               // Identifiant de l'usine (chaîne de caractères)
    double cap_max_trait;         // Capacité maximale de traitement de l'usine
    double volume_total_capte;    // Volume total capté par l'usine
    double volume_reel_traite;    // Volume réellement traité par l'usine
}Usine;

typedef struct avl{
    Usine us;                     // Données de l'usine stockées dans le nœud
    struct avl *fg;               // Pointeur vers le fils gauche (sous-arbre gauche)
    struct avl *fd;               // Pointeur vers le fils droit (sous-arbre droit)
    int equilibre;                // Facteur d'équilibre du nœud (AVL)
}Avl;



Avl * creerAVL(Usine r);                         // Crée un nouveau nœud AVL
int estVide(Avl * a);                           // Vérifie si l'arbre est vide
int existeFilsDroit(Avl * a);                   // Vérifie s'il y a un fils droit
int existeFilsGauche(Avl * a);                  // Vérifie s'il y a un fils gauche
int min(int a, int b);                          // Retourne le plus petit des deux
int max(int a, int b);                          // Retourne le plus grand des deux
int min3(int a, int b, int c);                  // Retourne le plus petit des trois
int max3(int a, int b, int c);                  // Retourne le plus grand des trois
Avl* rotationDroite(Avl* a);                    // Rotation droite de l'arbre
Avl * rotationGauche(Avl* a);                   // Rotation gauche de l'arbre
Avl* doubleRotationGauche(Avl* a);              // Double rotation gauche
Avl* doubleRotationDroite(Avl* a);              // Double rotation droite
Avl* equilibrerAVL(Avl* a);                     // Rééquilibre l'arbre AVL
int comparer_chaine(char *s1,char *s2);         // Compare deux chaînes
Avl* insertionAVL(Avl* a, Usine e, int *h);     // Ajoute une usine dans l'AVL
void libererAVL(Avl* a);                        // Libère la mémoire de l'AVL
Avl* rechercheAVL(Avl *a, char *id_usn);        // Cherche une usine par son id
Avl* traiter_ligne_usine(Avl* racine, char *id, double capacite); // Traite une ligne usine
Avl * traiter_ligne_source(Avl* racine, char *id, double volume, double fuite); // Traite une ligne source -> usine
int recupereLigne(FILE * nomFichier, char *id_us,char *id_amont,char *id_aval,double *cap, double *fuite); // Lit une ligne du fichier
Avl * ajouterVal(char *nom_fichier);            // Crée l'AVL à partir du fichier
void ajouterFichierMAX(FILE *fichier, Avl *a);  // Écrit les valeurs max dans un fichier
void ajouterFichierREAL(FILE *fichier, Avl *a); // Écrit les valeurs réelles dans un fichier
void ajouterFichierSRC(FILE *fichier, Avl *a);  // Écrit les valeurs source dans un fichier
void ajouterFichierALL(FILE *fichier, Avl *a);  // Écrit toutes les valeurs dans un fichier
int creationFichier(char *choix, char *nom_fichier); // Crée le fichier final selon le choix


