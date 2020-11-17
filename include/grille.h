#ifndef __GRILLE_H
#define __GRILLE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/**
 * \file grille.h
 * \brief [header] gère la grille et les cellules
 * \author Aki Schmatzler
 * \version 4.0
 */
 

/**
 * \struct grille 
 * \brief nombre de lignes, nombre de colonnes, tableau de tableau de cellules
 */
typedef struct {int nbl; int nbc; int** cellules;} grille;

/**
 * \brief alloue une grille de taille l*c, et initialise toutes les cellules à mortes
 * \param l nombre de lignes 
 * \param j nombre de colonnes 
 * \param g pointeur sur grille
 */
void alloue_grille (int l, int c, grille* g);

/**
 * \brief libère une grille 
 * \param g pointeur sur une grille
 */
void libere_grille (grille* g);

/**
 * \brief Alloue et initialise la grille g à partir d'un fichier
 * \param filename pointeur sur nom du fichier qui contient la grille
 * \param g pointeur sur grille
 */ 
void init_grille_from_file (char * filename, grille* g);

/**
 * \brief rend vivante la cellule de coordonnées (i,j) de la grille g
 * \param i abscisse de la cellule (entier)
 * \param j ordonnée de la cellule (entier)
 * \param g grille
 */
static inline void set_vivante(int i, int j, grille g){g.cellules[i][j] = 1;}

/**
 * \brief rend morte la cellule de coordonnées (i,j) de la grille g
 * \param i abscisse de la cellule
 * \param j ordonnée de la cellule
 * \param g grille
 */
static inline void set_morte(int i, int j, grille g){g.cellules[i][j] = 0;}


/**
 * \brief rend plus que morte (ne peut jamais vivre) la cellule de coordonnées (i,j) de la grille g
 * \param i abscisse de la cellule
 * \param j ordonnée de la cellule
 * \param g grille
 */
static inline void set_plus_que_morte(int i, int j, grille g){g.cellules[i][j] = -1;}


/**
 * \brief vérifie si la cellule de coordonnées (i,j) de la grille g est vivante
 * \param i abscisse de la cellule
 * \param j ordonnée de la cellule
 * \param g grille
 * \return an integer (for true or false)
 */
static inline int est_vivante(int i, int j, grille g){return ((1<=g.cellules[i][j]) && (g.cellules[i][j]<=9));}

/**
 * \brief recopie gs dans gd (sans allocation)
 * \param gs grille
 * \param gd grille
 */
void copie_grille (grille gs, grille gd);

#endif
