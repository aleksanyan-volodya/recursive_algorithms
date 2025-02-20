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
/*           structure des quadtree              */
/*                                               */
/*************************************************/

typedef struct bloc_image
{ 
	bool quatre ;
	struct bloc_image *hg, *hd, *bg, *bd ;
} bloc_image ;
typedef bloc_image *image ;

/*************************************************/
/*                                               */
/*           structure des Pile                  */
/*                                               */
/*************************************************/


typedef struct Bloc {
    image img;
    struct Bloc *suivant;
} Bloc;
typedef Bloc *Pile ;


/************************************************/
/*                                              */
/*           Fonctions et Procedures            */
/*                                              */
/************************************************/

Pile ajoute(image x, Pile Pl)
{
    Pile tmp = (Pile) malloc(sizeof(Bloc)) ;
    tmp->img = x ;
    tmp->suivant = Pl ;
    return tmp ;
}

void empile(image x, Pile *Pl)
{
    *Pl = ajoute(x,*Pl) ; 
}

void depile(Pile *Pl) {
    Pile tmp = *Pl ;
    *Pl = (*Pl)->suivant ;
    free(tmp) ;
}

/************************************************/
/*                                              */
/*         Blanc / Noir / Compose				*/
/*                                              */
/************************************************/
// OK

image Blanc()
{
	image img = (image)malloc(sizeof(bloc_image)) ; 
    img->quatre = false ;
    img->hg = NULL ;
    img->hd = NULL ;
    img->bg = NULL ;
    img->hd = NULL ;
    return img ;
}

/************************************************/

image Noir()
{
	return NULL ;
}

/************************************************/


image Compose(image i0, image i1, image i2, image i3)
{
	image img = (image)malloc(sizeof(bloc_image)); 
    img->quatre = true ;
    img->hg = i0 ;
    img->hd = i1 ;
    img->bg = i2 ;
    img->bd = i3 ;
    return img;
}


/************************************************/
/*                                              */
/*       unit_of_image                          */
/*                                              */
/************************************************/
// OK

void Affichage(image Image)
{
	if (Image==NULL)
	{
		printf("X") ;
		return ;
	}
	if (!Image->quatre) 
	{
		printf("o") ;
		return ;
	}
	else {
		Affichage(Image->hg) ;
		Affichage(Image->hd) ;
		Affichage(Image->bg) ;
		Affichage(Image->bd) ;
		printf("*");
	}
	// printf("\n") ;
}

/************************************************/
/*                                              */
/*         AffichageProfondeur                  */
/*                                              */
/************************************************/
// OK

void Bis(image img, int p){
	if (img == NULL)
	{
		printf("X%d ", p);
		return ;
	}
	if (! img->quatre)
	{
		printf("o%d ", p);
		return ;
	}
	else {
		Bis(img->hg,p+1);
		Bis(img->hd,p+1);
		Bis(img->bg,p+1);
		Bis(img->bd,p+1);
		printf("*%d ", p);
	}
	printf("\n") ;

}

void AffichageProfondeur(image Image)
{
	Bis(Image, 0);
}


/************************************************/
/*                                              */
/*         image_of_unit                        */
/*                                              */
/************************************************/

image Lecture()
{
    Pile P = NULL;

    image i0, i1, i2, i3 ;
	char ch;

	ch = getchar() ;
	 
	while (ch != '!')
	{

		if (ch == 'X') then
			empile(Noir(), &P) ;

		else if (ch == 'o') then
			empile(Blanc(), &P) ;

		else if (ch == '*') 
		{
			i3 = P->img ; depile(&P) ;
			i2 = P->img ; depile(&P) ;
			i1 = P->img ; depile(&P) ;
			i0 = P->img ; depile(&P) ;

			empile(Compose(i0, i1, i2, i3), &P) ;
		}
		ch = getchar() ;

	} 

	i0 = P->img ; depile(&P) ;
	return  i0 ;
}


/************************************************/
/*                                              */
/*     Test si	Blanche                          */
/*     ________ Noire                           */
/*                                              */
/************************************************/
// OK

bool EstNoire(image Image) 
{
	if (Image == NULL) then
		return true ;

	else if(!Image->quatre) then
		return false;

	else 
		return EstNoire(Image->hg) && EstNoire(Image->hd) && 
			   EstNoire(Image->bg) && EstNoire(Image->bd) ;
}

/************************************************/


bool EstBlanche(image Image) 
{
	if (Image == NULL) then 
		return false ;

	else if (!Image->quatre) then
		return true;

	else 
		return EstBlanche(Image->hg) && EstBlanche(Image->hd) && 
			   EstBlanche(Image->bg) && EstBlanche(Image->bd) ;
}


/************************************************/
/*                                              */
/*        Ratio	de noir                			*/
/*                                              */
/************************************************/

float Aire(image Image)
{
	if (Image == NULL) then
		return 1.0 ;

	else if (!Image->quatre) then
		return 0.0 ;

	else 
		return (Aire(Image->hg) 
				+ Aire(Image->hd) 
				+ Aire(Image->bg) 
				+ Aire(Image->bd)
				) * 0.25 ;
}

