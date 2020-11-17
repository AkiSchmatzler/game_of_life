#ifndef __GRAPHIC_H
#define __GRAPHIC_H

#include <stdio.h>
#include "grille.h"
#include "jeu.h"
#include "io.h"
#include <cairo/cairo.h>
#include <cairo/cairo-xlib.h>

/**
 * \file grpahic.h
 * \brief se charge de l'affichage graphique
 * \author Aki Schmatzler
 * \version 4.0
 */

#define SIZEX 550 //largeur de la fenetre créé
#define SIZEY 450 //hauteur de la fenetre créé
#define CASE 30   //taille d'une case 



/**
 *\brief lance l'execution de l'affichage prahique(similaire a debut_jeu)
 *\param g pointeur sur grille
 *\param gc pointeur sur grille
 */
int debut_jeu_cairo(grille *g, grille *gc);


/**
 *\brief affiche la grille vide et les informations sur l'état de la grille
 *\param surface pointeur sur cairo_surface_t 
 *\param g grille
 */
void init_grille_cairo(cairo_surface_t *surface, grille g);


/**
 *\brief affiche les numéros dans la grille 
 *\param surface pointeur sur cairo_surface_t 
 *\param g grille
 */
void affiche_grille_cairo(cairo_surface_t *surface, grille g);


/**
 *\brief affichage de l'écran d'attente quand l(utilisateur va choisir une nouvelle grille
 *\param surface pointeur sur cairo_surface_t 
 */
void switch_grid(cairo_surface_t *surface);



#endif