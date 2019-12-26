#include<MLV/MLV_all.h>
#define NBCL 10 
#define NBCH 10 
#define LONGUEURFENETRE 1500
#define HAUTEURFENETRE 1000
#define LONGUEURC LONGUEURFENETRE/NBCL
#define HAUTEURC HAUTEURFENETRE/NBCH
#include "menu.h"





	void retrecir_ecran(){ /* on affiche des rectangles noirs sur les cotés de l'écran pour rétrécir la zone d'affichage (blanche) */
		MLV_draw_filled_rectangle(0,
					  0,
                			  LONGUEURFENETRE,
					  HAUTEURFENETRE,
					  MLV_COLOR_WHITE);
		MLV_draw_filled_rectangle(0,
					  0,
                			  LONGUEURFENETRE/5-1,
					  HAUTEURFENETRE,
					  MLV_COLOR_BLACK);
		MLV_draw_filled_rectangle(LONGUEURFENETRE-LONGUEURFENETRE/5,
					  0,
                			  LONGUEURFENETRE,
					  HAUTEURFENETRE,
					  MLV_COLOR_BLACK);
	}

