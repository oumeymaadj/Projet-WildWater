#include"histo.h"

Avl * creerAVL(Usine r){
    Avl* noeud = malloc(sizeof(Avl));   // Allocation mémoire pour un nouveau nœud AVL
	if(noeud == NULL){                 // Vérification de l’allocation
		exit(1);                        // Arrêt du programme en cas d’échec
	}

    // Copie des informations numériques de l'usine
    noeud->us.cap_max_trait = r.cap_max_trait;           // Capacité maximale de traitement
    noeud->us.volume_total_capte = r.volume_total_capte; // Volume total capté
    noeud->us.volume_reel_traite = r.volume_reel_traite; // Volume réellement traité

    // Allocation mémoire pour l'identifiant de l'usine
    noeud->us.id_usine = malloc(strlen(r.id_usine) + 1); // +1 pour le caractère '\0'
	if(noeud->us.id_usine == NULL){                       // Vérification de l’allocation
		exit(2);                                          // Arrêt du programme en cas d’échec
	}
    strcpy(noeud->us.id_usine, r.id_usine);               // Copie de l'identifiant de l'usine

    // Initialisation des pointeurs et du facteur d'équilibre
    noeud->fg = NULL;            // Fils gauche initialement vide
    noeud->fd = NULL;            // Fils droit initialement vide
    noeud->equilibre = 0;        // Facteur d’équilibre initial
    return noeud;                // Retour du nœud créé
}




int estVide(Avl * a){
    return (a==NULL);   // Retourne 1 si l'arbre est vide (pointeur NULL), 0 sinon
}



int existeFilsGauche(Avl * a){
	if(estVide(a)){              // Si l'arbre (ou le nœud) est vide
		return 0;               // Il n'a pas de fils gauche
	}
	else if(estVide(a->fg)){     // Si le fils gauche est vide
		return 0;               // Le fils gauche n'existe pas
	}
	else{
		return 1;               // Sinon, le fils gauche existe
	}
}



int existeFilsDroit(Avl * a){
	if(estVide(a)){              // Si l'arbre (ou le nœud) est vide
		return 0;               // Il n'a pas de fils droit
	}
	else if(estVide(a->fd)){     // Si le fils droit est vide
		return 0;               // Le fils droit n'existe pas
	}
	else{
		return 1;               // Sinon, le fils droit existe
	}
}



int min(int a, int b) {
    if(a < b){
        return a;      // Retourne la plus petite des deux valeurs
    } 
    else{
        return b;      // Retourne la plus petite des deux valeurs
    }    
}

int max(int a, int b) {
    if (a > b){
        return a;      // Retourne la plus grande des deux valeurs
    }    
    else{
        return b;      // Retourne la plus grande des deux valeurs
    }    
}

int min3(int a, int b, int c){
    int m = a;         // Initialisation avec la première valeur
    if (b < m){
	    m = b;         // Mise à jour si b est plus petit
	}
    if (c < m){
        m = c;        // Mise à jour si c est plus petit
	}	         
    return m;          // Retourne la plus petite des trois valeurs
}

int max3(int a, int b, int c){
    int m = a;         // Initialisation avec la première valeur
    if (b > m){
        m = b;         // Mise à jour si b est plus grand
	}
    if (c > m){
        m = c;         // Mise à jour si c est plus grand
	}
    return m;          // Retourne la plus grande des trois valeurs
}



Avl* rotationDroite(Avl* a){
	Avl* pivot;              // Nœud pivot pour la rotation droite
	int eq_a, eq_p;          // Variables pour stocker les facteurs d'équilibre
	
	pivot = a->fg;           // Le pivot est le fils gauche
	a->fg = pivot->fd;       // Le sous-arbre droit du pivot devient le fils gauche de a
	pivot->fd = a;           // a devient le fils droit du pivot
	
	eq_a = a->equilibre;     // Sauvegarde de l'équilibre de a
	eq_p = pivot->equilibre;// Sauvegarde de l'équilibre du pivot
	
	// Mise à jour du facteur d'équilibre du nœud a après rotation
	a->equilibre = eq_a - min(eq_p, 0) +1;
	
	// Mise à jour du facteur d'équilibre du pivot après rotation
	pivot->equilibre = max3(eq_a+2, eq_a+eq_p+2, eq_p+1);
	
	a = pivot;               // Le pivot devient la nouvelle racine du sous-arbre
	
	return a;                // Retour du nouveau sommet après rotation
}

