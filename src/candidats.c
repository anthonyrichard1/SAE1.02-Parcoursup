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
	while ((strcmp(tCand[i]->nom, d->nom) <= 0 || (strcmp(tCand[i]->nom, d->nom) == 0 && strcmp(tCand[i]->prenom, d->prenom) <= 0)) && i < nbCand-1) i++;
	while ((strcmp(tCand[i]->nom, d->nom) >= 0 || (strcmp(tCand[i]->nom, d->nom) == 0 && strcmp(tCand[i]->prenom, d->prenom) >= 0)) && 0 < j) j--;

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
		if (strcmp(v->ville, iut) == 0 && strcmp(v->departement, depart) == 0) return 1;

	return 0;
}

void ajouterVoeu(VilleIUT **tiut, int *nbIUT, Candidat **tCand, int *nbCand)
{
	int num = 0, posIut;
	Bool trouve;
	char nom[30], depart[30];
	MaillonDept *mDept;
	Voeu *v;

	while (num != -1)
	{
		saisieIntControlee(&num, "Entrez votre numéro de candidat (-1 pour annuler) : ");
		
		while ((num < 0 && num != -1) || num > *nbCand)
		{
			fprintf(stderr, ROUGE"Erreur : le numéro entré n'est pas valide !\n"RESET);
			saisieIntControlee(&num, "Entrez votre numéro de candidat (-1 pour annuler) : ");
		}

		if (num != -1)
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
				else afficher1Candidat(tCand, num-1);

				strcpy(nom, "0");
				while (strcmp(nom, "-1") != 0)
				{
					saisieStringControlee(nom, "Entrez l'IUT correspondant à votre voeux (-1 pour annuler) : ");
					strcpy(nom, upperfcase(nom));

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
								saisieStringControlee(depart, "Entrez le nom du département auquel vous voulez candidater (-1 pour annuler) : ");
								strcpy(depart, upperfcase(depart));

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
	}	

	printf("Fin de l'opération...\n");	
}

Candidat **chargerCandidats(int *nbCand)
{
	FILE *f;
	Candidat **tCand;
	int i, j;

	while ((f = fopen("candidats.don", "rb")) == NULL) testFopen("candidats.don");

	fread(nbCand, sizeof(int), 1, f);

	tCand = (Candidat **)malloc(sizeof(Candidat *)*(*nbCand));
	testMalloc(tCand, "création d'un tableau de candidats");

	for (i = 0 ; i < *nbCand ; i++)
	{
		Candidat *c = (Candidat *)malloc(sizeof(Candidat));
		testMalloc(c, "Création d'un candidat");

		fread(&c->num, sizeof(int), 1, f);
		fread(&c->nom, sizeof(c->nom), 1, f);
		fread(&c->prenom, sizeof(c->prenom), 1, f);
		fread(&c->notes, sizeof(float), 4, f);
		c->moyenne = calculMoyenne(c->notes);
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
		fscanf(f, "\n");
	}

	fclose(f);
	
	return tCand;	
}

void sauvegarderCandidats(Candidat **tCand, int *nbCand, char *nomFichier)
{
	FILE *f = fopen(nomFichier, "wb");
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

		for (v = tCand[i]->choix->premier ; v != NULL ; v = v->suivant) fwrite(v, sizeof(Voeu), 1, f);

		fprintf(f, "\n");
	}

	fclose(f);
}

void afficher1Candidat(Candidat **tCand, int pos) {
	int j;
	Voeu* v;

	printf("\n\tNuméro du candidat : %d\n\tNommination : %s %s\n", tCand[pos]->num, tCand[pos]->prenom, tCand[pos]->nom);
	printf("\tNote de mathématique : %.2f\n\tNote de français : %.2f\n\tNote d'anglais : %.2f\n\tNote de la matière de spécialité : %.2f\n\tMoyenne des notes : %.2f\n", tCand[pos]->notes[0], tCand[pos]->notes[1],  tCand[pos]->notes[2], tCand[pos]->notes[3], tCand[pos]->moyenne); 
	printf("\tNombre de voeux : %d\n", tCand[pos]->nbChoix);

	for(v=tCand[pos]->choix->premier, j=1; v; v = v->suivant, ++j) {
		printf(GRAS"\t\tChoix n°%d\n"RESET, j);
		afficher1Voeu(tCand, v);
	}
}

