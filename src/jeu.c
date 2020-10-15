#include "jeu.h"

/**
 * \file jeu.c
 * \brief evolution de la partie
 * \author Aki Schmatzler
 * \version 1.0
 */

int compte_voisins_vivants (int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;
/*	v+= est_vivante(i-1, j-1, g);
	v+= est_vivante(i-1, j, g);
	v+= est_vivante(i-1, j+1, g);
	v+= est_vivante( i, j-1, g);
	v+= est_vivante(i, j+1, g);
	v+= est_vivante(i+1, j-1, g);
	v+= est_vivante(i+1, j, g);
	v+= est_vivante(i+1, j+1, g);*/
	
	v+= est_vivante(modulo(i-1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j+1,c),g);
		

	return v; 
}

/*int compte_voisins_vivants_nc (int i, int j, grille g){
	//cyclique
	int v=0, l=g.nbl, c=g.nbc;
	if (i!=0){
		v+= est_vivante(i-1, j-1, g);
		v+= est_vivante(i-1, j, g);
		v+= est_vivante(i-1, j+1, g);
		v+= est_vivante( i, j-1, g);
		v+= est_vivante(i, j+1, g);
		v+= est_vivante(i+1, j-1, g);
		v+= est_vivante(i+1, j, g);
		v+= est_vivante(i+1, j+1, g);*/
	
	





void evolue (grille *g, grille *gc){
	copie_grille (*g,*gc); // copie temporaire de la grille
	int i,j,l=g->nbl, c = g->nbc,v;
	for (i=0; i<l; i++)
	{
		for (j=0; j<c; ++j)
		{
			v = compte_voisins_vivants (i, j, *gc);
			if (est_vivante(i,j,*g)) 
			{ // evolution d'une cellule vivante
				if ( v!=2 && v!= 3 ) set_morte(i,j,*g);
			}
			else 
			{ // evolution d'une cellule morte
				if ( v==3 ) set_vivante(i,j,*g);
			}
		}
	}
	return;
}
