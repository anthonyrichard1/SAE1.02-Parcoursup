#include "structures.h"

#include <stdlib.h>

ListeDept creerListeDept(void)
{
    ListeDept ld = (ListeDept)malloc(sizeof(struct ListeDept));
    ld->premier = ld->dernier = NULL;

    return ld;
}