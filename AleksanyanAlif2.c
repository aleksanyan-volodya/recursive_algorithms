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
    int nombre;
    struct Bloc *suivant;
} Bloc;

typedef Bloc *Liste ;

/*************************************************/
/*                                               */
/*                predeclarations                */
/*                                               */
/*************************************************/

/* initialise une Liste à vide */
void initVide(Liste *L);

/* renvoie 1 si la Liste en parametre est vide, 0 sinon */
bool estVide(Liste l);

/* renvoie le premier element de la Liste en parametre */
int premier(Liste l);

/* renvoie une nouvelle Liste correspondant a celle en parametre, avec l'element x ajoute en haut de la pile */
Liste ajoute(int x, Liste l);

/* modifie la Liste en parametre: x est ajoute comme premier element */
void empile(int x, Liste* L);

/* renvoie une nouvelle Liste correspondant a celle en parametre sans son premier element */
Liste suite(Liste l);

/* modifie la Liste en parametre: le premier element est retire */
void depile(Liste* l);

/* affichage simple en recursif et en iteratif */
void affiche_rec(Liste l);
void affiche_iter(Liste l);

/* longueur en recursif et en iteratif */
int longueur_rec (Liste l);
int longueur_iter (Liste l);

/*  Elimination du dernier element en recursif et en iteratif  */
/*  VD est la sousprocedure utilitaire de la version recursive */
void VD (Liste *L);
void VireDernier_rec (Liste *L);
void VireDernier_iter (Liste *L);


/*************************************************/

bool UnPlusDeuxEgalTrois(Liste l) ;

bool CroissanteAux(Liste L) ;
bool Croissante(Liste L) ;

int NombreMemePosition_rec(Liste l1, Liste l2) ;
int NombreMemePosition_iter(Liste l1, Liste l2) ;
int NombreMemePosition_FnRecTerAux(Liste l1, Liste l2, int cpt) ;
int NombreMemePosition_FnRecTer(Liste l1, Liste l2) ;
void NombreMemePosition_PrRecTerAux(Liste l1, Liste l2, int* acc) ;
int NombreMemePosition_PrRecTer(Liste l1, Liste l2) ;

Liste FoncVireDernier_recAux(Liste l) ;
Liste FoncVireDernier_rec(Liste l) ;
Liste FoncVireDernier_iter(Liste l) ;

void AjouteDevantPremierZero(int x, Liste *L) ;

void AjouteDevantDernierZero_RNT_Aux(Liste *L, int x, bool f, bool *dernier0) ;
void AjouteDevantDernierZero_RNT(Liste *L, int x) ;
void AjouteDevantDernierZero_RT_Aux(Liste *L, int x, bool f, Liste *result) ;
void AjouteDevantDernierZero_RT(Liste *L, int x) ;
void AjouteDevantDernierZero_iter(Liste *L, int x) ;


void TicAux(Liste* L) ;
void Tic(Liste* L) ;

/*************************************************/
/*                                               */
/*                briques de base                */
/*                                               */
/*************************************************/


void initVide( Liste *L)
{
    *L = NULL ;
}

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



void depile(Liste *L)
{
    Liste tmp = *L ;
    *L = suite(*L) ;
    free(tmp) ;
}

/*************************************************/
/*                                               */
/*     Affiche, avec les briques de base         */
/*                                               */
/*************************************************/

void affiche_rec(Liste l)
{
    if(estVide(l))
        printf("\n");
    else
    {
        printf("%d ", premier(l));
        affiche_rec(suite(l));
    }
}


void affiche_iter(Liste l)
{
    Liste L2 = l;
    while(!estVide(L2))
    {
        printf("%d ", premier(L2));
        L2 = suite(L2);
    }
    printf("\n");
}

/*************************************************/
/*                                               */
/*     Longueur, sans les briques de base        */
/*                                               */
/*************************************************/

int longueur_rec (Liste l)
{
    if (l == NULL)
         return 0 ;
    else return (1 + longueur_rec(l->suivant)) ;
}


int longueur_iter (Liste l)
{
    Liste P = l;
    int cpt = 0 ;
    while (P ISNOT NULL)
    {   P = P->suivant ;
        cpt++ ;
    }
    return cpt ;
}

/*************************************************/
/*                                               */
/*       VireDernier,                            */
/*               sans les briques de base,       */
/*               ni le "->"                      */
/*                                               */
/*************************************************/

void VD (Liste *L)
          // *L non NULL ie liste non vide
{
     if ( ((**L).suivant) == NULL )
            depile(L) ;   // moralement : depile(& (*L)) ;
     else VD (& ( (**L).suivant )) ;
}

