/**
 * \file menus.h
 * \author Anthony RICHARD Léana BESSON
 * \date 14/12/2022
 * \brief Dans ce fichier sont répertoriées toutes les fonctions qui gère les menus de l'application.
 */
#include "administrateurs.h" 
 /**
 * \brief Cette fonction affiche le menu principal, un menu permettant de choisir entre les deux sous menus administrateur et utilisateur. Elle ne possède aucun paramètre car l'option choisie est récupéré par une saisie au clavier.
 */
void menuPrincipal(void);

/**
 * \brief Cette fonction affiche le menu des administrateurs, et permet de sélectionner l'opération que l'on souhaite effectuer. Le choix de l'utilisateur est récupéré par une saisie au clavier.
 */
 void menuAdministrateur(void);
 
 /**
 * \brief Cette fonction affiche le menu des utilisateurs, et permet de sélectionner l'opération que l'on souhaite effectuer. Le choix de l'utilisateur est récupéré par une saisie au clavier.
 */
 void menuUtilisateur(void);
