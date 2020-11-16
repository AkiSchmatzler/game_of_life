#include "graphic.h"
#include <string.h>
#include <stdio.h>




extern int tps_evol; //variable donnant la "génération" à laquelle on est (venant de io.c)
extern int voisinage; //voisinage cyclique ou non cyclique (0 correspond au voisinage cyclique) (venant de io.c)
extern int vieillissement; //vieillissement ou non (0 correspond à pas de vieillissement) (venant de io.c)
extern int noBug;  //permet d'assurer le bon fonctionnement du vieillissement (venant de io.c)




void init_grille_cairo(cairo_surface_t *surface, grille g){

	int lignes=g.nbl, colonnes=g.nbc;

	// create cairo mask
	cairo_t *cr;
	cr=cairo_create(surface);

	//background
	cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
	cairo_paint(cr);

	//titre et affichage activation/désactivation vieillissement et cyclique
	cairo_set_source_rgb (cr, 255,0,0);
	cairo_select_font_face(cr, "Arial",
		 CAIRO_FONT_SLANT_NORMAL,
     	 CAIRO_FONT_WEIGHT_BOLD);


  	cairo_set_font_size(cr, 45);

  	cairo_move_to(cr, SIZEX/2 - 9*(CASE/2), 40);
  	cairo_show_text(cr, "Game of Life");

  	cairo_set_font_size(cr, CASE/2);

  	cairo_move_to(cr, SIZEX/2 - 6*(CASE/2), 60);
  	cairo_show_text(cr, "aging of cells:");

  	cairo_move_to(cr, SIZEX/2 - 6*(CASE/2), 75);
  	cairo_show_text(cr, "cyclic grid: ");

  	cairo_move_to(cr, SIZEX/2 + CASE, 60);
  	if(vieillissement == 0) cairo_show_text(cr, "[desactivated]");
  	else if (vieillissement==1){
  		cairo_set_source_rgb (cr, 0,0,255);
  		cairo_show_text(cr, "[activated]");
  	}

  	
  	cairo_move_to(cr, SIZEX/2 + CASE, 75);
  	if(voisinage == 1){
  		cairo_set_source_rgb (cr, 255,0,0);
  		cairo_show_text(cr, "[desactivated]");
  	}
  	else if (voisinage == 0){
  		cairo_set_source_rgb (cr, 0,0,255);
  		cairo_show_text(cr, "[activated]");
  	}

  	cairo_move_to(cr,SIZEX/2 - 6*(CASE/2), 90);
  	cairo_set_source_rgb (cr, 255,0,0);
  	cairo_show_text(cr,"generation n°:");

  	cairo_move_to(cr, SIZEX/2 + CASE, 90);
  	cairo_set_source_rgb(cr, 0,0,255);

  	char generation[10];
  	sprintf(generation,"[%d]",tps_evol);
  	cairo_show_text(cr, generation);



	//print grid to the screen
	double start_point = (SIZEX - (CASE*colonnes)) / 2; 

	cairo_set_source_rgb (cr, 0,0,255);

	for(int i=0; i <= colonnes; i++){
		cairo_move_to (cr,  start_point+CASE*i, 105);
		cairo_line_to(cr, start_point+CASE*i, 105+CASE*(lignes));
		cairo_set_line_width (cr, 4);
		cairo_stroke (cr);
	}

	for(int j=0; j <= lignes; j++){
		cairo_move_to (cr, start_point, 105+CASE*j);
		cairo_line_to(cr, start_point+CASE*(colonnes), 105+CASE*j);
		cairo_set_line_width (cr, 4);
		cairo_stroke (cr);
	}

	cairo_destroy(cr); // destroy cairo mask
}



void affiche_grille_cairo(cairo_surface_t *surface, grille g){
	int lignes=g.nbl, colonnes=g.nbc;

	// create cairo mask
	cairo_t *cr;
	cr=cairo_create(surface);

	double start_point = (SIZEX - (CASE*colonnes)) / 2; 

	cairo_select_font_face(cr, "Arial",
		CAIRO_FONT_SLANT_NORMAL,
     	CAIRO_FONT_WEIGHT_BOLD);
		cairo_set_font_size(cr, CASE);

	for (int i= 0; i < lignes; ++i){	
		for(int j= 0; j< colonnes; ++j){
			cairo_set_source_rgb (cr, 255,0,0);
			cairo_move_to(cr,start_point+j*CASE+0.2*CASE, 105+i*CASE+0.8*CASE);
			
			int k = g.cellules[i][j];

			if (1<=k && vieillissement==0) cairo_show_text(cr, "0");//affichage normal sans vieillissement

			if(vieillissement==1){//Affichage vieillissment activé
				cairo_set_source_rgb (cr, 255,0,0);
				if(k>=1){
				char age[2];
				sprintf(age,"%d",k);
				cairo_show_text(cr,age);
				}
			}

			if(k==-1){//carré bleu pour les cases plus que mortes
				cairo_set_source_rgb (cr, 0.0, 0.0, 255.0);
				cairo_rectangle(cr,start_point+j*CASE,105+i*CASE, CASE, CASE);
				cairo_fill(cr);
			}
		}
	}
  	
	cairo_destroy(cr); // destroy cairo mask
}


