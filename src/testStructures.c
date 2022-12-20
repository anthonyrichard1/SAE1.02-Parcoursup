#include "structures.h"

int main (void)
{
    int nbIUT = 0;

    VilleIUT **tiut = chargerIUT(&nbIUT);
    
    afficherDepart(tiut, &nbIUT);
        
    return 0;
}
