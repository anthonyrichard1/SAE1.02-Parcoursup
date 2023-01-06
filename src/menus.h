#ifndef MENUS_H
#define MENUS_H

/**
 * \file menus.h
 * \author Anthony RICHARD 
 * \author Léana BESSON
 * \date 14/12/2022
 * \brief Dans ce fichier sont répertoriées toutes les fonctions qui gère les menus de l'application.
 */

#include "structures.h"
#include "informations.h"
 
 /**
 * \brief Cette fonction affiche le menu principal, un menu permettant de sélectionner l'opération que l'on souhaite effectuer ou d'aller dans le menus administrateur. Elle ne possède aucun paramètre car l'option choisie est récupéré par une saisie au clavier.
 * \param **tiut Tableau de pointeurs sur des VilleIUT 
 * \param *nbIUT Pointeur sur un entier - le nombre d'IUT contenus dans le tableau (taille logique de tiut).
 */
void menuPrincipal(VilleIUT** tiut, int *nbIUT);

/**
 * \brief Cette fonction affiche le menu des administrateurs, et permet de sélectionner l'opération que l'on souhaite effectuer. Le choix de l'utilisateur est récupéré par une saisie au clavier.
 * \param **tiut Tableau de pointeurs sur des VilleIUT
 * \param *nbIUT Pointeur sur un entier - le nombre d'IUT contenus dans le tableau (taille logique de tiut).
 */
void menuAdministrateur(VilleIUT** tiut, int *nbIUT);

/**
 * \brief Cette fonction permet de récupérer les données contenues dans le tableau de pointeurs sur des VilleIUT pour les stocker dans le fichier iut.don. Elle est utilisée à chaque modification du tableau de pointeur sur VilleIUT et à la fermeture de l'application.
 * \param **tiut Tableau de pointeurs sur des VilleIUT - le tableau qu'il faut sauvegarder dans le fichier iut.don.
 * \param *nbIUT Pointeur sur un entier - le nombre d'IUT contenus dans le tableau (taille logique de tiut).
 */
void sauvegarde(VilleIUT ** tiut, int *nbIUT);





#endif
