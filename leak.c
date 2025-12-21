#include"leak.h"


/*
 * Lit une ligne du fichier et récupère les informations utiles.
 * Retourne 1 si une ligne est lue, 0 si fin de fichier.
 */
int recupereLigne1(FILE * nomFichier, char *id_us,char *id_amont,char *id_aval,double *cap, double *fuite){
    char ligne[300];
    id_us[0] = '\0';
    id_amont[0] = '\0';
    id_aval[0] = '\0';

    if(fgets(ligne,299,nomFichier) == NULL){
        return 0;
    }

    int i =0;
    int i2 = 0;
    int colonne = 1;
    char cap_char[100];
    char fuite_char[100];

    cap_char[0] = '\0';
    fuite_char[0] = '\0';

    while(ligne[i] != '\n' && ligne[i] != '\0'){
        if(ligne[i] == ';'){
            switch (colonne) {
                case 1: id_us[i2] = '\0'; break;
                case 2: id_amont[i2] = '\0'; break;
                case 3: id_aval[i2] = '\0'; break;
                case 4: cap_char[i2] = '\0'; break;
            }
            i2 = 0;
            colonne ++;
            i++;
        }
        else{
            switch(colonne){
                case 1: id_us[i2] = ligne[i]; break;
                case 2: id_amont[i2] = ligne[i]; break;
                case 3: id_aval[i2] = ligne[i]; break;
                case 4: cap_char[i2] = ligne[i]; break;
                case 5: fuite_char[i2] = ligne[i]; break;        
            }
            i2 ++;
            i++;
        }
    }

    fuite_char[i2] = '\0';

    if(cap_char[0] == '-'){
        *cap = 0;
    }
    else{
        *cap = strtod(cap_char,NULL);
    }

    if(fuite_char[0] == '-'){
        *fuite = 0.0;
    }
    else{
        *fuite = strtod(fuite_char,NULL);
    }
    return 1;
}


/*
 * Crée un nœud du réseau avec son identifiant.
 */
Noeud *creer_noeud(char *id){
    Noeud *n = malloc(sizeof(Noeud));
    if(n == NULL){
        exit(1);
    }
    n->identifiant = malloc(strlen(id) +1);
    if(n->identifiant == NULL){
        exit(2);
    }
    strcpy(n->identifiant,id);
    n->listes_enfants = NULL;
    return n;
}


/*
 * Ajoute un enfant à un nœud avec un pourcentage de fuite.
 */
void ajouter_enfant(Noeud *parent, Noeud *fils, double fuit){
    Enfant *c = malloc(sizeof(Enfant));
    if(c == NULL){
        exit(3);
    }
    c->pourcentage_fuite = fuit;
    c->noeud = fils;
    c->suivant = parent->listes_enfants;
    parent->listes_enfants = c;
}


/*
 * Compare deux chaînes.
 * 1 : plus petit, 2 : plus grand, 5 : égal.
 */
