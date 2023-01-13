#include "responsable.h"

float calculMoyenne(float notes[]) {
	int i;
	float moyenne;

	for(i=0; i < 4; ++i) {
		moyenne += notes[i];
	}

	return moyenne/4;
}

Voeu* chercherVoeux(ListeVoeux l, char *iut, char *dept) {
	for(; l->premier != NULL; l->premier = l->premier->suivant) {
		if(strcmp(l->premier->ville, iut) == 0 && strcmp(l->premier->departement, dept) == 0) {
			return l->premier;
		}
	}
	return NULL;
}

void filtrerCandidatures(Candidats **tCand, int *nbCand)
{
	float noteMin = -5;

	saisieFloatControlee(&noteMin, "Quel est la note minimale pour être admis dans votre département (-1 pour annuler) : ");

	while ((noteMin < 0 || noteMin != -1) || noteMin > 20)
	{
		saisieFloatControlee(&noteMin, "Quel est la note minimale pour être admis dans votre département (-1 pour annuler) : ");
	}

	printf(UNDERLINE"Pour le département Informatique de l'IUT de Clermont-Ferrand :\n"RESET);
}