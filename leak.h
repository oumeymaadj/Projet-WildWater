#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>

typedef struct enfant Enfant;
typedef struct noeud Noeud;
typedef struct avl Avl;

typedef struct noeud{
    char *identifiant;
    Enfant *listes_enfants;
}Noeud;

typedef struct enfant{
    double pourcentage_fuite;
    Noeud *noeud;
    struct enfant *suivant;
}Enfant;

typedef struct avl {
    char *id_cle;          
    Noeud *valeur;      
    struct avl *fg;
    struct avl *fd;
    int equilibre;
}Avl;


int recupereLigne(FILE * nomFichier, char *id_us,char *id_amont,char *id_aval,double *cap, double *fuite);
Noeud *creer_noeud(char *id);
void ajouter_enfant(Noeud *parent, Noeud *fils, double fuit);
int comparer_chaine(char *s1,char *s2);
Noeud* recherche_noeudAVL(Avl *a, char *id_usn);
int retrouver_usine(Avl *a,char *id_usine, Noeud **usine);
int compter_enfants(Enfant *e);
double calcul_fuites(Noeud *n, double volume_entree);
double km3_to_Mm3(double volume_km3);
int min(int a, int b);
int max(int a, int b);
int min3(int a, int b, int c);
int max3(int a, int b, int c);
Avl* rotationDroite(Avl* a);
Avl * rotationGauche(Avl* a);
Avl* doubleRotationGauche(Avl* a);
Avl* doubleRotationDroite(Avl* a);
Avl* equilibrerAVL(Avl* a);
Avl *creerAVL(char *id, Noeud *val);
Avl* insertionAVL(Avl* a, char *e, Noeud *val,int *h);
Noeud *recuperer_ou_creer_noeud(Avl **arbre, char *id);
int construire_reseau(FILE *f, Avl **arbre, char *id_usine, double *cap_usine);
int ecrire_fuite_dat(const char *nom_fichier, const char *id_usine, double fuite_Mm3);
void liberer_enfants(Enfant *e);
void liberer_noeud(Noeud *n);
void liberer_avl(Avl *a);
void liberer_reseau(Avl **arbre);

