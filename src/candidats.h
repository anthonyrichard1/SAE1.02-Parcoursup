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
 * \brief Cette fonction permet de trier un tableau de candidat par ordre alphabétique de nom.
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
 * \param **tCand Tableau de pointeurs sur des Candidats - le tableau contenant la liste des candidats.
 * \param *nbCand Pointeur sur un entier - le nombre de candidats contenus dans le tableau des candidats.
*/
void ajouterVoeu(VilleIUT **tiut, int *nbIUT, Candidat **tCand, int *nbCand);

void sauvegarderCandidats(Candidat **tCand, int *nbCand);

Candidat **chargerCandidats(int *nbCand);

void afficher1Candidat(Candidat **tCand, int pos);

void afficher1Voeu(Candidat** tCand, Voeu* voeu);

void afficherCandidats(Candidat **tCand, int *nbCand);

void afficherCandidatsDepart(Candidat **tCand, int *nbCand);

Candidat** supprimerVoeux(Candidat** tCand, int *nbCand);

char *upperfcase(char *motIn);

char *uppercase(char *motIn);

Bool chiffreDansMot(char *mot);

void ajouterCandidats(Candidat **tCand, int *nbCand);

float CalculMoyenne(float notes[]);

Voeu* chercherVoeux(ListeVoeux l, char *iut, char *dept);