Avl * rotationGauche(Avl* a){
	Avl * pivot;             // Nœud pivot pour la rotation gauche
	int eq_a, eq_p;          // Variables pour stocker les facteurs d'équilibre
	
	pivot = a->fd;           // Le pivot est le fils droit
	a->fd = pivot->fg;       // Le sous-arbre gauche du pivot devient le fils droit de a
	pivot->fg = a;           // a devient le fils gauche du pivot
	
	eq_a = a->equilibre;     // Sauvegarde de l'équilibre de a
	eq_p = pivot->equilibre;// Sauvegarde de l'équilibre du pivot
	
	// Mise à jour du facteur d'équilibre du nœud a après rotation
	a->equilibre = eq_a - max(eq_p, 0) -1;
	
	// Mise à jour du facteur d'équilibre du pivot après rotation
	pivot->equilibre = min3(eq_a-2, eq_a+eq_p-2, eq_p-1);
	
	a = pivot;               // Le pivot devient la nouvelle racine du sous-arbre
	
	return a;                // Retour du nouveau sommet après rotation
}


Avl* doubleRotationGauche(Avl* a){
	a->fd = rotationDroite(a->fd);   // Rotation droite sur le fils droit
	return rotationGauche(a);        // Puis rotation gauche sur le nœud courant
}

Avl* doubleRotationDroite(Avl* a){
	a->fg = rotationGauche(a->fg);   // Rotation gauche sur le fils gauche
	return rotationDroite(a);        // Puis rotation droite sur le nœud courant
}


Avl* equilibrerAVL(Avl* a){
	if(a==NULL){                      // Si l'arbre est vide
		return NULL;                  // Rien à équilibrer
	}
	if(a->equilibre >= 2){            // Déséquilibre à droite
		if(a->fd->equilibre >= 0){    // Cas rotation gauche simple
			return rotationGauche(a);
		}
		else{                          // Cas double rotation gauche (droite + gauche)
			return doubleRotationGauche(a);
		}
	}
	else if(a->equilibre <= -2){      // Déséquilibre à gauche
		if(a->fg->equilibre <= 0){    // Cas rotation droite simple
			return rotationDroite(a);
		}
		else{                          // Cas double rotation droite (gauche + droite)
			return doubleRotationDroite(a);
		}
	}
	return a;                         // Arbre déjà équilibré
}


int comparer_chaine(char *s1,char *s2) {
    int i = 0;

    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] < s2[i]) {
            return 1;   // s1 plus petite que s2
        }
        if (s1[i] > s2[i]) {
            return 2;   // s1 plus grande que s2
        }
        i++;
    }

    // Si on sort de la boucle, l'une (ou les deux) chaînes est terminée
    if (s1[i] == '\0' && s2[i] == '\0') {
        return 5;       // chaînes égales
    }
    else if (s1[i] == '\0') {
        return 1;       // s1 plus petite (plus courte)
    }
    else {
        return 2;       // s1 plus grande
    }
}


Avl* insertionAVL(Avl* a, Usine e, int *h){
	if(a==NULL){                          // Si l'arbre est vide
		*h = 1;                          // La hauteur augmente
		return creerAVL(e);              // Création d'un nouveau nœud
	}
	else if(comparer_chaine(e.id_usine,a->us.id_usine) == 1){
		a->fg = insertionAVL(a->fg, e, h); // Insertion dans le sous-arbre gauche
		*h = -(*h);                        // Inversion du signe de la variation de hauteur
	}
	else if(comparer_chaine(e.id_usine,a->us.id_usine) == 2){
		a->fd = insertionAVL(a->fd, e, h); // Insertion dans le sous-arbre droit
	}
	else{
		*h = 0;                           // Aucun changement de hauteur (clé déjà présente)
		return a;                         // Pas d'insertion
	}
	if(*h != 0){                          // Si la hauteur du sous-arbre a changé
		a->equilibre = a->equilibre + *h; // Mise à jour du facteur d'équilibre
		a = equilibrerAVL(a);             // Rééquilibrage éventuel de l'arbre
		if(a->equilibre == 0){
			*h = 0;                       // La hauteur ne change plus
		}
		else{
			*h = 1;                       // La hauteur augmente
		}
	}
	return a;                             // Retour de la racine mise à jour
}



void libererAVL(Avl* a){
    if(a != NULL){                 // Si le nœud existe
        libererAVL(a->fg);         // Libération récursive du sous-arbre gauche
        libererAVL(a->fd);         // Libération récursive du sous-arbre droit
        free(a->us.id_usine);      // Libération de la mémoire allouée pour l'identifiant de l'usine
        free(a);                   // Libération du nœud AVL
    }
}


Avl* rechercheAVL(Avl *a, char *id_usn){
	if(a == NULL){                                   // Si l'arbre est vide
		return NULL;                                // L'élément n'existe pas
	}
	else if(comparer_chaine(id_usn,a->us.id_usine) == 5){
		return a;                                   // Identifiant trouvé : retour du nœud
	}
	else if(comparer_chaine(id_usn,a->us.id_usine) == 1){
		return rechercheAVL(a->fg,id_usn);          // Recherche dans le sous-arbre gauche
	}
	else if(comparer_chaine(id_usn,a->us.id_usine) == 2){
		return rechercheAVL(a->fd,id_usn);          // Recherche dans le sous-arbre droit
	}
	return NULL;                                    // Cas de sécurité (non trouvé)
}








