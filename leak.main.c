#include "leak.h"

int main(int argc, char *argv[]){
    FILE *f = NULL;
    Avl *arbre = NULL;
    Noeud *usine = NULL;
    double volume_entree_usine;
    double fuite_km3;
    double fuite_Mm3;
    f = fopen(argv[1], "r");
    if(f == NULL){
        perror("Erreur ouverture fichier");
        return 1;
    }
    construire_reseau(f, &arbre, argv[3], &volume_entree_usine);
    fclose(f);
    if(volume_entree_usine == 0.0){
        ecrire_fuite_dat("leaks.dat", argv[3], -1.0);
        liberer_reseau(&arbre);
        return 0;
    }
    usine = recherche_noeudAVL(arbre, argv[3]);
    if(usine == NULL){
        ecrire_fuite_dat("leaks.dat", argv[3], -1.0);
        liberer_reseau(&arbre);
        return 0;
    }
    fuite_km3 = calcul_fuites(usine, volume_entree_usine);
    fuite_Mm3 = km3_to_Mm3(fuite_km3);
    if(ecrire_fuite_dat("leaks.dat", argv[3], fuite_Mm3) != 0){
        fprintf(stderr, "Erreur écriture leaks.dat\n");
        liberer_reseau(&arbre);
        return 2;
    }
    liberer_reseau(&arbre);
    return 0;
}

