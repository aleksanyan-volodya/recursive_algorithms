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

typedef enum { false, true} bool;




/*************************************************/
/*                                               */
/*                  Pile                         */
/*                                               */
/*************************************************/

typedef struct Bloc {
    int nombre;
    struct Bloc *suivant;
} Bloc;
typedef Bloc *Pile ;

Pile ajoute(int x, Pile Pl)
{
    Pile tmp = (Pile) malloc(sizeof(Bloc)) ;
    tmp->nombre = x ;
    tmp->suivant = Pl ;
    return tmp ;
}

void empile(int x, Pile *Pl)
{
      *Pl = ajoute(x,*Pl) ; 
}

void depile(Pile *Pl) {
    Pile tmp = *Pl ;
    *Pl = (*Pl)->suivant ;
    free(tmp) ;
}




/*************************************************/
/*                                               */
/*            factorielle                        */
/*                                               */
/*************************************************/

long fact (int n) 
{ if (n==0) return 1 ;
  else return n * fact(n-1) ; 
}

// itou avec un arg out => passage par adresse

void bisfact(int n, long * r) 
{ if (n==0) 
         *r=1.0 ;
  else { bisfact(n-1,r) ;
         *r = *r *n ;
       }
}

long fact2 (int n) 
{ long r ;
  bisfact(n,&r) ;
  return r ;
}




/*************************************************/
/*                                               */
/*            Calcul de e                        */
/*                                               */
/*************************************************/

  // d'après google,
  // e = 2,7182818284 5904523536 0287471352 6624977572 4709369995 
  //       9574966967 6277240766 3035354759 4571382178 5251664274

     // Il est proposé de faire 3 versions pour observer des phénomènes de précision.
     // C'est le même code, seul le type change.

/*************************************************/

void EfloatAux(float* e, float terme, int n, float precision) 
{   
    if (terme >= precision) 
    {
        ++n;
        terme *= (1.0 / n);
        *e += terme;
        EfloatAux(e, terme, n, precision);
    }
}

float Efloat () 
{
    float e = 1.0;
    EfloatAux(&e, 1.0, 0, 1e-5f); // precision = 1e-5 car il est de type float
    return e ;
}

/*************************************************/

void EdoubleAux(double* e, double terme, int n, double precision) 
{   
    if (terme >= precision) 
    {
        ++n;
        terme *= (1.0 / n);
        *e += terme;
        EdoubleAux(e, terme, n, precision);
    }
}

double Edouble () 
{ 
    double e = 1.0;
    EdoubleAux(&e, 1.0, 0, 1e-12); // precision = 1e-12 car il est de type double
    return e ;
}

/*************************************************/

void ElongdoubleAux(long double* e, long double terme, int n, long double precision) 
{   
    if (terme >= precision) 
    {
        ++n;
        terme *= (1.0 / n);
        *e += terme;
        ElongdoubleAux(e, terme, n, precision);
    }
}

long double Elongdouble () 
{ 
    long double e = 1.0;
    ElongdoubleAux(&e, 1.0, 0, 1e-14L); // precision = 1e-14L car il est de type long double
    return e ;
}




/*************************************************/
/*                                               */
/*            Suite Y                            */
/*                                               */
/*************************************************/

void afficheYfloatAux (int n, float* y) 
{
    if (n == 0) 
    {
        *y = Efloat() - 1.0;
        printf("##Float## \n y0 = %f", *y );
    }
    else 
    {
        afficheYfloatAux(n-1, y);
        *y = (*y * n) - 1.0;
        printf(" y%d = %f ", n, *y );
    }
}

void afficheYfloat (int n) 
{
    float y;
    afficheYfloatAux (n, &y);
    printf("\n");
}

/*************************************************/

void afficheYdoubleAux (int n, double* y) 
{
    if (n == 0) 
    {
        *y = Edouble() - 1.0;
        printf("##double## \n y0 = %lf", *y );
    }
    else 
    {
        afficheYdoubleAux(n-1, y);
        *y = (*y * n) - 1.0;
        printf(" y%d = %lf ", n, *y );
    }
}

void afficheYdouble (int n) 
{
    double y;
    afficheYdoubleAux (n, &y);
    printf("\n");
}

/*************************************************/

