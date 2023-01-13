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
 * \param **tiut Tableau de pointeurs sur des VilleIUT - le tableau qui contient toutes les informations concernant les IUT.
 * \param *nbIUT Pointeur sur un entier - le nombre d'IUT contenus dans le tableau (taille logique de tiut).
 * \param **tCand Tableau de pointeurs sur des candidats - le tableau qui contient toutes les informations sur les candidats.
 * \param nbCand Entier - nombre de candidats contenus dans le tableau.
 * \param *phase Pointeur sur une structure Phase - contient l'état de la phase en cours.
 */
void menuPrincipal(VilleIUT** tiut, Candidat** tCand, int *nbIUT, int *nbCand, Phase *phase);

/**
 * \brief Cette fonction affiche le menu des administrateurs, et permet de sélectionner l'opération que l'on souhaite effectuer. Le choix de l'utilisateur est récupéré par une saisie au clavier.
 * \param **tiut Tableau de pointeurs sur des VilleIUT - le tableau qui contient toutes les informations concernant les IUT.
 * \param *nbIUT Pointeur sur un entier - le nombre d'IUT contenus dans le tableau (taille logique de tiut).
 * \param **tCand Tableau de pointeurs sur des candidats - le tableau qui contient toutes les informations sur les candidats.
 * \param nbCand Entier - nombre de candidats contenus dans le tableau.
 * \param *phase Pointeur sur une structure Phase - contient l'état de la phase en cours.
 */
void menuAdministrateur(VilleIUT** tiut, Candidat** tCand, int *nbIUT, int *nbCand, Phase *phase);

/**
 * \brief Cette fonction affiche le menu des candidats, et permet de sélectionner l'opération que l'on souhaite effectuer. Le choix de l'utilisateur est récupéré par une saisie au clavier.
 * \param **tiut Tableau de pointeurs sur des VilleIUT - le tableau qui contient toutes les informations concernant les IUT.
 * \param *nbIUT Pointeur sur un entier - le nombre d'IUT contenus dans le tableau (taille logique de tiut).
 * \param **tCand Tableau de pointeurs sur des candidats - le tableau qui contient toutes les informations sur les candidats.
 * \param nbCand Entier - nombre de candidats contenus dans le tableau.
 * \param *phase Pointeur sur une structure Phase - contient l'état de la phase en cours.
 * \param *pos Pointeur sur un enter - position du candidat dans le tableau.
 */
void menuCandidat(VilleIUT** tiut, Candidat** tCand, int *nbIUT, int *nbCand, Phase *phase, int *pos);

/**
 * \brief Cette fonction affiche le menu des responsables, et permet de sélectionner l'opération que l'on souhaite effectuer. Le choix de l'utilisateur est récupéré par une saisie au clavier.
 * \param **tiut Tableau de pointeurs sur des VilleIUT - le tableau qui contient toutes les informations concernant les IUT.
 * \param *nbIUT Pointeur sur un entier - le nombre d'IUT contenus dans le tableau (taille logique de tiut).
 * \param **tCand Tableau de pointeurs sur des candidats - le tableau qui contient toutes les informations sur les candidats.
 * \param nbCand Entier - nombre de candidats contenus dans le tableau.
 * \param *phase Pointeur sur une structure Phase - contient l'état de la phase en cours.
 */
void menuResponsable(VilleIUT** tiut, Candidat** tCand, int *nbIUT, int *nbCand, Phase *phase);

/**
 * \brief Cette fonction permet de récupérer les données contenues dans le tableau de pointeurs sur des VilleIUT pour les stocker dans le fichier iut.don. Elle est utilisée à chaque modification du tableau de pointeur sur VilleIUT et à la fermeture de l'application.
 * \param **tiut Tableau de pointeurs sur des VilleIUT - le tableau qu'il faut sauvegarder dans le fichier iut.don.
 * \param *nbIUT Pointeur sur un entier - le nombre d'IUT contenus dans le tableau (taille logique de tiut).
 */
void sauvegarde(VilleIUT ** tiut, int *nbIUT, Phase *phase);

/**
 * \brief Cette fonction gère le lancement de l'application en chargeant les différents tableaux et en lançant le menus principal.
*/
void lancement(void);

#endif
