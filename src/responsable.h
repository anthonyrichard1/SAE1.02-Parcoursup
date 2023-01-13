/**
 * \file responsable.h
 * \author Anthony RICHARD
 * \author Léana BESSON
 * \date 14/12/2022
 * \brief Dans ce fichier sont repertoriées les fonctions concernant le responsable.
*/

#include "structures.h"
#include "administrateurs.h"

/**
 * \brief Cette fonction permet de calculer la moyenne de quatre notes. 
 * \param note[] Tableau de flottant - la tableau qui contient les quatre notes pour lequel il faut calculer la moyenne.
 * \return Flottant - la moyenne des quatre notes. 
*/
float calculMoyenne(float notes[]);

/**
 * \brief Cette fonction permet de chercher un voeu en fonction d'un IUT et d'un département.
 * \param l Structure ListeVoeux - liste de voeux où il faut chercher le voeu.
 * \param *iut Chaîne de caractère - nom de l'IUT qui faut chercher.
 * \param *dept Chaîne de caratère - nom du département qu'il faut chercher. 
 * \return Pointeur sur un Voeu - le voeu qui a été trouvé ou NULL si le voeu n'a pas été trouvé. 
*/
Voeu* chercherVoeux(ListeVoeux l, char *iut, char *dept);

/**
 * \brief Cette fonction permet de filtrer les candidats pour stocker dans des fichiers différents les admis, les listes d'attentes et les refusés.
 * \param **tiut Tableau de pointeur sur des IUT - le tableau dans lequel sont répertoriés les iut.
 * \param *nbIUT Pointeur sur un entier - le nombre d'iut contenus dans le tableau.
 * \param **tCnand Tableau de pointeurs sur des candidats - le tableau contenant les candidats à filtrer.
 * \param *nbCand Pointeur sur un entier - le nombre de candidats contenus dans le tableau.
*/
void filtrerCandidatures(VilleIUT **tiut, int *nbIUT, Candidat **tCand, int *nbCand);

/**
 * \brief Cette fonction permet de trier un tableau de pointeurs sur des candidats par moyenne décroissante, avec la méthode du tri rapide récursif (quick sort inversé récursif).
 * \param **tab Tableau de pointeur sur des candidats - le tableau contenant les candidats à trier.
 * \param nbCand Entier - le nombre de candidats contenus dans le tableau.
*/
void triNumerique(Candidat **tab, int nbCand);

/**
 * \brief Cette fonction permet de sauvegarder dans un fichier une file de candidats.
 * \param fc File de candidats - la file de candidats à sauvegarder.
 * \param *nomFichier Chaîne de caractères - le nom du fichier dans lequel il faut sauvegarder les candidats.
*/
void sauvegarderFileCandidats(FileCandidats fc, char *nomFichier);

/**
 * \brief Cette fonction permet d'afficher tous les candidats admis dans un IUT quelque soit le département.
 * \param **tCnand Tableau de pointeurs sur des candidats - le tableau contenant les candidats à afficher.
 * \param *nbCand Pointeur sur un entier - le nombre de candidats contenus dans le tableau.
*/
void afficherCandidatsIUT(Candidat **tCand, int *nbCand);
