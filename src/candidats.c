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

void ajouterVoeu(VilleIUT **tiut, int *nbIUT, Candidat **tCand, int *nbCand, Phase *phase)
{
	int num = 0, posIut;
	Bool trouve;
	char nom[30] = "0", depart[30] = "0";
	MaillonDept *mDept;

	if (afficherPhase(phase) != 1) return;

	while (num != -1)
	{
		printf("Entrez votre numéro de candidat (-1 pour annuler) : ");
		scanf("%d", &num);

		if (num > 0)
		{
			if (num <= *nbCand)
			{
				printf("Bonjour %s %s\n", tCand[num]->prenom, tCand[num]->nom); 

				if (tCand[num]->choix->premier == NULL) printf("Vous n'avez pas encore de voeux\n");
				else
				{
					printf("Voici vos voeux :\n"); 
					//à finir
				}

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
							printf("Voici les départements de l'IUT %s", tiut[posIut]->ville);
							afficher1Depart(tiut[posIut]);

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
									for(mDept = tiut[posIut]->ldept->premier; mDept != NULL ; mDept = mDept->suivant)
									{
										if (strcmp(mDept->departement, depart) == 0)
										{
											if (tCand[num]->nbChoix == 0) tCand[num]->choix->premier = creerVoeu(nom, depart);

											tCand[num]->choix->dernier = creerVoeu(nom, depart);
											tCand[num]->nbChoix += 1;

											printf(VERT"Voeu ajouté !\n"BLANC);
											strcpy(depart, "-1"); strcpy(nom, "-1");
										}
									}
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
