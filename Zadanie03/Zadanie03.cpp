// Zadanie03.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//
#include <iostream>
#include <fstream>
#include <time.h>
#include <ctime>
#include <algorithm>

using namespace std;

// do obslugi pliku
string s;
ifstream plik;

//**** DANE Z PLIKU *****//
int liczba_wierszy = 0;
int liczba_kolumn = 0;

typedef struct dane {
public:
    int Indeks;  
    int Zadanie; 
} dane;

//**** WYSWIETLENIE DANYCH ****/
void Wyswietlanie(struct dane* neh)
{
    for (int i = 0; i < liczba_wierszy; i++)
    {
        for (int j = 0; j < liczba_kolumn; j++)
        {
            cout << ' ' << neh[j + i * liczba_kolumn].Zadanie;
        }
        cout << endl;
    }
}

//**** WCZYTANIE DANYCH ****//
void Wczytywanie(struct dane *neh)
{ 
    // Wczytywanie z pliku
    plik.open("data.txt");

    // Zignorowanie innych danych
    while (s != "data.0:")
    {
        plik >> s;
    }

    // Pobranie wybranych danych
    plik >> liczba_wierszy >> liczba_kolumn;
    int ilosc_danych = liczba_wierszy * liczba_kolumn;

    for (int i = 0; i < ilosc_danych; i++)
    {
        plik >> neh[i].Zadanie;
    }

    plik.close();

    // Wyswietlanie ilości pobranych danych
    cout << " > liczba wierszy: " << liczba_wierszy << endl;
    cout << " >> liczba kolumn: " << liczba_kolumn <<  " \n\n";

    // Wyswietlenie danych
    Wyswietlanie(neh);
}


//**** CMAX ****//
int CMAX(int liczba_wierszy, int liczba_kolumn, struct dane *neh)
{
    int Tab[50];

    for (int i = 0; i <= liczba_kolumn; i++)
    {
        Tab[i] = 0;
    }

    for (int i = 0; i < liczba_wierszy; i++)
    {
        for (int j = 1; j <= liczba_kolumn; j++)
        {
            Tab[j] = max(Tab[j], Tab[j - 1]) + neh[(j - 1) + (i * liczba_kolumn)].Zadanie;
        }
    }
    return Tab[liczba_kolumn];
}

//**** NEH ALGORYTM ****//
int Algorytm_NEH(int liczba_wierszy, int liczba_kolumn, struct dane* neh)
{

}

//**** MAIN ****//
int main()
{
    dane neh[500];

    Wczytywanie(neh);

    for (int i = 0; i < liczba_wierszy; i++)
    {
        neh[i].Indeks = "1234"[i] - '1';
    }

    cout << "\n Cmax: " << CMAX(liczba_wierszy, liczba_kolumn, neh) << endl;
    
    return 0;
}

