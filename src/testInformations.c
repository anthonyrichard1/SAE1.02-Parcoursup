#include "informations.h"

int main(void)
{
	int nbIUT;
	VilleIUT **tiut = chargerIUT(&nbIUT);
	afficherDepart(tiut, &nbIUT);
	return 0;
}
