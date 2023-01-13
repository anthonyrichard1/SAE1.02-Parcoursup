#include "menus.h"

void menuPrincipal(VilleIUT** tiut, Candidat** tCand, int *nbIUT, int *nbCand, Phase *phase) 
{
	int choix, pos;
	char motDePasse[12];

	tiut = chargerIUT(nbIUT);
	tCand = chargerCandidats(nbCand);

	while (1) {
		printf("\n----------------------------------------\n");

		printf(
		TITRE"\nMenu principal\n\n"RESET
		"1 - Afficher les informations des IUT\n"
		"2 - Afficher les villes où il y a un département\n"
		"3 - Afficher la phase en cours\n");

		if(*phase == 1) {
			printf(
			"4 - Inscription\n"
			"\n5 - Menu des candidats\n");
		}
		else printf("\n");
		
		if(*phase == 2) {
			printf("6 - Menu des responsables\n");
		}
		
		printf(
		"7 - Menu des administrateurs\n"
		"\n9 - Quitter\n");

		saisieIntControlee(&choix, "\nVotre choix : ");

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
				if(*phase == 1) {
					ajouterCandidats(tCand, nbCand);
					sauvegarderCandidats(tCand, nbCand, "candidats.don");
					break;
				}
				else {
					printf(ROUGE"\nChoix incorrect, recommencez\n"RESET);
					break;
				}

			case 5 :
				if(*phase == 1) {
					saisieIntControlee(&pos, "Entrez votre numéro de candidat (-1 pour annuler) : ");
					
					while (pos < -1 || pos > *nbCand)
					{
						fprintf(stderr, ROUGE"Le numéro de candidat saisie est invalide.\n"RESET);
						saisieIntControlee(&pos, "Entrez votre numéro de candidat (-1 pour annuler) : ");
					}

					if(pos > -1) {
						--pos;
						menuCandidat(tiut, tCand, nbIUT, nbCand, phase, &pos);
					}
				}
				else {
					printf(ROUGE"\nChoix incorrect, recommencez\n"RESET);
					break;
				}

			case 6 :
				if(*phase == 2) {
					menuResponsable(tiut, tCand, nbIUT, nbCand, phase);
					break;
				}
				else {
					printf(ROUGE"\nChoix incorrect, recommencez\n"RESET);
					break;
				}

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
		"1 - Lancer la phase de candidature\n"
		"2 - Arrêter la phase de candidature\n");
		
		if(*phase == 0) {
			printf(
			"3 - Créer un IUT\n"
			"4 - Créer un département\n"
			"5 - Supprimer un IUT\n"
			"6 - Supprimer un département\n"
			"7 - Modifier le nombre de places\n"
			"8 - Modifier le nom du responsable de département\n");
		}

		printf("\n9 - Menu principal\n");
		
		saisieIntControlee(&choix, "\nVotre choix : ");

		switch (choix) {
			case 1 :
				lancerCandidature(phase);
				break;

			case 2 :
				stopperCandidature(phase);
				break;

			
			case 3 :
				if(*phase == 0) {
					tiut = ajouterIUT(tiut, nbIUT);
					sauvegarde(tiut, nbIUT);
					break;
				}
				else {
					printf("\n\e[1;91mChoix incorrect, recommencez\e[0m\n");
					break;
				}

			case 4 :
				if(*phase == 0) {
					ajouterDepart(tiut, nbIUT);
					sauvegarde(tiut, nbIUT);
					break;
				}
				else {
					printf("\n\e[1;91mChoix incorrect, recommencez\e[0m\n");
					break;
				}

			case 5 :
				if(*phase == 0) {
					supprimerIUT(tiut, nbIUT);
					sauvegarde(tiut, nbIUT);
					break;
				}
				else {
					printf("\n\e[1;91mChoix incorrect, recommencez\e[0m\n");
					break;
				}

			case 6 :
				if(*phase == 0) {
					supprimerDepart(tiut, nbIUT);
					sauvegarde(tiut, nbIUT);
					break;
				}
				else {
					printf("\n\e[1;91mChoix incorrect, recommencez\e[0m\n");
					break;
				}

			case 7 :
				if(*phase == 0) {
					modifPlaces(tiut, nbIUT);
					sauvegarde(tiut, nbIUT);
					break;
				}
				else {
					printf("\n\e[1;91mChoix incorrect, recommencez\e[0m\n");
					break;
				}

			case 8 :
				if(*phase == 0) {
					modifierRes(tiut, nbIUT);
					sauvegarde(tiut, nbIUT);
					break;
				}
				else {
					printf("\n\e[1;91mChoix incorrect, recommencez\e[0m\n");
					break;
				}

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

void menuCandidat(VilleIUT** tiut, Candidat** tCand, int *nbIUT, int *nbCand, Phase *phase, int *pos) 
{
	int choix;

	tiut = chargerIUT(nbIUT);
	tCand = chargerCandidats(nbCand);
	
	while (1) {
		printf("\n----------------------------------------\n");
		
		printf(
		TITRE"\nMenu des candidats\n\n"RESET
		"1 - Afficher vos informations\n"
		"2 - Ajouter un voeu\n"
		"3 - Supprimer un voeu\n"
		"\n9 - Menu principal\n");

		saisieIntControlee(&choix, "\nVotre choix : ");

		switch (choix) {
			case 1 :
				printf(GRAS UNDERLINE"\nVos informations : "RESET);
				afficher1Candidat(tCand[*pos]);
				break;

			case 2 :
				ajouterVoeu(tiut, nbIUT, tCand[*pos]);
				sauvegarderCandidats(tCand, nbCand, "candidats.don");
				break;

			case 3 :
				supprimerVoeux(tCand[*pos]);
				sauvegarderCandidats(tCand, nbCand, "candidats.don");
				break;

			case 4 :
				validerVoeux(tCand[*pos]);
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
		"2 - Afficher les candidats d'un département\n");

		if(*phase == 2) {
			printf("3 - Filtrer les candidats\n");
		}

		printf(
		"\n9 - Menu principal\n");

		saisieIntControlee(&choix, "\nVotre choix : ");

		switch (choix) {
			case 1 :
				afficherCandidats(tCand, nbCand);
				break;

			case 2 :
				afficherCandidatsDepart(tCand, nbCand);
				break;

			case 3 :
				if(*phase == 2) {
					filtrerCandidatures(tiut, nbIUT, tCand, nbCand);
					break;
				}
				else {
					printf(ROUGE"\nChoix incorrect, recommencez\n"RESET);
					break;
				}

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