void afficheYlongdoubleAux (int n, long double* y) 
{
    if (n == 0) 
    {
        *y = Elongdouble() - 1.0;
        printf("##long double## \n y0 = %Lf", *y );
    }
    else 
    {
        afficheYlongdoubleAux(n-1, y);
        *y = (*y * n) - 1.0;
        printf(" y%d = %Lf ", n, *y );
    }
}

void afficheYlongdouble (int n) 
{
    long double y;
    afficheYlongdoubleAux (n, &y);
    printf("\n");
}




/*************************************************/
/*                                               */
/*            Puissance                          */
/*                                               */
/*************************************************/

double power1 (double x, long n) 
{
    if (n == 0) return 1.0 ; // no else
    if (x == 0) return 0 ; // probleme pour x = 0
    else {
        if (n > 0) return x * power1(x, n - 1) ;
        else return 1.0 / (x * power1(x, -n - 1)) ;
    }
    
}

/*************************************************/

double power2a (double x, long n) 
{    
    double r = 1.0;
    
    // Si n est négatif, calculez la puissance réciproque
    if (n < 0) {
        x = 1 / x; // oui ca plante pour 0^-1
        n = -n;
    } // no else

    for (int i = 0; i < n; ++i) {
        r *= x ;
    }
    
    return r;
}

/*************************************************/

double power2b (double x, long n) 
{ 
    double r = 1.0 ;
    while (n > 0) {
        r *= x ; 
        --n ;
    }
    return r ; 
}

/*************************************************/

void power3Aux (double x, long n, double* r)
{
    if (n == 0) then return ;
    else {
        *r *= x ;
        power3Aux (x, n-1, r) ;
    }
}

double power3 (double x, long n) 
{ 
    double r = 1.0 ;
    power3Aux(x, n, &r) ;
    return r ;
}

/*************************************************/

double power4Aux (double x, long n, double r)
{
    if (n == 0) return r;
    else return power4Aux (x, n-1, r*x) ;
}

double power4 (double x, long n) 
{ 
    return power4Aux(x, n, 1.0) ;
}

/*************************************************/

     //   Observation (1+1/10^k)^(10^k) : rame : 8 en 1/2s, 9 en qqs s, 10 en 1m

double power5 (double x, long n)
{
    if (n == 0)
        return 1 ;
    else if (n % 2 == 0)
        return (power5(x,n/2)*power5(x,n/2)   ) ;
    else    
        return (power5(x,n/2)*power5(x,n/2) *x) ;   
}

/*************************************************/

double power6 (double x, long n) 
{
    if (n == 0) 
        return 1.0 ;
    else {
        double y = power6 (x, n/2);
        if (n%2) return y * y * x ; 
        else     return y * y ; 
    }
}

/*************************************************/

double power7 (double x, long n) 
{
    if (n == 0) return 1.0 ;
    else {
        if (n%2) return power7( x*x, n/2) * x ; 
        else     return power7( x*x, n/2) ; 
    }
}

/*************************************************/

double power8Aux (double x, long n, double r) 
{
    if (n == 0) return r ;
    else {
        if (n%2) return power8Aux (x*x, n/2, r*x) ;
        else     return power8Aux (x*x, n/2,  r ) ;
    }
}

double power8 (double x, long n) 
{
    return power8Aux (x, n, 1.0);
}

/*************************************************/

void power9Aux(double x, long n, double* r){
    if (n == 0) {return;}
    
    else {
        if (n%2) then *r *= x;
        power9Aux(x*x, n/2.0, r);
    }
}
double power9 (double x, long n)
{
    double r = 1.0;
    power9Aux(x, n, &r);
    return r;
}



/*************************************************/

     //   Observation (1+1/10^k)^(10^k) : calcul immédiat

double power10 (double x, long n)
{
    double r = 1.0 ;
    while (n ISNOT 0) 
      { if (n % 2 == 1) then r = r*x ; // no else
        n = n / 2 ; 
        x = x * x ;
       }
    return r ;
}

/*************************************************/

double power (double x, long n, int i)
{ switch (i)  
   {
   case 1 : return power1(x,n) ; break ;
   case 2 : return power2a(x,n) ; break ;  // 2 pour 2a
   case 0 : return power2b(x,n) ; break ; // 0 pour 2b
   case 3 : return power3(x,n) ; break ;
   case 4 : return power4(x,n) ; break ;
   case 5 : return power5(x,n) ; break ;
   case 6 : return power6(x,n) ; break ;
   case 7 : return power7(x,n) ; break ;
   case 8 : return power8(x,n) ; break ;
   case 9 : return power9(x,n) ; break ;
  case 10 : return power10(x,n) ; break ;
     default : return 0 ; 
   }
}

   // remarque : les break sont ici inutiles car les returns font déjà des break

