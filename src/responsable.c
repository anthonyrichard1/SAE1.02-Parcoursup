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