void switch_grid(cairo_surface_t *surface){

	cairo_t *cr;
	cr=cairo_create(surface);
	cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
	cairo_paint(cr);

	cairo_set_source_rgb (cr, 0,0,255);
	cairo_move_to(cr, SIZEX/2 - 6*CASE, 60);
	cairo_select_font_face(cr, "Arial",
		CAIRO_FONT_SLANT_NORMAL,
    	CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size(cr, 30);

	cairo_show_text(cr,"#chose a new grid please#");

	cairo_set_source_rgb (cr, 255,0,0);
	cairo_move_to(cr, SIZEX/2 - 6*CASE, 80);
	cairo_set_font_size(cr, 15);

	cairo_show_text(cr,"#only numbers in range 1 to 8 included are allowed#");

cairo_move_to(cr, SIZEX/2 - 5*CASE, 95);

cairo_show_text(cr, "#any other key pressed won't have any effect#");

}


int debut_jeu_cairo (grille *g, grille *gc){
	// X11 display
	Display *dpy;
	Window rootwin;
	Window win;
	XEvent e;
	int scr;
	
	// init the display
	if(!(dpy=XOpenDisplay(NULL))) {
		fprintf(stderr, "ERROR: Could not open display\n");
		exit(1);
	}

	scr=DefaultScreen(dpy);
	rootwin=RootWindow(dpy, scr);

	win=XCreateSimpleWindow(dpy, rootwin, 1, 1, SIZEX, SIZEY, 0, 
			BlackPixel(dpy, scr), BlackPixel(dpy, scr));

	XStoreName(dpy, win, "Game of Life");
	XSelectInput(dpy, win, ExposureMask|ButtonPressMask|KeyPressMask);
	XMapWindow(dpy, win);
	
	// create cairo surface
	cairo_surface_t *cs; 
	cs=cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), SIZEX, SIZEY);



	// run the event loop
	int (*compte_voisins_vivants) (int, int, grille) = compte_voisins_vivants_c; 
	while(1) {
		XNextEvent(dpy, &e);
		if(e.type==Expose && e.xexpose.count<1) {
			init_grille_cairo(cs, *g);
			affiche_grille_cairo(cs, *g);
		} 

		else if(e.type == KeyPress){

			if(e.xkey.keycode==XKeysymToKeycode(dpy,'v')){//activation/désactivation vieillissement
				if (vieillissement == 0) {
					vieillissement = 1;
					noBug = 1;
				}
				else{
					vieillissement = 0;
					noBug = 1;
				}
				init_grille_cairo(cs, *g);
				affiche_grille_cairo(cs, *g);
			}

			else if(e.xkey.keycode==XKeysymToKeycode(dpy,'c')){//activation/désactivation voisinage cyclique
				if(voisinage == 0) {
					compte_voisins_vivants= compte_voisins_vivants_nc;
					voisinage = 1;
				}
				else{
					compte_voisins_vivants = compte_voisins_vivants_c;
					voisinage = 0;
				}
				init_grille_cairo(cs, *g);
				affiche_grille_cairo(cs, *g);
			}



			else if(e.xkey.keycode==XKeysymToKeycode(dpy,'n')){

				libere_grille(g);
				libere_grille(gc);
				char numGrille[2];
				char fileGrille[30] = "grilles/grille";

				switch_grid(cs);//affichage en attendant que l'utilisateur rentre un nouveau numéro

				int check = 1;
				while(check == 1){
					XNextEvent(dpy, &e);
					if(e.xkey.keycode==XKeysymToKeycode(dpy,'1')){ numGrille[0] = '1' ;check++;}
					else if(e.xkey.keycode==XKeysymToKeycode(dpy,'2')){numGrille[0] = '2';check++;}
					else if(e.xkey.keycode==XKeysymToKeycode(dpy,'3')){numGrille[0] = '3';check++;}
					else if(e.xkey.keycode==XKeysymToKeycode(dpy,'4')){numGrille[0] = '4';check++;}
					else if(e.xkey.keycode==XKeysymToKeycode(dpy,'5')){numGrille[0] = '5';check++;}
					else if(e.xkey.keycode==XKeysymToKeycode(dpy,'6')){numGrille[0] = '6';check++;}
					else if(e.xkey.keycode==XKeysymToKeycode(dpy,'7')){numGrille[0] = '7';check++;}
					else if(e.xkey.keycode==XKeysymToKeycode(dpy,'8')){numGrille[0] = '8';check++;}
				}

				strcat(fileGrille, numGrille);

				strcat(fileGrille, ".txt");
				init_grille_from_file(fileGrille, g);

				tps_evol = 0;

				alloue_grille(g->nbl, g->nbc, gc);
				init_grille_cairo(cs, *g);
				affiche_grille_cairo(cs, *g);
			}

		}
		

		else if(e.type == ButtonPress){
			if(e.xkey.keycode == 1){//pour faire évoluer la grille (clique gauche)

					evolue(g,gc, compte_voisins_vivants, vieillissement);
					tps_evol++;
				
				init_grille_cairo(cs, *g);
				affiche_grille_cairo(cs, *g);
			}
			else if(e.xkey.keycode){//pour fermer la fenetre proprement: clique droit
				break;
			}
		} 
	}
	
	cairo_surface_destroy(cs); // destroy cairo surface
	XCloseDisplay(dpy); // close the display
	return 0;
}


