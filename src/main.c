#include <stdio.h>

#include "grille.h"
#include "io.h"
#include "jeu.h"
#include "graphic.h"

/**
 * \file mainc.c
 * \brief lance l'execution en mode graphique ou shell
 * \author Aki Schmatzler
 * \version 4.0
 */

int main (int argc, char ** argv){
	if (argc != 2 )
	{
		printf("usage : main <fichier grille>");
		return 1;
	}

	grille g, gc;
	system("clear");
	init_grille_from_file(argv[1],&g);
	alloue_grille (g.nbl, g.nbc, &gc);


	#ifdef TEXTE
	
	affiche_grille(g);
	debut_jeu(&g, &gc);
	
	#else

	debut_jeu_cairo(&g, &gc);

	#endif 

	libere_grille(&g);
	libere_grille(&gc);

	return 0;
}
