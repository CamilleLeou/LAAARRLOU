#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#undef main

typedef struct Film Film;
typedef struct People People;
//typedef struct Date Date;

/*struct Date
 {
 char jour[10];
 char mois[10];
 char annee[10];
 };*/

struct People
{
    char nom[20];
    char prenom[20];
    char ville[20];
    char jour[10];
    char mois[10];
    char annee[10];
};


struct Film
{
    char titre[20];
    char date[10];
    char duree[10];
    //char buffer[6];
    int nbActeur;
    People acteurs[4];
    int type;
    People realisateur;
};

char ecrire(char buffer[20], SDL_Surface *ecran, SDL_Surface *fond, int x, int y, int xFond, int yFond, int taille)
{
    int i = 0;
    
    SDL_Color noir = {0, 0, 0};
    TTF_Font *police = NULL;
    police = TTF_OpenFont("Angelina.ttf", taille);
    
    SDL_Surface *texte = NULL, *fleche = NULL;
    SDL_Rect position, positionFond, positionFleche;
    
    fleche = SDL_LoadBMP("fleche.bmp");
    SDL_SetColorKey(fleche, SDL_SRCCOLORKEY, SDL_MapRGB(fleche->format, 255, 255, 255));
    
    position.x = x;     //position de l'écriture
    position.y = y;
    
    positionFond.x = xFond;     //position du fond de saisie
    positionFond.y = yFond;
    
    positionFleche.x = x- 50;
    positionFleche.y = y + 20 ;
    
    SDL_BlitSurface(fleche, NULL, ecran, &positionFleche);
    SDL_Flip(ecran);
    
    SDL_Event event;
    
    i=0;
    while(i < 20)
    {
        
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_KEYUP:
                if(event.key.keysym.sym >= SDLK_a && event.key.keysym.sym <= SDLK_z || event.key.keysym.sym == SDLK_SEMICOLON)
                {
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_q : buffer[i] = 'a';//continuer changement azerty, qwerty
                            break;
                            
                        case SDLK_w : buffer[i] = 'z';
                            break;
                            
                        case SDLK_a : buffer[i] = 'q';
                            break;
                            
                        case SDLK_SEMICOLON : buffer[i] = 'm';
                            break;
                            
                        case SDLK_z : buffer[i] = 'w';
                            break;
                            
                        case SDLK_m : buffer[i] = ';';
                            break;
                            
                        default : buffer[i] = event.key.keysym.sym;
                            break;
                    }
                    //sprintf(buffer, "%c", event.key.keysym.sym);
                    
                    //buffer[i+1] = '\0';
                    i++;
                    
                    if(i <= 20)
                    {
                        //i++;
                        buffer[i]='\0';
                    }
                    
                }
                else if(event.key.keysym.sym == SDLK_SPACE && i > 0)
                {
                    buffer[i] = ' ';
                    i++;
                    
                    if(i < 20)
                    {
                        buffer[i] = '\0';
                    }
                }
                else if(event.key.keysym.sym >= SDLK_0 && event.key.keysym.sym <= SDLK_9)
                {
                    buffer[i] = event.key.keysym.sym;
                    i++;
                    if(i < 20)
                    {
                        buffer[i] = '\0';
                    }
                }
                else if(event.key.keysym.sym == SDLK_ESCAPE)
                {
                    buffer[i] = '\0';
                    i = 21;
                    
                    exit(0);
                    //continuer = 0;
                }
                else if(event.key.keysym.sym == SDLK_BACKSPACE && i>0)
                {
                    buffer[--i]='\0';
                }
                else if(event.key.keysym.sym == SDLK_RETURN)
                {
                    buffer[i] = '\0';
                    
                    /*  texte = TTF_RenderText_Blended(police, buffer, noir);
                     positionZozor.x = 100;
                     positionZozor.y = 100;
                     
                     SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 100, 65, 40));
                     SDL_BlitSurface(texte, NULL, ecran, &positionZozor);    */
                    
                    SDL_FreeSurface(texte);
                    SDL_FreeSurface(ecran);
                    SDL_Flip(ecran);
                    
                    return buffer[20];
                }
                
                texte = TTF_RenderText_Blended(police, buffer, noir);
                
                //  positionDemande.x = x-14;
                //  positionDemande.y = y+2;    //-4
                
                position.x = x;
                position.y = y;
                
                /* positionfleche.x = x-74;
                 positionfleche.y = y;   */
                
                //SDL_BlitSurface(fond, NULL, ecran, &position);
                SDL_BlitSurface(fond, NULL, ecran, &positionFond);
                //SDL_BlitSurface(fleche, NULL, ecran, &positionfleche);
                SDL_BlitSurface(texte, NULL, ecran, &position);
                
                
                SDL_FreeSurface(texte);
                //SDL_FreeSurface(fleche);
                SDL_FreeSurface(ecran);
                SDL_Flip(ecran);
                
                
                break;
                
            case SDL_MOUSEBUTTONUP :
            {
                buffer[i] = '\0';
                
                texte = TTF_RenderText_Blended(police, buffer, noir);
                
                //positionDemande.x = x-14;
                //positionDemande.y = y-4;
                
                position.x = x;
                position.y = y;
                // i = 21;
                // SDL_BlitSurface(fond, NULL, ecran, &position);
                SDL_BlitSurface(fond, NULL, ecran, &positionFond);
                SDL_BlitSurface(texte, NULL, ecran, &position);
                //SDL_Flip(ecran);
                
                
                SDL_FreeSurface(texte);
                SDL_FreeSurface(fond);
                SDL_Flip(ecran);
                
                return buffer[20];
                break;
            }
            default : break;
                
        }   //fin switch
        
    }       //Fin boucle while
    
}

