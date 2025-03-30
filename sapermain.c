#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "funkcjaf.h"
#include "plansze.h"
#include "polecenia.h"
#include "top.h"

int D=0;    // liczba wskazująca na koniec gry, 0 - gra jeszcze trwa

// 9 - pole nieodsłonięte
// 10 - bomba
// 11 - flaga

int main(int argc, char *argv[])
{
    int poziom;
    int i,j,w,k,lm,opt;
    int T[30][30];      // T to tablica z wszystkimi numerkami i bombami
    int W[30][30];     // W to tablica wyświetlana użytkownikowi
    char imie[50];
    FILE *plik = fopen("wyniki.txt", "a+");
    for(i=0;i<30;i++)
    {
        for(j=0;j<30;j++)
        {
            W[i][j]=9;      // bo 9 to pole nieodsłonięte;
            // numery dla bomb, flag i pól nieodsłoniętych znajdują sie na górze tego pliku
            T[i][j]=0;
        }    
    }
    if((opt=getopt(argc,argv,"f:"))!= -1)   // sprawdzamy czy została podana jakaś flaga
    {
        if(opt == 'f')
        {
            FILE *plik2 = fopen(argv[2],"r");
            funkcjaf(plik2);
        }
        else
        {
            printf("Nieznana funkcja lub brak podanego argumentu.");
        }
    }
    else        // jeżeli nie została podana flaga to wykonuje się standardowe działanie programu
    {
        printf("Poziomy:\n 1. latwy - 9x9\n 2. sredni - 16x16\n 3. trudny - 16x30\n 4. Wlasna plansza\nPodaj poziom (1-3): ");
        scanf("%d",&poziom);
        if(poziom<1 || poziom>4)
        {
            printf("Podano nieprawidlowa wartosc.");
            return 1;
        }
        if(poziom==1)
        {
            w=9;
            k=9;
            lm=10;
        }
        if(poziom==2)
        {
            w=16;
            k=16;
            lm=40;
        }
        if(poziom==3)
        {
            w=16;
            k=30;
            lm=99;
        }
        if(poziom==4)
        {
            printf("\nPodaj liczbe wierszy (1-30):");
            scanf("%d",&w);
            if(w<1 || w>30)
            {
                printf("\nNieprawidlowa liczba wierszy.");
                return 1;
            }
            printf("\nPodaj liczbe kolumn (1-30):");
            scanf("%d",&k);
            if(k<1 || k>30)
            {
                printf("\nNieprawidlowa liczba kolumn.");
                return 1;
            }
            printf("\nPodaj liczbe min:");
            scanf("%d",&lm);
            if(lm<1 || lm>k*w)
            {
                printf("\nNieprawidlowa liczba min.");
                return 1;
            }
        }
        system("cls");      // dla systemu Linux "cls" trzeba zamienić na "clear"
        wyswietl_plansze(W,w,k);
        printf("\n");
        wczytaj_pierwsze(T,W,w,k,lm);
        wyswietl_plansze(W,w,k);
        while(D==0)     // dopóki gra trwa (nie jest przegrana bądź wygrana)
        {
            system("cls");      // dla systemu Linux "cls" trzeba zamienić na "clear"
            if(poziom != 4) printf("Aktualna liczba punktow: %d\n\n",poziom*liczba_pol(W,w,k));
            wyswietl_plansze(W,w,k);
            printf("\n");
            wczytaj_polecenie(T,W,w,k,lm);
            if(liczba_pol(W,w,k)==w*k-lm)
            {
                D=2;
                printf("Gratulacje! Wygrales!\n");
            }
            if(D!=0 && poziom!=4)       // jeżeli gra została skończona (wygrana bądź przegrana)
            {
                int wynik = poziom*liczba_pol(W,w,k);
                printf("\nLiczba punktow: %d\nPodaj imie: ", wynik);
                scanf("%s", &imie);
                fprintf(plik,"%d %s\n", wynik, imie);
                rewind(plik);
                topka(plik);
            }
        }
    }
    fclose(plik);
    return 0;
}

