//
//  mysqlPart.h
//  testSDL
//
//  Created by Jérôme COFFIN on 12/10/2018.
//  Copyright © 2018 Jérôme COFFIN. All rights reserved.
//

#ifndef mysqlPart_h
#define mysqlPart_h

#include <stdio.h>

void afficherTable();
void supprimerFilmBDD();
void entrer_Realisateur_BDD(Film Film);
void entrer_Film_BDD(Film Film);
void afficher(Film Film);
Film addFilm(Film Film);
People InitNull();
People addPeople();
void viderBuffer();

typedef struct Film Film;
typedef struct People People;
typedef struct Date Date;


struct Date
{
    int day;
    int month;
    int year;
};

struct People
{
    char* name;
    char* surname;
    char* birthplace;
    Date birthday;
};

struct Film
{
    char* name;
    Date date;
    People author;
    int numberOfActors;
    People* actors;
    int time;
    int type;
};

#endif /* mysqlPart_h */
