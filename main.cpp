#include "mysqlPart.h"
#include "SDLPart.h"

int main ( int argc, char** argv)
{

    MYSQL mysql;
    mysql_init(&mysql);
    mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "option");

    Film film;
    film = ajouterFilm(film);

    //entre le film, les acteurs et le realisateur dans la BDD
    entrer_Film_BDD(mysql, film);

    //supprime un acteur
    //supprimer_Acteurs_Realisateurs(mysql, film.acteurs);

    //Supprime un film
    //supprimer_Film(mysql, film);

    //affiche la table des individus
    //afficherTable_Acteurs_Realisateurs(mysql);

    //affiche la table des films
    //afficherTable_Films(mysql);


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
