#include "mysqlPart.h"
#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>
#include <MYSQL/mysql.h>
#undef main


//fonction pour vider le buffer
void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

//fonction qui ajoute a la structure un individu acteur ou realisateur
People addPeople()
{
    People Person;

    printf("What is his/her surname ?\n");
    gets(Person.prenom);

    printf("What is his/her name ?\n");
    gets(Person.nom);

    printf("Where is he/she born ?\n");
    gets(Person.ville);

    printf("What is his/her birth day ?\n");
    scanf("%d", &Person.jour);
    printf("What is his/her birth month ?\n");
    scanf("%d", &Person.mois);
    printf("What is his/her birth year ?\n");
    scanf("%d", &Person.annee);

    return Person;
}

//initialise un individu
People InitNull()
{
    People Person;

    Person.jour = 1;
    Person.mois = 1;
    Person.annee = 2001;
    Person.ville = "none";
    Person.nom = "No one";
    Person.prenom = "No one";

    return Person;
}

//ajout d un film depuis la console
Film addFilm(Film Film)
{
    int i =0;

    printf("What's the name of your movie ?\n");
    gets(Film.titre);

    printf("What's the release date (year) ?\n");
    scanf("%d", &Film.date);

    viderBuffer();

    printf("Who is the producer ?\n");
    Film.realisateur = addPeople();

    system("cls");

    printf("How many main actors is there ?\n");
    scanf("%d", &Film.nbActeur);

    viderBuffer();

    //initialiser tous les acteurs
    for(i = 0; i < Film.nbActeur; i++)
    {
        printf("Fill the infos for actor n°%d", i+1);
        Film.acteurs[i] = addPeople();
    }


    printf("How long the movie last (in min)?\n");
    scanf("%d", &Film.duree);

    printf("What kind of movie is this ?\n1-Action \n2-Horror \n3-Documentary \n4-Police \n5-Drama \n6-Animation \n7-SF \n");
    do
    {
        printf("Type the number \n");
        scanf("%d", &Film.type);
    }
    while(Film.type < 1 || Film.type > 7);


    return Film;
}
   

//entrer un film dans la BDD
void entrer_Film_BDD(MYSQL mysql, Film Film)
{

    //connection au server
    if(mysql_real_connect(&mysql,"127.0.0.1","root","","film_tp5",0,NULL,0))
    {
        
        //creation de la requete en mySQL --> INSERT
        char requete[150] = "";

        sprintf(requete, "INSERT INTO film VALUES (NULL, '%s', '%d', '%d', '%d', '%d')", Film.titre, Film.date, Film.duree, Film.type, Film.nbActeur);
        
        //envoie de la requete au server
        mysql_query(&mysql, requete);
    }
    else
    {
        //si connection impossible
        printf("Une erreur s'est produite lors de la connexion a la BDD!\n");
    }
}

//ajout d'un individu dans la BDD
void entrer_Realisateur_BDD(MYSQL mysql, People personne)
{

    //connnection à la BDD
    if(mysql_real_connect(&mysql,"127.0.0.1","root","","film_tp5",0,NULL,0))
    {

        //creation de la requete INSERT
        char requete[150] = "";

        sprintf(requete, "INSERT INTO acteurs_realisateurs VALUES (NULL, '%s', '%s', '1998-7-18', '%s')", personne.nom, personne.prenom, personne.ville);
        //envoie de la requete a la BDD
        mysql_query(&mysql, requete);
    }
    else
    {
        //si connection impossible
        printf("Une erreur s'est produite lors de la connexion a la BDD!\n");
    }
}

