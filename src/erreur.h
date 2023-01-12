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

/**
 * \brief Cette fonction permet de tester la présence de chiffres dans un mot. Elle renvoie 1 s'il y a un chiffre et 0 dans le cas contraire.
 * \param *mot Chaîne de caractères - le mot à tester.
 * \return Bool - ce booléen contient 1 s'il y a un chiffre dans le mot et 0 dans le cas contraire.
*/
Bool chiffreDansMot(char *mot);

/**
 * \brief Cette fonction permet de contrôler la saisie d'un entier lu sur l'entrée standard (stdin) pour éviter une boucle infinie dans le cas où l'utilisateur saisirait une chaîne de caractères. En plus du message d'erreur classique, elle affiche le message passé en argument pour donner plus de précision sur les conditions que l'entier saisie donc remplir pour être conforme.
 * \param *var Pointeur sur un entier - la variable dans laquelle il faut stocker l'entier lu sur l'entrée standard.
 * \param *message Chaîne de caractères - le message complémentaire à afficher.
*/
void saisieIntControlee(int *var, char *message);

/**
 * \brief Cette fonction permet de contrôler la saisie d'un flottant lu sur l'entrée standard (stdin) pour éviter une boucle infinie dans le cas où l'utilisateur saisirait une chaîne de caractères. En plus du message d'erreur classique, elle affiche le message passé en argument pour donner plus de précision sur les conditions que le flottant saisie donc remplir pour être conforme.
 * \param *var Pointeur sur un flottant - la variable dans laquelle il faut stocker le flottant lu sur l'entrée standard.
 * \param *message Chaîne de caractères - le message complémentaire à afficher.
*/
void saisieFloatControlee(float *var, char *message);

/**
 * \brief Cette fonction permet de contrôler la saisie d'une chaîne de caractères lue sur l'entrée standard (stdin) pour éviter par exemple qu'un chiffre se glisse dans le nom de Département ou d'un candidat. En plus du message d'erreur classique, elle affiche le message passé en argument pour donner plus de précision sur les conditions que la chaîne saisie donc remplir pour être conforme.
 * \param *var Chaîne de caractères - la variable dans laquelle il faut stocker la châine lue sur l'entrée standard.
 * \param *message Chaîne de caractères - le message complémentaire à afficher.
*/
void saisieStringControlee(char *var, char *message);