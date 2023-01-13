#include "candidats.h"

int main(void)
{
    int nbCand = 0;
    Candidat **tCand = chargerCandidats(&nbCand);
    afficherCandidats(tCand, &nbCand);


    ajouterCandidats(tCand, &nbCand);

    sauvegarderCandidats(tCand, &nbCand, "candidats.don"); 
    
    return 0; 
}