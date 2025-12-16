#include"histo.h"

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