void VireDernier_rec (Liste *L)
{
     if ( (*L) ISNOT NULL )
          VD(L);        // moralement : VD(& (*L)) ;
}

void VireDernier_iter (Liste *L)
{
    if ( (*L) ISNOT NULL)
    {
        while ( ((**L).suivant) ISNOT NULL )
                 L = & ( (**L).suivant ) ;
        free(*L) ;
        *L = NULL ;
     }
}


/*************************************************/
/*                                               */
/*       Libere la memoire                       */
/*                                               */
/*************************************************/

void VideListe(Liste *L)
{
    if(NOT(estVide(*L)))
    {
        depile(L) ;
        VideListe(L) ;
    }
      
}



/*************************************************/
/*************************************************/
/***                                           ***/
/***         Partie   I                        ***/
/***                                           ***/
/***   " Beware of bugs in the above code;     ***/
/***     I have only proved it correct,        ***/
/***     not tried it."  -  Donald Knuth       ***/
/***                                           ***/
/*************************************************/
/*************************************************/


/*************************************************/
/*                                               */
/*           1 + 2 = 3                           */
/*                                               */
/*************************************************/

bool UnPlusDeuxEgalTrois (Liste l) 
{
    int elem1 = 0 ;
    int elem2 = 0 ;

    if ( l ISNOT NULL )
    {
        elem1 = l->nombre ;
        if ( l->suivant ISNOT NULL )
        {
            elem2 = l->suivant->nombre ;
            if ( l->suivant->suivant ISNOT NULL ) 
            {
                return (elem1 + elem2 == l->suivant->suivant->nombre);
            }
        }
    }

    return ( elem1 == -elem2 ) ;
}




/*************************************************/
/*                                               */
/*           Croissante récursive                */
/*                                               */
/*************************************************/
bool CroissanteAux (Liste L) 
{
    if (L->suivant == NULL) 
        return TRUE ;
    
    else if (L->nombre >= L->suivant->nombre) 
        return FALSE ;
    
    else 
        return CroissanteAux(L->suivant) ;
}

bool Croissante (Liste L) 
{
    if (L == NULL) 
        return TRUE ; 
    else 
        return CroissanteAux(L) ;
}




/*************************************************/
/*                                               */
/*         Nombres sur la même place             */
/*                                               */
/*************************************************/

/***   RNT   ***/
int NombreMemePosition_rec (Liste l1, Liste l2) 
{
    if ( estVide(l1) OR estVide(l2) ) 
        return 0 ;

    else if ( premier(l1) == premier(l2) ) 
        return 1 + NombreMemePosition_rec (suite(l1), suite(l2)) ;
    
    else 
        return NombreMemePosition_rec (suite(l1), suite(l2)) ;
}

/*************************************************/

/***   Iter   ***/
int NombreMemePosition_iter(Liste l1, Liste l2) 
{
    int cpt = 0;
    while ( l1 ISNOT NULL AND l2 ISNOT NULL ) 
    {
        if (premier(l1) == premier(l2)) then ++cpt ;
        l1 = suite(l1) ;
        l2 = suite(l2) ;
    }
    return cpt ;
}

/*************************************************/

/***   FRT   ***/
int NombreMemePosition_FnRecTerAux (Liste l1, Liste l2, int cpt)
{
    if (estVide(l1) OR estVide(l2)) 
        return cpt ;

    else if (premier(l1) == premier(l2)) 
        return NombreMemePosition_FnRecTerAux(l1, l2, cpt+1) ;

    else 
        return NombreMemePosition_FnRecTerAux(l1, l2, cpt) ;
}

int NombreMemePosition_FnRecTer (Liste l1, Liste l2)
{
    return NombreMemePosition_FnRecTerAux (l1, l2, 0) ;
}

/*************************************************/

/***   PRT   ***/
void NombreMemePosition_PrRecTerAux (Liste l1, Liste l2, int* acc)
{
    if (estVide(l1) OR estVide(l2))
        return ;

    else 
    {
        if (premier(l1) == premier(l2)) then ++(*acc) ;
        NombreMemePosition_PrRecTerAux (l1, l2, acc) ;
    }
}

int NombreMemePosition_PrRecTer(Liste l1, Liste l2)
{
    int acc = 0 ;
    NombreMemePosition_PrRecTerAux(l1, l2, &acc) ;
    return acc ; 
}




/*************************************************/
/*                                               */
/*         deleate the last   element            */
/*                                               */
/*************************************************/

/***    RNT     ***/
Liste FoncVireDernier_recAux (Liste l) 
{
    if (l->suivant == NULL) 
       return NULL ;

    else 
       return ajoute(premier(l), 
                      FoncVireDernier_recAux (suite(l))) ;
}

