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
	if (!*phase) printf("\nLa phase de candidature n'est pas encore lancée...\n");

	else if (*phase == 1) printf("\nLa phase de candidature est en cours !\n");

	else printf("\nLa phase de candidature est terminée...\n");

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

void ajouterVoeu(VilleIUT **tiut, int *nbIUT, Candidat *cand)
{
	int posIut, j;
	Bool trouve;
	char nom[30], depart[30];
	MaillonDept *mDept;
	Voeu *v;
	if (cand->nbChoix == 0) printf("\nVous n'avez pas encore de voeux\n");
	else if (cand->nbChoix == 3)
	{
		fprintf(stderr, ROUGE"\nErreur : vous avez déjà atteint le nombre maximal de voeux !\n"RESET);
		return;
	}
	else {
		printf(GRAS UNDERLINE"\n\tListe de vos voeux : \n"RESET);
		for(v=cand->choix->premier, j=1; v; v = v->suivant, ++j) {
			printf(GRAS"\t\tChoix n°%d\n"RESET, j);
			afficher1Voeu(v);
		}
	}

	strcpy(nom, "0");
	while (strcmp(nom, "-1") != 0)
	{
		saisieStringControlee(nom, CYAN"\nEntrez l'IUT correspondant à votre voeux (-1 pour annuler) : "RESET);
		strcpy(nom, upperfcase(nom));

		if (strcmp(nom, "-1") == 0) return;
		else
		{
			posIut = rechercheIUT(tiut, nbIUT, nom, &trouve);

			if (trouve)
			{
				afficher1Depart(tiut[posIut]);

				while (strcmp(depart, "-1") != 0)
				{
					saisieStringControlee(depart, CYAN"Entrez le nom du département auquel vous voulez candidater (-1 pour annuler) : "RESET);
					strcpy(depart, upperfcase(depart));

					if (strcmp(depart, "-1") == 0) return;	
					else
					{
						int trouve = 0;
						for(mDept = tiut[posIut]->ldept->premier; mDept != NULL ; mDept = mDept->suivant)
						{
							if (strcmp(mDept->departement, depart) == 0)
							{
								if (!existeVoeu(cand, nom, depart))
								{
									v = creerVoeu(nom, depart);

									if (cand->nbChoix == 0)
									{
										cand->choix->premier = v;
										cand->choix->dernier = v;
									}
									else
									{
										cand->choix->dernier->suivant = v;
										cand->choix->dernier = v;
									}
											
									cand->nbChoix += 1;
									printf(VERT"\nVoeu ajouté !\n"RESET);
									return;
								}
								else
								{
									fprintf(stderr, ROUGE"\nErreur : vous avez déjà formulé ce voeu !\n"RESET);
									return;
								}
										
							}
									
						}
						if (!trouve) fprintf(stderr, ROUGE"\nErreur : le département est introuvable !\n"RESET);
					}		
				}
			}
			else fprintf(stderr, ROUGE"\nErreur : l'IUT est introuvable !\n"RESET);
		}
	}
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

void afficher1Candidat(Candidat *cand) {
	int j;
	Voeu* v;

	printf("\n\tNuméro du candidat : %d\n\tNommination : %s %s\n", cand->num, cand->prenom, cand->nom);
	printf("\tNote de mathématique : %.2f\n\tNote de français : %.2f\n\tNote d'anglais : %.2f\n\tNote de la matière de spécialité : %.2f\n\tMoyenne des notes : %.2f\n", cand->notes[0], cand->notes[1],  cand->notes[2], cand->notes[3], cand->moyenne); 
	printf("\tNombre de voeux : %d\n", cand->nbChoix);

	for(v=cand->choix->premier, j=1; v; v = v->suivant, ++j) {
		printf(GRAS"\t\tChoix n°%d\n"RESET, j);
		afficher1Voeu(v);
	}
}

void afficher1Voeu(Voeu* voeu) {
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

		for(i=0; i < *nbCand; ++i) afficher1Candidat(tCand[i]);
	}
	else fprintf(stderr, ROUGE"\nIl n'y a pas de candidat.\n"RESET);
}

