#include<stdio.h>
#include<stdlib.h>
#include<MLV/MLV_all.h>
#include <time.h>
#include "joueur.h"
#define JEU 1
#define FALSE 0
#define TRUE 1
#define MENU 0
#define FERMER 2
#define OPTION 3
#include <pthread.h>
#if defined (Win32)
#include <windows.h>
#define psleep(sec) Sleep ((sec) * 1000)
#elif defined (Linux)
#include <unistd.h>
#define sleep(sec) sleep ((sec))
#endif

	/* déclaration des variables */
	int etat = MENU ;
   	int  j;
	int stop = 1;
	int waitmouse = 1;
   	int x, y;
	int bool;
	int compteur_bombe = 0;
	/* déclaration des variables servant à la recupération d'une touche du clavier appuyée / d'un 		clic de souris et à l'affichage d'images */
	MLV_Image *imagemenu;
  	MLV_Image *imageoption;
	MLV_Keyboard_modifier mod;
   	MLV_Keyboard_button sym;
   	MLV_Button_state state;
	MLV_Mouse_button* mouse_button;
    MLV_Event evenement;
   	MLV_Event event;
	terrain terrain1;
	joueur j1;
	joueur j2;	
typedef struct
{
   terrain jeu;
 
   pthread_t deplacement_joueur1;
   pthread_t deplacement_joueur2;
   pthread_t explosion_bombe;
}
bombe_t;
typedef struct 
{
	int positionx;
	int positiony;
	int timer;
}ma_bombe;
ma_bombe tab_de_bombe[];
static bombe_t bombe =
{
   
};

bool = FALSE;
/* Fonction pour le thread du J1. */
static void * deplacementj1 (void * p_data)
{
	/* On traite l'évènement s'il s'agit d'un évènement clavier uniquement */  
	while(1){
		if( event == MLV_KEY )
		{                
			/* On compte le nombre de fois qu'une touche a été préssée */
			/*On déplacera un joueur / posera une bombe suivant la touche appuyée */
			
			if(state == MLV_PRESSED && bool==FALSE)
			{
				if ( sym == MLV_KEYBOARD_d )
				{
					deplacer_droite(&j1, &terrain1);
				}
				
				if ( sym == MLV_KEYBOARD_q )
				{
					deplacer_gauche(&j1, &terrain1);
				}
				
				if ( sym == MLV_KEYBOARD_z )
				{
					deplacer_haut(&j1, &terrain1);
				}
				
				if ( sym == MLV_KEYBOARD_s )
				{
					deplacer_bas(&j1, &terrain1);
				}
				bool=TRUE;
				if ( sym == MLV_KEYBOARD_SPACE )
				{
					if(poserBombe(&j1, &terrain1) == 1)
					{
					
						tab_de_bombe[compteur_bombe].positionx=j1.posx;
						tab_de_bombe[compteur_bombe].positiony=j1.posy;
						tab_de_bombe[compteur_bombe].timer=3;
						compteur_bombe += 1;
					}
				}
			}
			if(state == MLV_RELEASED){bool=FALSE;}
		}
				}
}
static void * fct_explose_bombe (void *p_data)
{
}
static void * deplacementj2 (void * p_data)
{
	/* On traite l'évènement s'il s'agit d'un évènement clavier uniquement */
	
	if( event == MLV_KEY )
	{               
			/* On compte le nombre de fois qu'une touche a été préssée */
	/*On déplacera un joueur / posera une bombe suivant la touche appuyée */
			
		if(state == MLV_PRESSED)
		{                          
			if ( sym == MLV_KEYBOARD_RIGHT )
			{
			deplacer_droite(&j2, &terrain1);
			}
			
			if ( sym == MLV_KEYBOARD_LEFT )
			{
				deplacer_gauche(&j2, &terrain1);
			}
			
			if ( sym == MLV_KEYBOARD_UP )
			{
				deplacer_haut(&j2, &terrain1);
			}
			
			if ( sym == MLV_KEYBOARD_DOWN )
			{
				deplacer_bas(&j2, &terrain1);
			}
			
			/*if ( sym == MLV_KEYBOARD_RETURN )
			{
				if(poserBombe(&j2, &terrain1) == 1)
				{
					
				}
			}*/
			
		}

	}
}

int main( int argc, char * argv[] )
{
	int ret, retbis;
	init_terrain(&terrain1);
 	init_map(&terrain1);
	init_joueur2(&j2,&terrain1);
	init_joueur1(&j1,&terrain1);
	/* On crée la fenêtre où tout sera affiché */
	MLV_create_window( "Bomberman", "Bomberman", LONGUEURFENETRE, HAUTEURFENETRE );
	imagemenu = MLV_load_image("menu.png");
   	imageoption = MLV_load_image("menu2.png");


	/*retbis = pthread_create(&bombe.deplacement_joueur2, NULL,deplacementj2, NULL);*/
	ret = pthread_create(&bombe.deplacement_joueur1, NULL,deplacementj1, NULL);
	while(stop>0)
	{
		while(etat == JEU) 
		{ 
				event = MLV_get_event( &sym, &mod, NULL, NULL, NULL, NULL, NULL, NULL, &state );

				
				
				afficherTerrain(&terrain1);
			
		}
		
		while(etat == MENU)
		{
			retrecir_ecran();
			MLV_draw_image(imagemenu,LONGUEURFENETRE/5,0); 
			MLV_actualise_window();
			MLV_wait_mouse(&x, &y);
			
			if (y > 300 && y <380 & x>300 & x <1200)
			{
				 MLV_clear_window(MLV_COLOR_BLACK);
				 etat = JEU;				
			}
			
			if (y > 500 && y < 560 && x>300 && x<1200)
			{
				MLV_free_window();
			}
			
			if (x > 1060 && y < 120 && x <1200 ) 
			{ 
				etat = OPTION ; 
			}
        }

		while (etat == OPTION)
		{
			retrecir_ecran();
			MLV_draw_image(imageoption,LONGUEURFENETRE/5,0);
			MLV_actualise_window(); 
			MLV_wait_mouse(&x, &y);
			
			if (x > 1060 && y < 120 && x <1200 ) 
			{ 
				etat = MENU ; 
			}
		}
     }
}
