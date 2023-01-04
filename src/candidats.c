#include "candidats.h"

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