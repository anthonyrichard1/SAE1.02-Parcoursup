/**
 * \file structures.h
 * \author Anthony RICHARD
 * \author Léana BESSON
 * \date 14/12/2022
*/
#include "structures.h" 
#include "menus.h"

/**
 * \brief Cette fonction permet d'ajouter un IUT dans un tableau d'IUT, qui est ensuite renvoyé.
 * \param **tiut Tableau de pointeurs sur des VilleIUT - le tableau dans lequel il faut ajouter la ville.
 * \param *nbIUT Pointeur sur un entier - le nombre d'IUT contenus dans le tableau (taille logique de tiut).
 * \returns VilleIUT - La nouvelle adresse du tableau passé en argument.
 */
VilleIUT **ajouterIUT(VilleIUT **tiut, int *nbIUT);

/**
 * \brief Cette fonction permet de supprimer un IUT dans un tableau de pointeurs sur des VilleIUT.
 * \param **tiut Tableau de pointeurs sur des VilleIUT - le tableau dans lequel il faut supprimer la ville.
 * \param *nbIUT Pointeur sur un entier - le nombre d'IUT contenus dans le tableau (taille logique de tiut).
 */ 
void supprimerIUT(VilleIUT **tiut, int *nbIUT);

/**
 * \brief Cette fonction de supprimer un département dans un tableau de pointeurs sur des VilleIUT.
 * \param **tiut Tableau de pointeurs sur des VilleIUT - le tableau dans lequel il faut supprimer la ville.
 * \param *nbIUT Pointeur sur un entier - le nombre d'IUT contenus dans le tableau (taille logique de tiut).
 */
void supprimerDepart(VilleIUT **tiut, int *nbIUT);