char ecrireChiffre(char chiffre[10], SDL_Surface *ecran, SDL_Surface *fond, int x, int y, int xFond, int yFond, int taille)
{
    int i = 0;
    
    SDL_Event event;
    
    SDL_Color noir = {0, 0, 0};
    TTF_Font *police = NULL;
    police = TTF_OpenFont("Angelina.ttf", taille);
    
    SDL_Surface *texte = NULL, *fleche = NULL;
    SDL_Rect position, positionFond, positionFleche;
    
    fleche = SDL_LoadBMP("fleche.bmp");
    SDL_SetColorKey(fleche, SDL_SRCCOLORKEY, SDL_MapRGB(fleche->format, 255, 255, 255));
    
    position.x = x;
    position.y = y;
    
    positionFond.x = xFond;
    positionFond.y = yFond;
    
    positionFleche.x = x - 50;
    positionFleche.y = y + 5;
    
    
    SDL_BlitSurface(fleche, NULL, ecran, &positionFleche);
    SDL_Flip(ecran);
    
    i=0;
    while(i <= 4)
    {
        SDL_WaitEvent(&event);
        
        switch(event.type)
        {
            case SDL_KEYUP :
                if(event.key.keysym.sym >= SDLK_0 && event.key.keysym.sym <= SDLK_9)
                {
                    chiffre[i] = event.key.keysym.sym;
                    i++;
                    if(i <= 5)
                    {
                        chiffre[i] = '\0';
                    }
                    
                }
                else if(event.key.keysym.sym == SDLK_BACKSPACE && i>0)
                {
                    chiffre[--i]='\0';
                }
                else if(event.key.keysym.sym == SDLK_ESCAPE)
                {
                    chiffre[i] = '\0';
                    
                    texte = TTF_RenderText_Blended(police, chiffre, noir);
                    
                    //positionDemande.x = x-9;    //-9
                    //positionDemande.y = y-6;
                    
                    position.x = x;
                    position.y = y;
                    
                    
                    SDL_BlitSurface(fond, NULL, ecran, &positionFond);
                    SDL_BlitSurface(fleche, NULL, ecran, &positionFleche);
                    SDL_BlitSurface(texte, NULL, ecran, &position);
                    
                    SDL_FreeSurface(texte);
                    //SDL_FreeSurface(rectangle);
                    SDL_FreeSurface(ecran);
                    
                    SDL_Flip(ecran);
                    
                    return chiffre[10];
                    
                }
                else if(event.key.keysym.sym == SDLK_RETURN)
                {
                    chiffre[i] = '\0';
                    
                    
                    SDL_FreeSurface(texte);
                    SDL_FreeSurface(ecran);
                    SDL_Flip(ecran);
                    
                    return chiffre[10];
                }
                
                texte = TTF_RenderText_Blended(police, chiffre, noir);
                
                // positionDemande.x = x-9;    //-9
                // positionDemande.y = y-6;
                
                position.x = x;
                position.y = y;
                
                SDL_BlitSurface(fond, NULL, ecran, &positionFond);
                SDL_BlitSurface(fleche, NULL, ecran, &positionFleche);
                SDL_BlitSurface(texte, NULL, ecran, &position);
                
                SDL_FreeSurface(texte);
                //SDL_FreeSurface(rectangle);
                SDL_FreeSurface(ecran);
                
                SDL_Flip(ecran);
                
                break;
                
            case SDL_MOUSEBUTTONUP :
            {
                chiffre[i] = '\0';
                
                texte = TTF_RenderText_Blended(police, chiffre, noir);
                
                //  positionDemande.x = x-14;
                // positionDemande.y = y-4;
                
                position.x = x;
                position.y = y;
                // i = 21;
                // SDL_BlitSurface(fond, NULL, ecran, &position);
                SDL_BlitSurface(fond, NULL, ecran, &positionFond);
                SDL_BlitSurface(texte, NULL, ecran, &position);
                //SDL_Flip(ecran);
                
                
                SDL_FreeSurface(texte);
                SDL_FreeSurface(fond);
                SDL_Flip(ecran);
                
                return chiffre[10];
                break;
            }
                
            default : break;
        }
    }
    
    return chiffre[10];
}

