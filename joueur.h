#define NBCL 10 /*nombre case longueur*/
#define NBCH 10 /*nombre case hauteur*/
#define LONGUEURFENETRE 1500
#define HAUTEURFENETRE 1000
#define LONGUEURC LONGUEURFENETRE/NBCL
#define HAUTEURC HAUTEURFENETRE/NBCH
#include "terrain.h"

typedef struct{
	int numero;
	int posx;
	int posy;
	int nombre_bombe;
	int puissance_bombe;
	int posxbombe;
	int posybombe;
	int num_bombe;
	time_t time_bombe;
}joueur;/*on définit joueur comme étant un type*/

void init_joueur1(joueur *j, terrain *t);/*on prend pour entrée un type joueur contenant (son numero , sa position, son nombre de bombes posables, leurs puissances, leurs numeros et leurs positions)
						puis on initialise le tout à des valeurs données */

void init_joueur2(joueur *j, terrain *t);/*on prend pour entrée un type joueur contenant (son numero , sa position, son nombre de bombes posables, leurs puissances, leurs numeros et leurs positions)
						puis on initialise le tout à des valeurs données */

void deplacer_gauche(joueur *j, terrain *t);/* on prend en entrée un joueur et le tableau du terrain, on change la position du joueur, et la valeur des cases d'arrivées et de départ */

void deplacer_droite(joueur *j, terrain *t);/* on prend en entrée un joueur et le tableau du terrain, on change la position du joueur, et la valeur des cases d'arrivées et de départ */

void deplacer_haut(joueur *j, terrain *t);/* on prend en entrée un joueur et le tableau du terrain, on change la position du joueur, et la valeur des cases d'arrivées et de départ */

void deplacer_bas(joueur *j, terrain *t);/* on prend en entrée un joueur et le tableau du terrain, on change la position du joueur, et la valeur des cases d'arrivées et de départ */

int poserBombe(joueur *j, terrain *t);/* on prend en entrée un joueur et le tableau du terrain, si une bombe est posée la bombe prend la position du joueur, la case prend la valeur MISS permettant l'affichage d'une bombe, et le joueur peut à présent poser une bombe de moins */
	

void explosion(joueur *j, terrain *t);/*on prend en entrée un joueur et le terrain pour récuperer les positions des bombes posées. Pour chaque direction haut bas droite et gauche on verifiera selon la puissance, si le case adjacente est un mur cassable ou non. */



