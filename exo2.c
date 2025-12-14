#include <stdio.h>
#include <stdlib.h>

typedef struct Arbre{
	int element;
	struct Arbre *fg, *fd;
	int equilibre;
}Arbre;

typedef Arbre *pArbre;

pArbre creerArbre(int r){
	pArbre noeud;
	noeud = malloc(sizeof(Arbre));
	noeud->element = r;
	noeud->fg = NULL;
	noeud->fd = NULL;
	noeud->equilibre = 0;
	return noeud;
}

int estVide(pArbre a){
	return (a==NULL);
}

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

int existeFilsDroit(pArbre a){
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

int ajouterFilsGauche(pArbre a, int e){
	if(estVide(a)){
		return 0;
	}
	else if(!existeFilsGauche(a)){
		a->fg = creerArbre(e);
		return 1;
	}
	else{
		return 0;
	}	
}

int ajouterFilsDroit(pArbre a, int e){
	if(estVide(a)){
		return 0;
	}
	else if(!existeFilsDroit(a)){
		a->fd = creerArbre(e);
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


pArbre rotationDroite(pArbre a){
	pArbre pivot;
	int eq_a, eq_p;
	
	pivot = a->fg;
	a->fg = pivot->fd;
	pivot->fd = a;
	
	eq_a = a->equilibre;
	eq_p = pivot->equilibre;
	
	a->equilibre = eq_a - min(eq_p, 0) +1;
	pivot->equilibre = max(eq_a+2, eq_a+eq_p+2, eq_p+1);
	a = pivot; 
	
	return a;
}


pArbre rotationGauche(pArbre a){
	pArbre pivot;
	int eq_a, eq_p;
	
	pivot = a->fd;
	a->fd = pivot->fg;
	pivot->fg = a;
	
	eq_a = a->equilibre;
	eq_p = pivot->equilibre;
	
	a->equilibre = eq_a - max(eq_p, 0) -1;
	pivot->equilibre = min(eq_a-2, eq_a+eq_p-2, eq_p-1);
	a = pivot; 
	
	return a;
}

pArbre doubleRotationGauche(pArbre a){
	a->fd = rotationDroite(a->fd));
	return rotationGauche(a);
}

pArbre doubleRotationDroite(pArbre a){
	a->fg = rotationDroite(a->fg));
	return rotationDroite(a);
}

pArbre insertionAVL(pArbre a, int e, int *h){
	if(a==NULL){
		*h = 1;
		return creerArbre(e);
	}
	else if(e < a->element){
		a->fg = insertionAVL(a->fg, e, h);
		*h = -*h;
	}
	else if(e > a->element){
		a->fd = insertionAVL(a->fd, e, h);
	}
	else{
		*h = 0;
		return a;
	}
	if(*h != 0){
		a->equilibre = a->equilibre + *h;
		if(a->equilibre == 0){
			*h = 0;
		}
		else{
			*h = 1;
		}
	}
	return a;
}

pArbre suppMinAVL(pArbre a, int *h, int *pe){
	pArbre tmp; 
	if(a->fg == NULL){
		*pe = a->element;
		*h = -1;
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
		if(a->equilibre == 0){
			*h = -1;
		}
		else{
			*h = 0;
		}
	}
	return a;
}

pArbre suppressionAVL(pArbre a, int e, int *h){
	pArbre tmp;
	
	if(a==NULL){
		*h = 0;
		return a;
	}
	else if(e > a->element){
		a->fd = suppressionAVL(a->fd, e);
	}
	else if(e < a->element){
		a->fg = suppressionAVL(a->fg, e);
		*h = -*h;
	}
	else if(existeFilsDroit(a)){
		a->fd = suppMinAVL(a->fd, h, &(a->element));
	}
	else{
		tmp = a;
		a = a->fg;
		free(tmp);
		*h = -1;
		return a;
	}
	
	if(*h != 0){
		a->equilibre = a-> equilibre + *h;
		if(a->equilibre == 0){
			*h = -1;
		}
		else{
			*h = 0;
		}
	}
	return a;
}

pArbre equilibrerAVL(pArbre a){
	if(a->equilibre >= 2){
		if(a->fd->equilibre >= 0){
			return rotationGauche(a));
		}
		else{
			return doubleRotationGauche(a));
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


int main(){
	pArbre racine = creerArbre(1);
	racine->fd = ajouterFilsDroit(racine, 2);
	racine->fd->fd = ajouterFilsDroit(racine->fd,3);
	
	
}

//Partie shell

#!/bin/bash

# ON SUPPOSE FICHIER S APPLEE WILDWATER

comment le prog c va savoir le choix de l utilsateur genre hito leaks 
generation de l histo 
gener un fcihier csv selon le choix de l user max src etc avec en tete avec les donne utile dans l rodre alphabetique inverse

max unsine 
src souce usine 
real usine ety source usine
# aff dure totale en ms
duree_totale() {
    fin_tps=$(date +%s)
    r_duree=$((fin_tps - START_TIME))
    echo "La durée totale est : $((r_duree * 1000)) mili-seconde"
}

#aff une erreur et art le script
fct_error() {
    echo "Erreur : $1" >&2
    duree_totale
    exit 1
}


# récupérer les arguments ecrit ds terlmianl
recup_arg() {
    if [ $# -lt 2 ]; then
        fct_error "Reesayer manque d'arguments"
    fi

    fichier_d="$1" #chemin du fichier
    Type="$2" #histo ou leaks 
    OPTION="$3" # max src real id usine
    NB_ARG=$# #nb argument
}


# vérif la validité des arguments
arg_valid_T() {
    case "$Type" in
        histo)
            if [ "$NB_ARG" -ne 3 ]; then
                fct_error "Nombre d'arguments insuffisant pour histo !"
            fi
            if [ "$OPTION" != "max" ] && [ "$OPTION" != "src" ] && [ "$OPTION" != "real" ]; then
                fct_error "Option invalide (max | src | real)"
            fi
            ;;
        leaks)
            if [ "$NB_ARG" -ne 3 ]; then # le prog shell ne verifie pas si l' id existe ou pas !
                fct_error "Nombre d'arguments insuffisant pour leaks !"
            fi
            ;;
        *)
            fct_error "Type inconnu (histo | leaks)"
            ;;
    esac
}


# vérif l'existence/ lecrure fichier
verif_fichier() {
    if [ ! -f "$fichier_d" ]; then # si fichier
        fct_error "Fichier introuvable : ("
    fi

    if [ ! -r "$fichier_d" ]; then # si on permission de le lire
        fct_error "Fichier non lisible"
    fi
}























