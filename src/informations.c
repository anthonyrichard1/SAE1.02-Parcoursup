#include "informations.h"

ListeDept creerListeDept(void)
{
    ListeDept ld = (ListeDept)malloc(sizeof(struct ListeDept));
    testMalloc(ld, "Liste de départements");

    ld->premier = ld->dernier = NULL;
    ld->nb = 0;

    return ld;
}

VilleIUT **chargerIUT(int *nbIUT)
{
    FILE *f;
    int i, j;
    VilleIUT **tab;

    while ((f = fopen("iut.don", "r")) == NULL) testFopen("iut.don");

    fscanf(f, "%d %d", phase, nbIUT);

    tab = (VilleIUT**)malloc(sizeof(VilleIUT*)*(*nbIUT));
    testMalloc(tab, "liste des IUT");
    
    for (j = 0 ; j < *nbIUT ; j++)
    {
		VilleIUT *iut = (VilleIUT*)malloc(sizeof(VilleIUT));
		testMalloc(iut, "IUT");

		fscanf(f, "%s", iut->ville);

		ListeDept listeDept = creerListeDept();

		fscanf(f, "%d", &listeDept->nb);
		
		for (i = 0 ; i < listeDept->nb ; i++)
		{
			MaillonDept *m = (MaillonDept*)malloc(sizeof(MaillonDept));

			fscanf(f, "%s", m->departement);
			fscanf(f, "%d", &m->nbP);
			fscanf(f, "%s", m->nomRes);

			if (listeDept->premier == NULL) listeDept->premier = listeDept->dernier = m;
			else
			{
				listeDept->dernier->suivant = m;
				listeDept->dernier = m;
			}
		}
		
		iut->ldept = listeDept;
		tab[j] = iut;
	}	
	
	fclose(f);
    return tab;
}

int rechercheIUT(VilleIUT **tab, int *nbIUT, char *val, Bool *trouve)
{
    int debut = 0, milieu, fin = *nbIUT-1, cmp;

    while (debut <= fin)
    {
        milieu = (debut+fin)/2;
        cmp = strcmp(val, tab[milieu]->ville);

        if (!cmp)
        {
            *trouve = 1;
            return milieu;
        }
        if (cmp < 0) fin = milieu-1;
        else debut = milieu+1;
    }

    *trouve = 0;
    return debut;
}

void afficher1Depart(VilleIUT *v)
{
	int i;
	MaillonDept *m;

	if (!v->ldept->nb) printf("\nAucun département dans cet IUT...\n");
	else
	{
		printf("\nListe des départements de l'IUT de %s\n", v->ville);
		m = v->ldept->premier;
		
		for (i = 0 ; i < v->ldept->nb ; i++)
		{
			printf("\t%s %d %s\n", m->departement, m->nbP, m->nomRes); 
			m = m->suivant;
		}
		
		printf("\n");
	}	
}

void afficherDepart(VilleIUT **tiut, int *nbIUT)
{
		char choix[30] = "";
		int i, pos;
		Bool trouve;
		
		while (strcmp(choix, "-1") != 0)
		{
			saisieStringControlee(choix, CYAN"\nQuel IUT souhaitez-vous voir en détail (nom de ville/tous/-1 pour annuler) ? "RESET);
			strcpy(choix, upperfcase(choix));

			if (strcmp(choix, "Tous") == 0)
			{
				for (i = 0 ; i < *nbIUT ; i++) afficher1Depart(tiut[i]);
			}
			else if (strcmp(choix, "-1") != 0)
			{
				pos = rechercheIUT(tiut, nbIUT, choix, &trouve);
				
				if (trouve) afficher1Depart(tiut[pos]);
				else fprintf(stderr, ROUGE"\nErreur : la ville %s ne possède pas d'IUT !\n"RESET, choix);				
			}
		}
		
		printf("\nFin de l'opération...\n");
}

void afficherDepartPrecis(VilleIUT **tiut, int *nbIUT) 
{
	char choix[30] = "0";
	int i;
	Bool trouve;

	while (strcmp(choix, "-1") != 0) {
		saisieStringControlee(choix, CYAN"\nQuel département souhaitez-vous trouver (nom du département/-1 pour annuler) ? "RESET);
		strcpy(choix, upperfcase(choix));

		if(strcmp(choix, "-1") != 0) {
			trouve = 0;

			for(i=0; i < *nbIUT; i++) 
			{
				if (existeDepart(tiut[i]->ldept, choix)) {
					trouve = 1;
					printf(GRAS UNDERLINE"\nListe des ville où l'IUT à un département %s\n"RESET, choix);
					printf("\t%s\n", tiut[i]->ville);
				}
			}

			if(trouve == 0) fprintf(stderr, ROUGE"\nLe département n'a pas été trouvé.\n"RESET);
		}
	}

	printf("\nFin de l'opération...\n");
}

int existeDepart(ListeDept ld, char *val)
{
	MaillonDept *d;

	for (d = ld->premier ; d != NULL ; d = d->suivant)
		if (strcmp(d->departement, val) == 0) return 1;
	
	return 0;
}
