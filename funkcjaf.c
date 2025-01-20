#include "funkcjaf.h"
#include "plansze.h"
#include <stdio.h>

int GRA=0;
void wyk_r2(int T[30][30], int W[30][30], int w, int k, int x, int y)   // funkcja r i przegrana dla "-f"
{
    if(T[x][y]!=0 && W[x][y]==9 && T[x][y]!=10)
    {
        W[x][y]=T[x][y];
        return;
    }
    else if(T[x][y]==0 && W[x][y]==9)
    {
        W[x][y]=0;
        if(x!=0)
        {
            if(y-1>=0)  wyk_r2(T,W,w,k,x-1,y-1);
            if(y+1<k)   wyk_r2(T,W,w,k,x-1,y+1);
            wyk_r2(T,W,w,k,x-1,y);
        }
        if(y-1>=0)  wyk_r2(T,W,w,k,x,y-1);
        if(y+1<k)   wyk_r2(T,W,w,k,x,y+1);
        if(x!=w-1)
        {
            if(y-1>=0)  wyk_r2(T,W,w,k,x+1,y-1);
            if(y+1<k)   wyk_r2(T,W,w,k,x+1,y+1);
            wyk_r2(T,W,w,k,x+1,y);
        }
        return;
    }
    else if(T[x][y]==10)
    {
        GRA=1;
    }
    return;
}
void funkcjaf(FILE *plik)   // co robi program gdy jest -f
{
    int W[30][30],T[30][30],lka=0,lk=0,lw=0,lm=0,i,j,c,x,y,lpk=0;
    int gra;
    for(i=0;i<30;i++)
    {
        for(j=0;j<30;j++)
        {
            T[i][j]=0;
            W[i][j]=9;
        }
    }    
    while((c=fgetc(plik))!=EOF)
    {
        if(c>='0' && c<='8')
        {
            T[lw][lka]=c-'0';
            lka++;
        }
        if(c=='*')
        {
            T[lw][lka]=10;
            lka++;
            lm++;
        }
        if(c=='\n'&& lka!=0) // lka!=0 bo wtedy pomijamy linijki w których nie ma żadnych liczb
        {
            lw++;
            lk=lka;
            lka=0;
        }
        if(c=='r')
            break;
    }
    wyswietl_plansze(T,lw,lk);

    fscanf(plik,"%d",&x);
    fscanf(plik,"%d",&y);
    if(x>0 && x<=lw && y>0 && y<=lk && W[x-1][y-1]==9)
    {
        wyk_r2(T,W,lw,lk,x-1,y-1);
        lpk++;
    }
    while((c=fgetc(plik))!=EOF)
    {
        if(c=='r')
        {
            fscanf(plik,"%d",&x);
            fscanf(plik,"%d",&y);
            if(x>0 && x<=lw && y>0 && y<=lk && W[x-1][y-1]==9)
            {
                wyk_r2(T,W,lw,lk,x-1,y-1);
                lpk++;
            }
            if(liczba_pol(W,lw,lk)==lw*lk-lm)
            {
                GRA=2;
            }
            if(GRA!=0)
            {
                if(GRA==2)    gra=1;
                else
                {
                    gra=0;
                    lpk--;  // usuwamy ostatni krok
                }
                printf("\nLiczba poprawnych krokow (do momentu zakonczenia gry): %d\nLiczba punktow: %d\nCzy wygrana? %d\n",lpk,liczba_pol(W,lw,lk),gra);
                break;
            }
                
        }
    }
}