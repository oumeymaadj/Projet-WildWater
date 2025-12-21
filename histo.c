#include"histo.h"



Avl* traiter_ligne_usine(Avl* racine, char *id, double capacite){
	Avl *n = rechercheAVL(racine,id);   // Recherche de l'usine dans l'AVL à partir de son identifiant
	if(n == NULL){                     // Si l'usine n'existe pas encore
		Usine u;                       // Création d'une nouvelle structure Usine
		u.id_usine = strdup(id);       // Duplication de l'identifiant
        if(u.id_usine == NULL){        // Vérification de l'allocation
            exit(1);                  // Arrêt du programme en cas d'échec
        }
		u.cap_max_trait = capacite;    // Initialisation de la capacité maximale
		u.volume_total_capte = 0;      // Initialisation du volume total capté
		u.volume_reel_traite = 0;      // Initialisation du volume réellement traité
		int h =0;                      // Variable indiquant la variation de hauteur
		racine = insertionAVL(racine,u,&h); // Insertion de la nouvelle usine dans l'AVL
	}
	else{
		n->us.cap_max_trait = capacite;// Mise à jour de la capacité si l'usine existe déjà
	}	
	return racine;                     // Retour de la racine mise à jour
}


Avl * traiter_ligne_source(Avl* racine, char *id, double volume, double fuite){
    Avl *n = rechercheAVL(racine,id);      // Recherche de l'usine correspondant à l'identifiant
	if(n == NULL){                         // Si l'usine n'existe pas encore dans l'AVL
		Usine u;                           // Création d'une nouvelle structure Usine
		u.id_usine = strdup(id);           // Duplication de l'identifiant
        if(u.id_usine == NULL){            // Vérification de l'allocation mémoire
            exit(2);                      // Arrêt du programme en cas d'échec
        }
		u.cap_max_trait = 0;               // Capacité de traitement inconnue à ce stade
		u.volume_total_capte = volume;     // Initialisation du volume total capté
		u.volume_reel_traite = volume * (1.0 - fuite / 100.0); // Calcul du volume réellement traité
		int h =0;                          // Variable de variation de hauteur
		racine = insertionAVL(racine,u,&h);// Insertion de la nouvelle usine dans l'AVL
	}
	else{                                  // Si l'usine existe déjà
		n->us.volume_total_capte += volume;// Ajout du volume capté
	    n->us.volume_reel_traite += volume *( 1.0 - fuite /100.0); // Ajout du volume réellement traité
	}
	return racine;                         // Retour de la racine mise à jour
}


