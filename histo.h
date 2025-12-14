#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>

typedef struct{
    char *id_usine;
    double cap_max_trait;
    double volume_total_capte;
    double volume_reel_traite;
}Usine;

typedef struct avl{
    Usine us;
    struct avl *fg;
    struct avl *fd;
    int equilibre;  
}Avl;


