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
/*                sucre syntaxique               */
/*************************************************/


#define AND &&
#define OR ||
#define ISNOT !=
#define NOT !
#define then

typedef enum { FALSE, TRUE} bool;


/*************************************************/
/*          definition type liste                */
/*************************************************/

typedef struct Bloc
{
    int nombre;
    struct Bloc *suivant;
} Bloc;

typedef Bloc *Liste ;



/*************************************************/
/*        definition type liste de liste         */
/*************************************************/

typedef struct Bloc_L
{
    Liste nombre;
    struct Bloc_L *suivant;
} Bloc_L;

typedef Bloc_L *Liste_L ;



/*************************************************/
/*        Fonctions de Base                      */
/*************************************************/

bool estVide(Liste l)
{
    return l == NULL ;
}




int premier(Liste l)
{
    return l->nombre ; 
}




Liste ajoute(int x, Liste l)
{
    Liste tmp = (Liste) malloc(sizeof(Bloc)) ;
    tmp->nombre = x ;
    tmp->suivant = l ;
    return tmp ;
}




void empile(int x, Liste *L)
{
      *L = ajoute(x,*L) ; 
}




Liste suite(Liste l)
{
    return l->suivant ;
}




void initVide( Liste *L )
{
    *L = NULL ;
}




void depile(Liste *L)
{
    Liste tmp = *L ;
    *L = suite(*L) ;
    free(tmp) ;
}




void VideListe(Liste *L)
{
    if(NOT(estVide(*L)))
    {
        depile(L) ;
        VideListe(L) ;
    }      
}




void affiche_rec(Liste l)
{
    if(estVide(l))
        printf("\n");
    else
    {
        printf("-> %d ", premier(l));
        affiche_rec(suite(l));
    }
}




int longueur_rec (Liste l)
{
    if (l == NULL)
         return 0 ;
    else return (1 + longueur_rec(l->suivant)) ;
}






bool estVide_L(Liste_L ll)
{
    return ll == NULL ;
}




Liste premier_L(Liste_L ll)
{
    return ll->nombre ; 
}




Liste_L ajoute_L(Liste x, Liste_L ll)
{
    Liste_L tmp = (Liste_L) malloc(sizeof(Bloc_L)) ;
    tmp->nombre = x ;
    tmp->suivant = ll ;
    return tmp ;
}




void empile_L(Liste x, Liste_L *LL)
{
      *LL = ajoute_L(x, *LL) ; 
}




Liste_L suite_L(Liste_L ll)
{
    return ll->suivant ;
}




void initVide_L( Liste_L *LL )
{
    *LL = NULL ;
}




int Llongueur_rec (Liste_L ll)
{
    if (ll == NULL)
         return 0 ;
    else return (1 + Llongueur_rec(ll->suivant)) ;
}




void depile_L(Liste_L* LL)
{
    Liste_L tmp = *LL ;
    VideListe(&((*LL)->nombre)) ;
    *LL = suite_L(*LL) ;
    free(tmp) ;
}




void VideListe_L(Liste_L *LL)
{
    if(NOT(estVide_L(*LL)))
    {
        depile_L(LL) ;
        VideListe_L(LL) ;
    }
}




void Laffiche_rec(Liste_L ll)
{
    if(estVide_L(ll))
       printf("\n");
    else
    {   
        printf("-");
        affiche_rec(premier_L(ll)) ;
        Laffiche_rec(suite_L(ll));
    }
}



/*************************************************/
/*            Permutations                       */
/*************************************************/


/*************************************************/
/*      Commentaire sur l'optimisation :         */
/*   I)                                          */
/*      Il est probablement plus judicieux       */
/*        de procéder par inout                  */
/*      affin d'éviter tous ces malloc.          */
/*  II)                                          */
/*      Essayer de faire une procedure           */
/*      pour vider la liste serai bien.          */
/*      Actuellement, elle ne marche pas         */
/*      car plusieurs Listes se repetes          */
/*      donc des fois on free plusieurs fois     */
/*      la même mémoire                          */
/*************************************************/



Liste_L AETTL(int x, Liste_L LL){
    if(estVide_L(LL))
       return LL ;
    else 
       return ajoute_L (ajoute (x, premier_L(LL) ),
                        AETTL (x, suite_L(LL) ));
}




Liste_L ATP(int x, Liste L){
    if (estVide(L)) 
    {
        Liste_L ll ; initVide_L(&ll) ;

        return ajoute_L (ajoute(x, L), ll);
    }

    else 
       return ajoute_L (ajoute (x, L), 
                        AETTL (premier(L), 
                               ATP (x, suite(L) )));
}




Liste_L Concat (Liste_L LL1, Liste_L LL2)
{
    if (estVide_L(LL1)) 
       return LL2 ;
    else 
       return ajoute_L (premier_L(LL1), 
                        Concat (suite_L(LL1), LL2));
}





Liste_L ATLTP (int x, Liste_L LL)
{
    if (estVide_L(LL)) 
    {
        Liste_L ll ; initVide_L(&ll) ;

        return ll ;
    }
    else 
       return Concat (ATP(x, premier_L(LL)),
                      ATLTP(x, suite_L(LL)));
}




Liste_L Permutations (int n)
{
    if (n == 0)
    {
        Liste_L ll ; initVide_L(&ll) ;

        Liste l ; initVide(&l) ;

        empile_L(l, &ll);

        return ll ;
    }
    else
       return ATLTP (n, Permutations (n - 1)) ;
}






int main(int argc, char const *argv[])
{   
    
	return 0;
}