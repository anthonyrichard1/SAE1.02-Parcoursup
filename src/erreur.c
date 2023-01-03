#include "erreur.h"

void testMalloc(void *elt, char *procedure)
{
    if (elt == NULL)
    {
        fprintf(stderr, ROUGE"%s : erreur d'allocation mémoire", procedure);
        perror(""BLANC);
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