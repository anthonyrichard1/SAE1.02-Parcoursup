/**
 * \file structures.h
 * \author Anthony RICHARD
 * \author Léana BESSON
 * \date 14/12/2022
*/

typedef struct MaillonDept MaillonDept;

/**
 * \struct MaillonDept structures.h
 * \brief Cette structure représente un département.
 * \param departement Chaîne de 30 caractères - Nom du département.
 * \param nbP Entier - Nombre de places en première année.
 * \param nomRes Chaîne de caractères - Nom du responsable du département.
 * \param suivant Pointeur sur un département - Le département suivant.
*/
struct MaillonDept
{
    char departement[30];
    int nbP;
    char nomRes[50];
    MaillonDept *suivant;
};

typedef struct ListeDept *ListeDept;

/**
 * \struct ListeDept structures.h
 * \brief Cette structure représente une liste de départements.
 * \param premier Pointeur sur un département - Le premier département de la liste.
 * \param dernier Pointeur sur un département - Le dernier département de la liste.
 * \param nb Entier - Nombre de départements dans la liste.
*/
struct ListeDept
{
    MaillonDept *premier;
    MaillonDept *dernier;
    int nb;
};

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
}VilleIUT;

typedef int bool;

ListeDept creerListeDept(void);

VilleIUT **chargerIUT(int *nbIUT);

void testMalloc(void *elt, char *procedure);

int testFopen(char *nomFichier);

int rechercheIUT(VilleIUT **tab, int *nbIUT, char *val, bool *trouve);

void afficher1Depart(VilleIUT *v);

void afficherDepart(VilleIUT ** tiut, int *nbIUT);

#define ROUGE "\e[1;31m"
#define VERT "\e[1;32m"
#define BLANC "\e[0m"
