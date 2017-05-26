#include <fstream>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include <string>
#include <stdlib.h>     // srand, rand
#include <time.h>       // time
#include "SDL/SDL_ttf.h"

using namespace std;

//<FUNCTII>
void meniu(); void joc(); void gen(); void scoate();
void elim(int poz1, int poz2); void afis_combo();
void dategen(); void scoruri(); void ajutor(); void pauza();
void power_up(); void scoate_power_up(); void game_over();
void aplica_imagine3(int x, int y, SDL_Surface*sursa, SDL_Surface*destinatie);
SDL_Surface*incarca_imagine(string nume_img);//functia de incarcare imagine
//functia pentru a lipi o imagine pe screen
void aplica_imagine(int x, int y, SDL_Surface*sursa, SDL_Surface*destinatie);
//functia pentru a lipi o portiune din imagine pe screen
void aplica_imagine2(int x, int y, SDL_Surface*sursa, SDL_Surface*destinatie);
//functie pentru a lipi o imagine la anumite coordonate
void aplica_imagine3(int x, int y, SDL_Surface*sursa, SDL_Surface*destinatie);
void pune_cursor(int a, int b);
void inchide_sdl(); void intro(); void ajutor();
void loadhighscore(); void highscore();
void load_files(); void eliberare_suprafete_joc(); void load_files_joc();
void citeste_nume(); void scrie(char v);
void generare_scoruri();
//</FUNCTII>


using namespace std;
//<IMAGINI>
SDL_Surface *screen=NULL;//ecranul
SDL_Surface *glow=NULL;
SDL_Surface *leftglow=NULL;
SDL_Surface *rightglow=NULL;
SDL_Surface *xglow=NULL;
SDL_Surface *scor=NULL;
SDL_Surface *mtl=NULL;
SDL_Surface *msc=NULL;
SDL_Surface *timeleft=NULL;
SDL_Surface *cartita=NULL;
SDL_Surface *power_up_timp=NULL;
SDL_Surface *timpfuu=NULL;
SDL_Surface *power_up_puncte=NULL;
SDL_Surface *punctefuu=NULL;
SDL_Surface *combo0=NULL;
SDL_Surface *combo2=NULL;
SDL_Surface *combo5=NULL;
SDL_Surface *combo8=NULL;
SDL_Surface *combo12=NULL;
SDL_Surface *combo15=NULL;
SDL_Surface *combo20=NULL;
SDL_Surface *combo30=NULL;
SDL_Surface *bomba=NULL;
SDL_Surface *bombafuu=NULL;
SDL_Surface *fundal_meniu=NULL;
SDL_Surface *fundal_ajutor=NULL;
SDL_Surface *fundal_joc=NULL;
SDL_Surface *ciocan=NULL;
SDL_Surface *ciocan2=NULL;
SDL_Surface *cartitafuu=NULL;
SDL_Surface *chuck=NULL;
SDL_Surface *chuckfuu=NULL;
SDL_Surface *transparenta=NULL;
SDL_Surface *soundon=NULL;
SDL_Surface *soundoff=NULL;
SDL_Surface *fundal_gameover=NULL;
SDL_Surface *instructiuni=NULL;
SDL_Surface *fundal_powerups=NULL;
SDL_Surface *fundal_scoruri=NULL;
SDL_Surface*p1=NULL;
SDL_Surface*p2=NULL;
SDL_Surface*p3=NULL;
//</IMAGINI>

TTF_Font*font=NULL;
TTF_Font*font2=NULL;

//<SUNETE>
Mix_Music*muzica_meniu=NULL;
Mix_Music*muzica_joc=NULL;
Mix_Chunk*cartita_hit=NULL;
Mix_Chunk*bomba_hit=NULL;
Mix_Chunk*chuck_hit=NULL;
Mix_Chunk*chuck_hit3=NULL;
Mix_Chunk*puncte_hit=NULL;
Mix_Chunk*timp_hit=NULL;
Mix_Music*muzica_gameover;
//</SUNETE>

//<DECLARATII
int scorhigh, lgnume;
long long int tpower, tscoatere_cartite, tscoatere_powerup, lastchuck, tref, soprit, tgen, powert, t;
short int x, y, q, r, ci, cj, miss, gauri, cartite_lovite;
short int a, b, gata, nrgen, succesive;
SDL_Event event;
long long int ttotal=31000;
short int matr[10][10];
short int pozx[10];
int i, j, xpos, ypos;
char st[10], sc[10], numejucator[20], sunet, pause, sc2[20], fost_ajutor, litera;
char numejucatorinitial[15];
short int pozy[10], lovit=0;
long long int timp[10][10], ceva;
long long int timp_power_up[10][10];
char pctj1[40], pctj2[40], pctj3[40], pctj4[40], pctj5[40];
short int lg1, lg2, lg3, lg4, lg5;

struct pachet{
int puncte;
char numejucator[15];
};
pachet auxiliar, player, jucatori[7];
//</DECLARATII>

int main (int argc, char* args[])
{
    //<DIMENISUNI>
    pozx[1]=100;
    pozy[1]=150;
    for (i=2; i<=5; i++)
        pozx[i]=pozx[i-1]+160;
    for (i=2; i<=4; i++)
        pozy[i]=pozy[i-1]+112;
    //</DIMENSIUNI>
    SDL_Init(SDL_INIT_EVERYTHING);//initializez totul

    //<TTF>
    TTF_Init();
    font=TTF_OpenFont( "vinque.ttf", 30 );
    font2=TTF_OpenFont( "comicsans.ttf", 48 );
    SDL_Color textColor = {186,102,0};
    mtl=TTF_RenderText_Solid( font, "Timp ramas: ", textColor );
    msc=TTF_RenderText_Solid( font, "Scor: ", textColor );
    //</TTF>

    Mix_OpenAudio (22050, MIX_DEFAULT_FORMAT, 2, 4096);//SUNET
    srand (time(NULL));
    screen=SDL_SetVideoMode(1000, 750, 32, SDL_SWSURFACE|SDL_FULLSCREEN);
    SDL_WM_SetCaption("SmashTheMole",NULL);
    intro();
    citeste_nume();
    load_files();
    meniu();//initializez meniul
    inchide_sdl();
    return 0;
}

