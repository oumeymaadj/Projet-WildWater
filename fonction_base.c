#include"histo.h"


/*
 * Crée un nouveau nœud AVL à partir d’une usine.
 * Alloue la mémoire et initialise les champs.
 */
Avl * creerAVL(Usine r){
    Avl* noeud = malloc(sizeof(Avl));
	if(noeud == NULL){
		exit(1);
	}

	noeud->us.cap_max_trait = r.cap_max_trait;
	noeud->us.volume_total_capte = r.volume_total_capte;
	noeud->us.volume_reel_traite = r.volume_reel_traite;

	noeud->us.id_usine = malloc(strlen(r.id_usine) + 1);
	if(noeud->us.id_usine == NULL){
		exit(2);
	}
	strcpy(noeud->us.id_usine, r.id_usine);

	noeud->fg = NULL;
	noeud->fd = NULL;
	noeud->equilibre = 0;

	return noeud;
}


/*
 * Teste si l’arbre est vide.
 */
int estVide(Avl * a){
    return (a==NULL);
}


/*
 * Indique si un nœud a un fils gauche.
 */
int existeFilsGauche(Avl * a){
	if(estVide(a) || estVide(a->fg)){
		return 0;
	}
	return 1;
}


/*
 * Indique si un nœud a un fils droit.
 */
int existeFilsDroit(Avl * a){
	if(estVide(a) || estVide(a->fd)){
		return 0;
	}
	return 1;
}


/*
 * Fonctions simples pour trouver min et max.
 * Utilisées dans les calculs d’équilibrage.
 */
int min(int a, int b) {
    if(a < b){
        return a;
    } 
    return b;
}

int max(int a, int b) {
    if (a > b){
        return a;
    }    
    return b;
}

int min3(int a, int b, int c){
    int m = a;
    if (b < m){
	    m = b;
	}
    if (c < m){
        m = c;
	}	         
    return m;
}

int max3(int a, int b, int c){
    int m = a;
    if (b > m){
        m = b;
	}
    if (c > m){
        m = c;
	}
    return m;
}


/*
 * Rotation droite pour rééquilibrer l’arbre.
 */
Avl* rotationDroite(Avl* a){
	Avl* pivot;
	int eq_a, eq_p;
	
	pivot = a->fg;
	a->fg = pivot->fd;
	pivot->fd = a;
	
	eq_a = a->equilibre;
	eq_p = pivot->equilibre;
	
	a->equilibre = eq_a - min(eq_p, 0) +1;
	pivot->equilibre = max3(eq_a+2, eq_a+eq_p+2, eq_p+1);
	
	return pivot;
}


/*
 * Rotation gauche pour rééquilibrer l’arbre.
 */
Avl * rotationGauche(Avl* a){
	Avl * pivot;
	int eq_a, eq_p;
	
	pivot = a->fd;
	a->fd = pivot->fg;
	pivot->fg = a;
	
	eq_a = a->equilibre;
	eq_p = pivot->equilibre;
	
	a->equilibre = eq_a - max(eq_p, 0) -1;
	pivot->equilibre = min3(eq_a-2, eq_a+eq_p-2, eq_p-1);
	
	return pivot;
}


/*
 * Doubles rotations utilisées dans certains cas.
 */
Avl* doubleRotationGauche(Avl* a){
	a->fd = rotationDroite(a->fd);
	return rotationGauche(a);
}

Avl* doubleRotationDroite(Avl* a){
	a->fg = rotationGauche(a->fg);
	return rotationDroite(a);
}


/*
 * Rééquilibre un nœud AVL si nécessaire.
 */
Avl* equilibrerAVL(Avl* a){
	if(a==NULL){
		return NULL;
	}
	if(a->equilibre >= 2){
		if(a->fd->equilibre >= 0){
			return rotationGauche(a);
		}
		return doubleRotationGauche(a);
	}
	else if(a->equilibre <= -2){
		if(a->fg->equilibre <= 0){
			return rotationDroite(a);
		}
		return doubleRotationDroite(a);
	}
	return a;
}


/*
 * Compare deux chaînes caractère par caractère.
 */
int comparer_chaine(char *s1,char *s2) {
    int i = 0;

    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] < s2[i]) {
            return 1;
        }
        if (s1[i] > s2[i]) {
            return 2;
        }
        i++;
    }

    if (s1[i] == '\0' && s2[i] == '\0') {
        return 5;
    }
    else if (s1[i] == '\0') {
        return 1;
    }
    else {
        return 2;
    }
}


/*
 * Insère une usine dans l’arbre AVL
 * et garde l’arbre équilibré.
 */
Avl* insertionAVL(Avl* a, Usine e, int *h){
	if(a==NULL){
		*h = 1;
		return creerAVL(e);
	}
	else if(comparer_chaine(e.id_usine,a->us.id_usine) == 1){
		a->fg = insertionAVL(a->fg, e, h);
		*h = -(*h);
	}
	else if(comparer_chaine(e.id_usine,a->us.id_usine) == 2){
		a->fd = insertionAVL(a->fd, e, h);
	}
	else{
		*h = 0;
		return a;
	}
	if(*h != 0){
		a->equilibre += *h;
		a = equilibrerAVL(a);
		if(a->equilibre == 0){
			*h = 0;
		}
		else{
			*h = 1;
		}
	}
	return a;
}


/*
 * Libère toute la mémoire de l’arbre AVL.
 */
void libererAVL(Avl* a){
    if(a != NULL){
        libererAVL(a->fg);
        libererAVL(a->fd);
        free(a->us.id_usine);
        free(a);
    }
}


/*
 * Recherche une usine dans l’arbre AVL
 * à partir de son identifiant.
 */
Avl* rechercheAVL(Avl *a, char *id_usn){
	if(a == NULL){
		return NULL;
	}
	else if(comparer_chaine(id_usn,a->us.id_usine) == 5){
		return a;
	}
	else if(comparer_chaine(id_usn,a->us.id_usine) == 1){
		return rechercheAVL(a->fg,id_usn);
	}
	else if(comparer_chaine(id_usn,a->us.id_usine) == 2){
		return rechercheAVL(a->fd,id_usn);
	}
	return NULL;
}







