#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>

typedef struct enfant Enfant;

typedef struct noeud{
    char *identifiant;
    Enfant *listes_enfants;
}Noeud;

typedef struct enfant{
    double pourcentage_fuite;
    Noeud *noeud;
    struct enfant *suivant;
}Enfant;

typedef struct avl2 {
    char *id_cle;          
    Noeud *valeur;      
    struct avl2 *fg;
    struct avl2 *fd;
    int equilibre;
}Avl2;


int recupereLigne1(FILE * nomFichier, char *id_us,char *id_amont,char *id_aval,double *cap, double *fuite);
Noeud *creer_noeud(char *id);
void ajouter_enfant(Noeud *parent, Noeud *fils, double fuit);
int comparer_chaine1(char *s1,char *s2);
Noeud* recherche_noeudAVL(Avl2 *a, char *id_usn);
int retrouver_usine(Avl2 *a,char *id_usine, Noeud **usine);
int compter_enfants(Enfant *e);
double calcul_fuites(Noeud *n, double volume_entree);
double km3_to_Mm3(double volume_km3);
int min1(int a, int b);
int max1(int a, int b);
int min4(int a, int b, int c);
int max4(int a, int b, int c);
Avl2* rotationDroite1(Avl2* a);
Avl2 * rotationGauche1(Avl2* a);
Avl2* doubleRotationGauche1(Avl2* a);
Avl2* doubleRotationDroite1(Avl2* a);
Avl2* equilibrerAVL1(Avl2* a);
Avl2 *creerAVL2(char *id, Noeud *val);
Avl2* insertionAVL1(Avl2* a, char *e, Noeud *val,int *h);
Noeud *recuperer_ou_creer_noeud(Avl2 **arbre, char *id);
int construire_reseau(FILE *f, Avl2 **arbre, char *id_usine, double *cap_usine);
int ecrire_fuite_dat(char *nom_fichier,char *id_usine, double fuite_Mm3);
void liberer_enfants(Enfant *e);
void liberer_noeud(Noeud *n);
void liberer_avl(Avl2 *a);
void liberer_reseau(Avl2 **arbre);

