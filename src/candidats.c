#include "candidats.h"

ListeVoeux creerListeVoeux(void)
{
	ListeVoeux v= (ListeVoeux)malloc(sizeof(struct Voeu));
	testMalloc(v, "création d'une liste de voeux");

	v->premier = v->dernier = NULL;
	
	return v;
}

Phase afficherPhase(Phase *phase)
{
	if (!*phase) printf("La phase de candidature n'est pas encore lancée...\n");

	else if (*phase == 1) printf("La phase de candidature est en cours !\n");

	else printf("La phase de candidature est terminée...\n");

	return *phase;
}

void triAlpha(Candidat **tCand, int nbCand)
{
  int i, j;
  Candidat *w, *d;

  if (nbCand <= 1) return ;

  i = 0;
  j = nbCand-2;
  d = tCand[nbCand-1];

  while (i <= j)
  {
	while (strcmp(tCand[i]->nom, d->nom) <= 0 && i < nbCand-1) i++;
	while (strcmp(tCand[i]->nom, d->nom) >= 0 && 0 < j) j--;

	if (i < j)
	{
		w = tCand[i];
		tCand[i] = tCand[j];
		tCand[j] = w;
	}

	tCand[nbCand-1] = tCand[i];
	tCand[i] = d;

	triAlpha(tCand, i);
	triAlpha(tCand+i+1, nbCand-i-1);
		
	return;
  }
}

Voeu *creerVoeu(char *iut, char *dept)
{
	Voeu *v = (Voeu*)malloc(sizeof(Voeu));
	testMalloc(v, "création d'un voeu");

	strcpy(v->ville, iut);
	strcpy(v->departement, dept);
	v->suivant = NULL;
	v->decCandidat = v->decDepartement = 0;

	return v;
}

int existeVoeu(Candidat *c, char *iut, char *depart)
{
	Voeu *v;

	for (v = c->choix->premier ; v != NULL ; v = v->suivant)
	{
		if (strcmp(v->ville, iut) == 0 && strcmp(v->departement, depart) == 0)
		{
			return 1;
		}
	}

	return 0;
}

void ajouterVoeu(VilleIUT **tiut, int *nbIUT, Candidat **tCand, int *nbCand, Phase *phase)
{
	int num = 0, posIut;
	Bool trouve;
	char nom[30], depart[30];
	MaillonDept *mDept;
	Voeu *v;

	if (afficherPhase(phase) != 1) return;

	while (num != -1)
	{
		printf("Entrez votre numéro de candidat (-1 pour annuler) : ");
		scanf("%d", &num);

		if (num > 0)
		{
			if (num <= *nbCand)
			{
				printf("Bonjour %s %s\n", tCand[num-1]->prenom, tCand[num-1]->nom); 

				if (tCand[num-1]->nbChoix == 0) printf("Vous n'avez pas encore de voeux\n");
				else if (tCand[num-1]->nbChoix == 3)
				{
					fprintf(stderr, ROUGE"Erreur : vous avez déjà atteint le nombre maximal de voeux !\n"RESET);
					break;
				}
				else //afficher étudiant

				strcpy(nom, "0");
				while (strcmp(nom, "-1") != 0)
				{
					
					printf("Entrez l'IUT correspondant à votre voeux (-1 pour annuler) : ");
					scanf("%s", nom);

					if (strcmp(nom, "-1") == 0) num = -1;
					else
					{
						posIut = rechercheIUT(tiut, nbIUT, nom, &trouve);

						if (trouve)
						{
							afficher1Depart(tiut[posIut]);

							strcpy(depart, "0");
							while (strcmp(depart, "-1") != 0)
							{
								printf("Entrez le nom du département auquel vous voulez candidater (-1 pour annuler) : ");
								scanf("%s", depart);

								if (strcmp(depart, "-1") == 0)
								{
									strcpy(nom, "-1");
									num = -1;
								}		
								else
								{
									int trouve = 0;
									for(mDept = tiut[posIut]->ldept->premier; mDept != NULL ; mDept = mDept->suivant)
									{
										if (strcmp(mDept->departement, depart) == 0)
										{
											if (!existeVoeu(tCand[num-1], nom, depart))
											{
												v = creerVoeu(nom, depart);

												if (tCand[num-1]->nbChoix == 0)
												{
													tCand[num-1]->choix->premier = v;
													tCand[num-1]->choix->dernier = v;
												}
												else
												{
													tCand[num-1]->choix->dernier->suivant = v;
													tCand[num-1]->choix->dernier = v;
												}
												
												tCand[num-1]->nbChoix += 1;
												printf(VERT"Voeu ajouté !\n"RESET);
												strcpy(depart, "-1"); strcpy(nom, "-1");
												trouve = 1;
											}
											else
											{
												fprintf(stderr, ROUGE"Erreur : vous avez déjà formulé ce voeu !\n"RESET);
												strcpy(depart, "-1"); strcpy(nom, "-1");
												trouve = 1;
											}
											
										}
										
									}
									if (!trouve) fprintf(stderr, ROUGE"Erreur : le département est introuvable !\n"RESET);
								}		
							}
						}
						else fprintf(stderr, ROUGE"Erreur : l'IUT est introuvable !\n"RESET);
					}
				}
			}
			else fprintf(stderr, ROUGE"Erreur : ce numéro de candidat est introuvable !\n"RESET);
		}
		else if (num != -1) fprintf(stderr, ROUGE"Erreur : le numéro entré n'est pas valide !\n"RESET);
	}	

	printf("Fin de l'opération...\n");	
}

