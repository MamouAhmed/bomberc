#include<stdio.h>
#include<stdlib.h>
#include<MLV/MLV_all.h>
#define NBCL 10 /*nombre case longueur*/
#define NBCH 10 /*nombre case hauteur*/
#define LONGUEURFENETRE 1500
#define HAUTEURFENETRE 1000
#define LONGUEURC LONGUEURFENETRE/NBCL
#define HAUTEURC HAUTEURFENETRE/NBCH
#define VIDE 0
#define CASSABLE 1
#define INCASSABLE 2
#define J1 3
#define J2 4
#define BOMB 5
#define MISS 6
#define EXPLOSION 7
#include "terrain.h"

void init_terrain(terrain *t){
	int i, j;

	/*declaration des cases comme etant vides */
	for (i=0;i<NBCL;i++){
		for(j=0;j<NBCH;j++){
			t->map[i][j]= VIDE;
		}
	}
}


void init_map(terrain *t){	/*declaration des cases telles que certaines soient vide, d'autres soient des murs cassables et d'autres incassables*/
	int i, j;
	for(i=0;i<NBCL;i++){
		for(j=0;j<NBCH;j++){
			if ((i != 0 && j!=0) && (i != NBCL-1 && j!= NBCH-1)){
				t->map[i][j]= CASSABLE;
			}
			if ((i == 0 ) && (j >= NBCH-3) || (j == 0 ) && (i >= NBCL-3)){
				t->map[i][j]= CASSABLE;
			}
			if ((i <= 2 ) && (j == NBCL-1) || (j <= 2 ) && (i == NBCH-1)){
				t->map[i][j]= CASSABLE;
			}
			if ((i == j) && (i !=0 ) && (i != NBCL-1) && (i != 4) && (i != 5)){
				t->map[i][j]= INCASSABLE;
			}
			if (((i == 4) && (j == 2)) || ((i == 5) && (j == 7))) {
				t->map[i][j]= INCASSABLE;
			}
		}
	}
}

void afficherTerrain(terrain *t){/* on parcours et affiche le terrain, avec une image donnée pour chaque type de case */

	MLV_clear_window( MLV_COLOR_FOREST_GREEN );

	MLV_Image *joueur1;
	MLV_Image *joueur2;
	MLV_Image *case_cassable;
	MLV_Image *case_incassable;
	MLV_Image *bomb;
	MLV_Image *bomberman_b;
	MLV_Image *explosion;

	joueur1 = MLV_load_image( "bomberman.png" );
	joueur2 = MLV_load_image( "bomberman2.png" );
	case_cassable = MLV_load_image( "block2.png" );
	case_incassable = MLV_load_image( "block.png" );
	bomb = MLV_load_image( "bomb.png" );
	bomberman_b = MLV_load_image( "bomberman_b.png" );
	explosion = MLV_load_image( "explosion.png" );

	MLV_resize_image_with_proportions( joueur1, LONGUEURC, HAUTEURC);
	MLV_resize_image_with_proportions( joueur2, LONGUEURC, HAUTEURC);
	MLV_resize_image_with_proportions( case_cassable, LONGUEURC, HAUTEURC);
	MLV_resize_image_with_proportions( case_incassable, LONGUEURC, HAUTEURC);
	MLV_resize_image_with_proportions( bomb, LONGUEURC, HAUTEURC);
	MLV_resize_image_with_proportions( bomberman_b, LONGUEURC, HAUTEURC);
	MLV_resize_image_with_proportions( explosion, LONGUEURC, HAUTEURC);


	int i, j;
	for(i=0;i<NBCL;i++){
		for(j=0;j<NBCH;j++){
			if (t->map[i][j] == J1){
				MLV_draw_image( joueur1, i*LONGUEURC+25, j*HAUTEURC );
			}
			if (t->map[i][j] == J2){
				MLV_draw_image( joueur2, i*LONGUEURC+25, j*HAUTEURC );
			}
			if (t->map[i][j] == CASSABLE){
				MLV_draw_image( case_cassable, i*LONGUEURC+25, j*HAUTEURC );
			}
			if (t->map[i][j] == INCASSABLE){
				MLV_draw_image( case_incassable, i*LONGUEURC+25, j*HAUTEURC );
			}
			if (t->map[i][j] == BOMB){
				MLV_draw_image( bomb, i*LONGUEURC+25, j*HAUTEURC );
			}
			if (t->map[i][j] == MISS){
				MLV_draw_image( bomb, i*LONGUEURC+25, j*HAUTEURC );
				MLV_draw_image( bomberman_b, i*LONGUEURC+25, j*HAUTEURC );
			}
			if (t->map[i][j] == EXPLOSION){
				MLV_draw_image( explosion, i*LONGUEURC+25, j*HAUTEURC );
			}
		}
	}

	/*affichage du cadrillage horizontal*/
	for(i=0;i<=NBCH;i++){
                MLV_draw_line( 0,
			       HAUTEURC*i,
			       LONGUEURFENETRE,
			       HAUTEURC*i,
			       MLV_COLOR_BLACK );
	}

	/*affichage du cadrillage vertical*/
	for(i=0;i<=NBCL;i++){
		MLV_draw_line( LONGUEURC*i, 
			       0, 
			       LONGUEURC*i, 
			       HAUTEURFENETRE,
			       MLV_COLOR_BLACK);
	}

	MLV_actualise_window();
}