void meniu()
{
gata=0; sunet=1;
Mix_PlayMusic(muzica_meniu,-1);
SDL_ShowCursor(0);
while(1)
    {
    pune_cursor(0,1);
    if (Mix_PausedMusic()==1 && sunet==1)//daca e sound on
        Mix_ResumeMusic();
        else
        if (Mix_PlayingMusic()==1 && sunet==-1)//daca e sound off
            Mix_PauseMusic();
    while (SDL_PollEvent(&event))//verific evenimentele
        if (event.type==SDL_MOUSEBUTTONDOWN)
        {
            if ( event.button.button == SDL_BUTTON_LEFT )
            {
            //testez aria unde a apasat
            x = event.button.x;
            y = event.button.y;
            pune_cursor(1,1);
            if (x>=360 && x<=360+270)
                {
                if (y>=268 && y<=350)
                {
                    //stop muzica
                    Mix_HaltMusic();
                    joc();
                    for (i=1; i<=4; i++)
                        for (j=1; j<=5; j++)
                            {
                                matr[i][j]=0;
                                timp[i][j]=0;
                            }
                    if (sunet)
                        Mix_PlayMusic(muzica_meniu,-1);
                }
                    else
                    if(y>=377 && y<=458)
                        scoruri();
                        else
                        if(y>=487 && y<=565)
                            ajutor();
                            else
                            if(y>=600 && y<=677)//exit
                                {return;}

                }
            if (x>=919 && x<=919+44 && !fost_ajutor)//pentru sunet
                if (y>=29 && y<=29+44)
                    sunet=-sunet;
            fost_ajutor=0;
            }
        }
            else
            if (event.type==SDL_QUIT)
                return;
    }
return;
}

void aplica_imagine(int x, int y, SDL_Surface*sursa, SDL_Surface*destinatie)
{
    SDL_Rect pos;
    pos.x=pozx[y]; pos.y=pozy[x];
    SDL_BlitSurface(sursa, NULL, destinatie, &pos);
    return;
}

SDL_Surface*incarca_imagine(string nume_img)
{
    SDL_Surface*imagine=NULL;
    imagine=IMG_Load (nume_img.c_str());
    SDL_Surface*imagine_optimizata=SDL_DisplayFormatAlpha(imagine);
    SDL_FreeSurface (imagine);
    return imagine_optimizata;
}

void joc()
{
//1, 2, 3
//load_files_joc();
SDL_BlitSurface(fundal_joc, NULL, screen, NULL);
SDL_BlitSurface(p3, NULL, screen, NULL);
SDL_Flip(screen);
SDL_Delay(1000);
SDL_BlitSurface(fundal_joc, NULL, screen, NULL);
SDL_BlitSurface(p2, NULL, screen, NULL);
SDL_Flip(screen);
SDL_Delay(1000);
SDL_BlitSurface(fundal_joc, NULL, screen, NULL);
SDL_BlitSurface(p1, NULL, screen, NULL);
SDL_Flip(screen);
SDL_Delay(1000);
ttotal=35000;
powert=SDL_GetTicks();
tref=SDL_GetTicks();
tpower=tref;
lastchuck=tref;
t=SDL_GetTicks();
gata=0;
cartite_lovite=0;
player.puncte=0;
tgen=2000;
nrgen=2; pause=0;
tscoatere_cartite=1500;
tscoatere_powerup=1000;
succesive=0;
miss=0;
gauri=0;
lovit=1;
Mix_PlayMusic (muzica_joc, -1);
while (!gata)
{
    pune_cursor(0,2);
    if (Mix_PausedMusic()==1 && sunet==1)//sound on
        Mix_ResumeMusic();
        else
        if (Mix_PlayingMusic()==1 && sunet==-1)//sound off
            Mix_PauseMusic();
    dategen();
    if (SDL_GetTicks()-tref>=tscoatere_cartite)
        scoate();
    if (SDL_GetTicks()-tpower>=tscoatere_powerup)
        scoate_power_up();
    if (SDL_PollEvent(&event))
    {
        if (event.type==SDL_MOUSEBUTTONDOWN)
        {
            if (event.button.button==SDL_BUTTON_LEFT)
                {
                //luam coord click-ului
                x = event.button.x;
                y = event.button.y;
                elim(x,y);  //vedem pe ce am dat click
                if(matr[i][j]>5)
                    {ci=i; cj=j;}
                    else
                    ci=cj=0;
                pune_cursor(1,2);
                }
        }
            else
            if (event.type==SDL_KEYDOWN)
                if (event.key.keysym.sym==SDLK_ESCAPE)//AICI VINE PAUZA
                    pauza();
    }
    if (SDL_GetTicks()-soprit>=tgen && gauri<20) //daca este timpul sa generam cartite pe ecran...
    {
        for (r=1;r<=nrgen && gauri<20;r++)
            {
            gen();
            timp[a][b]=SDL_GetTicks();
            soprit=SDL_GetTicks();
            gauri++;
            }
    }
    if (SDL_GetTicks()-powert>=4500 && gauri<20)
        {power_up();powert=SDL_GetTicks(); gauri++;}
    }
Mix_HaltMusic();
generare_scoruri();
if (!pause)
    game_over();
//eliberare_suprafete_joc();
return;
}

