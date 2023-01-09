#include "candidats.h"

int main(void)
{
    int nbCand = 1, nbIUT;
    
    Phase phase = 1;
    Candidat **tCand = chargerCandidats(&nbCand);
    printf("num : %d nom : %s prenom : %s notes %f %f %f %f\n", tCand[0]->num, tCand[0]->nom, tCand[0]->prenom, tCand[0]->notes[0], tCand[0]->notes[1], tCand[0]->notes[2], tCand[0]->notes[3]);
    printf("nbVoeux : %d\n", tCand[0]->nbChoix);
    /* Candidat **tCand = (Candidat **)malloc(sizeof(Candidat *)*100);
    testMalloc(tCand, "tCand");
    printf("nbCand : %d\n", nbCand);

    //testMalloc(tCand, "création d'un tableau de candidats");

    Candidat *t = (Candidat*)malloc(sizeof(Candidat));
    testMalloc(t, "création d'un candidat");

    strcpy(t->nom, "RICHARD");
    strcpy(t->prenom, "Anthony");
    t->num = 1;
    t->notes[0] = 10;
    t->notes[1] = 20;
    t->notes[2] = 30;
    t->notes[3] = 40;
    t->nbChoix = 0;
    t->choix = creerListeVoeux();

    VilleIUT **tiut = chargerIUT(&nbIUT);

    tCand[0] = t;

    ajouterVoeu(tiut, &nbIUT, tCand, &nbCand, &phase);
    printf("nbVoeux : %d ville : %s depart : %s\n", tCand[0]->nbChoix, tCand[0]->choix->premier->ville, tCand[0]->choix->dernier->ville);
    sauvegarderCandidats(tCand, &nbCand); */
    
    return 0; 
}