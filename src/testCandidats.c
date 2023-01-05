#include "candidats.h"

int main(void)
{
    int nbCand = 3;
    Candidat **tCand = (Candidat**)malloc(sizeof(Candidat*)*MAX_CANDIDATS);
    testMalloc(tCand, "création d'un tableau de candidats");
    
        Candidat *t = (Candidat*)malloc(sizeof(Candidat));
        testMalloc(t, "création d'un candidat");

        strcpy(t->nom, "D");
        tCand[0] = t;

        Candidat *u = (Candidat*)malloc(sizeof(Candidat));
        testMalloc(u, "création d'un candidat");

        strcpy(u->nom, "Z");
        tCand[1] = u;

        Candidat *v = (Candidat*)malloc(sizeof(Candidat));
        testMalloc(v, "création d'un candidat");

        strcpy(v->nom, "A");
        tCand[2] = v;
        

    triAlpha(tCand, nbCand);

    //printf("%s %s %s", tCand[0]->nom, tCand[1]->nom, tCand[2]->nom);

    
    return 0;
}