void afficher1Voeu(Candidat** tCand, Voeu* voeu) {
	printf("\t\tIUT choisi : %s\n", voeu->ville);
	printf("\t\tDépartement : %s\n", voeu->departement);
	printf("\t\tDécision du département : ");
			
	if(voeu->decDepartement == 1) printf("admis\n");
	else if(voeu->decDepartement == -1) printf("refusé\n");
	else if(voeu->decDepartement == 2) printf("liste d'attente\n");
	else printf("non traité\n");

	printf("\t\tChoix du candidat : ");

	if(voeu->decCandidat == 1) printf("accepté\n\n");
	else if(voeu->decCandidat == -1) printf("refusé\n\n");
	else printf("non décidé\n\n");
}

void afficherCandidats(Candidat **tCand, int *nbCand) {
	int i;

	if(*nbCand > 0) {
		printf(GRAS UNDERLINE"\nListe des candidats :"RESET);

		for(i=0; i < *nbCand; ++i) afficher1Candidat(tCand, i);
	}
	else fprintf(stderr, ROUGE"Il n'y a pas de candidat.\n"RESET);
}

void afficherCandidatsDepart(Candidat **tCand, int *nbCand) {
	int i, nbCandDept; 
	Voeu* v;
	char dept[30]; 
	Candidat** tCandDept;

	while (strcmp(dept, "-1") != 0) {
		nbCandDept = 0;

		saisieStringControlee(dept, "Pour quel département souhaitez-vous avoir la liste des candidats (-1 pour annuler) ? ");
		strcpy(dept, upperfcase(dept));

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

			if(nbCandDept == 0) fprintf(stderr, ROUGE"\nIl n'y a pas de candidat dans le département %s.\n"RESET, dept);
			else {
				triAlpha(tCandDept, nbCandDept);
				printf(GRAS UNDERLINE"\nListe des candidats du département %s : \n"RESET, dept);
				for(i=0; i<nbCandDept; ++i) afficher1Candidat(tCandDept, i);
			}

			free(tCandDept);
		}
	}
}

Candidat** supprimerVoeux(Candidat** tCand, int *nbCand) 
{
	int numCand, numVoeu;
	Voeu *prec, *voeuSup, *v;
	int i, j;

	while(numCand != -1 && numVoeu != -1) {
		saisieIntControlee(&numCand, "Quel est le numéro du candidat pour lequel vous souhaitez supprimé un voeu (-1 pour annuler) ? : ");

		while (numCand > *nbCand || (numCand < 0 && numCand != -1))
		{
			fprintf(stderr, ROUGE"Le numéro de candidat saisie est invalide.\n"RESET);
			saisieIntControlee(&numCand, "Quel est le numéro du candidat pour lequel vous souhaitez supprimé un voeu (-1 pour annuler) ? : ");
		}

		if(numCand != -1) {
			printf("Bonjour %s %s !\n", tCand[numCand-1]->prenom, tCand[numCand-1]->nom);
			printf(GRAS UNDERLINE"\n\tListe de vos voeux : \n"RESET);
			for(v=tCand[numCand-1]->choix->premier, j=1; v; v = v->suivant, ++j) {
				printf(GRAS"\t\tChoix n°%d\n"RESET, j);
				afficher1Voeu(tCand, v);
			}
			saisieIntControlee(&numVoeu, "Entrez le numéro du voeu que vous voulez supprimé (-1 pour annuler) : ");

			while(numVoeu < 0 && numVoeu > j-1) {
				fprintf(stderr, ROUGE"Choix incorrect.\n"RESET);
				saisieIntControlee(&numVoeu, "Entrez le numéro du voeu que vous voulez supprimé (-1 pour annuler) : ");
			}

			if(numVoeu != -1) {
				if(numVoeu == 1) {
					voeuSup = tCand[numCand-1]->choix->premier;
					tCand[numCand-1]->choix->premier = tCand[numCand-1]->choix->premier->suivant;
					free(voeuSup);
				}
				else if (numVoeu == j-1) {
					voeuSup = tCand[numCand-1]->choix->dernier;
					prec = tCand[numCand-1]->choix->premier;
					for(i=1; i < j-2; ++i) prec = prec->suivant;

					prec->suivant = NULL;
					free(tCand[numCand-1]->choix->dernier);
					tCand[numCand-1]->choix->dernier = prec;
				}
				else {
					printf("Ici\n");
					voeuSup = tCand[numCand-1]->choix->premier;
					prec = tCand[numCand-1]->choix->premier;
					for(i=1; i < j-2; ++i) voeuSup = voeuSup->suivant;

					for(i=1; i < j-3; ++i) prec = voeuSup->suivant;

					afficher1Voeu(tCand, prec);
					free(voeuSup);
				}
				printf(VERT"Le voeu a bien été supprimé.\n"RESET);
			}
		}
	}	
	printf("Annulation de l'opération.\n");
	return tCand;
}

