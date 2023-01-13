#include "menus.h"

void menuPrincipal(VilleIUT** tiut, Candidat** tCand, int *nbIUT, int *nbCand, Phase *phase) 
{
	int choix;
	char motDePasse[12];

	tiut = chargerIUT(nbIUT);
	tCand = chargerCandidats(nbCand);

	while (1) {
		printf("\n----------------------------------------\n");

		printf(
		TITRE"\nMenu principal\n\n"RESET
		"1 - Afficher les informations des IUT\n"
		"2 - Afficher les villes où il y a un département\n"
		"3 - Afficher la phase en cours\n"
		"4 - Inscription\n"
		"\n5 - Menu des candidats\n"
		"6 - Menu des responsables\n"
		"7 - Menu des administrateurs\n"
		"\n9 - Quitter\n"
		"\nVotre choix : ");

		scanf("%d", &choix);

		switch (choix) {
			case 1 :
				afficherDepart(tiut, nbIUT);
				break;

			case 2 :
				afficherDepartPrecis(tiut, nbIUT);
				break;

			case 3 :
				afficherPhase(phase);
				break;

			case 4 :
				ajouterCandidats(tCand, nbCand);
				sauvegarderCandidats(tCand, nbCand, "candidats.don");
				printf("nbCand : %d\n", *nbCand);
				break;

			case 5 :
				if(*phase != 1) {
					afficherPhase(phase);
					fprintf(stderr, ROUGE"Nous ne pouvez pas accéder à ce menus.\n"RESET);
				}
				else menuCandidat(tiut, tCand, nbIUT, nbCand, phase);
				break;

			case 6 :
				menuResponsable(tiut, tCand, nbIUT, nbCand, phase);
				break;

			case 7 :
				printf("\n----------------------------------------\n");

				printf("\nEntrez le mot de passe : ");
				scanf("%s%*c", motDePasse);
				if(strcmp(motDePasse, "mdp") != 0) {
					fprintf(stderr, ROUGE"Mot de passe incorrect..."RESET);
				}
				else {
					menuAdministrateur(tiut, tCand, nbIUT, nbCand, phase);
				}
				break;

			case 9 :
				sauvegarde(tiut, nbIUT);
				sauvegarderCandidats(tCand, nbCand, "candidats.don");
				exit(0);

			default :
				printf(ROUGE"\nChoix incorrect, recommencez\n"RESET);
				break;
		}
	}
}

void menuAdministrateur(VilleIUT** tiut, Candidat** tCand, int *nbIUT, int *nbCand, Phase *phase) 
{
	int choix;

	tiut = chargerIUT(nbIUT);
	tCand = chargerCandidats(nbCand);

	while (1) {
		printf("\n----------------------------------------\n");
		
		printf(
		TITRE"\nMenu des administrateurs\n\n"RESET
		"1 - Créer un IUT\n"
		"2 - Créer un département\n"
		"3 - Supprimer un IUT\n"
		"4 - Supprimer un département\n"
		"5 - Lancer la phase de candidature\n"
		"6 - Arrêter la phase de candidature\n"
		"7 - Modifier le nombre de places\n"
		"8 - Modifier le nom du responsable de département\n"

		"\n9 - Menu principal\n"
		"\nVotre choix : ");

		scanf("%d", &choix);

		switch (choix) {
			case 1 :
				tiut = ajouterIUT(tiut, nbIUT);
				sauvegarde(tiut, nbIUT);
				break;

			case 2 :
				ajouterDepart(tiut, nbIUT);
				sauvegarde(tiut, nbIUT);
				break;

			case 3 :
				supprimerIUT(tiut, nbIUT);
				sauvegarde(tiut, nbIUT);
				break;

			case 4 :
				supprimerDepart(tiut, nbIUT);
				sauvegarde(tiut, nbIUT);
				break;

			case 5:
				lancerCandidature(phase);
				break;

			case 6 :
				stopperCandidature(phase);
				break;

			case 7 :
				modifPlaces(tiut, nbIUT);
				sauvegarde(tiut, nbIUT);
				break;

			case 8 :
				modifierRes(tiut, nbIUT);
				sauvegarde(tiut, nbIUT);
				break;

			case 14 :
				tCand = ajouterCandidats(tCand, nbCand);
				sauvegarderCandidats(tCand, nbCand, "candidats.don");
				break;
			

			case 9 :
				sauvegarde(tiut, nbIUT);
				sauvegarderCandidats(tCand, nbCand, "candidats.don");
				return;

			default :
				printf("\n\e[1;91mChoix incorrect, recommencez\e[0m\n");
				break;
		}
	}
}

void menuCandidat(VilleIUT** tiut, Candidat** tCand, int *nbIUT, int *nbCand, Phase *phase) 
{
	int choix;

	tiut = chargerIUT(nbIUT);
	tCand = chargerCandidats(nbCand);
	
	printf("nbCand : %d\n", *nbCand);

	while (1) {
		printf("\n----------------------------------------\n");
		
		printf(
		TITRE"\nMenu des candidats\n\n"RESET
		"1 - Supprimer un voeu\n"
		"2 - Ajouter un voeu\n"
		"\n9 - Menu principal\n"
		"\nVotre choix : ");

		scanf("%d", &choix);

		switch (choix) {
			case 1 :
				tCand = supprimerVoeux(tCand, nbCand);
				sauvegarderCandidats(tCand, nbCand, "candidats.don");
				break;

			case 2 :
				ajouterVoeu(tiut, nbIUT, tCand, nbCand);
				sauvegarderCandidats(tCand, nbCand, "candidats.don");
				break;

			case 9 :
				sauvegarde(tiut, nbIUT);
				sauvegarderCandidats(tCand, nbCand, "candidats.don");
				return;

			default :
				printf("\n\e[1;91mChoix incorrect, recommencez\e[0m\n");
				break;
		}
	}
}

void menuResponsable(VilleIUT** tiut, Candidat** tCand, int *nbIUT, int *nbCand, Phase *phase) 
{
	int choix;

	tiut = chargerIUT(nbIUT);
	tCand = chargerCandidats(nbCand);
	
	while (1) {
		printf("\n----------------------------------------\n");
		
		printf(
		TITRE"\nMenu des responsables\n\n"RESET	
		"1 - Afficher tous les candidats\n"
		"2 - Afficher les candidats d'un département\n"
		"3 - Filtrer les candidats\n"	
		"\n9 - Menu principal\n"
		"\nVotre choix : ");

		scanf("%d", &choix);

		switch (choix) {
			case 1 :
				afficherCandidats(tCand, nbCand);
				break;

			case 2 :
				afficherCandidatsDepart(tCand, nbCand);
				break;

			case 3 :
				filtrerCandidatures(tiut, nbIUT, tCand, nbCand);
				break;

			case 9 :
				sauvegarde(tiut, nbIUT);
				sauvegarderCandidats(tCand, nbCand, "candidats.don");
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
	MaillonDept *tmp; 

	fo = fopen("iut.don", "w"); 

	fprintf(fo, "%d\n", *nbIUT); 
	for(i=0; i < *nbIUT; i++) { 
		fprintf(fo, "%s %d ", tiut[i]->ville, tiut[i]->ldept->nb); 
		for(tmp = tiut[i]->ldept->premier; tmp != NULL; tmp = tmp->suivant) { 
			fprintf(fo, "%s %d %s ", tmp->departement, tmp->nbP, tmp->nomRes); 
		} 
		fprintf(fo, "\n"); 
	} 
	fclose(fo); 
	return; 
} 

 