void power_up()
{
int tip=0;
tip=rand()%4+1;
if(SDL_GetTicks()-lastchuck>=16000)
{
    while(1)
    {
    a=rand()%4+1;
    b=rand()%5+1;
    if (matr[a][b]==0)
        {
        matr[a][b]=5;
        timp_power_up[a][b]=SDL_GetTicks();
        break;
        }
    }
    lastchuck=SDL_GetTicks();
    return;
}
if (tip==1)
     while (1)
        {
        a=rand()%4+1;//linia
        b=rand()%5+1;//coloana
        if (matr[a][b]==0)
            {
             timp_power_up[a][b]=SDL_GetTicks();
             matr[a][b]=2;
             return;
             }
        }
    else
    if (tip==2)//power up timp
        while (1)
        {
        a=rand()%4+1;
        b=rand()%5+1;
        if (matr[a][b]==0)
            {
             matr[a][b]=3;
             timp_power_up[a][b]=SDL_GetTicks();
             return;
             }
        }
        else
        if (tip==3)//bombetti
             while (1)
        {
        a=rand()%4+1;
        b=rand()%5+1;
        if (matr[a][b]==0)
            {
             matr[a][b]=4;
             timp_power_up[a][b]=SDL_GetTicks();
             return;
             }
        }
}

void scoate()
{
char scos=0;
for (i=1;i<=4;i++)
      for (j=1;j<=5;j++)
           if (matr[i][j]==1 && (SDL_GetTicks()-timp[i][j])>=tscoatere_cartite)
               {matr[i][j]=0;
                //daca a disparut o carita fara a fi lovita, eliminam combo-ul
                succesive=0;
                scos=1;
                timp[i][j]=0;
                aplica_imagine2 (i, j, fundal_joc, screen);
                gauri--;
               }
if (scos)
    tref=SDL_GetTicks();
}

void dategen()
{
if ((SDL_GetTicks()-t)/ttotal>=1 || ttotal<=0)
         gata=1;
if (SDL_GetTicks()-t>=8000 && SDL_GetTicks()-t<20000)
{
    nrgen=3; tgen=1800; tscoatere_cartite=1700; tscoatere_powerup=1300; return;
}
if (SDL_GetTicks()-t>=20000 && SDL_GetTicks()-t<35000)
{
    nrgen=4; tgen=1700; tscoatere_cartite=1900; tscoatere_powerup=1400; return;
}
if (SDL_GetTicks()-t>=35000)
{
    nrgen=5; tgen=2200; tscoatere_cartite=2000; tscoatere_powerup=1600; return;
}
return;
}

void gen()
{
while (1)
        {
        if(gauri>=20)
            return;
        a=rand()%4+1;//linia
        b=rand()%5+1;//coloana
        if (matr[a][b]==0) //daca spatiul este liber
            {
             matr[a][b]=1; //punem cartita in el
             timp[a][b]=SDL_GetTicks();
             return;
             }
       }
return;
}

void afis_combo()  //functia afiseaza pe ecran imaginea coresp combo-ului actual
{
if (succesive>=2 && succesive<5)
    aplica_imagine3(300,25,combo2,screen);
    else
    if (succesive>=5 && succesive<8)
        aplica_imagine3(300,25,combo5,screen);
        else
        if (succesive>=8 && succesive<12)
            aplica_imagine3(300,25,combo8,screen);
            else
            if (succesive>=12 && succesive<15)
                aplica_imagine3(300,25,combo12,screen);
                else
                if (succesive>=15 && succesive<20)
                    aplica_imagine3(300, 25, combo15, screen);
                    else
                    if (succesive>=20 && succesive<30)
                        aplica_imagine3(300, 25, combo20, screen);
                        else
                        if (succesive>=30)
                            aplica_imagine3(300, 25, combo30, screen);
                            else
                            aplica_imagine3(300, 25, combo0, screen);
    return;
}

void elim (int poz1,int poz2)
{
for (j=1; pozx[j]<poz1 && j<=5; j++);//coloana
for (i=1; pozy[i]<poz2 && i<=4; i++);//linia
i--; j--;
if (matr[i][j]==0)
    {
        succesive=0;
        miss++;  //numaram ratarea
        if (miss%2==0) //2 ratari, penalizare 1 secunda
        {
            if(ttotal<=1010)
                ttotal=100;
                else
                ttotal-=1000;
        }
    }
    else
    if (matr[i][j]==1)
        {
            miss=0;
            succesive++;
            player.puncte+=15+5*(succesive/2); //punctam
            if (succesive%8==0)
                ttotal+=2000;
            matr[i][j]=6; //CARTITA LOVITA
            gauri--;
            lovit=1;
        }
        else
        if (matr[i][j]==2)//daca e power up puncte
            {
                player.puncte+=100;
                matr[i][j]=7;
                succesive++;
                gauri--;
                lovit=1;
            }
            else
            if (matr[i][j]==3)
                {
                    ttotal+=5000; //timpul total creste cu 5 secunde
                    matr[i][j]=8;
                    succesive++;
                    gauri--;
                }
                else
                if (matr[i][j]==4) //daca am dat click pe o bomba
                    {
                     if(ttotal<=3010)
                        ttotal=100;
                        else
                        ttotal-=3000;
                     if(player.puncte>100)
                        player.puncte-=100;
                        else
                        player.puncte=0;
                     succesive=0;
                     matr[i][j]=9;
                     gauri--;
                     lovit=1;
                    }
                    else
                    if (matr[i][j]==5)//daca e chuck
                    {
                        player.puncte+=500;
                        ttotal+=5000;
                        matr[i][j]=10;
                        succesive++;
                        gauri--;
                        lovit=1;
                    }
return;
}

void scoruri()
{
    generare_scoruri();
    while(1)
    {
        pune_cursor(0, 8);
        if(SDL_PollEvent(&event))
            if(event.type==SDL_MOUSEBUTTONDOWN)
                if(event.button.button==SDL_BUTTON_LEFT)
        {
            x=event.button.x;
            y=event.button.y;
            pune_cursor(1, 8);
            if (xpos>=930 && xpos<=930+75)
                if (ypos>=25 && ypos<=25+65)
                {
                    fost_ajutor=1;
                    return;
                }
        }
    }
    return;
}

