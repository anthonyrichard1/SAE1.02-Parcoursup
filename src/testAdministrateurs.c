#include "administrateurs.h"

int main(void)
{
	int nbIUT;
	VilleIUT **tiut = chargerIUT(&nbIUT);
	//tiut = ajouterIUT(tiut, &nbIUT);
	//printf("%d\n", nbIUT);
	//afficherDepart(tiut, &nbIUT);
	//supprimerIUT(tiut, &nbIUT);
	//printf("%d\n", nbIUT);
	supprimerDepart(tiut, &nbIUT);
	afficherDepart(tiut, &nbIUT);
	return 0;
}
