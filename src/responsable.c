#include "responsable.h"

float calculMoyenne(float notes[]) {
	int i;
	float moyenne;

	for(i=0; i < 4; ++i) {
		moyenne += notes[i];
	}

	return moyenne/4;
}

Voeu* chercherVoeux(ListeVoeux l, char *iut, char *dept) {
	Voeu *v;
	for(v = l->premier; v != NULL; v = v->suivant) {
		if(strcmp(v->ville, iut) == 0 && strcmp(v->departement, dept) == 0) {
			return v;
		}
	}
	return NULL;
}

void filtrerCandidatures(VilleIUT **tiut, int *nbIUT, Candidat **tCand, int *nbCand)
{
	float noteMin = -5;
	char iut[30] = "0", depart[30] = "0";
	int pos, trouve, i, nbEligibles = 0, nbMax;
	FileCandidats fc;

	while (strcmp(iut, "-1") != 0)
	{
		saisieStringControlee(iut, CYAN"\nEntrez le nom de votre IUT (-1 pour annuler) : "RESET);
		strcpy(iut, upperfcase(iut));
		
		pos = rechercheIUT(tiut, nbIUT, iut, &trouve);

		if (trouve)
		{
			saisieStringControlee(depart, CYAN"Entrez le nom de votre département (-1 pour annuler) : "RESET);
			strcpy(depart, upperfcase(depart));

			if (existeDepart(tiut[pos]->ldept, depart))
			{
				saisieFloatControlee(&noteMin, CYAN"Quel est la note minimale pour être admis dans votre département (-1 pour annuler) : "RESET);
				while ((noteMin < 0 && noteMin != -1) || noteMin > 20)
				{
					fprintf(stderr, ROUGE"\nLa note minimale doit être comprise entre 0 et 20.\n"RESET);
					saisieFloatControlee(&noteMin, CYAN"\nQuel est la note minimale pour être admis dans votre département (-1 pour annuler) : "RESET);

					if (noteMin == -1)
					{
						printf("\nFin de l'opération...\n");
						return;
					}
				}

				saisieIntControlee(&nbMax, CYAN"Combien de candidats souhaitez-vous recruter (-1 pour annuler) : "RESET);
				while (nbMax <= 0 && nbMax != -1)
				{
					fprintf(stderr, ROUGE"\nLe nombre d'admis doit être supérieur à 0.\n"RESET);
					saisieIntControlee(&nbMax, CYAN"\nCombien de candidats souhaitez-vous recruter (-1 pour annuler) : "RESET);

					if (nbMax == -1)
					{
						printf("\nFin de l'opération...\n");
						return;
					}
				}

				Candidat **tElegibles = (Candidat **)malloc(sizeof(Candidat *)*(*nbCand));
				testMalloc(tElegibles, "création d'un tableau de candidats");

				for (i = 0 ; i < *nbCand ; i++)
				{
					if (existeVoeu(tCand[i], iut, depart))
					{
						if (tCand[i]->moyenne >= noteMin) tElegibles[nbEligibles++] = tCand[i];
						else chercherVoeux(tCand[i]->choix, iut, depart)->decDepartement = -1;
					}
				}
				triNumerique(tElegibles, nbEligibles);
				
				if (nbEligibles > nbMax)
				{
					fc = (FileCandidats)malloc(sizeof(struct FileCandidats));
					testMalloc(fc, "création d'une file de candidats");
					fc->tete = fc->queue = NULL;
					fc->nb = nbEligibles-nbMax;
					for (i = nbMax ; i < nbEligibles ; i++)
					{
						MaillonFileCandidat *c = (MaillonFileCandidat *)malloc(sizeof(MaillonFileCandidat));
						testMalloc(c, "création d'un candidat");
						
						c->candidat = tElegibles[i];
						c->suivant = NULL;
						
						if (fc->tete == NULL) fc->tete = c;
						else fc->queue->suivant = c;
						fc->queue = c;
						chercherVoeux(tElegibles[i]->choix, iut, depart)->decDepartement = 2;
					}
				}

				for (i = 0 ; i < nbEligibles ; i++) chercherVoeux(tElegibles[i]->choix, iut, depart)->decDepartement = 1;
				int nbTElegibles = nbEligibles-nbMax;
				if (strcmp(iut, "Clermont-ferrand") == 0 && strcmp(depart, "Informatique") == 0)
				{
					sauvegarderCandidats(tElegibles, &nbTElegibles, "admis.don");
					if (nbEligibles > nbMax) sauvegarderFileCandidats(fc, "attentes.don");
				}
				printf(VERT"\nFiltrage terminé !\n"RESET);
				printf(UNDERLINE"Voici la liste de vos candidats admis :\n");
				afficherCandidats(tElegibles, &nbTElegibles);
				return;

			}
			else if (strcmp(depart, "-1") != 0) fprintf(stderr, ROUGE"\nErreur : le département est introuvable !\n"RESET);
		}
		else if (strcmp(iut, "-1") != 0) fprintf(stderr, ROUGE"\nErreur : l'iut est introuvable !\n"RESET);
	}	
}

void triNumerique(Candidat **tCand, int nbCand)
{
  int i, j;
  Candidat *w, *d;

  if (nbCand <= 1) return ;

  i = 0;
  j = nbCand-2;
  d = tCand[nbCand-1];

  while (i >= j)
  {
	while (tCand[i]->moyenne >= d->moyenne && i < nbCand-1) i++;
	while (tCand[i]->moyenne <= d->moyenne && 0 <= j) j--;

	if (i > j)
	{
		w = tCand[i];
		tCand[i] = tCand[j];
		tCand[j] = w;
	}

	tCand[nbCand-1] = tCand[i];
	tCand[i] = d;

	triNumerique(tCand, i);
	triNumerique(tCand+i+1, nbCand-i-1);
		
	return;
  }
}

void afficherCandidatsIUT(Candidat **tCand, int *nbCand)
{
	int i, nbCandTrie = 0, trouve = 0;
	char iut[30];
	Voeu *v;
	Candidat **tCandTri = (Candidat **)malloc(sizeof(Candidat *) *(*nbCand));
	testMalloc(tCandTri, "création d'un tableau d'étudiants");

	saisieStringControlee(iut, CYAN"Entrez le nom de votre IUT (-1 pour annuler) : "RESET);
	strcpy(iut, upperfcase(iut));

	if (strcmp(iut, "-1") == 0) return;

	for (i = 0 ; i < *nbCand ; i++)
	{
		for (v = tCand[i]->choix->premier ; v != NULL ; v = v->suivant)
		{
			if (strcmp(v->ville, iut) == 0 && v->decDepartement && v->decCandidat)
			{
				trouve = 1;
				tCandTri[nbCandTrie++] = tCand[i];
			}
		}
	}

	if (trouve)
	{
		triAlpha(tCandTri, nbCandTrie);
		printf(UNDERLINE"Voici la liste de vos candidats admis :\n"RESET);
		for (i = 0 ; i < nbCandTrie ; i++) printf("%s %s\n", tCandTri[i]->nom, tCandTri[i]->prenom);
	}
	else fprintf(stderr, ROUGE"Aucun candidat n'a été admis dans votre IUT...\n"RESET);

	free(tCandTri);
}