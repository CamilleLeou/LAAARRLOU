#ifndef MYSQLPART_H_INCLUDED
#define MYSQLPART_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>        //Inclure les sockets pout windows
#include <MYSQL/mysql.h>    //Inclure API mySQL pour C
#undef main                 //l'API mySQL utilise un fichier main different de main.cpp
                            //cette ligne permet de ne pas les confondre

#include "Structures.h"


People addPeople(void);
void viderBuffer(void);
People InitNull(void);
Film addFilm(Film Film);
void entrer_Film_BDD(MYSQL mysql, Film Film);
void entrer_Realisateur_BDD(MYSQL mysql, People personne);
void afficherTable_Acteurs_Realisateurs(MYSQL mysql);
void afficherTable_Films(MYSQL mysql);
void supprimer_Film(MYSQL mysql, Film monFilm);
void supprimer_Acteurs_Realisateurs(MYSQL mysql, People personne);





#endif // MYSQLPART_H_INCLUDED
