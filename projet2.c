#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_C 20  // Définit la taille maximale d'une chaîne de caractères à 20
// fct copie colle prise de differenete corection pour nous donner des sources de fct pas pour les copier coller tel qu'elle une sorte de repertoire de fonction utile est possible 
typedef struct chainon_struct {
    char value[MAX_C];                // Le contenu du chainon, ici une chaîne de caractères
    struct chainon_struct* previous;  // Pointeur vers l'élément précédent dans la liste
    struct chainon_struct* next;      // Pointeur vers l'élément suivant dans la liste
} Chainon;


typedef struct liste_struct {
    Chainon* tete;  // Pointeur vers le premier élément de la liste
    Chainon* fin;   // Pointeur vers le dernier élément de la liste
} Liste;

Chainon* creationChainon(char* str) {
    // Vérification si la chaîne d'entrée est nulle
    if (str == NULL) {
        exit(EXIT_FAILURE);  // Si oui, on quitte le programme
    }
    // Vérification que la chaîne ne dépasse pas la taille maximale
    if (strlen(str) > MAX_C) {
        exit(EXIT_FAILURE);  // Si oui, on quitte le programme
    }

    Chainon* nouveau = malloc(sizeof(Chainon));
    if (nouveau == NULL) {
        exit(EXIT_FAILURE);  // Si l'allocation échoue, on quitte le programme
    }

    // Copier la chaîne de caractères dans le nouveau chainon
    strcpy(nouveau->value, str);
    nouveau->previous = NULL;  // Le pointeur vers le chainon précédent est initialisé à NULL
    nouveau->next = NULL;      // Le pointeur vers le chainon suivant est initialisé à NULL
    return nouveau;            // Retourne le nouveau chainon créé
}

Liste creationListe() {
    Liste lst;
    lst.tete = NULL;  // Initialise la tête de la liste à NULL (liste vide)
    lst.fin = NULL;   // Initialise la fin de la liste à NULL (liste vide)
    return lst;       // Retourne la liste vide créée
}

pArbre creerArbre(int e) {
    pArbre new = malloc(sizeof(Arbre));
    if (new == NULL) {           // Vérifie si l'allocation mémoire a réussi
        exit(EXIT_FAILURE);
    }
    new->fd = NULL;              // Initialisation du fils droit à NULL
    new->fg = NULL;              // Initialisation du fils gauche à NULL
    new->value = e;              // Assigne la valeur au nœud
    return new;
}
AVL* creerAVL(int e)
{
    // Alloue de la mémoire pour un nouveau nœud
    AVL* new = (AVL* )malloc(sizeof(AVL));
    if (new == NULL)
    {
        exit(EXIT_FAILURE); // Arrêt immédiat en cas d'erreur d'allocation
    }
    new->value = e; // Initialisation de la valeur
    new->fg = NULL; // Pas de fils gauche
    new->fd = NULL; // Pas de fils droit
    new->eq = 0;    // Facteur d'équilibre initialisé à 0
    return new;
}
AVL* insertionAVL(AVL* a, int e, int *h)
{
    if (a == NULL)
    {           // Si l'arbre est vide, crée un nouveau nœud
        *h = 1; // La hauteur a augmenté
        return creerAVL(e);
    }
    else if (e < a->value)
    { // Si l'élément est plus petit, insérer à gauche
        a->fg = insertionAVL(a->fg, e, h);
        *h = -*h; // Inverse l'impact de la hauteur
    }
    else if (e > a->value)
    { // Si l'élément est plus grand, insérer à droite
        a->fd = insertionAVL(a->fd, e, h);
    }
    else
    { // Élément déjà présent
        *h = 0;
        return a;
    }

    // Mise à jour du facteur d'équilibre et rééquilibrage si nécessaire
    if (*h != 0)
    {
        a->eq += *h;
        a = equilibrerAVL(a);
        *h = (a->eq == 0) ? 0 : 1; // Mise à jour de la hauteur
    }
    return a;
}



