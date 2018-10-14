#include "mysqlPart.h"
#include "SDLPart.h"

int main ( int argc, char** argv)
{

    MYSQL mysql;
    mysql_init(&mysql);
    mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "option");

    Film film;
    film = ajouterFilm(film);

    entrer_Film_BDD(mysql, film);


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