int comparer_chaine1(char *s1,char *s2) {
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
 * Recherche un nœud dans l’AVL à partir de son identifiant.
 */
Noeud* recherche_noeudAVL(Avl2 *a, char *id_usn){
	if(a == NULL){
		return NULL;
	}
	else if(comparer_chaine1(id_usn,a->id_cle) == 5){
		return a->valeur;
	}
	else if(comparer_chaine1(id_usn,a->id_cle) == 1){
		return recherche_noeudAVL(a->fg,id_usn);
	}
	else if(comparer_chaine1(id_usn,a->id_cle) == 2){
		return recherche_noeudAVL(a->fd,id_usn);
	}
	return NULL;
}


/*
 * Vérifie si une usine existe dans l’AVL.
 */
int retrouver_usine(Avl2 *a,char *id_usine, Noeud **usine){
    *usine = recherche_noeudAVL(a, id_usine);

    if(*usine == NULL){
        return -1;
    }
    return 0;
}


/*
 * Compte le nombre d’enfants d’un nœud.
 */
int compter_enfants(Enfant *e){
    int cpt = 0;
    while(e != NULL){
        cpt++;
        e = e->suivant;
    }
    return cpt;
}


/*
 * Calcule récursivement les fuites dans le réseau.
 */
double calcul_fuites(Noeud *n, double volume_entree){
    if(n == NULL || n->listes_enfants == NULL){
        return 0.0;
    }

    double total_fuites = 0.0;
    int nb_enfants = compter_enfants(n->listes_enfants);
    double volume_par_enfant = volume_entree / nb_enfants;

    Enfant *courant = n->listes_enfants;
    while(courant != NULL){
        double perte = volume_par_enfant * (courant->pourcentage_fuite / 100.0);
        double volume_restant = volume_par_enfant - perte;
        total_fuites += perte;
        total_fuites += calcul_fuites(courant->noeud, volume_restant);
        courant = courant->suivant;
    }

    return total_fuites;
}


/*
 * Conversion de km³ en Mm³.
 */
double km3_to_Mm3(double volume_km3){
    return volume_km3 /1000;
}


/*
 * Fonctions min et max simples.
 */
int min1(int a, int b) {
    if(a < b){
        return a;
    } 
    return b;
}

int max1(int a, int b) {
    if (a > b){
        return a;
    }    
    return b;
}

int min4(int a, int b, int c) {
    int m = a;
    if (b < m){
        m = b;
    }
    if (c < m){
        m = c;
    }
    return m;
}

int max4(int a, int b, int c) {
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
 * Rotations AVL pour garder l’arbre équilibré.
 */
Avl2* rotationDroite1(Avl2* a){
	Avl2* pivot;
	int eq_a, eq_p;
	
	pivot = a->fg;
	a->fg = pivot->fd;
	pivot->fd = a;
	
	eq_a = a->equilibre;
	eq_p = pivot->equilibre;
	
	a->equilibre = eq_a - min1(eq_p, 0) +1;
	pivot->equilibre = max4(eq_a+2, eq_a+eq_p+2, eq_p+1);
	
	return pivot;
}

Avl2 * rotationGauche1(Avl2* a){
	Avl2 * pivot;
	int eq_a, eq_p;
	
	pivot = a->fd;
	a->fd = pivot->fg;
	pivot->fg = a;
	
	eq_a = a->equilibre;
	eq_p = pivot->equilibre;
	
	a->equilibre = eq_a - max1(eq_p, 0) -1;
	pivot->equilibre = min4(eq_a-2, eq_a+eq_p-2, eq_p-1);
	
	return pivot;
}

Avl2* doubleRotationGauche1(Avl2* a){
	a->fd = rotationDroite1(a->fd);
	return rotationGauche1(a);
}

Avl2* doubleRotationDroite1(Avl2* a){
	a->fg = rotationGauche1(a->fg);
	return rotationDroite1(a);
}


/*
 * Rééquilibre un AVL si nécessaire.
 */
Avl2* equilibrerAVL1(Avl2* a){
	if(a==NULL){
		return NULL;
	}
	if(a->equilibre >= 2){
		if(a->fd != NULL && a->fd->equilibre >= 0){
			return rotationGauche1(a);
		}
		return doubleRotationGauche1(a);
	}
	else if(a->equilibre <= -2){
		if(a->fg != NULL && a->fg->equilibre <= 0){
			return rotationDroite1(a);
		}
		return doubleRotationDroite1(a);
	}
	return a;
}


/*
 * Crée un nœud AVL associant une clé à un nœud du réseau.
 */
Avl2 *creerAVL2(char *id, Noeud *val){
    Avl2 *a = malloc(sizeof(Avl2));
    if (a == NULL) {
        exit(4);
    }

    a->id_cle = malloc(strlen(id) + 1);
    if (a->id_cle == NULL){
        free(a);
        exit(5);
    }
    strcpy(a->id_cle, id);

    a->valeur = val;
    a->fg = NULL;
    a->fd = NULL;
    a->equilibre = 0;

    return a;
}


/*
 * Insère un élément dans l’AVL.
 */
Avl2* insertionAVL1(Avl2* a, char *e, Noeud *val,int *h){
	if(a==NULL){
		*h = 1;
		return creerAVL2(e,val);
	}
	else if(comparer_chaine1(e,a->id_cle) == 1){
		a->fg = insertionAVL1(a->fg, e, val,h);
		*h = -(*h);
	}
	else if(comparer_chaine1(e,a->id_cle) == 2){
		a->fd = insertionAVL1(a->fd, e, val,h);
	}
	else{
		*h = 0;
		return a;
	}
	if(*h != 0){
		a->equilibre = a->equilibre + *h;
		a = equilibrerAVL1(a);
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
 * Récupère un nœud du réseau ou le crée s’il n’existe pas.
 */
Noeud *recuperer_ou_creer_noeud(Avl2 **arbre, char *id){
    Noeud *n;
    int h = 0;

    if(id == NULL){
        return NULL;
    }
    if(comparer_chaine1(id, "-") == 5){
        return NULL;
    }

    n = recherche_noeudAVL(*arbre, id);
    if(n != NULL){
        return n;
    }

    n = creer_noeud(id);
    *arbre = insertionAVL1(*arbre, id, n, &h);
    return n;
}


/*
 * Construit le réseau à partir du fichier.
 */
int construire_reseau(FILE *f, Avl2 **arbre, char *id_usine, double *volume_entree_usine){
    char id_us[256];
    char id_amont[256];
    char id_aval[256];
    double cap;
    double fuite;

    Noeud *noeud_amont;
    Noeud *noeud_aval;

    *volume_entree_usine = 0.0;

    while(recupereLigne1(f, id_us, id_amont, id_aval, &cap, &fuite) == 1){
        if(comparer_chaine1(id_us, "-") == 5 &&
           comparer_chaine1(id_aval, id_usine) == 5 &&
           cap > 0){

            *volume_entree_usine += cap * (1.0 - fuite / 100.0);
            continue;
        }

        if(comparer_chaine1(id_us, "-") == 5 &&
           comparer_chaine1(id_amont, id_usine) == 5 &&
           id_aval[0] != '\0'){

            noeud_amont = recuperer_ou_creer_noeud(arbre, id_amont);
            noeud_aval  = recuperer_ou_creer_noeud(arbre, id_aval);

            if(noeud_amont && noeud_aval){
                ajouter_enfant(noeud_amont, noeud_aval, fuite);
            }
            continue;
        }

        if(comparer_chaine1(id_us, id_usine) == 5){
            noeud_amont = recuperer_ou_creer_noeud(arbre, id_amont);
            noeud_aval  = recuperer_ou_creer_noeud(arbre, id_aval);

            if(noeud_amont && noeud_aval){
                ajouter_enfant(noeud_amont, noeud_aval, fuite);
            }
        }
    }
    return 0;
}


/*
 * Écrit une ligne de fuite dans un fichier .dat.
 */
int ecrire_fuite_dat( char *nom_fichier, char *id_usine, double fuite_Mm3){
    FILE *f = fopen(nom_fichier, "a");
    if(f == NULL){
        return 1; 
    }
    fprintf(f, "%s;%fM.m3\n", id_usine, fuite_Mm3);
    fclose(f);
    return 0;
}


/*
 * Libère la liste des enfants.
 */
void liberer_enfants(Enfant *e){
    Enfant *tmp;
    while(e != NULL){
        tmp = e;
        e = e->suivant;
        free(tmp);
    }
}


/*
 * Libère un nœud du réseau.
 */
void liberer_noeud(Noeud *n){
    if(n == NULL){
        return;
    }
    free(n->identifiant);
    liberer_enfants(n->listes_enfants);
    free(n);
}


/*
 * Libère l’arbre AVL.
 */
void liberer_avl(Avl2 *a){
    if(a == NULL){
        return;
    }

    liberer_avl(a->fg);
    liberer_avl(a->fd);

    liberer_noeud(a->valeur);
    free(a->id_cle);
    free(a);
}


/*
 * Libère tout le réseau.
 */
void liberer_reseau(Avl2 **arbre){
    if(arbre == NULL || *arbre == NULL){
        return;
    }
    liberer_avl(*arbre);
    *arbre = NULL;
}














