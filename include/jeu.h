#ifndef __JEU_H
#define __JEU_H

#include "grille.h"

/**
 * \file jeu.h
 * \brief evolution de la partie
 * \author Aki Schmatzler
 * \version 1.0
 */


/**
 * \brief modulo modifié pour traiter correctement les bords i=0 et j=0 dans le calcul des voisins avec bords cycliques
 * \param i  
 * \param m
 * \return entier, modulo i%m
 */
static inline int modulo(int i, int m) {return (i+m)%m;}

/**
 * \brief compte le nombre de voisins vivants de la cellule(i,j). Les bords sont cycliques
 * \param i abscisse de la cellule
 * \param j ordonnée de la cellule
 * \param g grille
 * \return entier: nombre de voisins avec voisinage cyclique 
 */
int compte_voisins_vivants_c (int i, int j, grille g);

/**
 * \brief compte le nombre de voisins vivants de la cellule(i,j). Les bords sont non cycliques
 * \param i abscisse de la cellule
 * \param j ordonnée de la cellule
 * \param g grille
 * \return entier: nombre de voisins avec voisinage non cyclique
 */
int compte_voisins_vivants_nc (int i, int j, grille g);

/**
 * \brief faire évoluer la grille g d'un pas de temps
 * \param g pointeur sur la grille
 * \param gc pointeur sur grille vide
 * \param *compte_voisins_vivants pointeur sur une fonction qui prend comme args 2 entiers et une grille et qui renvoit un entier
 */
void evolue (grille *g, grille *gc, int (*compte_voisins_vivants)(int, int, grille));

#endif