void pauza()
{
    ceva=SDL_GetTicks();
    while (!gata)
    {
        pune_cursor(0,3);
        if (Mix_PausedMusic()==1 && sunet==1)//daca e sound on
            Mix_ResumeMusic();
            else
            if (Mix_PlayingMusic()==1 && sunet==-1)//daca e sound off
                Mix_PauseMusic();
        if (SDL_PollEvent(&event))
            if (event.type==SDL_MOUSEBUTTONDOWN)
                if (event.button.button==SDL_BUTTON_LEFT)
                {
                    x = event.button.x;
                    y = event.button.y;
                    pune_cursor (1,3);
                    if (x>=360 && x<=360+270)
                    {
                        if (y>=301 && y<=395)
                            break;
                        if (y>=410 && y<=503)
                            {
                                gata=1;
                                pause=1;
                                return;
                            }
                        if (y>=535-18 && y<=602)
                            ajutor();
                    }
                    if (x>=919 && x<=919+44 && !fost_ajutor)//pentru sunet
                        if (y>=29 && y<=29+44)
                            sunet=-sunet;
                    fost_ajutor=0;
                }
    }
    t+=SDL_GetTicks()-ceva;
    return;
}

void aplica_imagine2 (int x, int y, SDL_Surface*sursa, SDL_Surface*destinatie)//functia pentru a lipi o portiune din imagine pe screen
{
    SDL_Rect pos;
    pos.x=pozx[y]; pos.y=pozy[x];
    SDL_Rect pos2;
    pos2.x=pozx[y];
    pos2.y=pozy[x];
    pos2.w=160;
    pos2.h=112;
    SDL_BlitSurface (sursa, &pos2, destinatie, &pos);
    return;
}

//7 specials, 8 scoruri
void pune_cursor (int a, int b)//1 pentru meniu, 2 pentru joc, 3 pentru pauza, 4 game over, 5 lore, 6 instructiuni
{
    int k;
    if (b==2)
    {
        int invers, copie, lg;
        lg=0;
        int copie2;
        for (copie=ttotal-(SDL_GetTicks()-t), invers=0; copie; copie/=10)
            invers=invers*10+copie%10;
        while (invers)
        {
        st[++lg]=invers%10+'0';
        invers/=10;
        }
        st[0]=st[lg]=' ';
        if (lg>=1)
            st[lg-1]=' ';
        if (lg>=2)
            st[lg-2]=' ';
        for (++lg; lg<=10; lg++)
            st[lg]=' ';
        //AM CONSTRUIT ST-UL
        if(lovit)
        {
        for (copie2=copie=player.puncte, invers=0; copie; copie/=10)
            invers=invers*10+copie%10;
        lg=0;
        while (invers)
        {
        sc[++lg]=invers%10+'0';
        invers/=10;
        }
        if (copie2==0)
            sc[++lg]='0';
            else
            while (copie2%10==0)
            {
                sc[++lg]='0';
                copie2/=10;
            }
        sc[0]=' ';
        for (++lg; lg<=10; lg++)
            sc[lg]=' ';
        lovit=0;
        }
    }
    if (b==1)//redesenez meniul
    {
        SDL_BlitSurface(fundal_meniu, NULL, screen, NULL);
        if (sunet==1)//pun soundon
            aplica_imagine3(905, 9, soundon, screen);
            else
            aplica_imagine3(905, 9, soundoff, screen);
    }
        else//redesenez jocul
        if (b==2 || b==3 || b==4)
        {
        SDL_BlitSurface(fundal_joc, NULL, screen, NULL);
        for (i=1;i<=4;i++)
          for (j=1;j<=5;j++)
               if (matr[i][j])
               {
                   if (matr[i][j]==1) //pun cartita
                        aplica_imagine(i, j, cartita, screen);
                        else
                        if (matr[i][j]==2) //pun power up cu puncte
                            aplica_imagine(i, j, power_up_puncte, screen);
                            else
                            if (matr[i][j]==3) //pun timp
                                aplica_imagine(i, j, power_up_timp, screen);
                                else
                                if (matr[i][j]==4) //bombetti
                                    aplica_imagine(i, j, bomba, screen);
                                    else
                                    if (matr[i][j]==5) //CHUCK POWAAAAH
                                        aplica_imagine(i, j, chuck, screen);
               }
        SDL_Color textColor = {186,102,0};
        timeleft=TTF_RenderText_Solid( font, st, textColor );
        scor=TTF_RenderText_Solid( font, sc, textColor );
        aplica_imagine3 (10,50,mtl,screen);
        aplica_imagine3 (200,50,timeleft,screen);
        aplica_imagine3 (10,10,msc,screen);
        aplica_imagine3 (90,10,scor,screen);
        afis_combo();
        if (b==3)//redesenez pauza
            {
            SDL_BlitSurface(transparenta, NULL, screen, NULL);
            if (sunet==1)//pun soundon
                aplica_imagine3(905, 9, soundon, screen);
                else
                aplica_imagine3(905, 9, soundoff, screen);
            }
        }
    SDL_GetMouseState(&xpos, &ypos);
    if (b==1)//pun efect de glow
    {
        if (xpos>=360 && xpos<=360+270)
        {
            if (ypos>=268 && ypos<=350)
                aplica_imagine3(360-10, 268-6, glow, screen);
                else
                if (ypos>=377 && ypos<=458)
                    aplica_imagine3(360-10, 377-6, glow, screen);
                    else
                    if (ypos>=487 && ypos<=565)
                        aplica_imagine3(360-10, 486-6, glow, screen);
                        else
                        if (ypos>=600 && ypos<=677)
                            aplica_imagine3(360-10, 594-6, glow, screen);
        }
    }
    if (b==3)//glow pauza
    {
        if (xpos>=360 && xpos<=360+270)
        {
            if (ypos>=301 && ypos<=395)
                aplica_imagine3(360-10, 268+31, glow, screen);
                else
                if (ypos>=410 && ypos<=503)
                    aplica_imagine3(360-10, 377+31, glow, screen);
                    else
                    if (ypos>=535-18 && ypos<=602)
                        aplica_imagine3(360-10, 486+31, glow, screen);
        }
    }
    if (b==4)//gameover
    {
        SDL_BlitSurface(fundal_gameover, NULL, screen, NULL);
        SDL_Color textColor = {198,198,198};
        scor=TTF_RenderText_Solid( font2, sc, textColor );
        if (sc[5]>='0' && sc[5]<='9')
            aplica_imagine3(553,309,scor,screen);
            else
            if (sc[4]>='0' && sc[4]<='9')
                aplica_imagine3(553+15,309,scor,screen);
                else
                if (sc[3]>='0' && sc[3]<='9')
                    aplica_imagine3(553+30,309,scor,screen);
                    else
                    if (sc[2]>='0' && sc[2]<='9')
                        aplica_imagine3(553+45,309,scor,screen);
                        else
                        aplica_imagine3(553+60,309,scor,screen);
    }
    if (a && b<5)
    {
        if (b==2)
            if (ci)
        {
            //6 cartita, 7 puncte, 8 timp, 9 bomba, 10 chuck
            if (matr[ci][cj]==6)
            {
                aplica_imagine(ci, cj, cartitafuu, screen);
                if (sunet==1)
                    Mix_PlayChannel( -1, cartita_hit, 0 );
            }
                else
                if (matr[ci][cj]==9)//bombetti
                {
                    aplica_imagine(ci, cj, bombafuu, screen);
                    if(sunet==1)
                        Mix_PlayChannel(-1, bomba_hit, 0);
                }
                    else
                    if (matr[ci][cj]==10)//chuck powah
                    {
                        aplica_imagine(ci, cj, chuckfuu, screen);
                        k=rand()%2+1;
                        if (k==1 && sunet==1)
                            Mix_PlayChannel(-1, chuck_hit, 0);
                        if (k==2 && sunet==1)
                            Mix_PlayChannel(-1, chuck_hit3, 0);
                    }
                        else
                        if (matr[ci][cj]==7 && sunet==1)//puncte
                        {
                            aplica_imagine(ci, cj, punctefuu, screen);
                            Mix_PlayChannel(-1, puncte_hit, 0);
                        }
                            else
                            if (matr[ci][cj]==8 && sunet==1)//timp
                            {
                                aplica_imagine(ci, cj, timpfuu, screen);
                                Mix_PlayChannel(-1, timp_hit, 0);
                            }
            cartite_lovite++;
            matr[ci][cj]=0;
        }
        aplica_imagine3(xpos-9, ypos-49, ciocan2, screen);
        SDL_Flip(screen);
        SDL_Delay(100);
    }
    if (b==4)
        if (xpos>=350 && xpos<=625)
            if (ypos>=500 && ypos<=585)
                aplica_imagine3(336, 500-9, glow, screen);
    if(b==5 || b==6 || b==7)
    {
        if (b==5) //5 lore, 6 instructiuni, 7 power ups
            SDL_BlitSurface(fundal_ajutor, NULL, screen, NULL);
        if (b==6)
            SDL_BlitSurface(instructiuni, NULL, screen, NULL);
        if (b==7)
            SDL_BlitSurface(fundal_powerups, NULL, screen, NULL);
        if (b!=5)
            if (xpos>=870 && xpos<=870+50)
                if (ypos>=680 && ypos<=680+40)
                    aplica_imagine3 (869, 678, leftglow, screen);
        if (b!=7)
            if (xpos>=930 && xpos<=930+50)
                if (ypos>=680 && ypos<=680+40)
                    aplica_imagine3 (930, 679, rightglow, screen);
        if (xpos>=930 && xpos<=930+75)
            if (ypos>=25 && ypos<=25+65)
                aplica_imagine3(916, 14, xglow, screen);
    }
    if(b==8)
    {
        SDL_BlitSurface(fundal_scoruri, NULL, screen, NULL);
        if (xpos>=930 && xpos<=930+75)
            if (ypos>=25 && ypos<=25+65)
                aplica_imagine3(916, 14, xglow, screen);
        //TTF_Font*font=NULL;
        //font=TTF_OpenFont( "comicsans.ttf", 48 );
        SDL_Color textColor = {198,198,198};
        scor=TTF_RenderText_Solid( font2, pctj1, textColor );
        aplica_imagine3(280, 260, scor, screen);
        scor=TTF_RenderText_Solid( font2, pctj2, textColor );
        aplica_imagine3(280, 320, scor, screen);
        scor=TTF_RenderText_Solid( font2, pctj3, textColor );
        aplica_imagine3(280, 380, scor, screen);
        scor=TTF_RenderText_Solid( font2, pctj4, textColor );
        aplica_imagine3(280, 440, scor, screen);
        scor=TTF_RenderText_Solid( font2, pctj5, textColor );
        aplica_imagine3(280, 500, scor, screen);
    }
    if(a && b>=5)
    {
        aplica_imagine3(xpos-9, ypos-49, ciocan2, screen);
        SDL_Flip(screen);
        SDL_Delay(100);
    }
        else
        aplica_imagine3(xpos-9, ypos-49, ciocan, screen);
    SDL_Flip(screen);
    return;
}

