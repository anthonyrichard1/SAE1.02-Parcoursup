#include "structures.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

ListeDept creerListeDept(void)
{
    ListeDept ld = (ListeDept)malloc(sizeof(struct ListeDept));

    testMalloc(ld, "Liste de départements");

    ld->premier = ld->dernier = NULL;
    ld->nb = 0;

    return ld;
}

void testMalloc(void *elt, char *procedure)
{
    if (elt == NULL)
    {
        printf("%s : erreur d'allocation mémoire", procedure);
        perror("");
        exit(errno);
    }
}

int testFopen(char *nomFichier)
{
    int choix;
    perror(nomFichier);
    printf("Inserez le fichier %s dans ce dossier puis entrez 1 pour réessayer ou un autre chiffre pour quitter\n", nomFichier);
    scanf("%d", &choix);

    if (choix != 1)
    {
        printf("Abandon de la procédure...\n");
        exit(errno);
    }

    return choix;
}

VilleIUT **chargerIUT(int *nbIUT)
{
    FILE *f;
    int i, j, trouve, pos, nbDepart;
    char *nomRes;
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

int rechercheIUT(VilleIUT **tab, int nbIUT, char *val, bool *trouve)
{
    int debut = 0, milieu, fin = nbIUT-1, cmp;

    while (debut <= fin)
    {
        milieu = (debut+fin)/2;
        cmp = strcmp(val, tab[milieu]->ville);

        if (!cmp)
        {
            *trouve = 1;
            break;
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