int recupereLigne(FILE * nomFichier, char *id_us,char *id_amont,char *id_aval,double *cap, double *fuite){ // 1 si ligne recupoere 0 si plus de ligne
    char ligne[300];                               // Buffer pour stocker une ligne du fichier
    if(fgets(ligne,299,nomFichier) == NULL){       // Lecture d'une ligne du fichier
        return 0;                                  // Fin de fichier atteinte
    }
    int i =0;                                      // Indice de parcours de la ligne
    int i2 = 0;                                    // Indice pour remplir les champs
    int colonne = 1;                               // Numéro de la colonne courante
    char cap_char[100];                            // Chaîne pour stocker la capacité
    char fuite_char[100];                          // Chaîne pour stocker la fuite
    cap_char[0] = '\0';
    fuite_char[0] = '\0';                          // Initialisation de sécurité
    while(ligne[i] != '\n' && ligne[i] != '\0'){   // Parcours de la ligne caractère par caractère
        if(ligne[i] == ';'){                       // Détection d'un séparateur de colonne
            switch (colonne) {
                case 1: 
                    id_us[i2] = '\0';              // Fin de la chaîne id_us
                    break;
                case 2: 
                    id_amont[i2] = '\0';           // Fin de la chaîne id_amont
                    break;
                case 3: 
                    id_aval[i2] = '\0';            // Fin de la chaîne id_aval
                    break;
                case 4: 
                    cap_char[i2] = '\0';           // Fin de la chaîne capacité
                    break;
            }
            i2 = 0;                                // Réinitialisation de l'indice de champ
            colonne ++;                            // Passage à la colonne suivante
            i++;                                   // Avancement dans la ligne
        }
        else{
            switch(colonne){                       // Remplissage du champ correspondant à la colonne
                case 1:
                    id_us[i2] = ligne[i];          // Stockage de l'identifiant de l'usine
                    break;
                case 2:
                    id_amont[i2] = ligne[i];       // Stockage de l'identifiant amont
                    break;
                case 3:
                    id_aval[i2] = ligne[i];        // Stockage de l'identifiant aval
                    break;
                case 4:
                    cap_char[i2] = ligne[i];       // Stockage de la capacité
                    break;
                case 5:
                    fuite_char[i2] = ligne[i];     // Stockage du taux de fuite
                    break;
                default:
                    printf("erreur la phrase est trop longue \n"); // Cas d'erreur
            }
            i2 ++;                                 // Passage au caractère suivant du champ
            i++;                                   // Passage au caractère suivant de la ligne
        }
        
    }
    fuite_char[i2] = '\0';                          // Fin de la chaîne fuite
    if(cap_char[0] == '-'){                         // Cas capacité absente ou invalide
        *cap = 0;
    }
    else{
        *cap = strtod(cap_char,NULL);               // Conversion de la capacité en double
    }
    if(fuite_char[0] == '-'){                       // Cas fuite absente ou invalide
        *fuite = 0.0;
    }
    else{
        *fuite = strtod(fuite_char,NULL);           // Conversion de la fuite en double
    }
    return 1;                                       // Ligne correctement récupérée
}



Avl * ajouterVal(char *nom_fichier){
    Avl *avl = NULL;                                  // Initialisation de la racine de l'AVL
    FILE *fichier = fopen(nom_fichier,"r");           // Ouverture du fichier en lecture
    if(fichier == NULL){                              // Vérification de l'ouverture du fichier
        exit(5);                                      // Arrêt du programme en cas d'échec
    }
    char id_us[100];                                  // Tableau pour l'identifiant de l'usine
    char id_amont[100];                               // Tableau pour l'identifiant amont
    char id_aval[100];                                // Tableau pour l'identifiant aval
    double cap = 0;                                   // Variable pour la capacité
    double fuite = 0;                                 // Variable pour le taux de fuite
    while(recupereLigne(fichier,id_us,id_amont,id_aval,&cap,&fuite)){ // Lecture ligne par ligne du fichier
        if((id_us[0] == '-') && (id_aval[0] =='-') && (fuite == 0.0)){
            avl = traiter_ligne_usine(avl,id_amont,cap); // Traitement d'une ligne décrivant une usine
        }
        else if(id_us[0] == '-' && (cap != 0)){
            avl = traiter_ligne_source(avl,id_aval,cap,fuite); // Traitement d'une ligne décrivant une source
        }
    }
    fclose(fichier);                                  // Fermeture du fichier
    return avl;                                       // Retour de l'AVL construit
}


void ajouterFichierMAX(FILE *fichier, Avl *a){
    if(a != NULL){                                              // Si le nœud existe
        ajouterFichierMAX(fichier,a->fd);                       // Parcours du sous-arbre droit
        fprintf(fichier,"%s;%f\n",a->us.id_usine,a->us.cap_max_trait/1000.0); // Écriture de la capacité maximale
        ajouterFichierMAX(fichier,a->fg);                       // Parcours du sous-arbre gauche
    }
}

void ajouterFichierREAL(FILE *fichier, Avl *a){
    if(a != NULL){                                              // Si le nœud existe
        ajouterFichierREAL(fichier,a->fd);                      // Parcours du sous-arbre droit
        fprintf(fichier,"%s ; %fM.m3\n",a->us.id_usine,a->us.volume_reel_traite/1000.0); // Écriture du volume réellement traité
        ajouterFichierREAL(fichier,a->fg);                      // Parcours du sous-arbre gauche
    }
}

