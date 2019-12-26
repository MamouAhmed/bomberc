exec : clear main.o menu.o terrain.o joueur.o
	gcc -Wall main.o  menu.o terrain.o joueur.o -lpthread `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` `pkg-config --libs-only-l MLV` -o exec
main.o : main.c 
	gcc -c main.c -lpthread
menu.o : menu.c menu.h
	gcc -c menu.c
terrain.o : terrain.c terrain.h
	gcc -c terrain.c
joueur.o : joueur.c joueur.h 
	gcc -c joueur.c
clear :
	rm -f *.o *~ exec
