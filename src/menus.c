#include "structures.h"

void menuPrincipal(void) {
	int choix;
	
	while (1) {
		printf("\n----------------------------------------\n");

		printf(
		"\nMenu principal\n\n"
		"1 - Menu des administrateurs\n"
		"2 - Menu des utilisateurs\n"
		"9 - Quitter\n"
		"Votre choix : ");

		scanf("%d", &choix);

		switch(choix) {
			case 1 :
				menuAdministrateur();
				break;

			case 2 :
				menuUtilisateur();
				break;

			case 9 :
				
				exit(0);

			default :
				printf("\n\e[1;91mChoix incorrect, recommencez\e[0m\n");
				break;
		}
	}
}

void menuAdministrateur(void) {
	int choix;

	while (1) {
		printf("\n----------------------------------------\n");

		printf(
		"\nMenu des administrateurs\n\n"
		"1 - Modifier le nombre de places\n"
		"2 - Créer un département\n"
		"3 - Supprimer un département\n"
		"4 - Lancer la phase de candidature\n"
		"5 - Arrêter la phase de candidature\n" 
		"6 - Modifier le nom du responsable de département\n"
		"7 - \n"
		"9 - Menu principal\n"
		"Votre choix : ");

		scanf("%d", &choix);

		switch (choix) {
			case 1 :
				
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
				return;

			default :
				printf("\n\e[1;91mChoix incorrect, recommencez\e[0m\n");
				break;
		}
	}
}

void menuUtilisateur(void) {
	int choix;

	while (1) {
		printf("\n----------------------------------------\n");

		printf(
		"\nMenu des utilisateurs\n\n"
		"1 - Villes où il y a un IUT\n"
		"2 - Départements de chaque IUT\n"
		"3 - Nombre de place en première année\n"
		"4 - Département en fonction de l'IUT\n"
		"5 - \n" 
		"6 - \n"
		"7 - \n"
		"9 - Menu principal\n"
		"Votre choix : ");

		scanf("%d", &choix);

		switch (choix) {
			case 1 :
				
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
				return;

			default :
				printf("\n\e[1;91mChoix incorrect, recommencez\e[0m\n");
				break;
		}
	}
}

