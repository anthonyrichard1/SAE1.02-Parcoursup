/**
 * \file informations.h
 * \author Anthony RICHARD
 * \author Léana BESSON
 * \date 14/12/2022
 * \brief Dans ce fichier sont répertoriées toutes les fonctions qui permettent à un utilisateur de rechercher des informations sur des IUT.
*/
#include "structures.h" 
#include "erreur.h"

/**
 * \brief Cette fonction permet de creer une liste de departements vide.
 * \return ListeDept - la liste de départements vide.
 */
ListeDept creerListeDept(void);

/**
 * \brief Cette fonction permet de charger des VilleIUT depuis un fichier texte vers un tableau de pointeurs sur des VilleIUT, en retournant par *nbIUT la taille logique du tableau.
 * \param *nbIUT Pointeur sur un entier - le nombre d'IUT contenus dans le tableau.
 */
VilleIUT **chargerIUT(int *nbIUT);

/**
 * \brief Cette fonction permet de rechercher un IUT dans un tableau de pointeurs sur des VilleIUT. Elle renvoie la position de la VilleIUT dans le tableau si elle est présente ou la position d'insertion dans le cas contraire. Elle renvoie aussi par *trouve si la valeur est présente dans le tableau ou non.
 * \param **tab Tableau de pointeurs sur des VilleIUT - le tableau dans lequel il faut rechercher une ville.
 * \param *nbIUT Pointeur sur un entier - le nombre d'IUT contenus dans le tableau **tab (taille logique du tableau).
 * \param *val Chaîne de caractères - la ville à chercher dans le tableau.
 * \param *trouve Pointeur sur un entier (type bool) - cet entier est égal à 1 si l'IUT à chercher est dans le tableau et 0 dans le cas contraire.
 * \return Entier - la position de l'IUT s'il est dans le tableau, sa position d'insertion dans le cas contraire.
 */
int rechercheIUT(VilleIUT **tab, int *nbIUT, char *val, Bool *trouve);

/**
 * \brief Cette fonction permet d'afficher les informations de l'IUT passé en argument, à savoir la liste de ses départements avec à chaque le nom du département, le nombre de places en première année et le nom du responsable.
 * \param *v Pointeur sur un IUT - L'IUT à afficher.
 */
void afficher1Depart(VilleIUT *v);

/**
 * \brief Cette fonction permet d'afficher les informations d'un IUT, saisie par l'utilisateur au début de la fonction. L'utilisateur peut saisir "tous" s'il souhaite afficher les informations de tous les IUT.
 * \param **tiut Tableau de pointeurs sur des VilleIUT - le tableau contenant les IUT que l'on peut afficher.
 * \param *nbIUT Pointeur sur un entier - le nombre d'IUT contenus dans le tableau (taille logique de **tiut).
*/
void afficherDepart(VilleIUT **tiut, int *nbIUT);
