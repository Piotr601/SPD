#include <iostream>
#include <fstream>
#include <time.h>
#include <ctime>
#include <algorithm>

using namespace std;

// liczba zadan
int n = 0; 
int pomtime;

// do obslugi pliku
string s;
ifstream plik;

// struktura danych (wczytanych plikow)
typedef struct dane {
public:
    int t;  // czas wykonania zadania
    int w;  // współczynnik kary 
    int r;  // żądany termin zakończenia zadania
    int x;  // kolejnosc
} dane;

dane witi[20];

// wczytywanie danych
void Wczytywanie() 
{
    // Wczytywanie z pliku
    plik.open("data.txt");
    
    while (s != "data.20")
    {
        plik >> s;
    }
    plik >> n;

    for (int i = 0; i < n; i++)
    {
        witi[i].x = i;
        plik >> witi[i].t >> witi[i].w >> witi[i].r;
    }

    plik.close();

    // Wyswietlanie ilosci danych
    cout << " >>> n = " << n << " <<<\n\n";

    // Wyswietlenie procesow ( danych )
    for (int i = 0; i < n; i++)
    {
        cout << witi[i].x << ") " << witi[i].t << " " << witi[i].w << " " << witi[i].r << " " << endl;
    }
}

void Algorytm()
{
    // pomocnicza liczaca ilosc operacji
    int s = 0;

    // zmienna przechowująca ilosc operacji w postaci
    // poteg 2, np w przypadku 10 // 2^10
    int bit = 1 << n; 

    // zmienne dynamiczne
    int* F = new int[bit];
    
    // Wyzerowanie pierwszego elementu tablicy dynamicznej
    F[0] = 0;

    // dla wszystkich bitów
    for (int bitcount = 1; bitcount < bit; bitcount++)  // od 1 do 2^bit ( w przypadku 10 // 1023)
    {
        // liczenie ilosci rozwiązań
        pomtime = 0;
        for (int i = 0, b = 1; i < n; i++, b *= 2) // b = 1, 2, 4, 8, ..
        {
            if (bitcount & b)
            {
                pomtime += witi[i].t;
            }
        }

        // ustawienie ostatniej wartosci na maksymalną
        F[bitcount] = 999999;

        for (int j = 0, b = 1; j < n; j++, b *= 2)
        {
            if (bitcount & b)
            {
                // wybranie mniejszej wartosci ( 99999, 
                F[bitcount] = min( F[bitcount], F[bitcount - b] + witi[j].w * max( pomtime - witi[j].r, 0 ) ) ;

                //if ( F[bitcount] == F[bit - 1] )
                //{
                    //witi[j].x = F[bitcount - b];
                    //cout << witi[j].x << " ";
                //}
            }
        }
    }
    
    //cout << "\nIlosc operacji: " << bit << endl;
    //cout << "Optymalne rozwiazanie: " << F[bit - 1] << endl;

    delete[] F;
}

int main()
{
    // WCZYTYWANIE DANYCH
    Wczytywanie();

    // do mierzenia czasu
    int ilosc_powt = 1000;
    time_t start, stop;
    double t = 0;

    // ALGORYTM
    for (int i = 0; i < ilosc_powt; i++)
    {
        start = clock();
        Algorytm();
        stop = clock();

        t += (double_t)(stop - start) / CLOCKS_PER_SEC;
    }

    // CZAS WYKONANIA SAMEGO ALGORYTMU
    cout << "\nCzas wykonania: " << t/ilosc_powt << endl;
}


