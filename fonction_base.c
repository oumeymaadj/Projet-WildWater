#include"histo.h"

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



int estVide(Avl * a){
    return (a==NULL);
}

int existeFilsGauche(Avl * a){
	if(estVide(a)){
		return 0;
	}
	else if(estVide(a->fg)){
		return 0;
	}
	else{
		return 1;
	}
}


int existeFilsDroit(Avl * a){
	if(estVide(a)){
		return 0;
	}
	else if(estVide(a->fd)){
		return 0;
	}
	else{
		return 1;
	}
}


int min(int a, int b) {
    if(a < b){
        return a;
    } 
    else{
        return b;
    }    
}

int max(int a, int b) {
    if (a > b){
        return a;
    }    
    else{
        return b;
    }    
}


int min3(int a, int b, int c) {
    int m = a;
    if (b < m)
        m = b;
    if (c < m)
        m = c;
    return m;
}

int max3(int a, int b, int c) {
    int m = a;
    if (b > m)
        m = b;
    if (c > m)
        m = c;
    return m;
}


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
	a = pivot; 
	
	return a;
}


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
	a = pivot; 
	
	return a;
}

Avl* doubleRotationGauche(Avl* a){
	a->fd = rotationDroite(a->fd);
	return rotationGauche(a);
}

Avl* doubleRotationDroite(Avl* a){
	a->fg = rotationGauche(a->fg);
	return rotationDroite(a);
}

Avl* equilibrerAVL(Avl* a){
	if(a==NULL){
		return NULL;
	}
	if(a->equilibre >= 2){
		if(a->fd->equilibre >= 0){
			return rotationGauche(a);
		}
		else{
			return doubleRotationGauche(a);
		}
	}
	else if(a->equilibre <= -2){
		if(a->fg->equilibre <= 0){
			return rotationDroite(a);
		}
		else{
			return doubleRotationDroite(a);
		}
	}
	return a;
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
		a->equilibre = a->equilibre + *h;
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




void libererAVL(Avl* a){
    if(a != NULL){
        libererAVL(a->fg);
        libererAVL(a->fd);
        free(a->us.id_usine);
        free(a);
    }
}

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







