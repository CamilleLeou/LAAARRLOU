#include <stdio.h>
#include <stdlib.h>

typedef struct Film Film;
typedef struct People People;
typedef struct Date Date;

void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

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

People addPeople()
{
    People Person;
    Person.name = malloc(sizeof(char*));
    Person.surname = malloc(sizeof(char*));
    Person.birthplace = malloc(sizeof(char*));

    printf("What is his/her surname ?\n");
    gets(Person.surname);

    printf("What is his/her name ?\n");
    gets(Person.name);

    printf("Where is he/she born ?\n");
    gets(Person.birthplace);

    printf("What is his/her birth day ?\n");
    scanf("%d", &Person.birthday.day);
    printf("What is his/her birth month ?\n");
    scanf("%d", &Person.birthday.month);
    printf("What is his/her birth year ?\n");
    scanf("%d", &Person.birthday.year);

    return Person;
}

People InitNull()
{
    People Person;

    Person.birthday.day = 1;
    Person.birthday.month = 1;
    Person.birthday.year = 2001;
    Person.birthplace = "none";
    Person.name = "No one";
    Person.surname = "No one";

    return Person;
}

Film addFilm(Film Film)
{
    int i =0;
    Film.name = malloc(sizeof(char*));

    printf("What's the name of your movie ?\n");
    gets(Film.name);

    printf("What's the release date (year) ?\n");
    scanf("%d", &Film.date.year);

    viderBuffer();

    printf("Who is the producer ?\n");
    Film.author = addPeople(Film.author);

    system("cls");

    printf("How many main actors is there ?\n");
    scanf("%d", &Film.numberOfActors);

    viderBuffer();

    Film.actors = malloc(Film.numberOfActors*sizeof(People));
    for(i = 0; i < Film.numberOfActors; i++)
    {
        printf("Fill the infos for actor n°%d", i+1);
        Film.actors[i] = addPeople();

        //viderBuffer();
        system("cls");
        //printf("Actor n°%d", i+1);
        //Film.actors[i] = addPeople();
    }

    printf("How long the movie last (in min)?\n");
    scanf("%d", &Film.time);

    printf("What kind of movie is this ?\n1-Action \n2-Horror \n3-Documentary \n4-Police \n5-Drama \n6-Animation \n7-SF \n");
    do
    {
        printf("Type the number \n");
        scanf("%d", &Film.type);
    }while(Film.type < 1 || Film.type > 7);


    return Film;
}

void afficher(Film Film)
{
    int i = 0;
    printf("Movie name : %s \n", Film.name);
    printf("Release date : %d \n", Film.date.year);
    printf("Director : %s %s \n", Film.author.surname, Film.author.name);
    printf("Born in : %d/%d/%d in %s \n", Film.author.birthday.day, Film.author.birthday.month, Film.author.birthday.year, Film.author.birthplace);
    printf("Main actors : \n");

    for(i = 0; i < Film.numberOfActors; i++)
    {
        printf("%s %s \n", Film.actors[i].surname, Film.actors[i].name);
    }

    printf("Movie time : %d \n", Film.time);

    switch(Film.type)
    {
        case 1 : printf("Action");
                 break;
        case 2 : printf("Horror");
                 break;
        case 3 : printf("Doc");
                 break;
        case 4 : printf("Police");
                 break;
        case 5 : printf("Drama");
                 break;
        case 6 : printf("Animation");
                 break;
        case 7 : printf("SF");
                 break;

        default : break;

    }
}

int main()
{
    /*FILE* fichier = NULL;
    fichier = fopen(const char* liste, const char* r+);

    if(fichier == NULL)
    {
        printf("Error \n");
    }
    else
    {

    }

    fclose(fichier); */

    Film Titanic;

    Titanic = addFilm(Titanic);

    system("cls");

    afficher(Titanic);

    return 0;
}
