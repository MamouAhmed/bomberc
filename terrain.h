#include "menu.h"


typedef struct{
	int map[NBCL][NBCH];/*terrain est un type contenant un tableau de 2 dimensions*/
}terrain;
	

void init_terrain(terrain *t);	/*declaration des cases comme etant vides */

void init_map(terrain *t);/*declaration des cases telles que certaines soient vide, d'autres soient des murs cassables et d'autres incassables*/

void afficherTerrain(terrain *t);/* on parcours et affiche le terrain, avec une image donnée pour chaque type de case */







