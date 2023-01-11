/**
 * \file administrateurs.h
 * \author Anthony RICHARD
 * \author Léana BESSON
 * \date 14/12/2022
 * \brief Dans ce fichier sont répertoriées toutes les fonctions des administrateurs.
*/
#include "structures.h" 
#include "menus.h"

/**
 * \brief Cette fonction permet d'ajouter un IUT dans un tableau d'IUT, qui est ensuite renvoyé.
 * \param **tiut Tableau de pointeurs sur des VilleIUT - le tableau dans lequel il faut ajouter la ville.
 * \param *nbIUT Pointeur sur un entier - le nombre d'IUT contenus dans le tableau (taille logique de tiut).
 * \return VilleIUT - La nouvelle adresse du tableau passé en argument.
 */
VilleIUT **ajouterIUT(VilleIUT **tiut, int *nbIUT);

/**
 * \brief Cette fonction permet de créer un nouveau MaillonDept avec de nom du département passé en paramètre, le nombre de places et le nom du responsable est entré au clavier. 
 * \param newDept Chaine de caractère - le nom du département du nouveau maillon. 
 * \return MaillonDept* - L'addresse du nouveau maillon à ajouter dans la liste des départements. 
 */
MaillonDept* nouveauMaillonDept(char* newDept);

/**
 * \brief Cette fonction d'ajouter un département dans un tableau de pointeurs sur des VilleIUT.
 * \param **tiut Tableau de pointeurs sur des VilleIUT  - tableau dans lequel il faut recherché la ville où se trouve le département à ajouter.
 * \param *nbIUT Pointeur sur un entier - le nombre d'IUT contenus dans le tableau (taille logique de tiut).
 */
void AjouterDepart(VilleIUT** tiut, int *nbIUT);

/**
 * \brief Cette fonction permet de supprimer un IUT dans un tableau de pointeurs sur des VilleIUT.
 * \param **tiut Tableau de pointeurs sur des VilleIUT - le tableau dans lequel il faut supprimer la ville.
 * \param *nbIUT Pointeur sur un entier - le nombre d'IUT contenus dans le tableau (taille logique de tiut).
 */ 
void supprimerIUT(VilleIUT **tiut, int *nbIUT);

/**
 * \brief Cette fonction de supprimer un département dans un tableau de pointeurs sur des VilleIUT.
 * \param **tiut Tableau de pointeurs sur des VilleIUT  - tableau dans lequel il faut recherché la ville où se trouve le département à supprimer.
 * \param *nbIUT Pointeur sur un entier - le nombre d'IUT contenus dans le tableau (taille logique de tiut).
 */
void supprimerDepart(VilleIUT **tiut, int *nbIUT);

/**
 * \brief Cette fonction permet de stopper la phase de candidature.
 * \param *phase Phase - contient l'état de la phase en cours.
 */
void StopperCandidature(Phase *phase);

/**
 * \brief Cette fonction permet de lancer la phase de candidature.
 * \param *phase Phase - contient l'état de la phase en cours.
 */
void LancerCandidature(Phase *phase);

/**
 * \brief Cette fonction permet de modifier le nombre de place d'un département d'un IUT. 
 * \param **tiut Tableau de pointeurs sur des VilleIUT - tableau dans lequel il faut recherché la ville où se trouve le département à modifier. 
 * \param *nbIUT Pointeur sur un entier - le nombre d'IUT contenus dans le tableau (taille logique de tiut).
 */
void ModifPlaces(VilleIUT** tiut, int *nbIUT);

/**
 * \brief Cette fonction permet de modifier le nom du responsable d'un département d'un IUT. 
 * \param **tiut Tableau de pointeurs sur des VilleIUT - tableau dans lequel il faut recherché la ville où se trouve le département à modifier. 
 * \param *nbIUT Pointeur sur un entier - le nombre d'IUT contenus dans le tableau (taille logique de tiut).
 */
void ModifierRes(VilleIUT** tiut, int *nbIUT);