#include "structures.h" 
#include "candidats.h"

ListeDept creerListeDept(void);

VilleIUT **chargerIUT(int *nbIUT);

void testMalloc(void *elt, char *procedure);

int testFopen(char *nomFichier);

int rechercheIUT(VilleIUT **tab, int *nbIUT, char *val, bool *trouve);

void afficher1Depart(VilleIUT *v);

void afficherDepart(VilleIUT **tiut, int *nbIUT);
