#include "grille.h"
#include "io.h"
#include "jeu.h"
#define N 3 //nombre de case plus que mortes


/**
 * \file grille.c
 * \brief gère la grille et les cellules
 * \author Aki Schmatzler
 * \version 5.0
 */
 extern int vieillissement;
 extern int compte_voisins_vivants;
 extern int voisinage;
 extern int delais;


void alloue_grille(int l, int c, grille* g){
	int i, j;

	g->nbl = l;
	g->nbc = c;

	g->cellules = (int**) malloc(l*sizeof(int*));

	for (i = 0; i < l; i++) {

		g->cellules[i] = (int*) malloc(c*sizeof(int));
		for (j = 0; j < c; j++) {
			set_morte(i, j, *g);
		}
	}
}


void libere_grille (grille* g){
	int i;

	for (i=0; i < g->nbl; i++) {
		free(g->cellules[i]);
	}

	free(g->cellules);
}


void init_grille_from_file (char * filename, grille* g){
	FILE * pfile = NULL;
	pfile = fopen(filename, "r");
	assert (pfile != NULL);
	
	int i,j,n,l,c,vivantes=0;
	int mortes = 0;
	
	fscanf(pfile, "%d", & l);
	fscanf(pfile, "%d", & c);
	
	alloue_grille(l,c,g);
	
	fscanf(pfile, "%d", & vivantes);
	for (n=0; n< vivantes; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_vivante(i,j,*g);
		}

	fscanf(pfile, "%d", & mortes);
	for (n=0; n< mortes; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_plus_que_morte(i,j,*g);
		}

	
	fclose (pfile);
	return;
}




void copie_grille (grille gs, grille gd){
	int i, j;

	for (i=0; i<gs.nbl; ++i){
		for (j=0; j<gs.nbc; ++j){
		gd.cellules[i][j] = gs.cellules[i][j];
		}
	}
	return;	
}



int egalite_grilles(grille g, grille g2){
//precondition = les deux grilles ont la meme taille !!!
	int l = g.nbl;
	int c = g.nbc;

	for(int i = 0; i<l ; ++i){
		for(int j = 0; j<c; ++j){

			if(g.cellules[i][j] != g2.cellules[i][j])return 0;
		}
	}
	return 1;
}


int grille_vide(grille g){
	int l = g.nbl;
	int c = g.nbc;

	for(int i = 0; i<l ; ++i){
		for(int j = 0; j<c; ++j){

			if((g.cellules[i][j] != 0) && (g.cellules[i][j] != -1))return 0;

		}
	}
	return 1;
}



int check_oscillation(grille g){

	grille g1,g2,g3;
	int pas_oscillation=0;

	alloue_grille (g.nbl, g.nbc, &g1); 
	alloue_grille (g.nbl, g.nbc, &g2);
	alloue_grille (g.nbl, g.nbc, &g3);

	copie_grille(g,g1);	//copie temporaire
	copie_grille(g,g2);	//copie temporaire

	int (*compte_voisins_vivants) (int, int, grille) = compte_voisins_vivants_c;
	if(voisinage)compte_voisins_vivants = compte_voisins_vivants_nc;
	evolue(&g2, &g1, compte_voisins_vivants, vieillissement);

	for(int k = 0; k<ITERATION_0_D; k++){

		for(int i = 1; i<ITERATION_O_P; i++){

			
			if(egalite_grilles(g1, g2) == 1){

				pas_oscillation = (grille_vide(g1))? 0 : i;//si la grille est vide elle n'oscille pas

				libere_grille(&g2);//free
				libere_grille(&g1);
				libere_grille(&g3);

				delais = k;
				return pas_oscillation;
			}

			copie_grille(g2,g3);
			evolue(&g2, &g3, compte_voisins_vivants, vieillissement);

		}	
		copie_grille(g1,g3);
		evolue(&g1, &g3, compte_voisins_vivants, vieillissement);

	}
	
	libere_grille(&g2);
	libere_grille(&g1);
	libere_grille(&g3);
	return -1;
}
