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
				
				while (i >= pos)
				{
					ntiut[i+1] = ntiut[i];
					i--;
				}
				
				ntiut[pos] = iut;
				printf(VERT"IUT ajouté !\n"BLANC);
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

void supprimerIUT(VilleIUT **tiut, int *nbIUT)
{
	char choix[30] = "";
	int pos, trouve, i;	

	while (strcmp(choix, "-1") != 0)
	{
		printf("Entrez le nom de l'IUT à supprimer (-1 pour annuler) : ");
		scanf("%s", choix);

		if (strcmp(choix, "-1") != 0)
		{
			pos = rechercheIUT(tiut, nbIUT, choix, &trouve);

			if (trouve)
			{
				for (i = pos; i < *nbIUT-2 ; i++)
				{
					tiut[pos] = tiut[pos+1];
				}

				*nbIUT-=1;
				printf(VERT"IUT supprimé !\n"BLANC);
			}
			else fprintf(stderr, ROUGE"Erreur : l'IUT est introuvable !\n"BLANC);
		}
	}
}

void supprimerDepart(VilleIUT **tiut, int *nbIUT)
{
	// a faire quand on aura la recherche depart
}

void ModifPlaces(VilleIUT** tiut, int *nbIUT) {
	char ville[30] = "", dept[30] = "";
	Bool trouve;
	int pos;
	MaillonDept* tmp;

	while (strcmp(ville, "-1") != 0 && strcmp(dept, "-1") != 0) {
		printf("\nEntrez le nom de la ville où ce trouve le département (-1 pour annuler) : ");
		scanf("%s%*c", ville);
		
		if (strcmp(ville, "-1") != 0) {
			pos = rechercheIUT(tiut, nbIUT, ville, &trouve);

			if(trouve == 1) {
				printf("\nEntrez le nom du département pour lequel vous souhaitez modifier le nombre de place (-1 pour annuler) : ");
				scanf("%s%*c", dept);

				if (strcmp(dept, "-1") != 0) {
					for(tmp=tiut[pos]->ldept->premier; tmp; tmp = tmp->suivant) {									
						if(strcmp(tmp->departement, dept) == 0) {
							printf("Dans le département %s de %s, il y a %d places.\nNouveau nombre de place : ", dept, ville, tmp->nbP);
							scanf("%d", &tmp->nbP);

							printf(VERT"Nombre de place modifié"BLANC);
							afficher1Depart(tiut[pos]);
						}	
						else {
							printf(ROUGE"Le département que vous cherchez n'a pas été trouvé.\n"BLANC);
						}	
					} 
				}
			}
			else {
				printf(ROUGE"L'IUT que vous cherchez n'a pas été trouvé.\n"BLANC);
			}
		}
	}
}
