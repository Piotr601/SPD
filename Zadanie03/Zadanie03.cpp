// Zadanie03.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//
#include <iostream>
#include <fstream>
#include <time.h>
#include <ctime>
#include <algorithm>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// do obslugi pliku
string s;
ifstream plik;

//**** DANE Z PLIKU *****//
int liczba_wierszy = 0;
int liczba_kolumn = 0;

//**** WYSWIETLENIE DANYCH ****/
void Wyswietlanie(int* Zadanie, int* Indeks)
{
    cout << " >|<  D A N E  >|< \n\n";

    for (int i = 0; i < liczba_wierszy; i++)
    {
        for (int j = 0; j < liczba_kolumn; j++)
        {
            cout << ' ' << Zadanie[j + i * liczba_kolumn];
        }
        cout << endl;
    }
}

//**** WCZYTANIE DANYCH ****//
void Wczytywanie(string nazwa, int* Zadanie, int* Indeks)
{ 
    // Wczytywanie z pliku
    plik.open("data.txt");

    // Zignorowanie innych danych
    while (s != nazwa)
    {
        plik >> s;
    }

    // Pobranie wybranych danych
    plik >> liczba_wierszy >> liczba_kolumn;
    int ilosc_danych = liczba_wierszy * liczba_kolumn;

    for (int i = 0; i < ilosc_danych; i++)
    {
        plik >> Zadanie[i];
    }

    plik.close();

    // Wyswietlanie ilości pobranych danych
    // cout << " > liczba wierszy: " << liczba_wierszy << endl;
    // cout << " >> liczba kolumn: " << liczba_kolumn <<  " \n\n";

    //Indeksowanie
    for (int i = 0; i < liczba_wierszy; i++)
    {
        Indeks[i] = i;
    }
}

//**** CMAX ****//
int CMAX(int liczba_wierszy, int liczba_kolumn, int *Zadanie, int *Indeks)
{
    // Zadeklarowanie tablicy
    int Tab[50];

    // Uzupełnienie tablicy zerami
    for (int i = 0; i <= liczba_kolumn; i++)
    {
        Tab[i] = 0;
    }

    // Porównywanie i zwracanie największego cmaxa
    for (int i = 0; i < liczba_wierszy; i++)
    {
        for (int j = 1; j <= liczba_kolumn; j++)
        {
            Tab[j] = max(Tab[j], Tab[j - 1]) + Zadanie[(j - 1) + Indeks[i] * liczba_kolumn];
        }
    }
    return Tab[liczba_kolumn];
}

//**** SORTOWANIE ****//
void Sortowanie(int* Waga, int lewa_strona, int prawa_strona, int *Indeks)
{
    // Gdy tablica jest posortowana
    if (prawa_strona <= lewa_strona) return;

    // lewa strona
    int i = lewa_strona - 1;
    // prawa strona
    int j = prawa_strona + 1;
    // punkt odniesienia
    int pivot = Waga[(lewa_strona + prawa_strona) / 2]; 

    while (1)
    {
        // przeszukiwanie lewej czesci
        while (Waga[++i] > pivot);

        // przeszukiwanie prawej czesci
        while (Waga[--j] < pivot);

        // zamienianie elementu, gdy pivoty się nie minęły
        if (i <= j)
        {
            // Zamiana wartości
            swap(Waga[i], Waga[j]);
            swap(Indeks[i], Indeks[j]);
        }
        // gdy wszystko się wykona
        else
            //wyjście z pętli
            break;
    }
    //powtarzanie, gdy prawa strona jest większa
    if (j > lewa_strona)
        // sortowanie
        Sortowanie(Waga, lewa_strona, j, Indeks);
    // powtarzanie, gdy lewa strona jest większa
    if (i < prawa_strona)
        //sortowanie
        Sortowanie(Waga, i, prawa_strona, Indeks);
}

//**** SORTOWANIE BABELKOWE ****//
void Sortowanie2(int* Waga, int liczba_wierszy, int* Indeks)
{
    for (int i = 0; i < liczba_wierszy - 1; i++)
    {
        for (int j = 0; j < liczba_wierszy - 1; j++)
        {
            if (Waga[j] < Waga[j + 1])
            {
                swap(Waga[j], Waga[j + 1]);
                swap(Indeks[j], Indeks[j + 1]);
            }
        }
    }
}

