#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include "grille.h"
#include "jeu.h"

/**
 * \file io.h
 * \brief se charge de l'affichage (shell)
 * \author Aki Schmatzler
 * \version 3.0
 */

/**
 * \brief affichage d'un trait horizontal
 * \param c definit la taille du trait
 */
void affiche_trait (int c);

// affichage d'une ligne de la grille
/**
 * \brief affichage d'une ligne de la grille
 * \param c taille de la ligne
 * \param ligne pointeur sur tableau d'entier qui indique si les differentes cellules de la ligne sont vivantes ou mortes
 */
void affiche_ligne (int c, int* ligne);

/**
 * \brief affiche une grille
 * \param g grille
 */
void affiche_grille (grille g);

/**
 * \brief efface une grille
 * \param g grille
 */
void efface_grille (grille g);

/**
 * \brief debute le jeu
 * \param g pointeur sur grille
 * \param gc pointeur sur grille
 */
void debut_jeu(grille *g, grille *gc);

#endif