Candidat **chargerCandidats(int *nbCand)
{
	FILE *f;
	Candidat **tCand;
	int i, j;

	while ((f = fopen("candidats.don", "rb")) == NULL)
	{
		testFopen("candidats.don");
	}

	fread(nbCand, sizeof(int), 1, f);

	tCand = (Candidat **)malloc(sizeof(Candidat *)*(*nbCand));
	testMalloc(tCand, "création d'un tableau de candidats");

	for (i = 0 ; i < *nbCand ; i++)
	{
		Candidat *c = (Candidat *)malloc(sizeof(Candidat));
		testMalloc(c, "Création d'un candidat");

		fread(&c->num, sizeof(int), 1, f);
		fread(&c->prenom, sizeof(c->prenom), 1, f);
		fread(&c->nom, sizeof(c->nom), 1, f);
		fread(&c->notes, sizeof(float), 4, f);
		fread(&c->nbChoix, sizeof(int), 1, f);
		ListeVoeux lv = creerListeVoeux();

		for (j = 0 ; j < c->nbChoix ; j++)
		{
			Voeu *v = (Voeu*)malloc(sizeof(Voeu));
			
			fread(v, sizeof(Voeu), 1, f);

			if (lv->premier == NULL) lv->premier = lv->dernier = v;
			else
			{
				lv->dernier->suivant = v;
				lv->dernier = v;
			}
		}

		c->choix = lv;
		tCand[i] = c;
	}

	return tCand;	
}

void sauvegarderCandidats(Candidat **tCand, int *nbCand)
{
	FILE *f = fopen("candidats.don", "wb");
	int i;
	Voeu *v;

	fwrite(nbCand, sizeof(int), 1, f);

	for (i = 0 ; i < *nbCand ; i++)
	{
		fwrite(&(tCand[i]->num), sizeof(int), 1, f);
		fwrite(&(tCand[i]->nom), sizeof(tCand[i]->nom), 1, f);
		fwrite(&(tCand[i]->prenom), sizeof(tCand[i]->prenom), 1, f);
		fwrite(&(tCand[i]->notes), sizeof(float), 4, f);
		fwrite(&(tCand[i]->nbChoix), sizeof(int), 1, f);

		for (v = tCand[i]->choix->premier ; v != NULL ; v = v->suivant)
		{
			fwrite(v, sizeof(Voeu), 1, f);
		}
	}
}