void scoate_power_up()
{
    char scos=0;
    for (i=1;i<=4;i++)
      for (j=1;j<=5;j++)
           if (matr[i][j]>1 && SDL_GetTicks()-timp_power_up[i][j]>=999)
               {
                matr[i][j]=0;
                timp_power_up[i][j]=0;
                scos=1;
                gauri--;
               }
if(scos)
    tpower=SDL_GetTicks();
}

void aplica_imagine3 (int x, int y, SDL_Surface*sursa, SDL_Surface*destinatie)
{
    SDL_Rect pos;
    pos.x=x; pos.y=y;
    SDL_BlitSurface (sursa, NULL, destinatie, &pos);
    return;
}

void inchide_sdl()
{
    /*eliberare_suprafete_joc();
    //<ELIBERARE SUPRAFETE>
    SDL_FreeSurface(screen);
    SDL_FreeSurface(glow);
    SDL_FreeSurface(leftglow);
    SDL_FreeSurface(leftglow);
    SDL_FreeSurface(xglow);
    SDL_FreeSurface(fundal_meniu);
    SDL_FreeSurface(fundal_ajutor);
    SDL_FreeSurface(ciocan);
    SDL_FreeSurface(ciocan2);
    SDL_FreeSurface(instructiuni);
    SDL_FreeSurface(fundal_powerups);
    SDL_FreeSurface(fundal_scoruri);
    //</ELIBEREARE SUPRAFETE>

    //<ELIBERARE SUNETE>
    Mix_FreeMusic(muzica_meniu);
    Mix_FreeMusic(muzica_gameover);
    //</ELIBERARE SUNETE>*/

    TTF_Quit();
    Mix_CloseAudio();
    IMG_Quit();
    SDL_Quit();
    return;
}

