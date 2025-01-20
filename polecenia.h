#ifndef _POLECENIA_H
#define _POLECENIA_H

void wyk_r(int T[30][30], int W[30][30], int w, int k, int x, int y);    // funkcja r i przegrana
void wczytaj_polecenie(int T[30][30], int W[30][30], int w, int k, int lm);  // wczytanie polecenia r lub f
void wczytaj_pierwsze(int T[30][30], int W[30][30], int w, int k, int lm);   // wczytanie pierwszego polecenia, zmuszamy użytkownika do polecenia r

#endif