void ajouterFichierSRC(FILE *fichier, Avl *a){
    if(a != NULL){                                              // Si le nœud existe
        ajouterFichierSRC(fichier,a->fd);                       // Parcours du sous-arbre droit
        fprintf(fichier,"%s ; %fM.m3\n",a->us.id_usine,a->us.volume_total_capte/1000.0); // Écriture du volume total capté
        ajouterFichierSRC(fichier,a->fg);                       // Parcours du sous-arbre gauche
    }
}

void ajouterFichierALL(FILE *fichier, Avl *a){
    if(a != NULL){                                              // Si le nœud existe
        ajouterFichierALL(fichier,a->fd);                       // Parcours du sous-arbre droit
        fprintf(fichier,"%s ; %fM.m3 ; %fM.m3 ; %fM.m3 \n",a->us.id_usine,a->us.cap_max_trait/1000.0,a->us.volume_total_capte/1000.0,a->us.volume_reel_traite/1000.0); // Écriture de toutes les données
        ajouterFichierALL(fichier,a->fg);                       // Parcours du sous-arbre gauche
    }
}


int creationFichier(char *choix, char *nom_fichier){
    Avl *avl = NULL;                                      // Initialisation de l'arbre AVL
    avl = ajouterVal(nom_fichier);                        // Construction de l'AVL à partir du fichier
    if(avl == NULL){                                      // Si l'AVL est vide
        return 1;                                         // Erreur ou aucun traitement possible
    }
    if(comparer_chaine(choix,"max") == 5){                // Cas génération du fichier des capacités maximales
        FILE *fichier = fopen("histo_max.dat","w");       // Ouverture du fichier de sortie
        if(fichier == NULL){                              // Vérification de l'ouverture
            exit(5);                                      // Arrêt du programme en cas d'échec
        }
        fprintf(fichier, "identifier ; max volume (M.m3.year)\n"); // En-tête du fichier
        ajouterFichierMAX(fichier,avl);                   // Écriture des données dans le fichier
        fclose(fichier);                                  // Fermeture du fichier
    }
    else if(comparer_chaine(choix,"src") == 5){            // Cas génération du fichier des sources
        FILE *fichier = fopen("histo_src.dat","w");       // Ouverture du fichier de sortie
        if(fichier == NULL){                              // Vérification de l'ouverture
            exit(5);                                      // Arrêt du programme en cas d'échec
        }
        fprintf(fichier, "identifier ; source volume (M.m3.year)\n"); // En-tête du fichier
        ajouterFichierSRC(fichier,avl);                   // Écriture des données dans le fichier
        fclose(fichier);                                  // Fermeture du fichier
    }
    else if(comparer_chaine(choix,"real") == 5){           // Cas génération du fichier des volumes réels
        FILE *fichier = fopen("histo_real.dat","w");      // Ouverture du fichier de sortie
        if(fichier == NULL){                              // Vérification de l'ouverture
            exit(5);                                      // Arrêt du programme en cas d'échec
        }
        fprintf(fichier, "identifier ; real volume (M.m3.year)\n"); // En-tête du fichier
        ajouterFichierREAL(fichier,avl);                  // Écriture des données dans le fichier
        fclose(fichier);                                  // Fermeture du fichier
    }
    else if(comparer_chaine(choix,"all") == 5){            // Cas génération du fichier contenant toutes les données
        FILE *fichier = fopen("histo_all.dat","w");       // Ouverture du fichier de sortie
        if(fichier == NULL){                              // Vérification de l'ouverture
            exit(5);                                      // Arrêt du programme en cas d'échec
        }
        fprintf(fichier, "identifier ; max volume (M.m3.year) ; source volume (M.m3.year) ; real volume (M.m3.year)\n"); // En-tête du fichier
        ajouterFichierALL(fichier,avl);                   // Écriture de toutes les données
        fclose(fichier);                                  // Fermeture du fichier
    }
    else{                                                   // Cas choix invalide
        libererAVL(avl);                                   // Libération de la mémoire
        return 1;                                          // Erreur
    }
    libererAVL(avl);                                       // Libération de l'AVL
    return 0;                                              // Succès
}

