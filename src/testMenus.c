#include "menus.h"

int main (void)
{
	VilleIUT** tiut;
	Candidat** tCand;
	int nbIUT, nbCand;

	tiut = chargerIUT(&nbIUT);
	tCand = chargerCandidats(&nbCand);

	menuPrincipal(tiut, tCand, &nbIUT, &nbCand);
	return 0;
}
