#include "menus.h"

int main (void)
{
	VilleIUT** tiut;
	int nbIUT;

	tiut = chargerIUT(&nbIUT);

	menuPrincipal(tiut, &nbIUT);
	return 0;
}
