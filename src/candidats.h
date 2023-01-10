/**
 * \file candidats.h
 * \author Anthony RICHARD
 * \author Léana BESSON
 * \date 14/12/2022
 * \brief Dans ce fichier sont repertoriées les structures utilisées par l'application.
*/
#include "structures.h"
#include "responsable.h"

Phase afficherPhase(Phase *phase);

void triAlpha(Candidat **tCand, int nbCand);

ListeVoeux creerListeVoeux(void);

Voeu *creerVoeu(char *iut, char *dept);

int existeVoeu(Candidat *c, char *iut, char *depart);

void ajouterVoeu(VilleIUT **tiut, int *nbIUT, Candidat **tCand, int *nbCand, Phase *phase);

void sauvegarderCandidats(Candidat **tCand, int *nbCand);

Candidat **chargerCandidats(int *nbCand);

void afficher1Candidat(Candidat **tCand, int pos);

void afficherCandidats(Candidat **tCand, int *nbCand);

void afficherCandidatsDepart(Candidat **tCand, int *nbCand);

char *upperfcase(char *motIn);

char *uppercase(char *motIn);
