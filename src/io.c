#include "io.h"
#include <string.h>
int tps_evol=1; //variable donnant la "génération" à laquelle on est
int voisinage = 0;

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
	printf("Voisinage: %d", voisinage);
	printf("	temps d'évolution: %d",tps_evol);
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
	system("clear"); 
}

void debut_jeu(grille *g, grille *gc){
	int (*compte_voisins_vivants) (int, int, grille) = compte_voisins_vivants_c;
	char c = getchar(); 
	while (c != 'q') // touche 'q' pour quitter
	{ 
		switch (c) {
			case '\n' : 
			{ // touche "entree" pour évoluer
				evolue(g,gc, compte_voisins_vivants);
				efface_grille(*g);
				tps_evol++;
				affiche_grille(*g);
				break;
			}
			case 'n': //demande pour changer de grille
			{
				libere_grille(g);
				libere_grille(gc);
				char numGrille[5];
				char fileGrille[30] = "grilles/grille";
				printf("Numero de la nouvelle grille: ");
				scanf("%s",numGrille);
				strcat(fileGrille, numGrille); //Permet de rajouter a une chaine existante le contenu d'une seconde
				strcat(fileGrille, ".txt");
				init_grille_from_file(fileGrille, g);
				alloue_grille(g->nbl, g->nbc, gc);
				tps_evol=0;
				affiche_grille(*g);
				printf("\n");
				break;
			}
			case 'c': //demande pour passer de cyclique à non cyclique et vice-versa
			{
				if(voisinage == 0) {
					compte_voisins_vivants= compte_voisins_vivants_nc;
					voisinage = 1;
				}
				else{
					compte_voisins_vivants = compte_voisins_vivants_c;
					voisinage = 0;
				}
				break;
					
			}
			default : 
			{ // touche non traitée
				printf("\n\e[1A");
				break;
			}
		}
		c = getchar(); 
		system("clear");
	}
	return;	
}
