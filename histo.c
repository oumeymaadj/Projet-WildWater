#include"histo.h"


/*
 * Traite une ligne décrivant une usine.
 * Ajoute l’usine si elle n’existe pas ou met à jour sa capacité.
 */
Avl* traiter_ligne_usine(Avl* racine, char *id, double capacite){
	Avl *n = rechercheAVL(racine,id);
	if(n == NULL){
		Usine u;
		u.id_usine = strdup(id);
        if(u.id_usine == NULL){
            exit(1);
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


/*
 * Traite une ligne décrivant une source.
 * Met à jour les volumes captés et réellement traités.
 */
Avl * traiter_ligne_source(Avl* racine, char *id, double volume, double fuite){
    Avl *n = rechercheAVL(racine,id);
	if(n == NULL){
		Usine u;
		u.id_usine = strdup(id);
        if(u.id_usine == NULL){
            exit(2);
        }
		u.cap_max_trait = 0;
		u.volume_total_capte = volume;
		u.volume_reel_traite = volume * (1.0 - fuite / 100.0);
		int h =0;
		racine = insertionAVL(racine,u,&h);
	}
	else{
		n->us.volume_total_capte += volume;
	    n->us.volume_reel_traite += volume *( 1.0 - fuite /100.0);
	}
	return racine;
}


/*
 * Lit une ligne du fichier et sépare les champs.
 * Retourne 1 si une ligne est lue, 0 sinon.
 */
int recupereLigne(FILE * nomFichier, char *id_us,char *id_amont,char *id_aval,double *cap, double *fuite){
    char ligne[300];
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
                default:
                    printf("erreur la phrase est trop longue \n");
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
 * Construit l’arbre AVL à partir du fichier d’entrée.
 */
Avl * ajouterVal(char *nom_fichier){
    Avl *avl = NULL;
    FILE *fichier = fopen(nom_fichier,"r");
    if(fichier == NULL){
        exit(5);
    }

    char id_us[100];
    char id_amont[100];
    char id_aval[100];
    double cap = 0;
    double fuite = 0;

    while(recupereLigne(fichier,id_us,id_amont,id_aval,&cap,&fuite)){
        if((id_us[0] == '-') && (id_aval[0] =='-') && (fuite == 0.0)){
            avl = traiter_ligne_usine(avl,id_amont,cap);
        }
        else if(id_us[0] == '-' && (cap != 0)){
            avl = traiter_ligne_source(avl,id_aval,cap,fuite);
        }
    }
    fclose(fichier);
    return avl;
}


/*
 * Écrit les capacités maximales dans un fichier.
 */
void ajouterFichierMAX(FILE *fichier, Avl *a){
    if(a != NULL){
        ajouterFichierMAX(fichier,a->fd);
        fprintf(fichier,"%s;%f\n",a->us.id_usine,a->us.cap_max_trait/1000.0);
        ajouterFichierMAX(fichier,a->fg);
    }
}


/*
 * Écrit les volumes réellement traités.
 */
void ajouterFichierREAL(FILE *fichier, Avl *a){
    if(a != NULL){
        ajouterFichierREAL(fichier,a->fd);
        fprintf(fichier,"%s ; %fM.m3\n",a->us.id_usine,a->us.volume_reel_traite/1000.0);
        ajouterFichierREAL(fichier,a->fg);
    }
}


/*
 * Écrit les volumes provenant des sources.
 */
void ajouterFichierSRC(FILE *fichier, Avl *a){
    if(a != NULL){
        ajouterFichierSRC(fichier,a->fd);
        fprintf(fichier,"%s ; %fM.m3\n",a->us.id_usine,a->us.volume_total_capte/1000.0);
        ajouterFichierSRC(fichier,a->fg);
    }
}


/*
 * Écrit toutes les données disponibles.
 */
void ajouterFichierALL(FILE *fichier, Avl *a){
    if(a != NULL){
        ajouterFichierALL(fichier,a->fd);
        fprintf(fichier,"%s ; %fM.m3 ; %fM.m3 ; %fM.m3 \n",
                a->us.id_usine,
                a->us.cap_max_trait/1000.0,
                a->us.volume_total_capte/1000.0,
                a->us.volume_reel_traite/1000.0);
        ajouterFichierALL(fichier,a->fg);
    }
}


/*
 * Crée le fichier final selon le choix demandé.
 */
int creationFichier(char *choix, char *nom_fichier){
    Avl *avl = NULL;
    avl = ajouterVal(nom_fichier);

    if(avl == NULL){
        return 1;
    }

    if(comparer_chaine(choix,"max") == 5){
        FILE *fichier = fopen("histo_max_e.dat","w");
        if(fichier == NULL){
            exit(5);
        }
        fprintf(fichier, "identifier ; max volume (M.m3.year)\n");
        ajouterFichierMAX(fichier,avl);
        fclose(fichier);
    }
    else if(comparer_chaine(choix,"src") == 5){
        FILE *fichier = fopen("histo_src_e.dat","w");
        if(fichier == NULL){
            exit(5);
        }
        fprintf(fichier, "identifier ; source volume (M.m3.year)\n");
        ajouterFichierSRC(fichier,avl);
        fclose(fichier);
    }
    else if(comparer_chaine(choix,"real") == 5){
        FILE *fichier = fopen("histo_real_e.dat","w");
        if(fichier == NULL){
            exit(5);
        }
        fprintf(fichier, "identifier ; real volume (M.m3.year)\n");
        ajouterFichierREAL(fichier,avl);
        fclose(fichier);
    }
    else if(comparer_chaine(choix,"all") == 5){
        FILE *fichier = fopen("histo_all_e.dat","w");
        if(fichier == NULL){
            exit(5);
        }
        fprintf(fichier, "identifier ; max volume (M.m3.year) ; source volume (M.m3.year) ; real volume (M.m3.year)\n");
        ajouterFichierALL(fichier,avl);
        fclose(fichier);
    }
    else{
        libererAVL(avl);
        return 1;
    }

    libererAVL(avl);
    return 0;
}