char ecrireDate(char chiffre[10], SDL_Surface *ecran, SDL_Surface *fond, int x, int y, int xFond, int yFond, int taille)
{
    int i = 0;
    
    SDL_Event event;
    
    SDL_Color noir = {0, 0, 0};
    TTF_Font *police = NULL;
    police = TTF_OpenFont("Angelina.ttf", taille);
    
    SDL_Surface *texte = NULL, *fleche = NULL;
    SDL_Rect position, positionFond, positionFleche;
    
    fleche = SDL_LoadBMP("fleche.bmp");
    SDL_SetColorKey(fleche, SDL_SRCCOLORKEY, SDL_MapRGB(fleche->format, 255, 255, 255));
    
    position.x = x;
    position.y = y;
    
    positionFond.x = xFond;
    positionFond.y = yFond;
    
    positionFleche.x = x - 50;
    positionFleche.y = y + 5;
    
    
    SDL_BlitSurface(fleche, NULL, ecran, &positionFleche);
    SDL_Flip(ecran);
    
    i=0;
    while(i < 2)
    {
        SDL_WaitEvent(&event);
        
        switch(event.type)
        {
            case SDL_KEYUP :
                if(event.key.keysym.sym >= SDLK_0 && event.key.keysym.sym <= SDLK_9)
                {
                    chiffre[i] = event.key.keysym.sym;
                    i++;
                    if(i <= 2)
                    {
                        chiffre[i] = '\0';
                    }
                    
                }
                else if(event.key.keysym.sym == SDLK_BACKSPACE && i>0)
                {
                    chiffre[--i]='\0';
                }
                else if(event.key.keysym.sym == SDLK_ESCAPE)
                {
                    chiffre[i] = '\0';
                    
                    texte = TTF_RenderText_Blended(police, chiffre, noir);
                    
                    //positionDemande.x = x-9;    //-9
                    //positionDemande.y = y-6;
                    
                    position.x = x;
                    position.y = y;
                    
                    
                    SDL_BlitSurface(fond, NULL, ecran, &positionFond);
                    SDL_BlitSurface(fleche, NULL, ecran, &positionFleche);
                    SDL_BlitSurface(texte, NULL, ecran, &position);
                    
                    SDL_FreeSurface(texte);
                    //SDL_FreeSurface(rectangle);
                    SDL_FreeSurface(ecran);
                    
                    SDL_Flip(ecran);
                    
                    return chiffre[10];
                    
                }
                else if(event.key.keysym.sym == SDLK_RETURN)
                {
                    chiffre[i] = '\0';
                    
                    
                    SDL_FreeSurface(texte);
                    SDL_FreeSurface(ecran);
                    SDL_Flip(ecran);
                    
                    return chiffre[10];
                }
                
                texte = TTF_RenderText_Blended(police, chiffre, noir);
                
                // positionDemande.x = x-9;    //-9
                // positionDemande.y = y-6;
                
                position.x = x;
                position.y = y;
                
                SDL_BlitSurface(fond, NULL, ecran, &positionFond);
                SDL_BlitSurface(fleche, NULL, ecran, &positionFleche);
                SDL_BlitSurface(texte, NULL, ecran, &position);
                
                SDL_FreeSurface(texte);
                //SDL_FreeSurface(rectangle);
                SDL_FreeSurface(ecran);
                
                SDL_Flip(ecran);
                
                break;
                
            case SDL_MOUSEBUTTONUP :
            {
                chiffre[i] = '\0';
                
                texte = TTF_RenderText_Blended(police, chiffre, noir);
                
                //  positionDemande.x = x-14;
                // positionDemande.y = y-4;
                
                position.x = x;
                position.y = y;
                // i = 21;
                // SDL_BlitSurface(fond, NULL, ecran, &position);
                SDL_BlitSurface(fond, NULL, ecran, &positionFond);
                SDL_BlitSurface(texte, NULL, ecran, &position);
                //SDL_Flip(ecran);
                
                
                SDL_FreeSurface(texte);
                SDL_FreeSurface(fond);
                SDL_Flip(ecran);
                
                return chiffre[10];
                break;
            }
                
            default : break;
        }
    }
    
    return chiffre[10];
}

