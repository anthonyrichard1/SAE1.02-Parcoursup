#include "structures.h" 
#include "erreur.h"

ListeDept creerListeDept(void);

VilleIUT **chargerIUT(int *nbIUT);

int rechercheIUT(VilleIUT **tab, int *nbIUT, char *val, bool *trouve);

void afficher1Depart(VilleIUT *v);

void afficherDepart(VilleIUT **tiut, int *nbIUT);

void afficherDepartPrecis(VilleIUT ** tiut, int *nbIUT);