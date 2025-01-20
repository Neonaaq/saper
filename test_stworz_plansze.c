#include <stdio.h>
#include <time.h>
#include <stdlib.h>

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
    srand(time(NULL));
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
    for(i=0;i<w;i++)
    {
        for(j=0;j<k;j++)
        {
            printf("%3d",T[i][j]);
        }
        printf("\n");
    }
}
int main()
{
    int T[30][30],i,j;
    for(i=0;i<30;i++)
        for(j=0;j<30;j++)
            T[i][j]=0;
    
    stworz_plansze(T,5,5,5,1,1);
    return 0;
}