//**** NEH ALGORYTM ****//
int Algorytm_NEH(int liczba_wierszy, int liczba_kolumn, int *Zadanie, int *Indeks)
{
    // Tworzenie dynamicznej tablicy wag
    int* Waga = new int[liczba_wierszy];

    //-------------------------------------------------------------
    // Wypisywanie nieposortowanych wag
    //-------------------------------------------------------------
    for (int i = 0; i < liczba_wierszy; i++)
    {
        Waga[i] = CMAX(1, liczba_kolumn, Zadanie, &i);
        //cout << ' ' << Indeks[i]+1 << ' ' << Waga[i] << endl;
    }
    //-------------------------------------------------------------
     
    // Sortowanie wag - SZYBKIE
    Sortowanie(Waga, 0, liczba_wierszy-1, Indeks);
    
    // SORTOWANIE BABELKOWE
    //Sortowanie2(Waga, liczba_wierszy, Indeks);
    
    /*-------------------------------------------------------------
    // Wypisywanie posortowanych wag
    //-------------------------------------------------------------
    for (int i = 0; i < liczba_wierszy; i++)
    {
        cout << ' ' << Indeks[i]+1 << ' ' << Waga[i] << endl;
    }
    //-------------------------------------------------------------*/
    
    // Zwolnienie pamieci
    delete[] Waga;

    //-------------------------------------------------------------
    //                    A L G O R Y T M
    //-------------------------------------------------------------
    for (int i = 0; i < liczba_wierszy; i++)
    {
        // ustalenie wartości
        int najlepszy_wynik = -1;
        int maksymalny = 999999999;

        // szukanie najlepszej wartości
        for (int j = i; j >= 0; j--)
        {
            int pom = CMAX(i + 1, liczba_kolumn, Zadanie, Indeks);

            if (pom <= maksymalny)
            {
                najlepszy_wynik = j;
                maksymalny = pom;
            }

            // zamiana indeksu
            if (j)
            {
                swap(Indeks[j], Indeks[j - 1]);
            }
        }

        // zamiana indeksu
        for (int k = 0; k < najlepszy_wynik; k++)
        {
            swap(Indeks[k], Indeks[k + 1]);
        }

    }
    // zwracanie najlepszego wyniku
    return CMAX(liczba_wierszy, liczba_kolumn, Zadanie, Indeks);
}

//**** MAIN ****//
int main()
{
    string nazwa;
    int ilosc = 10;

    for (int x = 0; x < 121; x++)
    {
        if (x < 10)
        {
            nazwa = "data.00";
        }

        else if (x < 100)
        {
            nazwa = "data.0";
        }

        else if (x >= 100)
        {
            nazwa = "data.";
        }

        nazwa +=  to_string(x) + ':';
        cout << nazwa;

        time_t start, stop;
        long double t = 0.00000;

        int Zadanie[10001];
        int Indeks[1001];
        // liczenie czasu algorytmów:

        Wczytywanie(nazwa, Zadanie, Indeks);

        // Wyswietlanie(Zadanie, Indeks);
     
        //-------------------------------------------------------------
        // Wyswietlenie CMAXA
        // cout << "\n Cmax: " << CMAX(liczba_wierszy, liczba_kolumn, Zadanie, Indeks) << endl;
        //-------------------------------------------------------------
    
        for (int i = 0; i < ilosc; i++)
        {
            start = clock();
            if(i==0)
                cout << ", NEH: " << Algorytm_NEH(liczba_wierszy, liczba_kolumn, Zadanie, Indeks);
            stop = clock();

            t += (double_t)(stop - start) / CLOCKS_PER_SEC;
        }
        cout << ", Czas: " << t/ilosc << endl;
    }

    /*-------------------------------------------------------------
    // Kolejność końcowa
    for (int i = 0; i < liczba_wierszy; i++)
    {
        cout << " " << Indeks[i] + 1;
    }
    cout << endl;
    //-------------------------------------------------------------*/

    return 0;
}