void intro()
{
    int ceva, volum=110;
    char altaltaltceva=0;
    unsigned int altceva, altaltceva;
    Mix_Music*muzica=NULL;
    muzica=Mix_LoadMUS("wav/intro.wav");
    SDL_Surface*imagine=NULL;
    SDL_Surface*imagine_optimizata=NULL;
    imagine=IMG_Load("img/intro.png");
    imagine_optimizata=SDL_DisplayFormat(imagine);
    Mix_PlayMusic(muzica, -1);
    for (ceva=0; ceva<=128; ceva++)
    {
        SDL_SetAlpha(imagine_optimizata, SDL_SRCALPHA, ceva);
        SDL_BlitSurface(imagine_optimizata, NULL, screen, NULL);
        SDL_Flip(screen);
        SDL_Delay(15);
    }
    SDL_FreeSurface(imagine);
    //incarc imaginea neagra in imagine
    SDL_Surface*imagine_optimizata2=NULL;
    imagine=IMG_Load("img/black.png");
    imagine_optimizata2=SDL_DisplayFormat(imagine);
    for (ceva=0; ceva<=255; ceva++)
    {
        SDL_SetAlpha(imagine_optimizata2, SDL_SRCALPHA, ceva);
        SDL_BlitSurface(imagine_optimizata, NULL, screen, NULL);
        SDL_BlitSurface(imagine_optimizata2, NULL, screen, NULL);
        SDL_Flip(screen);
        SDL_Delay(10);
        while(SDL_PollEvent(&event))
            //if(event.type==SDL_KEYDOWN)
                if(event.key.keysym.sym==SDLK_SPACE)
                    altaltaltceva=1;
        if(altaltaltceva)
            break;
    }
    altceva=SDL_GetTicks();
    altaltceva=altceva;
    while (SDL_GetTicks()-altceva<=2500)
    {
        if (SDL_GetTicks()-altaltceva>=30)
        {
            if(volum<=0)
                volum=1;
            volum-=1;
            altaltceva=SDL_GetTicks();
        }
        Mix_VolumeMusic(volum);
    }
    SDL_FreeSurface (imagine);
    SDL_FreeSurface (imagine_optimizata);
    SDL_FreeSurface (imagine_optimizata2);
    Mix_VolumeMusic (MIX_MAX_VOLUME);
    Mix_HaltMusic();
    return;
}

void game_over()
{
    int op=0;
    if(sunet==1)
        Mix_PlayMusic(muzica_gameover, 0);
    while(!op)
    {
        pune_cursor(0, 4);
        if (SDL_PollEvent(&event))
            if (event.type==SDL_MOUSEBUTTONDOWN)
                if (event.button.button==SDL_BUTTON_LEFT)
                    {
                        x=event.button.x;
                        y=event.button.y;
                        pune_cursor(1, 4);
                        if (x>=350 && x<=625)
                            if (y>=500 && y<=585)
                                op=1;
                    }
    }
    if(sunet==1)
        Mix_HaltMusic();
    return;
}

void ajutor()
{
    int bt=5;//5 lore, 6 instructiuni, 7 power ups
    fost_ajutor=1;
    while(1)
    {
        pune_cursor(0, bt);
        if(SDL_PollEvent(&event))
            if(event.type==SDL_MOUSEBUTTONDOWN)
                if(event.button.button==SDL_BUTTON_LEFT)
        {
            x=event.button.x;
            y=event.button.y;
            pune_cursor(1, bt);
            if (bt==5 || bt==6)
                if (x>=930 && x<=930+50)
                    if (y>=680 && y<=680+40)
                        bt++;
            if (bt==6 || bt==7)
                if (x>=870 && x<=870+50)
                    if (y>=680 && y<=680+40)
                        bt--;
            //exit?
            if (x>=930 && x<=930+75)
                if (y>=25 && y<=25+65)
                    return;
        }
    }
    return;
}

void highscore()
{
ofstream fout ("highscore.txt");
int i, j, maximus, pozmax, chestie=6;
char gasit=0;
for(i=1; i<=5; i++)
    if(strcmp(jucatori[i].numejucator, player.numejucator)==0)
        {gasit=1;
        if(player.puncte>jucatori[i].puncte)
            {
            jucatori[i]=player;
            break;}
        }
if(!gasit)
    jucatori[6]=player;
if(!gasit)
    chestie=6;
    else
    chestie=5;
for(i=1; i<=chestie; i++)//sortez descrescator
{
    maximus=jucatori[i].puncte;
    pozmax=i;
    for(j=i+1; j<=chestie; j++)
        if(jucatori[j].puncte>=maximus)
    {
        maximus=jucatori[j].puncte;
        pozmax=j;
    }
    auxiliar=jucatori[pozmax];
    jucatori[pozmax]=jucatori[i];
    jucatori[i]=auxiliar;
}
//afisez primii 5
for(i=1; i<=5; i++)
    fout<<jucatori[i].puncte<<"\n";
for(i=1; i<=5; i++)
    fout<<jucatori[i].numejucator<<"\n";
fout.close();
}

void loadhighscore()
{
ifstream fin ("highscore.txt");
int i;
for(i=1; i<=5; i++)
    fin>>jucatori[i].puncte;
fin.getline(jucatori[1].numejucator, 2);
for(i=1; i<=5; i++)
    fin.getline(jucatori[i].numejucator, 15);
fin.close();
}

