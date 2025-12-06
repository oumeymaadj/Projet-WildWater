#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>



typedef struct chaine
{
    char* value;
    struct chaine* prev;
    struct chaine* next; 
} Chainon;


typedef struct fil
{
    Chainon* tete; 
    Chainon* fin; 
    int nb; 
} File ;


typedef struct av
{
    int value;             
    int eq;                
    struct av *fg; 
    struct av *fd; 
} Avl;


int max(int a,int b)
{
    return (a > b) ? a : b;
}

int min(int a,int b)
{
    return (a < b) ? a : b;
}

int alea(int max,int min)
{
    return min +rand()%(max-min+1);
}

int comparechaine(char *ch1, char *ch2)
{
    return strcmp(ch1,ch2) == 0;
}

void copierchaine(char *dest, char *chaine)
{
    strcpy(dest,chaine);
}

void tricroissant(int tab,int *n)
{
    int tmp;
    for(int i=0 ;i<n-1 ;i++)
    {
        for(int j=0 ;j<n-1-i ;j++)
        {
            if(tab[j]>tab[j+1])
            {
                tmp = tab[j];
                tab[j] = tab[j+1];
                tab[j+1] = tmp;
            }
        }

    }
}
void tridecroissant(int tab,int *n)
{
    int tmp;
    for(int i=0 ;i<n-1 ;i++)
    {
        for(int j=0 ;j<n-1-i ;j++)
        {
            if(tab[j]<tab[j+1])
            {
                tmp = tab[j];
                tab[j] = tab[j+1];
                tab[j+1] = tmp;
            }
        }

    }
}