void afficherCandidatsDepart(Candidat **tCand, int *nbCand) {
	int i, nbCandDept; 
	Voeu* v;
	char dept[30]; 
	Candidat** tCandDept;

	while (strcmp(dept, "-1") != 0) {
		nbCandDept = 0;

		saisieStringControlee(dept, CYAN"\nPour quel département souhaitez-vous avoir la liste des candidats (-1 pour annuler) ? "RESET);
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
				for(i=0; i<nbCandDept; ++i) printf("%s %s\n", tCandDept[i]->nom, tCandDept[i]->nom);
			}

			free(tCandDept);
		}
	}
}

void supprimerVoeux(Candidat* cand) 
{
	int numVoeu;
	Voeu *prec, *voeuSup, *v;
	int i, j;

	if(cand->nbChoix == 0) {
		fprintf(stderr, ROUGE"\nVous n'avez pas de voeu.\n"RESET);
		return;
	}

	while(numVoeu != -1) {
		printf(GRAS UNDERLINE"\n\tListe de vos voeux : \n"RESET);
		for(v=cand->choix->premier, j=1; v; v = v->suivant, ++j) {
			printf(GRAS"\t\tChoix n°%d\n"RESET, j);
			afficher1Voeu(v);
		}
		saisieIntControlee(&numVoeu, CYAN"Entrez le numéro du voeu que vous voulez supprimé (-1 pour annuler) : "RESET);

		while((numVoeu < 0 && numVoeu != -1) || numVoeu > j-1) {
			fprintf(stderr, ROUGE"\nChoix incorrect.\n"RESET);
			saisieIntControlee(&numVoeu, CYAN"\nEntrez le numéro du voeu que vous voulez supprimé (-1 pour annuler) : "RESET);
		}

		if(numVoeu != -1) {
			if(numVoeu == 1) {
				voeuSup = cand->choix->premier;
				cand->choix->premier = cand->choix->premier->suivant;
				free(voeuSup);
			}
			else if (numVoeu == j-1) {
				voeuSup = cand->choix->dernier;
				prec = cand->choix->premier;
				for(i=1; i < j-2; ++i) prec = prec->suivant;
				prec->suivant = NULL;
				free(cand->choix->dernier);
				cand->choix->dernier = prec;
			}
			else {
				voeuSup = cand->choix->premier;
				prec = cand->choix->premier;
				for(i=1; i < j-2; ++i) voeuSup = voeuSup->suivant;
				for(i=1; i < j-3; ++i) prec = voeuSup->suivant;
				prec->suivant = voeuSup->suivant;
				free(voeuSup);
			}
			--cand->nbChoix;
			printf(VERT"\nLe voeu a bien été supprimé.\n"RESET);
			
		}
	}	
	printf("\nFin de l'opération.\n");
	return;
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
		saisieStringControlee(prenom, CYAN"\nEntrez votre prénom (-1 pour annuler) : "RESET);
		strcpy(prenom, upperfcase(prenom));

		if (strcmp(prenom, "-1") != 0)
		{
			strcpy(c->prenom, prenom);
			strcpy(prenom, "-1");
			while (strcmp(nom, "-1") != 0)
			{
				saisieStringControlee(nom, CYAN"Entrez votre nom (-1 pour annuler) : "RESET);
				strcpy(nom, uppercase(nom));

				if (strcmp(nom, "-1") != 0)
				{
					strcpy(c->nom, nom);
					strcpy(nom, "-1");
					ma=0;fr=0;an=0;spe=0;
					while (ma != -1 && fr != -1 && an != -1 && spe != -1)
					{
						saisieFloatControlee(&ma, CYAN"Entrez votre note de maths (-1 pour annuler) : "RESET);
						while ((ma < 0 && ma != -1) || ma > 20)
						{
							fprintf(stderr, ROUGE"\nLa note doit être comprise entre 0 et 20\n"RESET);
							saisieFloatControlee(&ma, CYAN"\nEntrez votre note de maths (-1 pour annuler) : ");
						}
						if (ma == -1) break;

						saisieFloatControlee(&fr, CYAN"Entrez votre note de français (-1 pour annuler) : "RESET);
						while ((fr < 0 && fr != -1) || fr > 20)
						{
							fprintf(stderr, ROUGE"\nLa note doit être comprise entre 0 et 20\n"RESET);
							saisieFloatControlee(&fr, CYAN"\nEntrez votre note de français (-1 pour annuler) : "RESET);
						}
						if (fr == -1) break;
						
						saisieFloatControlee(&an, CYAN"Entrez votre note d'anglais (-1 pour annuler) : "RESET);
						while ((an < 0 && an != -1) || an > 20)
						{
							fprintf(stderr, ROUGE"\nLa note doit être comprise entre 0 et 20\n"RESET);
							saisieFloatControlee(&an, CYAN"\nEntrez votre note d'anglais (-1 pour annuler) : "RESET);
						}
						if (an == -1) break;

						saisieFloatControlee(&spe, CYAN"Entrez votre note de spécialité (-1 pour annuler) : "RESET);
						while ((spe < 0 && spe != -1) || spe > 20)
						{
							fprintf(stderr, ROUGE"\nLa note doit être comprise entre 0 et 20\n"RESET);
							saisieFloatControlee(&spe, CYAN"\nEntrez votre note de spécialité (-1 pour annuler) : "RESET);
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
						
						printf(VERT"\nCandidat ajouté !\n"RESET);
						return ntCand;
					}
				}
			}
		}
	}
	
	printf("\nFin de l'opération...\n");
	free(c);
	return tCand;
}