/*************************************************/

    // memes versions que la 10 mais avec des long double, puis des floats
    // but du jeu : observer des variations de precision

   // observation :
   //   imprécision à partir de k~5 (float), k~12 (double), k~14 (long double)
   //   rend 1 à partir de k=8 (float), k=16 (double)
   //   rend 1 non observé sur les long double, maxint atteint avant

long double power11 (long double x, long n)
{
    long double r = 1.0 ;
    while (n ISNOT 0) 
      { if (n % 2 == 1) then r = r*x ; // no else
        n = n / 2 ; 
        x = x * x ;
       }
    return r ;
}

/*************************************************/

float power12 (float x, long n)
{
    float r = 1.0 ;
    while (n ISNOT 0) 
      { if (n % 2 == 1) then r = r*x ; // no else
        n = n / 2 ; 
        x = x * x ;
       }
    return r ;
}




/*************************************************/
/*                                               */
/*             Ackermann                         */
/*                                               */
/*************************************************/

// algo classique
int A1(int m, int n)
{
    if (m==0) {
        return n+1;
    }
    else if (n==0) {
        return A1 (m-1, 1);
    }
    else {
        return A1 (m-1, A1 (m, n-1));
    }
}

int Ackermann1 (int m) { 
    return A1 (m, 0);
}

/*************************************************/
// r iterative, m recursive
int A2 (int m, int n) 
{ 
    if (m == 0) {
        return n+1;
    } 
    else 
    { 
        int r = 1;
        for (int i = 1; i <= n+1; i++) {
            r = A2 (m-1, r);
        }
        return r; 
    } 
}

int Ackermann2 (int m) {
    return A2 (m, 0);
}


/*************************************************/

// recursive n, iterative m
int A3 (int m, int n) {
    while (m > 0) {
        if (n == 0){
            n = 1;
        }
        else{
            n = A3(m, n - 1);
        }
        m -= 1;
    }
    return n + 1;
} 

int Ackermann3 (int m) 
{
    return A3 (m, 0);
}

/*************************************************/

// Full iterative with stacks
int A4 (int m, int n) 
{
    Pile pileAcker = ajoute(m, NULL) ; 

    while ( pileAcker != NULL )
    {
        m = pileAcker->nombre ; depile(&pileAcker);

        if ( m == 0 ) {
            ++n ;
        }
        else if ( n == 0 ) {
            empile (m-1, &pileAcker) ;
            n = 1 ;
        }
        else {
            empile(m - 1, &pileAcker) ;
            empile(m, &pileAcker) ;
            --n ;
        }
    }
    return n ;
}
int Ackermann4 (int m) 
{ 
    return A4 (m, 0) ;
}

/*************************************************/
/*                                               */ 
/*    Complexité en espace Ɵ(2m)                 */
/*                                               */ 
/*************************************************/

// optimization
int A5(int m, int n)
{
    int memoiz_table[2][m+1] ;
    int valeur, next_iter, m_actuelle ;

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j <= m ; ++j) { 
            memoiz_table[i][j] = i ; 
        }
    } 
    memoiz_table[1][m] = -1 ;

    do {
        m_actuelle = 0 ;
        next_iter = true ;
        valeur = memoiz_table[0][0] + 1 ;

        while (next_iter)
        {
            if (memoiz_table[0][m_actuelle] == memoiz_table[1][m_actuelle]) 
                memoiz_table[1][m_actuelle] = valeur ;
            else 
                next_iter = false ;

            memoiz_table[0][m_actuelle] += 1 ;
            m_actuelle += 1;
        }
     } while (memoiz_table[0][m] != n+1); 
    return valeur ;
}
int Ackermann5 (int m) 
{ 
    return A5 (m, 0) ;
}




/*************************************************/
  
int Ackermann (int m, int i)
{ switch (i)  
   {
   case 1 : return Ackermann1 (m) ; // break ;
   case 2 : return Ackermann2 (m) ; // break ;
   case 3 : return Ackermann3 (m) ; // break ;
   case 4 : return Ackermann4 (m) ; // break ;
   case 5 : return Ackermann5 (m) ; // break ;
   default : return 0 ; 
   }
}




