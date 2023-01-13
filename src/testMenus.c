#include "menus.h"

int main (void)
{
	VilleIUT** tiut;
	Candidat** tCand;
	Phase phase = 0;
	int nbIUT, nbCand;
	printf("coucou\n");
	tiut = chargerIUT(&nbIUT);
	tCand = chargerCandidats(&nbCand);

	menuPrincipal(tiut, tCand, &nbIUT, &nbCand, &phase);
	return 0;
}
