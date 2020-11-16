#ifndef __GRAPHIC_H
#define __GRAPHIC_H

#include <stdio.h>
#include "grille.h"
#include "jeu.h"
#include "io.h"
#include <cairo/cairo.h>
#include <cairo/cairo-xlib.h>


#define SIZEX 550 //largeur de la fenetre créé
#define SIZEY 450 //hauteur de la fenetre créé
#define CASE 30   //taille d'une case 


int debut_jeu_cairo(grille *g, grille *gc);

void init_grille_cairo(cairo_surface_t *surface, grille g);

void affiche_grille_cairo(cairo_surface_t *surface, grille g);

void switch_grid(cairo_surface_t *surface);



#endif