Liste FoncVireDernier_rec (Liste l) 
{
    if (l == NULL) 
       return NULL ;

    else 
       return FoncVireDernier_recAux(l) ;
}

/*************************************************/

/***    Iter     ***/
Liste FoncVireDernier_iter (Liste l) 
{
    if (l == NULL || l->suivant == NULL) 
        return NULL ;
    
    else {
        Liste nouvelleListe = (Liste)malloc(sizeof(Bloc)) ;
        Liste tmp = nouvelleListe ;
        
        while (suite(suite(l)) ISNOT NULL) {
            empile (premier(l), &tmp) ;
            l = l->suivant ;
            tmp = tmp->suivant ;
        }
        
        depile(&tmp) ;
        
        return nouvelleListe ;
    }
}






/*************************************************/
/*                                               */
/*         Ajoute x devant 0                     */
/*                                               */
/*************************************************/

void AjouteDevantPremierZero (int x, Liste *L) 
{
    if (estVide(*L) OR premier(*L) == 0) 
        empile(x, L) ;

    else
        AjouteDevantPremierZero (x, &((*L)->suivant)) ;

}




/*************************************************/
/*                                               */
/*         Ajoute x devant dernier 0             */
/*                                               */
/*************************************************/

/***    RNT     ***/
void AjouteDevantDernierZero_RNT_Aux(Liste *L, int x, bool f, bool *dernier0) {
    if (estVide(*L)) {
        if (f) *dernier0 = 1;
        else empile(x, L);
    } else {
        if (premier(*L) == 0) {
            f = 1;
        }
        AjouteDevantDernierZero_RNT_Aux(&((*L)->suivant), x, f, dernier0);
        if (*dernier0 && premier(*L) == 0) {
            empile(x, L);
            *dernier0 = 0;
        }
    }
}

void AjouteDevantDernierZero_RNT(Liste *L, int x) {
    bool dernier0 = 0;
    AjouteDevantDernierZero_RNT_Aux(L, x, 0, &dernier0);
}



/***   RT   ***/
void AjouteDevantDernierZero_RT_Aux(Liste *L, int x, bool f, Liste *result) {
    if (estVide(*L)) {
        if (f) 
            empile(x,result);
        else 
            empile(x,L);
    }
    else if (premier(*L)==0) 
        AjouteDevantDernierZero_RT_Aux(&((*L)->suivant),x,1,L);
    else
        AjouteDevantDernierZero_RT_Aux(&((*L)->suivant),x,f,result);
}
void AjouteDevantDernierZero_RT(Liste *L, int x) {
    if (estVide(*L)) empile(x,L);
    else {
        Liste *result=L;
        AjouteDevantDernierZero_RT_Aux(L,x,0,result);
    }
}


/***   Iter   ***/
void AjouteDevantDernierZero_iter(Liste *L, int x) {
    if (estVide(*L)) {
        empile(x,L);
    } else {
        Liste *L2=L;  
        Liste *L3=NULL;
        while (!estVide(*L2)){
            if (premier(*L2)==0) L3=L2;
            L2= &((*L2)->suivant); 
        }
        if (L3==NULL) empile(x,L2);
        else empile(x, L3);
    }
}


/*************************************************/
/*                                               */
/*         re-repeat                             */
/*                                               */
/*************************************************/
void TicAux(Liste* L)
{
    if (*L != NULL && premier(*L) == 0)
    {
        depile(L);
        TicAux(L);
    }
}

void Tic(Liste* L) 
{
    if (estVide(*L)) 
       return;

    if (premier(*L) != 0) 
    {
        empile(0, L);
        Tic(&(((*L)->suivant)->suivant));
    } 
    else
       TicAux(L);
}




/*************************************************/
/*                                               */
/*           Main                                */
/*                                               */
/*************************************************/

void poup (Liste l)
{
        printf("Double Affichage \n") ;
        affiche_rec(l) ;
        affiche_iter(l) ;

        printf("Longueur en double %d %d \n\n", 
                           longueur_rec(l), 
                           longueur_iter(l) 
               ) ;
}

int main(int argc, char** argv)
{
    Liste l ;

        initVide (&l) ;
             empile(4, &l) ;
             empile(5, &l) ;
             empile(6, &l) ;
             empile(0, &l) ;
             empile(0, &l) ;
             empile(0, &l) ;
             empile(0, &l) ;
             empile(0, &l) ;
             empile(6, &l) ;
             empile(7, &l) ;
             empile(9, &l) ;

          poup(l) ;
          Tic(&l) ;
          poup(l) ;


    VideListe(&l);

    return 0;
}





