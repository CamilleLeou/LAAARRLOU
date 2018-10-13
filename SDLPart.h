#ifndef MYSQLPART_H_INCLUDED
#define MYSQLPART_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>        //Bibliotheque SDL
#include <SDL_image.h>  //Bibliotheque permettant d'afficher des images pour la SDL
#include <SDL_ttf.h>    //Bibliotheque permettant d'écrire du texte avec la SDL
#undef main

#include "Structures.h"

char ecrire(char buffer[20], SDL_Surface *ecran, SDL_Surface *fond, int x, int y, int xFond, int yFond, int taille);
char ecrireChiffre(char chiffre[10], SDL_Surface *ecran, SDL_Surface *fond, int x, int y, int xFond, int yFond, int taille);
char ecrireDate(char chiffre[10], SDL_Surface *ecran, SDL_Surface *fond, int x, int y, int xFond, int yFond, int taille);
int dansZone(SDL_Event event, int x, int y, int x2, int y2);
int saisieType(SDL_Event event, SDL_Surface *ecran);
People personne(SDL_Surface *ecran, People humain);
int saisieNbActeurs(SDL_Event event, SDL_Surface *ecran);
Film ajouterFilm(Film film);
void afficherFilm(Film film);




#endif // MYSQLPART_H_INCLUDED
