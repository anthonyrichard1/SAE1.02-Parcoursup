#include "candidats.h"

int main(void)
{
    int nbCand = 1, nbIUT;

    VilleIUT **tiut = chargerIUT(&nbIUT);
    Candidat **tCand = chargerCandidats(&nbCand);
    afficherCandidats(tCand, &nbCand);


    ajouterCandidats(tCand, &nbCand);

    sauvegarderCandidats(tCand, &nbCand); 
    
    return 0; 
}