void load_files()
{
 //<INCARCARI>
muzica_meniu=Mix_LoadMUS ("wav/muzica_meniu.wav");
fundal_meniu=incarca_imagine ("img/fundal_meniu.png");
glow=incarca_imagine ("img/glow.png");
soundon=incarca_imagine ("img/soundon.png");
soundoff=incarca_imagine ("img/soundoff.png");
fundal_ajutor=incarca_imagine ("img/fundal_ajutor.png");
instructiuni=incarca_imagine ("img/instructiuni.png");
fundal_powerups=incarca_imagine ("img/fundal_powerups.png");
leftglow=incarca_imagine ("img/leftglow.png");
rightglow=incarca_imagine ("img/rightglow.png");
xglow=incarca_imagine ("img/xglow.png");
fundal_scoruri=incarca_imagine("img/fundal_scoruri.png");
ciocan=incarca_imagine ("img/ciocan.png");
ciocan2=incarca_imagine ("img/ciocan2.png");
load_files_joc();
//</INCARCARI>
return;
}

void eliberare_suprafete_joc()
{
    //<ELIBERARE SUPRAFETE>
    SDL_FreeSurface(scor);
    SDL_FreeSurface(mtl);
    SDL_FreeSurface(msc);
    SDL_FreeSurface(timeleft);
    SDL_FreeSurface(cartita);
    SDL_FreeSurface(cartitafuu);
    SDL_FreeSurface(power_up_timp);
    SDL_FreeSurface(timpfuu);
    SDL_FreeSurface(power_up_puncte);
    SDL_FreeSurface(punctefuu);
    SDL_FreeSurface(combo0);
    SDL_FreeSurface(combo2);
    SDL_FreeSurface(combo5);
    SDL_FreeSurface(combo8);
    SDL_FreeSurface(combo12);
    SDL_FreeSurface(combo15);
    SDL_FreeSurface(combo20);
    SDL_FreeSurface(combo30);
    SDL_FreeSurface(bomba);
    SDL_FreeSurface(bombafuu);
    SDL_FreeSurface(fundal_joc);
    SDL_FreeSurface(chuck);
    SDL_FreeSurface(chuckfuu);
    SDL_FreeSurface(fundal_gameover);
    Mix_FreeChunk(cartita_hit);
    Mix_FreeChunk(timp_hit);
    Mix_FreeChunk(puncte_hit);
    Mix_FreeChunk(bomba_hit);
    Mix_FreeChunk(chuck_hit);
    Mix_FreeChunk(chuck_hit3);
    Mix_FreeMusic(muzica_joc);
    //</ELIBEREARE SUPRAFETE>
    return;
}

void load_files_joc()
{
     //<INCARCARI>
    muzica_joc=Mix_LoadMUS ("wav/muzica_joc.wav");
    cartita_hit=Mix_LoadWAV ("wav/cartita_hit.wav");
    bomba_hit=Mix_LoadWAV ("wav/bomba_hit.wav");
    chuck_hit=Mix_LoadWAV ("wav/chuck_hit.wav");
    chuck_hit3=Mix_LoadWAV ("wav/chuck_hit3.wav");
    puncte_hit=Mix_LoadWAV ("wav/puncte_hit.wav");
    muzica_gameover=Mix_LoadMUS("wav/muzica_gameover.wav");
    timp_hit=Mix_LoadWAV ("wav/timp_hit.wav");
    cartita=incarca_imagine ("img/cartita.png");
    power_up_puncte=incarca_imagine ("img/puncte.png");
    punctefuu=incarca_imagine ("img/punctefuu.png");
    power_up_timp=incarca_imagine ("img/timp.png");
    timpfuu=incarca_imagine ("img/timpfuu.png");
    combo0=incarca_imagine ("img/combo0.png");
    combo2=incarca_imagine ("img/combo2.png");
    combo5=incarca_imagine ("img/combo5.png");
    combo8=incarca_imagine ("img/combo8.png");
    combo12=incarca_imagine ("img/combo12.png");
    combo15=incarca_imagine ("img/combo15.png");
    combo20=incarca_imagine ("img/combo20.png");
    combo30=incarca_imagine ("img/combo30.png");
    bomba=incarca_imagine ("img/bomba.png");
    bombafuu=incarca_imagine ("img/bombafuu.png");
    fundal_joc=incarca_imagine ("img/fundal_joc.png");
    cartitafuu=incarca_imagine ("img/cartitafuu.png");
    chuck=incarca_imagine ("img/chuck.png");
    chuckfuu=incarca_imagine ("img/chuckfuu.png");
    transparenta=incarca_imagine ("img/transparenta.png");
    fundal_gameover=incarca_imagine ("img/fundal_gameover.png");
    p1=incarca_imagine("img/1.png");
    p2=incarca_imagine("img/2.png");
    p3=incarca_imagine("img/3.png");
    //</INCARCARI>
}

