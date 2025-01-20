#ifndef _PLANSZE_H
#define _PLANSZE_H

int liczba_pol(int W[30][30], int w, int k);       // liczba odsłoniętych pól
int ile_bomb(int T[30][30], int w, int k,int i, int j);  // liczba bomb wokół danej komórki
void stworz_plansze(int T[30][30], int w,int k, int lm, int x, int y);  // tworzy planszę z uwzględnieniem, że pierwszy ruch to nie jest bomba
void wyswietl_plansze(int W[30][30], int w, int k);  // wyświetla planszę

#endif