#include <stdio.h>
#include <stdlib.h>
#include "polecenia.h"
#include "plansze.h"

extern int D;

void wyk_r(int T[30][30], int W[30][30], int w, int k, int x, int y)    // funkcja r i przegrana
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
            if(y-1>=0)  wyk_r(T,W,w,k,x-1,y-1);
            if(y+1<k)   wyk_r(T,W,w,k,x-1,y+1);
            wyk_r(T,W,w,k,x-1,y);
        }
        if(y-1>=0)  wyk_r(T,W,w,k,x,y-1);
        if(y+1<k)   wyk_r(T,W,w,k,x,y+1);
        if(x!=w-1)
        {
            if(y-1>=0)  wyk_r(T,W,w,k,x+1,y-1);
            if(y+1<k)   wyk_r(T,W,w,k,x+1,y+1);
            wyk_r(T,W,w,k,x+1,y);
        }
        return;
    }
    else if(T[x][y]==10)
    {
        system("cls");
        D=1;
        printf("Przegrales!\nOto pelna plansza:\n");
        wyswietl_plansze(T,w,k);
    }
    return;
}
void wczytaj_polecenie(int T[30][30], int W[30][30], int w, int k, int lm)  // wczytanie polecenia r lub f
{
    int x, y;
    char p;
    scanf(" %c %d %d",&p,&x,&y);
    if(p == 'r')
    {
        if(x>0 && x<=w && y>0 && y<=k && W[x-1][y-1]==9)
            wyk_r(T,W,w,k,x-1,y-1);
    }
    else if(p == 'f')
    {
        if(x>0 && x<=w && y>0 && y<=k && W[x-1][y-1]==9)    // wstawianie flagi
            W[x-1][y-1]=11;
        else if(x>0 && x<=w && y>0 && y<=k && W[x-1][y-1]==11)  // usuwanie flagi
            W[x-1][y-1]=9;
    }
}
void wczytaj_pierwsze(int T[30][30], int W[30][30], int w, int k, int lm)   // wczytanie pierwszego polecenia, zmuszamy użytkownika do polecenia r
{
    int x, y;
    char p;
    printf("\nOdslon swoje pierwsze pole! (polecenie ""r x y"", gdzie x to liczba wierszy a y liczba kolumn)\n");
    scanf(" %c %d %d", &p, &x,&y);
    if(p != 'r')
    {
        printf("Zle polecenie! Sprobuj jeszcze raz.\n");
        wczytaj_pierwsze(T,W,w,k,lm);
        return;
    }
    else
    {
        if(x>0 && x<=w && y>0 && y<=k)
        {
            stworz_plansze(T,w,k,lm,x,y);
            wyk_r(T,W,w,k,x-1,y-1);
            return;
        } 
        else
        {
            printf("Nieprawidlowe wartosci x lub/i y. Sprobuj jeszcze raz!\n");
            wczytaj_pierwsze(T,W,w,k,lm);
            return;
        }
    }
}