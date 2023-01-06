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

void ajouterVoeu(VilleIUT **tiut, int *nbIUT, Candidat **tCand, int *nbCand, Phase *phase);
