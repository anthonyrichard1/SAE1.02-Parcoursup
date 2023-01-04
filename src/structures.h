#ifndef STRUCT_H
#define STRUCT_H

/**
 * \file structures.h
 * \author Anthony RICHARD
 * \author Léana BESSON
 * \date 14/12/2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define ROUGE "\e[1;31m"
#define VERT "\e[1;32m"
#define BLANC "\e[0m"

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
}*ListeDept;

/**
 * \struct VilleIUT structures.h
 * \brief Cette structure représente une ville où il y a au moins 1 IUT.
 * \param ville Chaîne de 30 caractères - Le nom de la ville.
 * \param ldept Liste de départements - La liste des départements présents dans la ville.
*/
typedef struct
{
    char ville[30];
    ListeDept ldept;
} VilleIUT;

typedef int Bool;

typedef struct Voeux Voeux;

typedef int Decision;

struct Voeux
{
    Voeux *suivant;
    char ville[30];
    char departement[30];
    Decision decDepartement;
    Decision decCandidat;
};

#endif
