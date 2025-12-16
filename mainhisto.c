#include"histo.h"

int main(int argc, char **argv){
    if(argc < 4){
        return 1;
    }

    if(comparer_chaine(argv[2], "histo") == 5){
        return creationFichier(argv[3], argv[1]);
    }

    return 1;
}
