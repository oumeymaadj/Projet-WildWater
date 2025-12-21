#include "leak.h"
#include "histo.h"

int main(int argc, char *argv[]){

    /*
     * Cas du mode histogramme :
     * si le deuxième argument est "histo",
     * on génère le fichier demandé et on quitte le programme.
     */
    if (comparer_chaine(argv[2], "histo") == 5) {
        return creationFichier(argv[3], argv[1]);
    }

    /*
     * Déclaration des variables nécessaires
     * pour la construction du réseau et le calcul des fuites.
     */
    FILE *f = NULL;
    Avl2 *arbre = NULL;
    Noeud *usine = NULL;
    double volume_entree_usine;
    double fuite_km3;
    double fuite_Mm3;

    /*
     * Ouverture du fichier d’entrée contenant les données.
     */
    f = fopen(argv[1], "r");
    if (f == NULL) {
        return 1;
    }

    /*
     * Construction du réseau à partir du fichier
     * et calcul du volume entrant dans l’usine demandée.
     */
    construire_reseau(f, &arbre, argv[3], &volume_entree_usine);
    fclose(f);

    /*
     * Si aucun volume n’arrive à l’usine,
     * on écrit une valeur d’erreur et on termine.
     */
    if (volume_entree_usine == 0.0) {
        ecrire_fuite_dat("leaks_e.dat", argv[3], -1.0);
        liberer_reseau(&arbre);
        return 0;
    }

    /*
     * Recherche du nœud correspondant à l’usine.
     */
    usine = recherche_noeudAVL(arbre, argv[3]);
    if (usine == NULL) {
        ecrire_fuite_dat("leaks_e.dat", argv[3], -1.0);
        liberer_reseau(&arbre);
        return 0;
    }

    /*
     * Calcul des fuites à partir du volume entrant,
     * puis conversion de l’unité.
     */
    fuite_km3 = calcul_fuites(usine, volume_entree_usine);
    fuite_Mm3 = km3_to_Mm3(fuite_km3);

    /*
     * Écriture du résultat dans le fichier de sortie.
     */
    if (ecrire_fuite_dat("leaks_e.dat", argv[3], fuite_Mm3) != 0) {
        liberer_reseau(&arbre);
        return 2;
    }

    /*
     * Libération de la mémoire avant la fin du programme.
     */
    liberer_reseau(&arbre);
    return 0;
}