void afficher1Candidat(Candidat **tCand, int pos) {
	int j;
	Voeu* v;

	printf("\n\tNuméro du candidat : %d\n\tNommination : %s %s\n", tCand[pos]->num, tCand[pos]->prenom, tCand[pos]->nom);
	printf("\tNote de mathématique : %.2f\n\tNote de français : %.2f\n\tNote d'anglais : %.2f\n\tNote de la matière de spécialité : %.2f\n", tCand[pos]->notes[0], tCand[pos]->notes[1],  tCand[pos]->notes[2], tCand[pos]->notes[3]); 
	printf("\tNombre de voeux : %d\n", tCand[pos]->nbChoix);

	for(v=tCand[pos]->choix->premier, j=1; v; v = v->suivant, ++j) {
		printf(GRAS"\t\tChoix n°%d\n"RESET, j);
		printf("\t\tIUT choisi : %s\n", v->ville);
		printf("\t\tDépartement : %s\n", v->departement);
		printf("\t\tDécision du département : ");
			
		if(v->decDepartement == 1) printf("admis\n");
		else if(v->decDepartement == -1) printf("refusé\n");
		else if(v->decDepartement == 2) printf("liste d'attente\n");
		else printf("non traité\n");

		printf("\t\tChoix du candidat : ");

		if(v->decCandidat == 1) printf("accepté\n\n");
		else if(v->decCandidat == -1) printf("refusé\n\n");
		else printf("non décidé\n\n");
	}
}

void afficherCandidats(Candidat **tCand, int *nbCand) {
	int i;

	printf(GRAS UNDERLINE"\nListe des candidats :"RESET);

	for(i=0; i < *nbCand; ++i) {
		afficher1Candidat(tCand, i);
	}
}

void afficherCandidatsDepart(Candidat **tCand, int *nbCand) {
	int i, nbCandDept; 
	Voeu* v;
	char dept[30]; 
	Candidat** tCandDept;

	while (strcmp(dept, "-1") != 0) {
		nbCandDept = 0;

		printf("\nPour quel département souhaitez-vous avoir la liste des candidats (-1 pour annuler) ? ");
		scanf("%s", dept);

		if(strcmp(dept, "-1") != 0) {
			tCandDept = (Candidat **)malloc(sizeof(Candidat *)*(*nbCand));
			testMalloc(tCandDept, "Tableaux des candidats suivant département");

			for(i=0; i < *nbCand; ++i) {
				for(v=tCand[i]->choix->premier; v; v = v->suivant) {
					if(strcmp(v->departement,dept)==0) {
						tCandDept[nbCandDept]=tCand[i];
						nbCandDept += 1;
					}
				}
			}

			if(nbCandDept == 0) printf(ROUGE"\nIl n'y a pas de candidat dans le département %s.\n"RESET, dept);
			else {
				triAlpha(tCandDept, nbCandDept);
				printf(GRAS UNDERLINE"\nListe des candidats du département %s : \n"RESET, dept);
				for(i=0; i<nbCandDept; ++i) {
					afficher1Candidat(tCandDept, i);
				}
			}

			free(tCandDept);
		}
	}
}

char *upperfcase(char *motIn)
{	
	int len = strlen(motIn), i;
	char *motOut = (char *)malloc(sizeof(char)*len);
	testMalloc(motOut, "Mise en uppercase");

	if (len != 0) motOut[0] = toupper(motIn[0]);

	for (i = 1 ; i < len ; i++) motOut[i] = tolower(motIn[i]);

	return motOut;
}

char *uppercase(char *motIn)
{
	int len = strlen(motIn), i;
	char *motOut = (char *)malloc(sizeof(char)*len);
	testMalloc(motOut, "Mise en uppercase");

	for (i = 0 ; i < len ; i++) motOut[i] = toupper(motIn[i]);

	return motOut;
}
