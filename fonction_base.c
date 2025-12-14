#include"histo.h"

Avl * creerAVL(Usine r){
    Avl* noeud = malloc(sizeof(Avl));

    noeud->us.cap_max_trait = r.cap_max_trait;
    noeud->us.volume_total_capte = r.volume_total_capte;
    noeud->us.volume_reel_traite = r.volume_reel_traite;

    noeud->us.id_usine = malloc(strlen(r.id_usine) + 1);
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

int ajouterFilsGauche(Avl * a, Usine e){
	if(estVide(a)){
		return 0;
	}
	else if(!existeFilsGauche(a)){
		a->fg = creerAVL(e);
		return 1;
	}
	else{
		return 0;
	}	
}

int ajouterFilsDroit(Avl * a, Usine e){
	if(estVide(a)){
		return 0;
	}
	else if(!existeFilsDroit(a)){
		a->fd = creerAVL(e);
		return 1;
	}
	else{
		return 0;
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


Avl* suppMinAVL(Avl* a, int *h, Usine *pe){
	Avl* tmp; 
	if(a->fg == NULL){
		free(pe->id_usine);
		pe->id_usine = a->us.id_usine;
        pe->cap_max_trait = a->us.cap_max_trait;
        pe->volume_total_capte = a->us.volume_total_capte;
        pe->volume_reel_traite = a->us.volume_reel_traite;
		*h = -1;
		tmp = a;
		a = a->fd;
		free(tmp);
		return a;
	}
	else{
		a->fg = suppMinAVL(a->fg, h, pe);
		*h = -*h;
	}
	
	if(*h != 0){
		a->equilibre = a->equilibre + *h;
		a = equilibrerAVL(a);
		if(a->equilibre == 0){
			*h = -1;
		}
		else{
			*h = 0;
		}
	}
	return a;
}


Avl* suppressionAVL(Avl* a, Usine e, int *h){
	Avl* tmp;
	
	if(a==NULL){
		*h = 0;
		return a;
	}
	else if(comparer_chaine(e.id_usine, a->us.id_usine) == 2){
		a->fd = suppressionAVL(a->fd, e,h);
	}
	else if(comparer_chaine(e.id_usine, a->us.id_usine) == 1){
		a->fg = suppressionAVL(a->fg, e,h);
		*h = -*h;
	}
	else{
		if(existeFilsDroit(a)){
		    a->fd = suppMinAVL(a->fd, h, &(a->us));
	    }
	    else{
		    tmp = a;
		    a = a->fg;
		    free(tmp);
		    *h = -1;
		    return a;
	    }
    }
	if(*h != 0){
		a->equilibre = a->equilibre + *h;
		a = equilibrerAVL(a);
		if(a->equilibre == 0){
			*h = -1;
		}
		else{
			*h = 0;
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

Avl* traiter_ligne_usine(Avl* racine, char *id, double capacite){
	Avl *n = rechercheAVL(racine,id);
	if(n == NULL){
		Usine u;
		u.id_usine = strdup(id);
		if(u.id_usine == NULL){
			exit(3);
		}
		u.cap_max_trait = capacite;
		u.volume_total_capte = 0;
		u.volume_reel_traite = 0;
		int h =0;
		racine = insertionAVL(racine,u,&h);
	}
	else{
		n->us.cap_max_trait = capacite;
	}	
	return racine;

}

Avl * traiter_ligne_source(Avl* racine, char *id, double volume, double fuite){
	Avl *n = rechercheAVL(racine,id);
	if(n == NULL){
		Usine u;
		u.id_usine = strdup(id);
		if(u.id_usine == NULL){
			exit(3);
		}
		u.cap_max_trait = 0;
		u.volume_total_capte = volume;
		u.volume_reel_traite = volume * (1.0 -  fuite / 100.0);
		int h =0;
		racine = insertionAVL(racine,u,&h);
	}
	else{
		n->us.volume_total_capte += volume;
	    n->us.volume_reel_traite += volume *( 1.0 - fuite /100.0);   
	}
	return racine;
}



/// ----------------------------------------------------------------------------------------------




Avl* lire_fichier_histo(char *nom_fichier)
{
    FILE *f = fopen(nom_fichier, "r");
    if (f == NULL) {
        perror("Erreur ouverture fichier histo");
        exit(1);
    }

    Avl *racine = NULL;
    char ligne[256];

    while (fgets(ligne, sizeof(ligne), f)) {

        // enlever le \n
        ligne[strcspn(ligne, "\n")] = '\0';

        char *type = strtok(ligne, ";");

        if (type == NULL) continue;

        // ----- CAS USINE -----
        if (strcmp(type, "USINE") == 0) {

            char *id = strtok(NULL, ";");
            char *cap_str = strtok(NULL, ";");

            if (id == NULL || cap_str == NULL) {
                printf("Ligne USINE invalide\n");
                continue;
            }

            double capacite = atof(cap_str);
            racine = traiter_ligne_usine(racine, id, capacite);
        }

        // ----- CAS SOURCE -----
        else if (strcmp(type, "SOURCE") == 0) {

            char *id = strtok(NULL, ";");
            char *vol_str = strtok(NULL, ";");
            char *fuite_str = strtok(NULL, ";");

            if (id == NULL || vol_str == NULL || fuite_str == NULL) {
                printf("Ligne SOURCE invalide\n");
                continue;
            }

            double volume = atof(vol_str);
            double fuite = atof(fuite_str);

            if (!traiter_ligne_source(racine, id, volume, fuite)) {
                printf("Erreur traitement SOURCE pour %s\n", id);
                fclose(f);
                exit(2);
            }
        }
    }

    fclose(f);
    return racine;
}


/// -----------------------------------------------------------------------------------------------


//On va faire un parcours infixe récursif.

void ecrire_resultat_histo_rec_inverse(Avl *a, FILE *f)
{
    if (a == NULL){
		return ;
	}

    ecrire_resultat_histo_rec(a->fd, f);

    fprintf(f, "%s;%.2f;%.2f;%.2f\n",
            a->us.id_usine,
            a->us.cap_max_trait / 1000.0,
            a->us.volume_total_capte / 1000.0,
            a->us.volume_reel_traite / 1000.0);

    ecrire_resultat_histo_rec(a->fg, f);
}

void ecrire_resultat_histo(Avl *racine,char *nom_fichier)
{
    FILE *f = fopen(nom_fichier, "w");
    if (f == NULL) {
        perror("Erreur ouverture fichier resultat histo");
        exit(4);
    }

    // en-tête
    fprintf(f, "id_usine;cap_max;volume_capte;volume_reel\n");

    ecrire_resultat_histo_rec(racine, f);

    fclose(f);
}


