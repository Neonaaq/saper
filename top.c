#include <stdio.h>
#include <string.h>
#include "top.h"
struct topgraczy {
    char imie[50];
    int wynik;
};
void topka(FILE *plik)  // wpisywanie i sortowanie top 5 graczy i wyświetlenie
{
    struct topgraczy top[5];
    int wynik,i, wynik2;
    char imie[50], imie2[50];
    for(i=0;i<5;i++)
    {
        top[i].wynik=0;
        strcpy(top[i].imie,"");
    }
    while(fscanf(plik,"%d",&wynik)==1)
    {
        fscanf(plik,"%s",&imie);
        for(i=0;i<5;i++)
        {
            if(wynik>top[i].wynik)
            {
                wynik2=top[i].wynik;
                strcpy(imie2,top[i].imie);
                top[i].wynik=wynik;
                strcpy(top[i].imie,imie);
                wynik=wynik2;
                strcpy(imie,imie2);
            }
        }
    }
    printf("\nTop 5 graczy:\n");
    for(i=0;i<5;i++)
    {
        printf("%d. %d\t%s\n", i+1, top[i].wynik,top[i].imie);
    }
}