/*************************************************/
/*                                               */
/*             Suite (Xn)                        */
/*                                               */
/*************************************************/

// La suite d’entiers (xn )n∈N est définie par récurrence: 
// x0 = 2
// ∀n ≥ 1, xn = x(n−1) + log_2(x(n−1)).
// x0 = 2, x1 = 3, x2 = 4, x3 = 6, x4 = 8, x5 = 11, x6 = 14, x7 = 17, x8 = 21 ...
// Coder la fonction X(n). Donner quatre versions :

int log_2_aux (int n, int cpt){
    if (n==0) then return cpt;
    else return log_2_aux (n/2, cpt+1);
}

int log_2 (int n) {
    return log_2_aux (n, 0);
}

/*************************************************/

// • une version itérative,
int Xn_1 (int n) {
    int res = 2;
    for (int i = 1; i <= n; ++i)
        res += log_2 (res);
    return res;
}


/*************************************************/

// • une version récursive sans utiliser de sous-fonctionnalité,
int Xn_2 (int n) {
    if (n == 0) then return 2;
    else {
        int xn = Xn_2 (n-1);
        return xn + log_2 (xn);
    }
}

/*************************************************/

// • une version récursive terminale avec sous fonction
int Xn_3_aux (int n, int result) {
    if (n <= 0) 
        return result;
    else{
        return Xn_3_aux ((n-1), result + log_2 (result));
        }
}
int Xn_3 (int n) {
    return Xn_3_aux (n, 2);
}

/*************************************************/

// • une version récursive terminale avec sous procédure

void Xn_4_aux (int n, int* res) {
    if (n > 0) {
        *res += log_2 (*res);
        Xn_4_aux ((n-1), res);
    }
}
int Xn_4 (int n) {
    int res = 2;
    Xn_4_aux (n, &res);
    return res;
}

/*************************************************/

int Xn (int n, int i)
{ switch (i)  
   {
   case 1 : return Xn_1 (n) ; // break ;
   case 2 : return Xn_2 (n) ; // break ;
   case 3 : return Xn_3 (n) ; // break ;
   case 4 : return Xn_4 (n) ; // break ;
   default : return 0 ; 
   }
}




/*************************************************/
/*                                               */
/*               main                            */
/*                                               */
/*************************************************/


