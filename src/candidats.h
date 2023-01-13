/**
 * \file candidats.h
 * \author Anthony RICHARD
 * \author Léana BESSON
 * \date 14/12/2022
 * \brief Dans ce fichier sont repertoriées les structures utilisées par l'application.
*/
#include "structures.h"
#include "responsable.h"

/**
 * \brief Cette fonction permet d'afficher la phase en cours et de renvoyer la phase. Cela permet de réutiliser de manière efficace le retour de la fonction dans une autre.
 * \param *phase Phase - la phase en cours.
 * \return Phase - la phase passée en argument.
*/
Phase afficherPhase(Phase *phase);

/**
 * \brief Cette fonction permet de trier un tableau de candidat par ordre alphabétique de nom, avec la méthode du tri rapide récursif.
 * \param **tCand Tableau de pointeurs sur des candidats - le tableau à trier.
 * \param nbCand Entier - nombre de candidats contenus dans le tableau.
*/
void triAlpha(Candidat **tCand, int nbCand);

/**
 * \brief Cette fonction permet de créer une liste de Voeux vide.
 * \return ListeVoeux - la liste de voeux vide.
*/
ListeVoeux creerListeVoeux(void);

/**
 * \brief Cette fonction permet de créer un voeu à partir d'un iut et d'un département.
 * \param *iut Chaîne de 30 caractères - le nom de l'IUT.
 * \param *dept Chaîne de 30 caractères - le nom du département.
 * \return Voeu - le voeu crée.
*/
Voeu *creerVoeu(char *iut, char *dept);

/**
 * \brief Cette fonction permet de tester l'existance d'un voeu à partir d'un candidat.
 * \param *c Pointeur sur un Candidat - le candidat dont il faut tester les voeux.
 * \param *iut Chaîne de 30 caractères - le nom de l'IUT à tester.
 * \param *depart Chaîne de 30 caractères - le nom du département.
 * \return Entier - renvoie 1 si le voeu est trouvé et 0 dans le cas contraire.
*/
int existeVoeu(Candidat *c, char *iut, char *depart);

/**
 * \brief Cette fonction permet d'ajouter un voeu à un candidat.
 * \param **tiut Tableau de pointeurs sur des VillesIUT - le tableau contenant la liste des IUT.
 * \param *nbIUT Pointeur sur un entier - le nombre d'IUT contenus dans le tableau des IUT.
 * \param *cand Pointeur sur un candidat - le candidat auquel il faut ajouter un voeu.
*/
void ajouterVoeu(VilleIUT **tiut, int *nbIUT, Candidat *cand);

/**
 * \brief Cette fonction permet de sauvegarder les candidats depuis un tableau de pointeurs sur des candidats vers le fichier binaire candidats.don.
 * \param **tCand Tableau de pointeurs sur des candidats - le tableau à sauvegarder.
 * \param *nbCand Pointeur sur un entier - le nombre de candidats contenus dans le tableau.
 * \param *nomFichier Chaîne de caractères - le fichier dans lequel il faut sauvegarder les données.
*/
void sauvegarderCandidats(Candidat **tCand, int *nbCand, char *nomFichier);

/**
 * \brief Cette fonction permet de charger un tableau de pointeurs sur des candidats depuis le fichier binaire candidats.bin
 * \param *nbCand Pointeur sur un entier - le nombre de candidats contenus dans le tableau.
 * \return Tableau de pointeurs sur des candidats - le tableau chargé.
*/
Candidat **chargerCandidats(int *nbCand);

/**
 * \brief Cette fonction permet d'afficher un seul candidat.
 * \param *cand Pointeur sur un candidat - le candidat qu'il faut afficher.
*/
void afficher1Candidat(Candidat *cand);

/**
 * \brief Cette fonction permet d'afficher un seul voeu. 
 * \param voeu Poiteur sur une structure voeu - le voeu à affiche. 
*/
void afficher1Voeu(Voeu* voeu);

/**
 * \brief Cette fonction permet d'afficher tous les candidats contenu dans le tableau des candidats.
 * \param **tCand Tableau de pointeurs sur des candidats - le tableau qui contient les informations sur les candidats à afficher.
 * \param *nbCand Pointeur sur un entier - le nombre de candidats contenus dans le tableau.
*/
void afficherCandidats(Candidat **tCand, int *nbCand);

/**
 * \brief Cette fonction permet d'afficher tous les candidats en fonction des départements de leur voeu.
 * \param **tCand Tableau de pointeurs sur des candidats - le tableau qui contient les informations sur les candidats à afficher.
 * \param *nbCand Pointeur sur un entier - le nombre de candidats contenus dans le tableau.
*/
void afficherCandidatsDepart(Candidat **tCand, int *nbCand);

/**
 * \brief Cette fonction permet de supprimer le voeu d'un candidat. 
 * \param *cand Pointeur sur un candidat - le candidat doit il faut supprimer le voeu.
*/
void supprimerVoeux(Candidat* cand);

/**
 * \param **tCand Tableau de pointeurs sur des candidats - le tableau dans lequel il faut ajouter un candidat.
 * \param *nbCand Pointeur sur un entier - le nombre de candidats contenus dans le tableau.
 * \return Tableau de pointeur sur des candidats - le nouveau tableau de candidats.
*/
Candidat **ajouterCandidats(Candidat **tCand, int *nbCand);

/**
 * \brief Cette fonction permet au candidat de voir les voeux qui ont été accepté et de valider un voeu.
 * \param *cand Pointeur sur un candidat - le candidat doit il faut valider un voeu.
*/
void validerVoeux(Candidat *cand);
