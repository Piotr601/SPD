#include <iostream>
#include <fstream>
#include <time.h>
#include <ctime>

using namespace std;

// liczba zadan
int n = 0; 

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
    
    while (s != "data.10")
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

int main()
{
    Wczytywanie();
    
}


