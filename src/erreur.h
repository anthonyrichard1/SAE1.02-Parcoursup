/**
 * \file erreur.h
 * \author Anthony RICHARD
 * \author Léana BESSON
 * \date 14/12/2022
 * \brief Dans ce fichier sont répertoriées toutes les fonctions qui permettent de gérer les erreurs.
*/
#include "candidats.h"

/**
 * \brief Cette fonction permet de tester les malloc et les realloc et affiche un message d'erreur avec errno si l'opération n'a pas fonctionné.
 * \param *elt Pointeur sur * - l'adresse du malloc à tester.
 * \param *procedure Chaîne de caractères - la procédure à afficher dans le message d'erreur.
*/
void testMalloc(void *elt, char *procedure);

/**
 * \brief Cette fonction permet d'afficher un message d'erreur lors d'un fopen et de renvoyer le choix de l'utilisateur (abandon ou pas).
 * \param *nomFichier Chaîne de caractères - le nom du fichier sur lequel on a fait le fopen à tester.
 * \return Entier - le choix de l'utilisateur, 1 pour réessayer d'ouvrir le fichier ou un autre chiffre pour quitter le programme.
*/
int testFopen(char *nomFichier);
