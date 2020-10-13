#include "io.h"

/**
 * \file io.c
 * \brief se charge de l'affichage (shell)
 * \author Aki Schmatzler
 * \version 1.0
 */

void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

void affiche_ligne (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i) 
		if (ligne[i] == 0 ) printf ("|   "); else printf ("| O ");
	printf("|\n");
	return;
}

void affiche_grille (grille g){
	int i, l=g.nbl, c=g.nbc;
	printf("\n");
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}	
	printf("\n"); 
	return;
}

void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl*2 + 5); 
}

void debut_jeu(grille *g, grille *gc){
	char c = getchar(); 
	while (c != 'q') // touche 'q' pour quitter
	{ 
		switch (c) {
			case '\n' : 
			{ // touche "entree" pour évoluer
				evolue(g,gc);
				efface_grille(*g);
				affiche_grille(*g);
				break;
			}
			case 'n': //demande pour changer de grille
			{
				libere_grille(g);
				libere_grille(gc);
				char numGrid[10];
				char fileGrid[100] = "grilles/grille";
				printf("Numero de la nouvelle grille a charger: ");
				scanf("%s",numGrid);
				strcat(fileGrid, numGrid); //Permet de rajouter a une chaine existante le contenu d'une seconde
				strcat(fileGrid, ".txt");
				init_grille_from_file(fileGrid, g);
				alloue_grille(g->nbl, g->nbc, gc);
				affiche_grille(*g);
				printf("\n");
				break;
			}
			default : 
			{ // touche non traitée
				printf("\n\e[1A");
				break;
			}
		}
		c = getchar(); 
	}
	return;	
}
