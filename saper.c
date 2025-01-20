#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <getopt.h>

int D=0;    // liczba wskazująca na koniec gry, 0 - gra jeszcze trwa
// 9 - pole nieodsłonięte
// 10 - bomba
// 11 - flaga
int liczba_pol(int W[30][30], int w, int k)       // liczba odsłoniętych pól
{
    int i, j,l=0;
    for(i=0;i<w;i++)
    {
        for(j=0;j<k;j++)
        {
            if(W[i][j]!=9 && W[i][j]!=11)  l++;
        }
    }
    return l;
}
int ile_bomb(int T[30][30], int w, int k,int i, int j)  // liczba bomb wokół danej komórki
{
    int l=0;
    // sprawdzamy komórki w dolnej części planszy
    if(i!=0)
    {
        if(j-1>=0 && T[i-1][j-1]==10) l++;
        if(j+1<k && T[i-1][j+1]==10) l++;
        if(T[i-1][j]==10) l++;
    }
    // sprawdzamy komórki po bokach
    if(j-1>=0 && T[i][j-1]==10)  l++;
    if(j+1<k && T[i][j+1]==10)  l++;
    // sprawdzamy komórki w górnej części planszy
    if(i!=w-1)
    {
        if(j-1>=0 && T[i+1][j-1]==10) l++;
        if(j+1<k && T[i+1][j+1]==10) l++;
        if(T[i+1][j]==10) l++;
    }
    return l;
}
void stworz_plansze(int T[30][30], int w,int k, int lm, int x, int y)   // tworzy planszę z uwzględnieniem, że pierwszy ruch to nie jest bomba
{
    int i,j,l=0;
    while(l<lm)     // dopóki aktualna liczba bomb mniejsza niż liczba bomb, która ma być
    {
        i=rand()%w; // losowa liczba z zakresu {0,1,...,w-1}
        j=rand()%k; // losowa liczba z zakresu {0,1,...,k-1}
        if(i!=x-1 && j!=y-1 && T[i][j]!=10)
        {
            T[i][j]=10; // bo 10 to bomba (na górze pliku są numery dla bomb,flag i pól nieodsłoniętych)
            l++;
        }
    }
    for(i=0;i<w;i++)
    {
        for(j=0;j<k;j++)
        {
            if(T[i][j]!=10) T[i][j] = ile_bomb(T,w,k,i,j);
        }
    }
    // for(i=0;i<w;i++)
    // {
    //     for(j=0;j<k;j++)
    //     {
    //         printf("%3d",T[i][j]);
    //     }
    //     printf("\n");
    // }
}
void wyswietl_plansze(int W[30][30], int w, int k)  // wyświetla planszę
{
    int i, j;
    printf("  ");
    for(j=0;j<k;j++)
    {
        printf("%3d", j+1);
    }
    printf("\n");
    for(i=0;i<w;i++)
    {
        if(i<9) printf("\n%d  ", i+1);
        else printf("\n%d ", i+1);
        for(j=0;j<k;j++)
        {
            if(W[i][j]==9)          printf(" # ");
            else if(W[i][j]==11)    printf("\033[32m f \033[0m");
            else if(W[i][j]==10)    printf("\033[31m * \033[0m");
            else if(W[i][j]==0)     printf("\033[36m 0 \033[0m");
            else                    printf("\033[34m %d \033[0m", W[i][j]);
        }
    }
    
}
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
        D=1;
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
                D=2;
            }
            if(D!=0)
            {
                if(D==2)    gra=1;
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
int main(int argc, char *argv[])
{
    srand(time(NULL));
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
    if((opt=getopt(argc,argv,"f:"))!= -1)   // sprawdzamy czy została podana jakaś funkcja
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
    else        // jeżeli nie została podana funkcja to wykonuje się standardowe działanie programy
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
        wczytaj_pierwsze(T,W,w,k,lm);   // pierwsze polecenie bo ono różni się od normalnego wczytywania
        wyswietl_plansze(W,w,k);
        while(D==0)     // dopóki gra trwa (nie jest przegrana bądź wygrana)
        {
            system("cls");      // dla systemu Linux "cls" trzeba zamienić na "clear"
            if(poziom != 4) printf("Aktualna liczba punktow: %d\n\n",poziom*liczba_pol(W,w,k));
            wyswietl_plansze(W,w,k);
            printf("\n");
            wczytaj_polecenie(T,W,w,k,lm);
            if(liczba_pol(W,w,k)==w*k-lm)       // jeżeli wszystkie pola - liczba min są odsłonięte
            {
                D=2;
                printf("Gratulacje! Wygrales!\n");
            }
            if(D!=0 && poziom!=4)       // jeżeli gra została wygrana bądź przegrana
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