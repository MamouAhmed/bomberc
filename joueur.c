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
#include "joueur.h"	
#include <time.h> 


void init_joueur1(joueur *j, terrain *t){/*on prend pour entrée un type joueur contenant (son numero , sa position, son nombre de bombes posables, leurs puissances, leurs numeros et leurs positions)
						puis on initialise le tout à des valeurs données */
	j->numero = 3;
	j->posx = 0;
	j->posy = 0;
	j->nombre_bombe = 5;
	j->puissance_bombe = 4;
	j->num_bombe = 0;
	t->map[j->posx][j->posy] = J1;
}

void init_joueur2(joueur *j, terrain *t){/*on prend pour entrée un type joueur contenant (son numero , sa position, son nombre de bombes posables, leurs puissances, leurs numeros et leurs positions)
						puis on initialise le tout à des valeurs données */
	j->numero = 4;
	j->posx = 9;
	j->posy = 9;
	j->nombre_bombe = 5;
	j->puissance_bombe = 4;
	j->num_bombe = 0;
	t->map[j->posx][j->posy] = J2;
}

void deplacer_droite(joueur *j, terrain *t){/* on prend en entrée un joueur et le tableau du terrain, on change la position du joueur, et la valeur des cases d'arrivées et de départ */
	if(t->map[j->posx][j->posy] == MISS && t->map[(j->posx)+1][j->posy] == VIDE && ((j->posx)+1 != NBCL)){
		t->map[j->posx][j->posy] = BOMB;
    	t->map[(j->posx)+1][j->posy] = j->numero;
    	j->posx += 1;
	}
	else if(t->map[(j->posx)+1][j->posy] == VIDE && ((j->posx)+1 != NBCL)){
		t->map[j->posx][j->posy] = VIDE;
    	t->map[(j->posx)+1][j->posy] = j->numero;
    	j->posx += 1;
    }
}

void deplacer_gauche(joueur *j, terrain *t){/* on prend en entrée un joueur et le tableau du terrain, on change la position du joueur, et la valeur des cases d'arrivées et de départ */
	if(t->map[j->posx][j->posy] == MISS && t->map[(j->posx)-1][j->posy] == VIDE && ((j->posx)-1 >= 0)){
		t->map[j->posx][j->posy] = BOMB;
    	t->map[(j->posx)-1][j->posy] = j->numero;
    	j->posx -= 1;
	}
	else if(t->map[(j->posx)-1][j->posy] == VIDE && ((j->posx)-1 >= 0)){
		t->map[j->posx][j->posy] = VIDE;
    	t->map[(j->posx)-1][j->posy] = j->numero;
    	j->posx -= 1;
    }
}

void deplacer_haut(joueur *j, terrain *t){/* on prend en entrée un joueur et le tableau du terrain, on change la position du joueur, et la valeur des cases d'arrivées et de départ */
	if(t->map[j->posx][j->posy] == MISS && t->map[(j->posx)][(j->posy)-1] == VIDE && ((j->posy)-1 >= 0)){
		t->map[j->posx][j->posy] = BOMB;
    	t->map[(j->posx)][(j->posy)-1] = j->numero;
    	j->posy -= 1;
	}
	else if(t->map[(j->posx)][(j->posy)-1] == VIDE && ((j->posy)-1 >= 0)){
		t->map[j->posx][j->posy] = VIDE;
    	t->map[(j->posx)][(j->posy)-1] = j->numero;
    	j->posy -= 1;
    }
}

void deplacer_bas(joueur *j, terrain *t){/* on prend en entrée un joueur et le tableau du terrain, on change la position du joueur, et la valeur des cases d'arrivées et de départ */
	if(t->map[j->posx][j->posy] == MISS && t->map[(j->posx)][(j->posy)+1] == VIDE && ((j->posy)+1 != NBCH)){
		t->map[j->posx][j->posy] = BOMB;
    	t->map[(j->posx)][(j->posy)+1] = j->numero;
    	j->posy += 1;
	}
	else if(t->map[(j->posx)][(j->posy)+1] == VIDE && ((j->posy)+1 != NBCH)){
		t->map[j->posx][j->posy] = VIDE;
    	t->map[(j->posx)][(j->posy)+1] = j->numero;
    	j->posy += 1;
    }
}

int poserBombe(joueur *j, terrain *t){/* on prend en entrée un joueur et le tableau du terrain, si une bombe est posée la bombe prend la position du joueur, la case prend la valeur MISS permettant l'affichage d'une bombe, et le joueur peut à présent poser une bombe de moins */
	if (j->nombre_bombe > 0){
		t->map[j->posx][j->posy] = MISS;
		j->nombre_bombe -= 1;
		j->posxbombe = j->posx;
		j->posybombe = j->posy; 
		return 1;
	}else{
		return 0;
	}
}

void explosion(joueur *j, terrain *t){/*on prend en entrée un joueur et le terrain pour récuperer les positions des bombes posées. Pour chaque direction haut bas droite et gauche on verifiera selon la puissance, si le case adjacente est un mur cassable ou non. */
	int i, ok1=1, ok2=1, ok3=1, ok4=1;
	for(i=0;i<=j->puissance_bombe;i++){
		if((t->map[(j->posxbombe)+i][(j->posybombe)]) == INCASSABLE){
			ok1 = 0;
		}
		if((t->map[(j->posxbombe)][(j->posybombe)+i]) == INCASSABLE){
			ok2 = 0;
		}
		if((t->map[(j->posxbombe)-i][(j->posybombe)]) == INCASSABLE){
			ok3 = 0;
		}
		if((t->map[(j->posxbombe)][(j->posybombe)-i]) == INCASSABLE){
			ok4 = 0;
		}
		if (((j->posxbombe)+i < NBCL) && ok1 == 1){
			t->map[(j->posxbombe)+i][(j->posybombe)] = EXPLOSION;
		}
		if (((j->posybombe)+i < NBCH) && ok2 == 1){
			t->map[(j->posxbombe)][(j->posybombe)+i] = EXPLOSION;
		}
		if (((j->posxbombe)-i >= 0) && ok3 == 1){
			t->map[(j->posxbombe)-i][(j->posybombe)] = EXPLOSION;
		}
		if (((j->posybombe)-i >= 0) && ok4 == 1){
			t->map[(j->posxbombe)][(j->posybombe)-i] = EXPLOSION;
		}
	}
	j->nombre_bombe +=1;/* on peut de nouveau poser toutes ses bombes */
}




