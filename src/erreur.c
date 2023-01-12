#include "erreur.h"

void testMalloc(void *elt, char *procedure)
{
    if (elt == NULL)
    {
        fprintf(stderr, ROUGE"%s : erreur d'allocation mémoire", procedure);
        perror(""RESET);
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

void saisieIntControlee(int *var, char *message)
{
    printf(message);
    int resscanf = scanf("%d", var);

    while (!resscanf)
    {
        fprintf(stderr, ROUGE"saisie invalide, recommencez : "RESET);
        resscanf = scanf("%*c%d", var);
    }
}

void saisieFloatControlee(float *var, char *message)
{
    printf(message);
    int resscanf = scanf("%f", var);

    while (!resscanf)
    {
        fprintf(stderr, ROUGE"saisie invalide, recommencez : "RESET);
        resscanf = scanf("%*c%f", var);
    }
}

void saisieStringControlee(char *var, char *message)
{
    printf(message);
    scanf("%s", var);
    
    while (chiffreDansMot(var) && strcmp(var, "-1") != 0)
    {
        fprintf(stderr, ROUGE"Saisie invalide, recommencez : "RESET);
        scanf("%s", var);
    }
}

Bool chiffreDansMot(char *mot)
{
	int len = strlen(mot), i;

	for (i = 0 ; i < len ; i++)
	{
		if (mot[i] == '0' || mot[i] == '1' || mot[i] == '2' || mot[i] == '3' || mot[i] == '4' || mot[i] == '5' || mot[i] == '6' || mot[i] == '7' || mot[i] == '8' || mot[i] == '9')
			return 1;
	}

	return 0;
}
