/********************************/
/*                              */
/*      ALEKSANYAN Volodya      */
/*         ALIF Yassine         */
/*                              */
/*           LDD2 IM            */
/*                              */
/********************************/

#include <stdio.h>
#include <stdlib.h>

/*************************************************/
/*                                               */
/*                sucre syntaxique               */
/*                                               */
/*************************************************/

#define AND &&
#define OR ||
#define ISNOT !=
#define NOT !
#define then

typedef enum { FALSE, TRUE} bool;

/*************************************************/
/*                                               */
/*          definition type liste                */
/*                                               */
/*************************************************/
typedef struct Bloc
{
    int valeur;
    struct Bloc* next;
    struct Bloc** pred;
} Bloc;

typedef Bloc* ListesZ ;
typedef Bloc*** Acces ;

//////////////////////////////////////

void ZAjouteAvant(int x, Acces* acces)
{
    ListesZ monBloc = (ListesZ) malloc(sizeof(Bloc)) ;
    monBloc->valeur = x ;
    monBloc->next = monBloc ;
    monBloc->pred = &monBloc->next ;

    if (*acces != NULL){
        monBloc->next = ***acces ;
        monBloc->pred = **acces ;
        
        ***acces = monBloc ;
        **acces = &(monBloc->next) ;
        *acces = &(monBloc->pred) ;
    }
    
    *acces = &(monBloc->pred) ;
}


int main(int argc, char** argv)
{
    return 0;
}

