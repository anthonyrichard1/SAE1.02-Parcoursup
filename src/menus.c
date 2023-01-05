#include "menus.h"

void menuPrincipal(VilleIUT** tiut, int *nbIUT) 
{
	int choix;
	char motDePasse[12];

	while (1) {
		printf("\n----------------------------------------\n");

		printf(
		"\nMenu principal\n\n"
		"1 - Afficher les informations des IUT\n"
		"2 - Afficher les villes où il y a un département\n"
		"3 - \n"
		"4 - \n"
		"7 - Menu des administrateurs\n\n"
		"9 - Menu principal\n"
		"Votre choix : ");

		scanf("%d", &choix);

		switch (choix) {
			case 1 :
				afficherDepart(tiut, nbIUT);
				break;

			case 2 :
				afficherDepartPrecis(tiut, nbIUT);
				break;

			case 3 :
				
				break;

			case 4 :
				
				break;

			case 7 :
				printf("\n----------------------------------------\n");

				printf("\nEntrez le mot de passe : ");
				scanf("%s%*c", motDePasse);
				if(strcmp(motDePasse, "motdepasse102") != 0) {
					fprintf(stderr, ROUGE"Mot de passe incorrect..."BLANC);
				}
				else {
					menuAdministrateur(tiut, nbIUT);
				}
				break;

			case 9 :
				sauvegarde(tiut, nbIUT);
				exit(0);

			default :
				printf("\n\e[1;91mChoix incorrect, recommencez\e[0m\n");
				break;
		}
	}
}

void menuAdministrateur(VilleIUT** tiut, int *nbIUT) 
{
	int choix;
	
	while (1) {
		printf("\n----------------------------------------\n");
		
		printf(
		"\nMenu des administrateurs\n\n"
		"1 - Créer un IUT\n"
		"2 - Créer un département\n"
		"3 - Supprimer un IUT\n"
		"4 - Supprimer un département\n"
		"5 - Lancer la phase de candidature\n"
		"6 - Arrêter la phase de candidature\n"
		"7 - Modifier le nombre de places\n"
		"8 - Modifier le nom du responsable de département\n"
		"10 - \n"
		"19 - Menu principal\n"
		"Votre choix : ");

		scanf("%d", &choix);

		switch (choix) {
			case 1 :
				ajouterIUT(tiut, nbIUT);
				break;

			case 2 :
				AjouterDepart(tiut, nbIUT);
				break;

			case 3 :
				
				break;

			case 4 :
				
				break;

			case 5:
				
				break;

			case 6 :
				
				break;

			case 7 :
				ModifPlaces(tiut, nbIUT);
				break;

			case 8 :
				ModifierRes(tiut, nbIUT);
				break;

			case 19 :
				menuPrincipal(tiut, nbIUT);
				return;

			default :
				printf("\n\e[1;91mChoix incorrect, recommencez\e[0m\n");
				break;
		}
	}
}

void sauvegarde(VilleIUT ** tiut, int *nbIUT) 
{
	FILE *fo;
	int i;

	fo = fopen("iut.don", "w");

	fprintf(fo, "%d\n", *nbIUT);
	for(i=0; i < *nbIUT; i++) {
		fprintf(fo, "%s %d ", tiut[i]->ville, tiut[i]->ldept->nb);
		for(; tiut[i]->ldept->premier; tiut[i]->ldept->premier = tiut[i]->ldept->premier->suivant) {
			fprintf(fo, "%s %d %s ", tiut[i]->ldept->premier->departement, tiut[i]->ldept->premier->nbP, tiut[i]->ldept->premier->nomRes);
		}
		fprintf(fo, "\n");
	}
	fclose(fo);
	return;
}