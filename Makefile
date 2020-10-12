main : main.o grille.o io.o jeu.o
	gcc -o main.c grille.c io.c jeu.c -lm

main.o : main.c grille.h io.h jeu.h
	gcc -c main.c

grille.o : grille.c grille.h
	gcc -c grille.c

io.o : io.c io.h
	gcc -c io.c

jeu.o : jeu.c jeu.h
	gcc -c jeu.c

clean : 
	rm main main.o grille.o io.o jeu.o
