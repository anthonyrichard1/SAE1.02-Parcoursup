#ifndef STRUCT_H
#define STRUCT_H

/**
 * \file structures.h
 * \author Anthony RICHARD
 * \author Léana BESSON
 * \date 14/12/2022
 * \brief Dans ce fichier sont repertoriées les structures utilisées par l'application.
*/

//Inclusion des .h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

//Définition des couleurs
#define ROUGE "\e[1;31m"
#define VERT "\e[1;32m"
#define RESET "\e[0m"
#define GRAS "\e[1;37m"
#define UNDERLINE "\e[4;37m"
#define TITRE "\e[1;36m\e[4;36m"
#define CYAN "\e[0,36m"

typedef struct MaillonDept MaillonDept;

/**
 * \struct MaillonDept structures.h
 * \brief Cette structure représente un département.
 * \param departement Chaîne de 30 caractères - Nom du département.
 * \param nbP Entier - Nombre de places en première année.
 * \param nomRes Chaîne de caractères - Nom du responsable du département.
 * \param *suivant Pointeur sur un département - Le département suivant.
*/
struct MaillonDept
{
    char departement[30];
    int nbP;
    char nomRes[50];
    MaillonDept *suivant;
};

/**
 * \struct ListeDept structures.h
 * \brief Cette structure représente une liste de départements.
 * \param *premier Pointeur sur un département - Le premier département de la liste.
 * \param *dernier Pointeur sur un département - Le dernier département de la liste.
 * \param nb Entier - Nombre de départements dans la liste.
*/
typedef struct ListeDept
{
    MaillonDept *premier;
    MaillonDept *dernier;
    int nb;
} *ListeDept;

/**
 * \struct VilleIUT structures.h
 * \brief Cette structure représente une ville où il y a un IUT.
 * \param ville Chaîne de 30 caractères - Le nom de la ville.
 * \param ldept Liste de départements - La liste des départements présents dans la ville.
*/
typedef struct
{
    char ville[30];
    ListeDept ldept;
}VilleIUT;

/**
 * \typedef int Bool
 * \brief Ce type représente un booléen ou 1 = vrai et 0 = faux.
*/
typedef int Bool;

/**
 * \typedef int Decision
 * \brief Ce type représente une décision sur un voeu, par un candidat ou un membre de département où 0 = dossier non traité, 1 = admis, -1 = refusé et 2 = sur liste d'attente.
*/
typedef int Decision;

typedef struct Voeu Voeu;

/**
 * \struct Voeu structures.h
 * \brief Cette structure représente un voeu d'un candidat.
 * \param *suivant Voeu - le voeu suivant.
 * \param ville Chaîne de 30 caractères - la ville concernée.
 * \param departement Chaîne de 30 caractères - le département concerné.
 * \param decDepartement Decision - la décision du département sur ce voeu.
 * \param decCandidat Decision - la décision du candidat sur ce voeu.
*/
struct Voeu
{
    Voeu *suivant;
    char ville[30];
    char departement[30];
    Decision decDepartement;
    Decision decCandidat;
};

/**
 * \struct ListeVoeux structures.h
 * \brief Cette structure représente une liste de voeux.
 * \param *premier Voeu - le premier voeu de la liste.
 * \param *dernier Voeu - le dernier voeu de la liste.
*/
typedef struct ListeVoeux
{
    Voeu *premier;
    Voeu *dernier;
}*ListeVoeux;

/**
 * \struct Candidat structures.h
 * \brief Cette structure représente un candidat.
 * \param num Entier - le numéro du candidat.
 * \param nom Chaîne de 30 caractères - le nom du candidat.
 * \param prenom Chaîne de 30 caractères - le prénom du candidat.
 * \param notes Tableau de 4 flottants - tableau contenant les notes du candidat dans l'ordre suivant : maths, français, anglais, spécialité.
 * \param nbChoix Entier - le nombre de voeux du candidat (taille de la liste de voeux).
 * \param choix ListeVoeux - la liste des voeux du candidat.
*/
typedef struct
{   unsigned num;
    char nom[30];
    char prenom[30];
    float notes[4];
    float moyenne;
    int nbChoix;
    ListeVoeux choix;
}Candidat;

typedef struct MaillonFileCandidat MaillonFileCandidat;

/**
 * \struct MaillonFileCandidat structures.h
 * \brief Cette structure représente un maillon dans une file de candidats.
 * \param *suivant Pointeur sur un maillon - le maillon suivant dans la file.
 * \param *candidat Pointeur sur un candidat - le candidat contenu dans le maillon.
*/
struct MaillonFileCandidat
{
    MaillonFileCandidat *suivant;
    Candidat *candidat;
};

/**
 * \struct FileCandidats structures.h
 * \brief Cette structure représente une liste d'attente pour les candidats qui souhaite rejoindre une formation mais n'ont pas le niveau pour être instantanément admis.
 * \param *tete Pointeur sur un maillon - le candidat en tête de la liste d'attente, le premier qui sera admis.
 * \param *queue Pointeur sur un maillon - le candidat qui est en fin de liste, celui qui aura le moins de chances d'être admis dans la formation.
 * \param nb Entier - le nombre de candidats en file d'attente.
*/
typedef struct FileCandidats
{
    MaillonFileCandidat *tete;
    MaillonFileCandidat *queue;
    int nb;
}*FileCandidats;


/**
 * \typedef int Phase
 * \brief Ce type représente une phase, égale à 0 si la phase de candidature n'a pas encore commencée, 1 si elle a commencée et 2 si elle est terminée.
*/
typedef int Phase;

#endif
