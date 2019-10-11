Launcher : PROJET EXEC clean

menu.o : menu.c menu.h affichage_carte.h librairies.h
	gcc -c -Wall menu.c

affichage_carte.o : affichage_carte.c affichage_carte.h librairies.h
	gcc -c -Wall affichage_carte.c

vehicules.o : vehicules.c vehicules.h librairies.h
	gcc -c -Wall vehicules.c

pietons.o : pietons.c pietons.h librairies.h
	gcc -c -Wall pietons.c
	
trains.o : trains.c trains.h librairies.h
	gcc -c -Wall trains.c

foncitons.o : fonctions.c fonctions.h librairies.h
	gcc -c -Wall fonctions.c

launchers.o : launchers.c launchers.h librairies.h
	gcc -c -Wall launchers.c

main.o : main.c menu.h vehicules.h pietons.h fonctions.h launchers.h trains.h affichage_carte.h librairies.h
	gcc -c -Wall main.c

PROJET : menu.o fonctions.o launchers.o trains.o vehicules.o pietons.o affichage_carte.o main.o
	gcc -o PROJET menu.o fonctions.o launchers.o trains.o vehicules.o pietons.o affichage_carte.o main.o

EXEC :
	./PROJET

clean :
	rm *.o PROJET


sound : 
	play 0910.mp3 
