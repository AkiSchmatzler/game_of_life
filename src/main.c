#include <stdio.h>

#include "grille.h"
#include "io.h"
#include "jeu.h"

/**
 * \file jeu.h
 * \brief evolution de la partie
 * \author Aki Schmatzler
 * \version 3.0
 */

int main (int argc, char ** argv){
	system("clear");
	if (argc != 2 )
	{
		printf("usage : main <fichier grille>");
		return 1;
	}

	grille g, gc;
	init_grille_from_file(argv[1],&g);
	alloue_grille (g.nbl, g.nbc, &gc);
	affiche_grille(g);

	debut_jeu(&g, &gc);

	libere_grille(&g);
	libere_grille(&gc);
	return 0;
}