int main(int argc, char** argv) {

       double x ;
       long double y ;
       float z ;
       
       int cptx ;
  
       long nx ;
       
       int i,j ; 
       
/******************************************************************************/
 
    // mettre "if true" vs "if false" selon que vous voulez les tests ou non
  
/****************  petit test sur le fonctionnement du switch  ************/

if (false) {

 switch (2)  
   {
   case 1 : printf("toc\n") ;  break ;
   case 2 : printf("pata") ; 
   case 3 : printf("pouf\n") ;  break ;
   case 4 : printf("youpla") ; 
   default : printf("boum\n") ; 
   }


 switch (4)  
   {
   case 1 : printf("toc\n") ;  break ;
   case 2 : printf("pata") ; 
   case 3 : printf("pouf\n") ;  break ;
   case 4 : printf("youpla") ; 
   default : printf("boum\n") ; 
   }

   printf("\n") ; 

}
      
      
/************************  taille des nombres  *************************/
      
if (false) {     
       
       printf("ce programme suppose que les long font 8 octets\n") ;
       printf("S'ils n'en font que 4, il faudra utiliser long long\n") ;

       printf("short : %d octets\n", (int) sizeof(short));
       printf("int : %d octets\n", (int) sizeof(int));
       printf("long : %d octets\n", (int) sizeof(long));
       printf("long long : %d octets\n", (int) sizeof(long long));
       printf("float : %d octets\n", (int) sizeof(float));
       printf("double : %d octets\n", (int) sizeof(double));
       printf("long double : %d octets\n", (int) sizeof(long double));
       printf("\n") ;
 
       x = 1.0 ;
       cptx = 0 ;
       while ( (1.0 + x) - 1.0 != 0 )
          { x = x/10 ; cptx ++ ; }
       printf("1+1/10^c devient 1 a partir de c=%d pour les double\n", cptx) ; 
       printf("et 1+1/10^%d vaut en fait 1+%lf\n", cptx-1, (1.0 + 10*x) - 1.0) ;
        
       printf("ce programme suppose que les doubles font au moins 8 octets\n") ;
       printf("et que ((double) 1+1/10^-15) n'est pas 1 \n") ;       
       printf("Si ce n'est pas le cas, utiliser des long double \n") ;
       
       printf("\n") ;      
}

/************************  factorielle  *************************/

if (false) {

     printf("%ld \n",fact(5)) ;
     printf("%ld \n",fact2(5)) ;
     printf("\n") ;
}


/******************    Autour de e      *******************************/

  // d'après google,
  // e = 2,7182818284 5904523536 0287471352 6624977572 4709369995 
  //       9574966967 6277240766 3035354759 4571382178 5251664274

if (false) {  
       

        printf(" e1 = %.20f \n", Efloat()) ;
        printf(" e3 = %.30lf \n", Edouble()) ; 
        printf(" e3 = %.40Lf \n", Elongdouble()) ; 
        
}

if (false) {  
            afficheYfloat(30) ;
            afficheYdouble(30) ;
            afficheYlongdouble(30) ;
}
        
/******************    power     *******************************/

if (false) {  

        //   test simplet, vérifie le B.A. BA, test de 2^10 pour toutes les versions
        
        for(i=0 ; i<=10 ; i++)
        printf("Power %d dit que power(2,10) vaut %.0lf \n", i, power(2,10,i) ) ;
        
        printf("\n") ;
      
}

        
if (false) {  

        i=10 ;  // numéro de la version que l'on teste

        // test de la résistance de power version i, calcul de (1+1/N)^N
        // pour des N puissances de 10 de plus en plus grosses
     
        x = 1.0 ;
        nx = 1 ;
        for(j=0 ; j<=15 ; j++)
        {
        printf("power %d ((1+10^-%2d)^(10^%2d)) rend %.12lf\n", i, j, j, power(1+x,nx,i)) ;
        x = x/10 ;
        nx = nx * 10 ;
        }
        printf("\n") ;
       
}
     
if (false) {

        // tests sur la précision que l'on obtient suivant que
        // l'on utilise float, double, long double

        printf("VERSION 12 avec float \n") ;
        z = 1.0 ;
        nx = 1 ;
        for(j=0 ; j<=18 ; j++)
        {
        printf("power((1+10^-%2d)^(10^%2d)) rend %.12f\n", j, j, power12(1+z,nx)) ;
        z = z/10 ;
        nx = nx * 10 ;
        }
        printf("\n") ;


        printf("VERSION 10 avec double \n") ;
        x = 1.0 ;
        nx = 1 ;
        for(j=0 ; j<=18 ; j++)
        {
        printf("power((1+10^-%2d)^(10^%2d)) rend %.12lf\n", j, j, power10(1+x,nx)) ;
        x = x/10 ;
        nx = nx * 10 ;
        }
        printf("\n") ;


        printf("VERSION 11 avec long double \n") ;
        y = 1.0 ;
        nx = 1 ;
        for(j=0 ; j<=18 ; j++)
        {
        printf("power((1+10^-%2d)^(10^%2d)) rend %.12LF\n", j, j, power11(1+y,nx)) ;
        y = y/10 ;
        nx = nx * 10 ;
        }
        printf("\n") ;



}

/******************    Ackermann    *******************************/
for(j=0 ; j<=4 ; j++){  // test de A(j,0) pour j de 0 à 4
    printf("Ack%d(%d, 0) = %d \n", i, j, Ackermann(j, 5)) ;
}
printf("fin");       

if (false) { 
 
    for(i=1 ; i<=5 ; i++){  // numéro de version
        for(j=0 ; j<=5 ; j++){  // test de A(j,0) pour j de 0 à 4
            printf("Ack%d(%d, 0) = %d \n", i, j, Ackermann(j, i)) ;
        }
        printf("fin");
    }
    printf("FIN");
        

}

/*******************       Xn       *******************************/

if (false) { 
 
        for(i=1 ; i<=4 ; ++i)  // numéro de version
        
        for(j=199 ; j<=201 ; ++j)  // test de A(j,0) pour j de 0 à 5
        
        printf("Xn_%d( %d ) = %d \n", i, j, Xn(j, i)) ;
}

/***********************************************************************/

    return 0;
}