void citeste_nume()
{
SDL_Surface*fundal=NULL;
SDL_Surface*poza_nume=NULL;
fundal=incarca_imagine("img/numejucator.png");
SDL_Color textColor = {198,198,198};
int i;
//for(i=0; i<=15; i++)
    //numejucatorinitial[i]=' ';
while(1)
    {
        if(SDL_PollEvent(&event))
            if(event.type==SDL_KEYDOWN)
        {
            //testez :)
            if(event.key.keysym.sym==SDLK_a) {litera='A';scrie(litera);}
            if(event.key.keysym.sym==SDLK_b) {litera='B';scrie(litera);}
            if(event.key.keysym.sym==SDLK_c) {litera='C';scrie(litera);}
            if(event.key.keysym.sym==SDLK_d) {litera='D';scrie(litera);}
            if(event.key.keysym.sym==SDLK_e) {litera='E';scrie(litera);}
            if(event.key.keysym.sym==SDLK_f) {litera='F';scrie(litera);}
            if(event.key.keysym.sym==SDLK_g) {litera='G';scrie(litera);}
            if(event.key.keysym.sym==SDLK_h) {litera='H';scrie(litera);}
            if(event.key.keysym.sym==SDLK_i) {litera='I';scrie(litera);}
            if(event.key.keysym.sym==SDLK_j) {litera='J';scrie(litera);}
            if(event.key.keysym.sym==SDLK_k) {litera='K';scrie(litera);}
            if(event.key.keysym.sym==SDLK_l) {litera='L';scrie(litera);}
            if(event.key.keysym.sym==SDLK_m) {litera='M';scrie(litera);}
            if(event.key.keysym.sym==SDLK_n) {litera='N';scrie(litera);}
            if(event.key.keysym.sym==SDLK_o) {litera='O';scrie(litera);}
            if(event.key.keysym.sym==SDLK_p) {litera='P';scrie(litera);}
            if(event.key.keysym.sym==SDLK_q) {litera='Q';scrie(litera);}
            if(event.key.keysym.sym==SDLK_r) {litera='R';scrie(litera);}
            if(event.key.keysym.sym==SDLK_s) {litera='S';scrie(litera);}
            if(event.key.keysym.sym==SDLK_t) {litera='T';scrie(litera);}
            if(event.key.keysym.sym==SDLK_u) {litera='U';scrie(litera);}
            if(event.key.keysym.sym==SDLK_v) {litera='V';scrie(litera);}
            if(event.key.keysym.sym==SDLK_w) {litera='W';scrie(litera);}
            if(event.key.keysym.sym==SDLK_x) {litera='X';scrie(litera);}
            if(event.key.keysym.sym==SDLK_y) {litera='Y';scrie(litera);}
            if(event.key.keysym.sym==SDLK_z) {litera='Z';scrie(litera);}
            if(event.key.keysym.sym==SDLK_BACKSPACE) {scrie('0');}
            if(event.key.keysym.sym==SDLK_RETURN)
                {
                    SDL_FreeSurface(fundal);
                    SDL_FreeSurface(poza_nume);
                    for(i=0; i<lgnume; i++)
                        player.numejucator[i]=numejucatorinitial[i];
                    return;
                }
    }
    SDL_BlitSurface(fundal, NULL, screen, NULL);
    poza_nume=TTF_RenderText_Solid (font2, numejucatorinitial, textColor);
    aplica_imagine3(530, 308, poza_nume, screen);
    SDL_Flip(screen);
    }
return;
}

void scrie(char v)
{
    if (v!='0' && lgnume<16)
        numejucatorinitial[lgnume++]=litera;
        else
        if(lgnume>0)
            {
            numejucatorinitial[--lgnume]=' ';
            }
    return;
}

void generare_scoruri()
{
    loadhighscore();
    int copie, contor;
    if(!pause)
        highscore();
    for(copie=0; copie<40; copie++)
        pctj1[copie]=pctj2[copie]=pctj3[copie]=pctj4[copie]=pctj5[copie]=' ';
    //construiesc cele 5 punctaje
    int invers1=0, invers2=0, invers3=0, invers4=0, invers5=0;
    for(copie=jucatori[1].puncte; copie; copie/=10)
        invers1=invers1*10+copie%10;
    for(copie=jucatori[2].puncte; copie; copie/=10)
        invers2=invers2*10+copie%10;
    for(copie=jucatori[3].puncte; copie; copie/=10)
        invers3=invers3*10+copie%10;
    for(copie=jucatori[4].puncte; copie; copie/=10)
        invers4=invers4*10+copie%10;
    for(copie=jucatori[5].puncte; copie; copie/=10)
        invers5=invers5*10+copie%10;
    pctj1[0]='1';pctj2[0]='2';pctj3[0]='3';pctj4[0]='4';pctj5[0]='5';
    lg1=lg2=lg3=lg4=lg5=1;
    pctj1[lg1++]='.';pctj2[lg2++]='.';pctj3[lg3++]='.';pctj4[lg4++]='.';pctj5[lg5++]='.';
    pctj1[lg1++]=' ';pctj2[lg2++]=' ';pctj3[lg3++]=' ';pctj4[lg4++]=' ';pctj5[lg5++]=' ';
    for(contor=0; contor<16; contor++)
    {
        if(jucatori[1].numejucator[contor]!='\0')
            pctj1[lg1++]=jucatori[1].numejucator[contor];
        if(jucatori[2].numejucator[contor]!='\0')
            pctj2[lg2++]=jucatori[2].numejucator[contor];
        if(jucatori[3].numejucator[contor]!='\0')
            pctj3[lg3++]=jucatori[3].numejucator[contor];
        if(jucatori[4].numejucator[contor]!='\0')
            pctj4[lg4++]=jucatori[4].numejucator[contor];
        if(jucatori[5].numejucator[contor]!='\0')
            pctj5[lg5++]=jucatori[5].numejucator[contor];
    }
    pctj1[lg1++]=':';pctj2[lg2++]=':';pctj3[lg3++]=':';pctj4[lg4++]=':';pctj5[lg5++]=':';
    pctj1[lg1++]=' ';pctj2[lg2++]=' ';pctj3[lg3++]=' ';pctj4[lg4++]=' ';pctj5[lg5++]=' ';
    for( contor=0; contor<=6; contor++)
    {
        if(invers1>0)
            pctj1[lg1++]=invers1%10+'0';
        if(invers2>0)
            pctj2[lg2++]=invers2%10+'0';
        if(invers3>0)
            pctj3[lg3++]=invers3%10+'0';
        if(invers4>0)
            pctj4[lg4++]=invers4%10+'0';
        if(invers5>0)
            pctj5[lg5++]=invers5%10+'0';
        invers1/=10; invers2/=10; invers3/=10; invers4/=10; invers5/=10;
    }
    for(copie=jucatori[1].puncte; copie%10==0&& copie>0; copie/=10)
        pctj1[lg1++]='0';
    for(copie=jucatori[2].puncte; copie%10==0&& copie>0; copie/=10)
        pctj2[lg2++]='0';
    for(copie=jucatori[3].puncte; copie%10==0&& copie>0; copie/=10)
        pctj3[lg3++]='0';
    for(copie=jucatori[4].puncte; copie%10==0&& copie>0; copie/=10)
        pctj4[lg4++]='0';
    for(copie=jucatori[5].puncte; copie%10==0&& copie>0; copie/=10)
        pctj5[lg5++]='0';
}
