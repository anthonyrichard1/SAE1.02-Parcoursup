#include "administrateurs.h"

VilleIUT **ajouterIUT(VilleIUT **tiut, int *nbIUT)
{
	char ville[30] = "";
	int pos, trouve, i;
	
	while (strcmp(ville, "-1") != 0)
	{
		printf("Entrez le nom de la ville à ajouter (-1 pour annuler) : ");
		scanf("%s", ville);
		
		if (strcmp(ville, "-1") != 0)
		{
			pos = rechercheIUT(tiut, nbIUT, ville, &trouve);
			
			if (!trouve)
			{
				i = *nbIUT-1;
				*nbIUT += 1;
				VilleIUT **ntiut = (VilleIUT**)realloc(tiut, sizeof(VilleIUT*)*(*nbIUT));
				testMalloc(tiut, "agrandissement du tableau des IUT");
				
				VilleIUT *iut = (VilleIUT*)malloc(sizeof(VilleIUT));
				testMalloc(iut, "IUT");
				
				strcpy(iut->ville, ville);
				iut->ldept = creerListeDept();
				
				//décalage
				
				while (i >= pos)
				{
					ntiut[i+1] = ntiut[i];
					i--;
				}
				
				ntiut[pos] = iut;
				
				return ntiut;
			}
			else
			{
				fprintf(stderr, ROUGE"Erreur : la ville %s est déjà enregistrée !\n"BLANC, ville);
			}
		}
	}
	
	printf("Abandon de l'opération...\n");
	return tiut;
}
