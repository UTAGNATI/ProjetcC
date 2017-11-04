Launcher : PROJET EXEC

menu.o : menu.c menu.h affichage_carte.h librairies.h
	gcc -c -Wall menu.c

affichage_carte.o : affichage_carte.c affichage_carte.h librairies.h
	gcc -c -Wall affichage_carte.c

vehicules.o : vehicules.c vehicules.h librairies.h
	gcc -c -Wall vehicules.c
	
trains.o : trains.c trains.h librairies.h
	gcc -c -Wall trains.c

foncitons.o : fonctions.c fonctions.h librairies.h
	gcc -c -Wall fonctions.c

main.o : main.c menu.h vehicules.h fonctions.h trains.h affichage_carte.h librairies.h
	gcc -c -Wall main.c

PROJET : menu.o fonctions.o trains.o vehicules.o affichage_carte.o main.o
	gcc -o PROJET menu.o fonctions.o trains.o vehicules.o affichage_carte.o main.o

EXEC :
	./PROJET
