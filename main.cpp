#include "SDLPart.h"
#include "mysqlPart.h"
#include "Structures.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock.h>
#include <MYSQL/mysql.h>
#include <SDL.h>        //Bibliothèque SDL
#include <SDL_image.h>  //Bibliothèque permettant d'afficher des images pour la SDL
#include <SDL_ttf.h>    //Bibliothèque permettant d'écrire du texte avec la SDL
#undef main


int main ( int argc, char** argv)
{

    MYSQL mysql;
    mysql_init(&mysql);
    mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "option");

    Film film;
    film = ajouterFilm(film);

    afficherFilm(film);

    SDL_Event event;
    int continuer = 1;
    while(continuer)
    {
        SDL_WaitEvent(&event);

        if(event.type == SDL_MOUSEBUTTONUP)
        {
            exit(0);
        }
    }


    return EXIT_SUCCESS;
}
