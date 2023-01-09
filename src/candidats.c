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

int ExisteVoeu(Candidat *c, char *iut, char *depart)
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
					fprintf(stderr, ROUGE"Erreur : vous avez déjà atteint le nombre maximal de voeux !\n"BLANC);
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
											if (!ExisteVoeu(tCand[num-1], nom, depart))
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
												printf(VERT"Voeu ajouté !\n"BLANC);
												strcpy(depart, "-1"); strcpy(nom, "-1");
												trouve = 1;
											}
											else
											{
												fprintf(stderr, ROUGE"Erreur : vous avez déjà formulé ce voeu !\n"BLANC);
												strcpy(depart, "-1"); strcpy(nom, "-1");
												trouve = 1;
											}
											
										}
										
									}
									if (!trouve) fprintf(stderr, ROUGE"Erreur : le département est introuvable !\n"BLANC);
								}		
							}
						}
						else fprintf(stderr, ROUGE"Erreur : l'IUT est introuvable !\n"BLANC);
					}
				}
			}
			else fprintf(stderr, ROUGE"Erreur : ce numéro de candidat est introuvable !\n"BLANC);
		}
		else if (num != -1) fprintf(stderr, ROUGE"Erreur : le numéro entré n'est pas valide !\n"BLANC);
	}	

	printf("Fin de l'opération...\n");	
}

Candidat **ChargerCandidats(int *nbCand)
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
