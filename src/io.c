#include "io.h"

#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int tps_evol=1; //variable donnant la "génération" à laquelle on est
int voisinage = 0; //voisinage cyclique ou non cyclique (0 correspond au voisinage cyclique)
int vieillissement = 0; //vieillissement ou non (0 correspond à pas de vieillissement)
int noBug = 0;  //permet d'assurer le bon fonctionnement du vieillissement

/**
 * \file io.c
 * \brief se charge de l'affichage (shell)
 * \author Aki Schmatzler
 * \version 3.0
 */

void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

void affiche_ligne (int c, int* ligne){
	if(vieillissement == 0){
		int i;
		for (i=0; i<c; ++i) 
			if (ligne[i] == 0 ) printf ("|   "); else if (ligne[i] == -1) printf ("|\e[31m X \e[0m"); else printf("| O ");
		printf("|\n");
	}
	
	//affichage vieillissement 
	else{
		int i;
		for (i=0; i<c; ++i) 
			if (ligne[i] == 0 ) printf ("|   "); else if (ligne[i] == -1) printf ("|\e[31m X \e[0m"); else printf ("| %d ", ligne[i]);
		printf("|\n");
	}
	return;
}

void affiche_grille (grille g){
	
	int i, l=g.nbl, c=g.nbc;
	printf("Voisinage: %d", voisinage);
	printf("	Vieillissement: %d", vieillissement);
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
	char c = getchar();
	int (*compte_voisins_vivants) (int, int, grille) = compte_voisins_vivants_c; 
	while (c != 'q') // touche 'q' pour quitter
	{ 
		switch (c) {
			case '\n' : 
			{ // touche "entree" pour évoluer
				if(noBug == 0) {
					evolue(g,gc, compte_voisins_vivants, vieillissement);
					tps_evol++;
				}
				
				efface_grille(*g);
				affiche_grille(*g);

				noBug = 0;
			
				break;
			}
			case 'n': //demande pour changer de grille
			{
				libere_grille(g);
				libere_grille(gc);
				char numGrille[5];
				char fileGrille[30] = "grilles/grille";
				system("clear");
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
			case 'v': //activation et désactivation du vieilissement
			{
				if (vieillissement == 0) {
					vieillissement = 1;
					noBug = 1;
				}
				else{
					vieillissement = 0;
					noBug = 1;
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



