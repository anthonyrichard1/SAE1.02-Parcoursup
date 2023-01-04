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

    while ((f = fopen("iut.don", "r")) == NULL)
    {
        testFopen("iut.don");
    }

    fscanf(f, "%d", nbIUT);

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

			if (listeDept->premier == NULL)
			{
				listeDept->premier = listeDept->dernier = m;
			}
			else
			{
				listeDept->dernier->suivant = m;
				listeDept->dernier = m;
			}
		}
		
		iut->ldept = listeDept;
		tab[j] = iut;
	}	
	
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
        if (cmp < 0)
        {
            fin = milieu-1;
        }
        else
        {
            debut = milieu+1;
        }
    }

    *trouve = 0;
    return debut;
}

void afficher1Depart(VilleIUT *v)
{
	int i;
	MaillonDept *m;
	
	printf("\nListe des départements de l'IUT de %s\n", v->ville);
	m = v->ldept->premier;
	
	for (i = 0 ; i < v->ldept->nb ; i++)
	{
		printf("\t%s %d %s\n", m->departement, m->nbP, m->nomRes); 
		m = m->suivant;
	}
	
	printf("\n");
}

void afficherDepart(VilleIUT ** tiut, int *nbIUT)
{
		char choix[30] = "";
		int i, pos, trouve;
		
		while (strcmp(choix, "-1") != 0)
		{
			printf("Quel IUT souhaitez-vous voir en détail (nom de ville/tous/-1 pour annuler) ? ");
			scanf("%s", choix);
			
			if (strcmp(choix, "tous") == 0)
			{
				for (i = 0 ; i < *nbIUT ; i++)
				{
					afficher1Depart(tiut[i]);
				}
			}
			else if (strcmp(choix, "-1") != 0)
			{
				pos = rechercheIUT(tiut, nbIUT, choix, &trouve);
				
				if (trouve)
				{
					afficher1Depart(tiut[pos]);
				}
				else
				{
					fprintf(stderr, ROUGE"Erreur : la ville %s ne possède pas d'IUT !\n"BLANC, choix);
				}
				
			}
		}
		
		printf("Abandon de l'opération...\n");
}
