#include "candidats.h"

ListeVoeux creerListeVoeux(void)
{
	ListeVoeux v= (ListeVoeux)malloc(sizeof(struct Voeu));
	testMalloc(v, "création d'une liste de voeux");

	v->premier = v->dernier = NULL;
	
	return v;
}

void afficherPhase(Phase *phase)
{
	if (!*phase)
	{
		printf("La phase de candidature n'est pas encore lancée...\n");
	}
	else if (*phase)
	{
		printf("La phase de candidature est en cours !\n");
	}
	else
	{
		printf("La phase de candidature est terminée...\n");
	}
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

void ajouterVoeu(Candidat **tCand, int *nbCand, Phase phase)
{

}