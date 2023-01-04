#include "menus.h"

void menuPrincipal(void) {
	int choix;
	VilleIUT** tiut;
	int nbIUT;

	tiut = chargerIUT(&nbIUT);

	while (1) {
		printf("\n----------------------------------------\n");

		printf(
		"\nMenu des utilisateurs\n\n"
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
				afficherDepart(tiut, &nbIUT);
				break;

			case 2 :
				afficherDepartPrecis(tiut, &nbIUT);
				break;

			case 3 :
				
				break;

			case 4 :
				
				break;

			case 7 :
				menuAdministrateur(tiut, nbIUT);
				break;

			case 9 :
				sauvegarde(tiut, nbIUT);
				return;

			default :
				printf("\n\e[1;91mChoix incorrect, recommencez\e[0m\n");
				break;
		}
	}
}

void menuAdministrateur(VilleIUT** tiut, int nbIUT) {
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
		"7 - \n"
		"9 - Menu principal\n"
		"Votre choix : ");

		scanf("%d", &choix);

		switch (choix) {
			case 1 :
				ajouterIUT(tiut, &nbIUT);
				break;

			case 2 :
				
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
				
				break;

			case 9 :
			menuPrincipal();
				return;

			default :
				printf("\n\e[1;91mChoix incorrect, recommencez\e[0m\n");
				break;
		}
	}
}

void sauvegarde(VilleIUT ** tiut, int nbIUT) {
	FILE *fo;
	int i;

	fo = fopen("iut.don", "w");

	fprintf(fo, "%d\n", nbIUT);
	for(i=0; i < nbIUT; i++) {
		fprintf(fo, "%s %d ", tiut[i]->ville, tiut[i]->ldept->nb);
		for(; tiut[i]->ldept->premier; tiut[i]->ldept->premier = tiut[i]->ldept->premier->suivant) {
			fprintf(fo, "%s %d %s ", tiut[i]->ldept->premier->departement, tiut[i]->ldept->premier->nbP, tiut[i]->ldept->premier->nomRes);
		}
		fprintf(fo, "\n");
	}

	fclose(fo);
}