void sauvegarderFileCandidats(FileCandidats fc, char *nomFichier)
{
	FILE *f = fopen(nomFichier, "wb");
	Voeu *v;
	MaillonFileCandidat *mfc;

	for (mfc = fc->tete ; mfc != NULL ; mfc = mfc->suivant)
	{
		fwrite(&(mfc->candidat->num), sizeof(int), 1, f);
		fwrite(&(mfc->candidat->nom), sizeof(mfc->candidat->nom), 1, f);
		fwrite(&(mfc->candidat->prenom), sizeof(mfc->candidat->prenom), 1, f);
		fwrite(&(mfc->candidat->notes), sizeof(float), 4, f);
		fwrite(&(mfc->candidat->nbChoix), sizeof(int), 1, f);
		
		for (v = mfc->candidat->choix->premier ; v != NULL ; v = v->suivant) fwrite(v, sizeof(Voeu), 1, f);

		fprintf(f, "\n");
	}
	
	fclose(f);
}

void validerVoeux(Candidat *cand)
{
	int numVoeu, nbVoeuxValide = 0, i = 0;
	Bool valide = 0;
	Voeu *v;

	printf("Voici les départements où vous avez été accepté :\n");
	for (v = cand->choix->premier ; v != NULL ; v = v->suivant)
	{
		if (v->decDepartement)
		{ 
			if (v->decCandidat == 1)
			{
				fprintf(stderr, ROUGE"Vous avez déjà accepté un voeu de manière définitive !\n"RESET);
				return;
			}
			valide = 1;
			nbVoeuxValide++;
			afficher1Voeu(v);
		}
	}
	if (valide) 
	{
        saisieIntControlee(&numVoeu, CYAN"\nEntrez le numéro du voeu à accepter (cette décision est définitive) : "RESET);
		while (numVoeu > nbVoeuxValide || (numVoeu < 0 && numVoeu != -1))
        {
            fprintf(stderr, ROUGE"\nChoix invalide\n"RESET);
            saisieIntControlee(&numVoeu, CYAN"\nEntrez le numéro du voeu à accepter (cette décision est définitive) : "RESET);
        }
		if (numVoeu == -1) return;

        for (v = cand->choix->premier ; v != NULL ; v = v->suivant)
        {
            if (v->decDepartement && ++i == numVoeu) v->decCandidat = 1;
            else v->decCandidat = -1;
        }

		printf(VERT"\nVotre voeu à bien été validé !\n"RESET);
		
	}
	else printf("\nAucun département ne vous a accepté...\n");
}