int dansZone(SDL_Event event, int x, int y, int x2, int y2)
{
    if(event.button.x >= x && event.button.x <= x2 && event.button.y >= y && event.button.y <= y2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int saisieType(SDL_Event event, SDL_Surface *ecran)
{
    // SDL_Event event;
    SDL_Surface *tick = NULL, *typeFilm = NULL, *next = NULL;
    SDL_Rect positionTick, position, positionnext;
    // int continuer = 1;
    
    typeFilm = SDL_LoadBMP("typeFilm.bmp");
    tick = SDL_LoadBMP("tick.bmp");
    next = SDL_LoadBMP("next.bmp");
    
    SDL_SetColorKey(tick, SDL_SRCCOLORKEY, SDL_MapRGB(tick->format, 255, 255, 255));
    SDL_SetColorKey(next, SDL_SRCCOLORKEY, SDL_MapRGB(next->format, 255, 255, 255));
    
    position.x = 0;
    position.y = 0;
    
    positionTick.x = event.button.x - 15;
    positionTick.y = event.button.y - 15;
    
    positionnext.x = 945;
    positionnext.y = 540;
    
    SDL_BlitSurface(typeFilm, NULL, ecran, &position);
    SDL_Flip(ecran);
    
    //while(continuer)
    //{
    //    SDL_WaitEvent(&event);
    
    
    
    // switch(event.type)
    // {
    //  case SDL_MOUSEBUTTONUP :
    if(dansZone(event, 198, 128, 214, 233) == 1)
    {
        SDL_BlitSurface(tick, NULL, ecran, &positionTick);
        SDL_BlitSurface(next, NULL, ecran, &positionnext);
        SDL_Flip(ecran);
        return 1;
    }
    else if(dansZone(event, 197, 177, 214, 292) == 1)
    {
        SDL_BlitSurface(tick, NULL, ecran, &positionTick);
        SDL_BlitSurface(next, NULL, ecran, &positionnext);
        SDL_Flip(ecran);
        return 2;
    }
    else if(dansZone(event, 198, 335, 214, 350) == 1)
    {
        SDL_BlitSurface(tick, NULL, ecran, &positionTick);
        SDL_BlitSurface(next, NULL, ecran, &positionnext);
        SDL_Flip(ecran);
        return 3;
    }
    else if(dansZone(event, 197, 388, 214, 402) == 1)
    {
        SDL_BlitSurface(tick, NULL, ecran, &positionTick);
        SDL_BlitSurface(next, NULL, ecran, &positionnext);
        SDL_Flip(ecran);
        return 4;
    }
    else if(dansZone(event, 631, 244, 649, 258) == 1)
    {
        SDL_BlitSurface(tick, NULL, ecran, &positionTick);
        SDL_BlitSurface(next, NULL, ecran, &positionnext);
        SDL_Flip(ecran);
        return 5;
    }
    else if(dansZone(event, 631, 308, 648, 322) == 1)
    {
        SDL_BlitSurface(tick, NULL, ecran, &positionTick);
        SDL_BlitSurface(next, NULL, ecran, &positionnext);
        SDL_Flip(ecran);
        return 6;
    }
    else if(dansZone(event, 631, 314, 648, 385) == 1)
    {
        SDL_BlitSurface(tick, NULL, ecran, &positionTick);
        SDL_BlitSurface(next, NULL, ecran, &positionnext);
        SDL_Flip(ecran);
        return 7;
    }
    //  }   //fin while
    
    
    //}
    
}

People personne(SDL_Surface *ecran, int typePersonne, People humain)
{
    SDL_Surface *fond = NULL, *caseNom = NULL, *caseDate = NULL, *caseAnnee = NULL, *lieuDeNaissance = NULL;// *next = NULL;
    
    SDL_Rect position;// positionnext;
    
    SDL_Event event;
    int continuer = 1;
    int nomOK = 0, prenomOK = 0, lieuOK = 0, jourOK = 0, moisOK = 0, anneeOK = 0;
    
    caseNom = SDL_LoadBMP("caseRealisateur.bmp");
    lieuDeNaissance = SDL_LoadBMP("caseLieu.bmp");
    caseDate = SDL_LoadBMP("caseDate.bmp");
    caseAnnee = SDL_LoadBMP("annee.bmp");
    //next = SDL_LoadBMP("next.bmp");
    
    //SDL_SetColorKey(next, SDL_SRCCOLORKEY, SDL_MapRGB(next->format, 255, 255, 255));
    
    position.x = 0;
    position.y = 0;
    
    //  positionnext.x = 945;  //Définir les positions
    // positionnext.y = 540;
    
    if(typePersonne == 1)
    {
        fond = SDL_LoadBMP("rea.bmp");
        SDL_BlitSurface(fond, NULL, ecran, &position);
        SDL_Flip(ecran);
        
        while(continuer)
        {
            SDL_WaitEvent(&event);
            
            switch(event.type)
            {
                case SDL_QUIT : exit(0);
                    break;
                    
                case SDL_MOUSEBUTTONUP :
                    if(dansZone(event, 109, 270, 349, 336) == 1)
                    {
                        humain.prenom[20] = ecrire(humain.prenom, ecran, caseNom, 113, 273, 109, 270, 60);
                        prenomOK = 1;
                    }
                    else if(dansZone(event, 623, 268, 868, 324) == 1)
                    {
                        humain.nom[20] = ecrire(humain.nom, ecran, caseNom, 628, 273, 623, 268, 60);
                        nomOK = 1;
                    }
                    else if(dansZone(event, 299, 388, 658, 454) == 1)
                    {
                        humain.ville[20] = ecrire(humain.ville, ecran, lieuDeNaissance, 303, 394, 299, 388, 60);
                        lieuOK = 1;
                    }
                    else if(dansZone(event, 280, 499, 352, 552) == 1)
                    {
                        humain.jour[10] = ecrireDate(humain.jour, ecran, caseDate, 284, 504, 280, 499, 60);
                        jourOK = 1;
                    }
                    else if(dansZone(event, 417, 498, 490, 552) == 1)
                    {
                        humain.mois[10] = ecrireDate(humain.mois, ecran, caseDate, 423, 504, 417, 498, 60);
                        moisOK = 1;
                    }
                    else if(dansZone(event, 551, 497, 681, 551) == 1)
                    {
                        humain.annee[10] = ecrireChiffre(humain.annee, ecran, caseAnnee, 556, 504, 551, 497, 60);
                        anneeOK = 1;
                    }
                    
                    if(nomOK == 1 && prenomOK == 1 && lieuOK == 1 && jourOK == 1 && moisOK == 1 && anneeOK == 1)
                    {
                        return humain;
                        continuer = 0;
                        
                    }
                    
                    break;
                default : break;
            }//fin switch
        }//fin while
    }
    else
    {
        
    }
}

int saisieNbActeurs(SDL_Event event, SDL_Surface *ecran)
{
    //SDL_Event event;
    SDL_Surface *tick = NULL, *fond = NULL, *next = NULL, *zozor = NULL;
    SDL_Rect positionTick, position, positionnext, positionZozor;
    //int continuer = 1;
    
    zozor = SDL_LoadBMP("zozor.bmp");
    fond = SDL_LoadBMP("nb_acteurs.bmp");
    tick = SDL_LoadBMP("tick.bmp");
    next = SDL_LoadBMP("next.bmp");
    
    SDL_SetColorKey(tick, SDL_SRCCOLORKEY, SDL_MapRGB(tick->format, 255, 255, 255));
    SDL_SetColorKey(next, SDL_SRCCOLORKEY, SDL_MapRGB(next->format, 255, 255, 255));
    
    positionZozor.x = 0;
    positionZozor.y = 0;
    
    position.x = 0;
    position.y = 0;
    
    positionTick.x = event.button.x - 15;
    positionTick.y = event.button.y - 15;
    
    positionnext.x = 945;
    positionnext.y = 540;
    
    SDL_BlitSurface(fond, NULL, ecran, &position);
    SDL_Flip(ecran);
    
    //while(continuer)
    //{
    //SDL_WaitEvent(&event);
    
    //switch(event.type)
    //{
    // case SDL_MOUSEBUTTONUP :
    
    
    if(dansZone(event, 223, 336, 241, 350) == 1)
    {
        SDL_BlitSurface(tick, NULL, ecran, &positionTick);
        SDL_BlitSurface(next, NULL, ecran, &positionnext);
        SDL_Flip(ecran);
        return 1;
    }
    else if(dansZone(event, 400, 336, 416, 350) == 1)
    {
        SDL_BlitSurface(tick, NULL, ecran, &positionTick);
        SDL_BlitSurface(next, NULL, ecran, &positionnext);
        SDL_Flip(ecran);
        return 2;
    }
    else if(dansZone(event, 557, 335, 572, 350) == 1)
    {
        SDL_BlitSurface(tick, NULL, ecran, &positionTick);
        SDL_BlitSurface(next, NULL, ecran, &positionnext);
        SDL_Flip(ecran);
        return 3;
    }
    else if(dansZone(event, 703, 335, 717, 350) == 1)
    {
        SDL_BlitSurface(tick, NULL, ecran, &positionTick);
        SDL_BlitSurface(next, NULL, ecran, &positionnext);
        SDL_Flip(ecran);
        return 4;
    }
    else if(dansZone(event, 465, 435, 481, 448) == 1)
    {
        SDL_BlitSurface(tick, NULL, ecran, &positionTick);
        SDL_BlitSurface(next, NULL, ecran, &positionnext);
        SDL_Flip(ecran);
        return 0;
    }
    
    
    // }   //fin while
    
    
    //}
    return -1;
    
}

Film ajouterFilm(Film film)
{
    //Film Film;
    film.type = 0;
    film.nbActeur = 0;
    int continuer = 1, continuer1 = 1, continuer2 = 1, continuer3 = 1, continuer4 = 1;
    int i = 0; //compteur pour les acteurs
    
    int titreOK = 0, dateOK = 0, dureeOK = 0, typeOK = 0, nomOK = 0, prenomOK = 0, reaOK = 0, nbOK = 0;
    
    SDL_Surface *ecran = NULL, *ajouterFilm = NULL, *zozor = NULL, *typeFilm = NULL, *next = NULL, *acteur = NULL, *caseNom = NULL; //, *texte = NULL; // *imageDeFond = NULL;
    SDL_Surface *rectangle = NULL, *casePage1 = NULL;
    SDL_Rect position, positionZozor, positionnext; //, position;
    TTF_Init();                                     //on initialise la SDL qui permet d'afficher du text
    //   SDL_EnableUNICODE(SDL_ENABLE);
    SDL_Color noir = {0, 0, 0};
    
    position.x = 0;
    position.y = 0;
    
    positionZozor.x = 100;
    positionZozor.y = 100;
    
    positionnext.x = 945;  //Définir les positions
    positionnext.y = 540;
    
    
    
    SDL_Event event, event2, event3, event4, event5;
    
    TTF_Font *police = NULL;
    police = TTF_OpenFont("Angelina.ttf", 50);
    
    ecran = SDL_SetVideoMode(1024, 576, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    next = SDL_LoadBMP("next.bmp");
    typeFilm = SDL_LoadBMP("typeFilm.bmp");
    zozor = SDL_LoadBMP("zozor.bmp");
    rectangle = SDL_LoadBMP("titre.bmp");
    casePage1 = SDL_LoadBMP("case.bmp");
    acteur = SDL_LoadBMP("acteur.bmp");
    caseNom = SDL_LoadBMP("caseRealisateur.bmp");
    
    SDL_SetColorKey(next, SDL_SRCCOLORKEY, SDL_MapRGB(next->format, 255, 255, 255));
    
    if(ecran == NULL) //On v�rifie que la SDL s'ouver bien
    {
        printf("Erreur dans le chargement de la SDL : %s \n", SDL_GetError()); //On affiche le code erreur en cas d'erreur
        
        exit(EXIT_FAILURE);
    }
    
    //SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 100, 65, 40));
    SDL_WM_SetCaption("BEST PROGRAM EVER", NULL);
    
    
    /* Chargement d'une image Bitmap dans une surface */
    
    ajouterFilm = SDL_LoadBMP("ajouter.bmp");
    
    /* On blitte par-dessus l'�cran */
    
    SDL_BlitSurface(ajouterFilm, NULL, ecran, &position);
    
    SDL_Flip(ecran);        //On rafraichit l'écran
    
    
    
    while(continuer)
    {
        SDL_WaitEvent(&event);
        
        switch(event.type)
        {
            case SDL_QUIT: continuer = 0;
                break;
                
            case SDL_MOUSEBUTTONUP:
                // test = TTF_RenderText_Blended(police, "Oooooooh", noir);
                // SDL_BlitSurface(test, NULL, ecran, &position);
                // SDL_Flip(ecran);
                if(dansZone(event, 222, 111, 800, 280) == 1)
                {
                    film.titre[20] = ecrire(film.titre, ecran, rectangle, 236, 210, 222, 212, 70);
                    //saisie(Film.titre, ecran, 236, 210, 70);
                    titreOK = 1;
                }
                else if(dansZone(event, 67, 371, 352, 425) == 1)
                {
                    film.date[10] = ecrireChiffre(film.date, ecran, casePage1, 76, 377, 67, 371, 60);
                    //saisie2(Film.date, ecran, 76, 377, 60);
                    dateOK = 1;
                }
                else if(dansZone(event, 621, 373, 906, 426) == 1)
                {
                    film.duree[10] = ecrireChiffre(film.duree, ecran, casePage1, 630, 379, 621, 373, 60);
                    //saisie2(Film.duree, ecran, 630, 379, 60);
                    dureeOK = 1;
                }
                
                
                if(titreOK == 1 && dateOK == 1 && dureeOK == 1)
                {
                    SDL_BlitSurface(next, NULL, ecran, &positionnext);
                    SDL_Flip(ecran);
                    
                    if(dansZone(event, 932, 545, 1021, 573) == 1)
                    {
                        continuer = 0;
                    }
                    
                }
                //continuer = 1;
                break;
                
            case SDL_KEYUP : if(event.key.keysym.sym == SDLK_ESCAPE)
            {
                exit(0);
            }
                break;
                
                
                /*      buffer[i] = event.key.keysym.sym;
                 if(buffer[i] == 'a')
                 {
                 positionZozor.x = 0;
                 positionZozor.y = 0;
                 }   */
                
            default: break;
                
        }
        
        //SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 100, 65, 40));
        //SDL_BlitSurface(zozor, NULL, ecran, &positionZozor);
        //SDL_Flip(ecran);
        
    }   // accolade du while général
    
    
    
    //Film.type = 0;
    while(continuer1)
    {
        SDL_WaitEvent(&event2);
        
        //SDL_BlitSurface(zozor, NULL, ecran, &positionZozor);
        //SDL_Flip(ecran);
        
        switch(event2.type)
        {
            case SDL_QUIT : continuer1 = 0;
                break;
                
            case SDL_MOUSEBUTTONUP :
                if(film.type != 0 && dansZone(event2, 932, 545, 1021, 573) == 1)
                {
                    //SDL_BlitSurface(zozor, NULL, ecran, &positionZozor);
                    //SDL_Flip(ecran);
                    continuer1 = 0;
                }
                else
                {
                    film.type = saisieType(event2, ecran);
                }
                
                
                break;
                
        }   //accolade du switch
        
    }
    
    film.realisateur = personne(ecran, 1, film.realisateur);
    reaOK = 1;
    SDL_BlitSurface(next, NULL, ecran, &positionnext);
    SDL_Flip(ecran);
    
    while(continuer2)
    {
        
        
        SDL_WaitEvent(&event3);
        
        switch(event3.type)
        {
            case SDL_QUIT : continuer2 = 0;
                break;
                
            case SDL_MOUSEBUTTONUP :
                if(reaOK == 1)
                {
                    if(dansZone(event3, 932, 545, 1021, 573) == 1)
                    {
                        
                        continuer2 = 0;
                    }
                }
                
                
                break;
                
        }
        
    }
    
    if(film.type != 6)
    {
        while(continuer3)
        {
            SDL_WaitEvent(&event4);
            
            switch(event4.type)
            {
                case SDL_QUIT : exit(0);
                    break;
                    
                case SDL_MOUSEBUTTONUP :
                    
                    
                    
                    if( nbOK != 0 &&dansZone(event4, 932, 545, 1021, 573) == 1)
                    {
                        //SDL_BlitSurface(zozor, NULL, ecran, &positionZozor);
                        //SDL_Flip(ecran);
                        continuer3 = 0;
                    }
                    else
                    {
                        film.nbActeur = saisieNbActeurs(event4, ecran);
                        nbOK = 1;
                    }
                    break;
                    
            }   //accolade du switch
        }//fin while 1
    } //fin if
    else
    {
        film.nbActeur = 0;
    }
    
    
    if(film.nbActeur != 0)
    {
        SDL_BlitSurface(acteur, NULL, ecran, &position);
        SDL_Flip(ecran);
        //while(continuer4)
        //{
        while(i < film.nbActeur)
        {
            
            SDL_WaitEvent(&event5);
            
            switch(event5.type)
            {
                case SDL_QUIT : exit(0);
                    break;
                    
                case SDL_MOUSEBUTTONUP :
                    if(dansZone(event5, 108, 270, 349, 337) == 1)
                    { //Changer fond si besoin
                        film.acteurs[i].prenom[20] = ecrire(film.acteurs[i].prenom, ecran, caseNom, 116, 275, 109, 270, 60);
                        prenomOK = 1;
                    }
                    else if(dansZone(event5, 624, 269, 868, 334) == 1)
                    {
                        film.acteurs[i].nom[20] = ecrire(film.acteurs[i].nom, ecran, caseNom, 623, 275, 624, 269, 60);
                        nomOK = 1;
                    }
                    
                    if(prenomOK == 1 && nomOK == 1)
                    {
                        SDL_BlitSurface(next, NULL, ecran, &positionnext);
                        SDL_Flip(ecran);
                        
                        if(dansZone(event5, 932, 545, 1021, 573) == 1)
                        {
                            nomOK = 0;
                            prenomOK = 0;
                            i++;
                            SDL_BlitSurface(acteur, NULL, ecran, &position);
                            SDL_Flip(ecran);
                        }
                        
                    }//Fin if OK
                    
                    
            }//Fin switch
        }//Fin while 2
        
        //}//fin while 1
    }
    return film;
    SDL_FreeSurface(ajouterFilm);
    SDL_FreeSurface(zozor);
    SDL_FreeSurface(typeFilm);
    //SDL_EnableUNICODE(SDL_DISABLE);
    TTF_CloseFont(police);
    TTF_Quit();
    SDL_Quit(); //On ferme la SDL
}

void afficherFilm(Film film)
{
    SDL_Surface *ecran = NULL, *fond = NULL;
    SDL_Surface *titre = NULL, *duree = NULL, *date = NULL;
    SDL_Surface *reaNom = NULL, *reaPrenom = NULL, *reaVille = NULL, *reaJour = NULL, *reaMois = NULL, *reaAnnee = NULL;
    SDL_Surface *type = NULL;
    SDL_Surface *acteurNom = NULL, *acteurPrenom = NULL;
    
    SDL_Rect position, positionTitre, positionDuree, positionDate;
    SDL_Rect positionreaNom, positionreaPrenom, positionreaVille, positionreaJour, positionreaMois, positionreaAnnee;
    SDL_Rect positionType;
    SDL_Rect positionActeurNom, positionActeurPrenom;
    
    TTF_Init();
    SDL_Color noir = {0, 0, 0};
    TTF_Font *police = NULL;
    police = TTF_OpenFont("Angelina.ttf", 50);
    
    ecran = SDL_SetVideoMode(1024, 576, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    fond = SDL_LoadBMP("affichage.bmp");
    
    position.x = 0;
    position.y = 0;
    
    positionTitre.x = 369;
    positionTitre.y = 151;
    
    positionDuree.x = 485;
    positionDuree.y = 263;
    
    positionDate.x = 65;
    positionDate.y = 259;
    
    positionreaNom.x = 2;
    positionreaNom.y = 368;
    
    positionreaPrenom.x = 253;
    positionreaPrenom.y = 368;
    
    positionreaVille.x = 765;
    positionreaVille.y = 379;
    
    positionreaJour.x = 459;
    positionreaJour.y = 364;
    
    positionreaMois.x = 544;
    positionreaMois.y = 364;
    
    positionreaAnnee.x = 635;
    positionreaAnnee.y = 364;
    
    positionType.x = 769;
    positionType.y = 164;
    
    titre = TTF_RenderText_Blended(police, film.titre, noir);
    duree = TTF_RenderText_Blended(police, film.duree, noir);
    date = TTF_RenderText_Blended(police, film.date, noir);
    reaNom = TTF_RenderText_Blended(police, film.realisateur.nom, noir);
    reaPrenom = TTF_RenderText_Blended(police, film.realisateur.prenom, noir);
    reaVille = TTF_RenderText_Blended(police, film.realisateur.ville, noir);
    reaJour = TTF_RenderText_Blended(police, film.realisateur.jour, noir);
    reaMois = TTF_RenderText_Blended(police, film.realisateur.mois, noir);
    reaAnnee = TTF_RenderText_Blended(police, film.realisateur.annee, noir);
    
    switch(film.type)
    {
        case 1 : type = TTF_RenderText_Blended(police, "action", noir);
            break;
        case 2 : type = TTF_RenderText_Blended(police, "horreur", noir);
            break;
        case 3 : type = TTF_RenderText_Blended(police, "documentaire", noir);
            break;
        case 4 : type = TTF_RenderText_Blended(police, "policier", noir);
            break;
        case 5 : type = TTF_RenderText_Blended(police, "drama", noir);
            break;
        case 6 : type = TTF_RenderText_Blended(police, "animation", noir);
            break;
        case 7 : type = TTF_RenderText_Blended(police, "Science-fiction", noir);
            break;
        default : break;
    }
    
    SDL_BlitSurface(fond, NULL, ecran, &position);
    SDL_BlitSurface(titre, NULL, ecran, &positionTitre);
    SDL_BlitSurface(duree, NULL, ecran, &positionDuree);
    SDL_BlitSurface(date, NULL, ecran, &positionDate);
    SDL_BlitSurface(reaNom, NULL, ecran, &positionreaNom);
    SDL_BlitSurface(reaPrenom, NULL, ecran, &positionreaPrenom);
    SDL_BlitSurface(reaVille, NULL, ecran, &positionreaVille);
    SDL_BlitSurface(reaJour, NULL, ecran, &positionreaJour);
    SDL_BlitSurface(reaMois, NULL, ecran, &positionreaMois);
    SDL_BlitSurface(reaAnnee, NULL, ecran, &positionreaAnnee);
    SDL_BlitSurface(type, NULL, ecran, &positionType);
    
    SDL_Flip(ecran);
    
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
    
    
}

int main ( int argc, char** argv)
{
    Film film;
    
    
    
    //SDL_Event event;*/
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
    
    //afficherFilm(film);
    
    
    //actions();
    
    
    return EXIT_SUCCESS;
}