Candidat **ajouterCandidats(Candidat **tCand, int *nbCand)
{
	char prenom[30] = "0";
	char nom[30] = "0";
	float ma = 50, fr = 50, an = 50, spe = 50;

	Candidat *c = (Candidat *)malloc(sizeof(Candidat));
	testMalloc(c, "création d'un candidat");
	c->num = *nbCand+1;
	

	while (strcmp(prenom, "-1") != 0)
	{
		saisieStringControlee(prenom, "Entrez votre prénom (-1 pour annuler) : ");
		strcpy(prenom, upperfcase(prenom));

		if (strcmp(prenom, "-1") != 0)
		{
			strcpy(c->prenom, prenom);
			strcpy(prenom, "-1");
			while (strcmp(nom, "-1") != 0)
			{
				saisieStringControlee(nom, "Entrez votre nom (-1 pour annuler) : ");
				strcpy(nom, uppercase(nom));

				if (strcmp(nom, "-1") != 0)
				{
					strcpy(c->nom, nom);
					strcpy(nom, "-1");
					ma=0;fr=0;an=0;spe=0;
					while (ma != -1 && fr != -1 && an != -1 && spe != -1)
					{
						saisieFloatControlee(&ma, "Entrez votre note de maths (-1 pour annuler) : ");
						while ((ma < 0 && ma != -1) || ma > 20)
						{
							fprintf(stderr, ROUGE"La note doit être comprise entre 0 et 20\n"RESET);
							saisieFloatControlee(&ma, "Entrez votre note de maths (-1 pour annuler) : ");
						}
						if (ma == -1) break;

						saisieFloatControlee(&fr, "Entrez votre note de français (-1 pour annuler) : ");
						while ((fr < 0 && fr != -1) || fr > 20)
						{
							fprintf(stderr, ROUGE"La note doit être comprise entre 0 et 20\n"RESET);
							saisieFloatControlee(&fr, "Entrez votre note de français (-1 pour annuler) : ");
						}
						if (fr == -1) break;
						
						saisieFloatControlee(&an, "Entrez votre note d'anglais (-1 pour annuler) : ");
						while ((an < 0 && an != -1) || an > 20)
						{
							fprintf(stderr, ROUGE"La note doit être comprise entre 0 et 20\n"RESET);
							saisieFloatControlee(&an, "Entrez votre note d'anglais (-1 pour annuler) : ");
						}
						if (an == -1) break;

						saisieFloatControlee(&spe, "Entrez votre note de spécialité (-1 pour annuler) : ");
						while ((spe < 0 && spe != -1) || spe > 20)
						{
							fprintf(stderr, ROUGE"La note doit être comprise entre 0 et 20\n"RESET);
							saisieFloatControlee(&spe, "Entrez votre note de spécialité (-1 pour annuler) : ");
						}
						if (spe == -1) break;

						c->notes[0] = ma;
						c->notes[1] = fr;
						c->notes[2] = an;
						c->notes[3] = spe;
						c->moyenne = calculMoyenne(c->notes);
						c->nbChoix = 0;
						c->choix = creerListeVoeux();
						*nbCand += 1;
						Candidat **ntCand = (Candidat **)realloc(tCand, sizeof(tCand)*(*nbCand));
						testMalloc(ntCand, "aggrandissement du tableau des candidats");
						ntCand[c->num-1] = c;
						
						printf(VERT"Candidat ajouté !\n"RESET);
						return ntCand;
					}
				}
			}
		}
	}
	
	printf("Fin de l'opération...\n");
	free(c);
	return tCand;
}