//afficher la table des individus dans la console
void afficherTable_Acteurs_Realisateurs(MYSQL mysql)
{
    //Afficher une table
    if(mysql_real_connect(&mysql, "127.0.0.1", "root", "", "film_tp5", 0, NULL, 0))
    {

        //Requete : tout selctionner dans la table
        mysql_query(&mysql, "SELECT * FROM acteurs_realisateurs");

        //Declaration objet
        MYSQL_RES *result = NULL;
        MYSQL_ROW row;

        unsigned int i = 0;
        unsigned int num_champs = 0;

        //On met le jeu de resultat dans le pointeur result
        result = mysql_use_result(&mysql);

        //On recupere le nombre de champs
        num_champs = mysql_num_fields(result);

        //Tant qu'il y a encore un résultat ...
        while ((row = mysql_fetch_row(result)))
        {
            //On déclare un pointeur long non signé pour y stocker la taille des valeurs
            unsigned long *lengths;

            //On stocke ces tailles dans le pointeur
            lengths = mysql_fetch_lengths(result);

            //On fait une boucle pour avoir la valeur de chaque champs
            for(i = 0; i < num_champs; i++)
            {
                //On ecrit toutes les valeurs
                printf("[%.*s] ", (int) lengths[i], row[i] ? row[i] : "NULL");
            }
            printf("\n");

        }

        //Liberation du jeu de resultat

        mysql_free_result(result);

    }
    else
    {
        printf("Une erreur s'est produite lors de la connexion a la BDD!\n");
    }

}

//afficher la table film dans la console
void afficherTable_Films(MYSQL mysql)
{
    //Afficher une table
    if(mysql_real_connect(&mysql, "127.0.0.1", "root", "", "film_tp5", 0, NULL, 0))
    {

        //Requete : tout selctionner dans la table
        mysql_query(&mysql, "SELECT * FROM film");

        //Declaration objet
        MYSQL_RES *result = NULL;
        MYSQL_ROW row;

        unsigned int i = 0;
        unsigned int num_champs = 0;

        //On met le jeu de resultat dans le pointeur result
        result = mysql_use_result(&mysql);

        //On recupere le nombre de champs
        num_champs = mysql_num_fields(result);

        //Tant qu'il y a encore un résultat ...
        while ((row = mysql_fetch_row(result)))
        {
            //On déclare un pointeur long non signé pour y stocker la taille des valeurs
            unsigned long *lengths;

            //On stocke ces tailles dans le pointeur
            lengths = mysql_fetch_lengths(result);

            //On fait une boucle pour avoir la valeur de chaque champs
            for(i = 0; i < num_champs; i++)
            {
                //On ecrit toutes les valeurs
                printf("[%.*s] ", (int) lengths[i], row[i] ? row[i] : "NULL");
            }
            printf("\n");

        }

        //Liberation du jeu de resultat

        mysql_free_result(result);

    }
    else
    {
        printf("Une erreur s'est produite lors de la connexion a la BDD!\n");
    }

}

//supprimer un film dans la BDD
void supprimer_Film(MYSQL mysql, Film monFilm)
{

    //connection au server
    if(mysql_real_connect(&mysql, "127.0.0.1", "root", "", "film_tp5", 0, NULL, 0))
    {
        //creation de la requete en mySQL --> DELETE
        char requeteDelete[150] = "";

        sprintf(requeteDelete, "DELETE FROM film where titre = '%s'", monFilm.titre);
        //envoie de la requete au server
        mysql_query(&mysql, requeteDelete);

    }

    else
    {
        //si connection impossible
        printf("Une erreur s'est produite lors de la connexion a la BDD!\n");
    }
}

//supprimer un individu dans la BDD
void supprimer_Acteurs_Realisateurs(MYSQL mysql, People personne)
{

    //connection au server
    if(mysql_real_connect(&mysql, "127.0.0.1", "root", "", "film_tp5", 0, NULL, 0))
    {
        //creation de la requete DELETE
        char requeteDelete[150] = "";

        sprintf(requeteDelete, "DELETE FROM acteurs_realisateurs where nom = '%s'", personne.nom);
        //envoie de la requete
        mysql_query(&mysql, requeteDelete);

    }

    else
    {
        //si connection impossible
        printf("Une erreur s'est produite lors de la connexion a la BDD!\n");
    }

}