/************************************************/
/*                                              */
/*     (Base-1) * (Hauteur-1) / 2				*/
/*                                              */
/************************************************/

image TriangleBD(int p)
{
	if (p == 0) then
		return Blanc() ;
	
	else
	{
		image hdETbg = TriangleBD(p-1) ;
		return Compose (Blanc(), hdETbg, hdETbg, Noir()) ;
	}
}

/************************************************/
/*                                              */
/*      Arrondit l'image (Noir si égalité)      */
/*                                              */
/************************************************/

void freeImage(image *Image)
{
	if (*Image != NULL)
	{
		freeImage(&((*Image)->hg)) ;
		freeImage(&((*Image)->hd)) ;
		freeImage(&((*Image)->bg)) ;
		freeImage(&((*Image)->bd)) ;
		free(*Image) ;
		*Image = NULL;
	}
}

void Arrondit(image *Image, int p)
{
	if (p <= 0) 
	{
		if (Aire(*Image) >= 0.5)
		{
			freeImage(Image) ;
			*Image = Noir() ;
		}
		else
		{
			freeImage(Image) ;
			*Image = Blanc();
		}
	}
	else if ((*Image != NULL) && (*Image)->quatre) 
	{
		Arrondit(&((*Image)->hg), p-1) ;
		Arrondit(&((*Image)->hd), p-1) ;
		Arrondit(&((*Image)->bg), p-1) ;
		Arrondit(&((*Image)->bd), p-1) ;
	}
}


/************************************************/
/*                                              */
/*      test si C'est le même dessin            */
/*                                              */
/************************************************/

bool MemeDessin(image image1, image image2)
{
	if (image1 == NULL) then
		return EstNoire(image2) ;

	if (image2 == NULL) then
		return EstNoire(image1) ;

	if (! image1->quatre) then
		return EstBlanche(image2) ;

	if (! image2->quatre) then
		return EstBlanche(image1) ;

	return MemeDessin(image1->hg, image2->hg)
		&& MemeDessin(image1->hd, image2->hd)
		&& MemeDessin(image1->bg, image2->bg)
		&& MemeDessin(image1->bd, image2->bd);
}


/************************************************/
/*                                              */
/*     intersection d'images			        */
/*								                */
/*                                              */
/************************************************/

void echanger(image *image1, image *image2)
{
	image tmp = *image1 ;
	*image1 = *image2 ;
	*image2 = tmp ;
}

void InterUnion(image *image1, image *image2)
{
	// premier image est noire
	if (*image1 == NULL) then
		echanger(image1, image2) ;

	// deuxieme image est blanche
	else if (*image2 != NULL)
	{
		if (!(*image2)->quatre) then
			echanger(image1, image2) ;
	
		else if ((*image1)->quatre)
		{
			InterUnion(&((*image1)->hg), &((*image2)->hg) ) ;
			InterUnion(&((*image1)->hd), &((*image2)->hd) ) ;
			InterUnion(&((*image1)->bg), &((*image2)->bg) ) ;
			InterUnion(&((*image1)->bd), &((*image2)->bd) ) ;
		}
	}
}


/************************************************/
/*                                              */
/*      compter nb de damier					*/
/*                                              */
/************************************************/


int CompteDamiers(image Image)
{
	if (Image == NULL || !Image->quatre) then
		return 0;

	else if ((Image->hd == NULL ) && 
			(Image->bg == NULL ) && 
			(Image->hg != NULL && !Image->hg->quatre) && 
			(Image->bd != NULL && !Image->bd->quatre)) then
		return 1;
	else 
	{
		int hg = CompteDamiers(Image->hg) ;
		int hd = CompteDamiers(Image->hd) ;
		int bg = CompteDamiers(Image->bg) ;
		int bd = CompteDamiers(Image->bd) ;

		if (hg && hg==hd && hg==bg && hg==bd) then
			return hg+hd+bg+bd+1;

		else
			return hg+hd+bg+bd;
	}
}

/************************************************/
/*                                              */
/*      DAG <-> Tree                            */
/*                                              */
/************************************************/

void Compresse(image* Image)
{
	return;
}

/************************************************/

// On cree une table de hachage ou on stock les adresses des noeuds.
// On cree une fonction memoryCopy qui renvoie une copie de l'arbre passé en argument.
// pour chaque noeud, si l'adresse existe dans hashtable on fais une copie et on colle à l'arbre

void Dilate(image* Image)
{
	return;
}

/************************************************/
/*                                              */
/*               main                           */
/*                                              */
/************************************************/


int main(int argc, char** argv)
{
	printf("compilé && exectuté\n");
	image img1 = Lecture() ;
	// image img2 = Lecture() ;
	printf("\n\n\n") ;
	Affichage(img1) ;
	printf("\n") ;
	// Affichage(img2) ;
	// if (MemeDessin(img1, img2)) then printf("meme dessin"); else printf("oh bah non") ;
	Arrondit(&img1, 2);
	// printf("\n%d", CompteDamiers(img1)) ;
	Affichage(img1) ;
	//printf("\n") ;
	//Affichage(img2) ;

	
	return 0;
}