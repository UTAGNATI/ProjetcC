Launcher : PROJET EXEC

menu.o : menu.c menu.h affichage_carte.h librairies.h
	gcc -c -Wall menu.c

affichage_carte.o : affichage_carte.c affichage_carte.h librairies.h
	gcc -c -Wall affichage_carte.c

foncitons.o : fonctions.c fonctions.h librairies.h
	gcc -c -Wall fonctions.c

main.o : main.c menu.h fonctions.h affichage_carte.h librairies.h
	gcc -c -Wall main.c

PROJET : menu.o fonctions.o affichage_carte.o main.o
	gcc -o PROJET menu.o fonctions.o affichage_carte.o main.o

EXEC :
	./PROJET
