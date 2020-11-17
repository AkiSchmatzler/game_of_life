#include "jeu.h"

/**
 * \file jeu.c
 * \brief evolution de la partie
 * \author Aki Schmatzler
 * \version 4.0
 */

int compte_voisins_vivants_c (int i, int j, grille g){
	//nombre voisins voisinage cyclique
	int v = 0, l=g.nbl, c = g.nbc;

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

int compte_voisins_vivants_nc (int i, int j, grille g){
	//nombre voisins voisinage non cyclique
	int v = 0, l=g.nbl, c = g.nbc, plus_i=i+1, moins_i=i-1, plus_j=j+1, moins_j=j-1;
	
	v+= (moins_i>=0 && moins_j>=0)? est_vivante(i-1, j-1, g) : 0;
	v+= (moins_i>=0) ? est_vivante(i-1, j, g) : 0;
	v+= (moins_i>=0 && plus_j<c) ? est_vivante(i-1, j+1, g) : 0;
	v+= (moins_j>=0) ? est_vivante(i, j-1, g) : 0;
	v+= (plus_j<c) ? est_vivante(i, j+1, g) : 0;
	v+= (plus_i<l && moins_j>=0) ? est_vivante(i+1, j-1, g) : 0;
	v+= (plus_i<l) ? est_vivante(i+1, j, g) : 0;
	v+= (plus_i<l && plus_j<c) ? est_vivante(i+1, j+1, g) : 0;
	
	return v;
}
	
	





void evolue (grille *g, grille *gc, int (*compte_voisins_vivants)(int, int, grille), int vieillissement){
	copie_grille (*g,*gc); // copie temporaire de la grille

	int i,j,l=g->nbl, c = g->nbc,v;

	if(vieillissement == 0){
		for (i=0; i<l; i++)
		{
			for (j=0; j<c; ++j)
			{
				v = compte_voisins_vivants(i, j, *gc);
				if (est_vivante(i,j,*g)) 
				{ // evolution d'une cellule vivante
					if ( v!=2 && v!= 3 ) set_morte(i,j,*g);
					else set_vivante(i,j,*g);
				}
				else 
				{ // evolution d'une cellule morte
					if ( v==3 && (g->cellules[i][j]!=-1)) set_vivante(i,j,*g);
				}
			}
		}
	}

	else{
		for (i=0; i<l; i++)
		{
			for (j=0; j<c; ++j)
			{
				v = compte_voisins_vivants(i, j, *gc);
				if (est_vivante(i,j,*g)) 
				{ // evolution d'une cellule vivante avec incrémentation
					
					g->cellules[i][j]+=1;

					if ((v!=2 && v!= 3) || (g->cellules[i][j]>9)) set_morte(i,j,*g);
				}
				else 
				{ // evolution d'une cellule morte
					if ( v==3 && (g->cellules[i][j]!=-1)) set_vivante(i,j,*g);
				}
			}
		}
	}
	return;
}
