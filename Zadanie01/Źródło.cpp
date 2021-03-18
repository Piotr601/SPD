#include <iostream>
#include <fstream>
#include <time.h>
#include <ctime>

using namespace std;

//****************************************//
//                ZMIENNE
//****************************************//

// zmienna wczytujaca ilosc danych w pliku
int n;
// zmienna decyzyjna ( do obslugi switcha i casow)
char a;
// zmienna pomocnicza
int pom1 = 0;

// do obslugi wczytywania z pliku
string s;
ifstream plik;

// struktura wczytanych plikow
typedef struct dane{
public:
    int x;
    int r;
    int p;
    int q;
} dane;

// tablica obiektow
dane rpq[100];

//****************************************//
//               FUNKCJE
//****************************************//

// Wczytywanie z pliku
void Wczytywanie()
{
    // Wczytywanie z pliku
    plik.open("data.txt");

    // wybranie danych
    switch (a)
    {
        case '1':
            while (s != "data.1")
            { plik >> s; }
            break;

        case '2':
            while (s != "data.2")
            { plik >> s; }
            break;

        case '3':
            while (s != "data.3")
            { plik >> s; }
            break;

        case '4':
            while (s != "data.4")
            { plik >> s; }
            break;
        default:
            break;
    }
    plik >> n;

    // wczytanie danych z pliku
    for (int i = 0; i < n; i++)
    {
        rpq[i].x = i;
        plik >> rpq[i].r >> rpq[i].p >> rpq[i].q;
    }

    plik.close();

    // Wyswietlanie ilosci danych
    cout << " >>> n = " << n << " <<<\n\n";

    // Wyswietlenie procesow ( danych )
    for (int i = 0; i < n; i++)
    {
        cout << rpq[i].x << ") " << rpq[i].r << " " << rpq[i].p << " " << rpq[i].q << " " <<endl;
    }
}

// Funkcja zliczajaca calkowity czas wykonania
int cmax(int n, dane rpq[100])
{
    int m = 0, c = 0;
    for (int i = 0; i < n; i++)
    {
        int id = rpq[i].x;
        m = max(m, rpq[id].r) + rpq[id].p;
        c = max(c, m + rpq[id].q);
    }
    // zmienna pomocnicza do zliczania sumy
    pom1 = c;
    return c;
}

// Algorytm
void Algorytm(int n, dane rpq[100])
{
    // zmienna pomocnicza do porownania
    int pom = cmax(n, rpq);

    // petla dzieki ktorej pomiary sa dokladniejsze
    // wczesniej wychodzilo 10537
    // a teraz z nia 10370
    for (int x = 0; x < 6; x++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n - 1; j++)
            {
                // zamiana miejscami
                swap(rpq[n - j - 1].x, rpq[n - j - 2].x);
                
                // gdy cmax jest mniejsze/rowne po zamianie, to nastepuje
                // przypisanie nowego cmaxa
                // DAZYMY DO ZMINIMALIZOWANIA CMAX
                if (cmax(n, rpq) <= pom)
                {
                    pom = cmax(n, rpq);
                }
                // gdy cmax rosnie po zamianie, wtedy wracamy do
                // stanu poczatkowego i bierzemy nastepny indeks
                else
                {
                    swap(rpq[n - j - 1].x, rpq[n - j - 2].x);
                }
                // Algorytm ten porownuje dane, a takze sprawdza
                // czy jest to oplacalne, a gdy nie jest, operacja
                // zamiany jest cofana.
                // Taki algorytm wykonuje sie w przypadku:
                // 24 danych ~ 3500 operacji
                // 48 danych ~ 14000 operacji
                // mozna stwierdzic ze jego zlozonosc wynosi
                // O(n^2), bo mamy wzor 6*n^2
            }
        }
    }
}

// Wyswietlanie wynikow
void Wyswietlanie()
{
    // Wyœwietlanie kolejnoœci
    cout << "\nKolejnosc: \n";

    for (int i = 0; i < n; i++)
    {
        cout << rpq[i].x + 1 << " ";
    }

    // Wyœwietlanie wyniku CMAX
    cout << "\nCmax: " << cmax(n, rpq) << endl;

}

//****************************************//
//                 MAIN
//****************************************//

int main()
{
    int zliczaj = 0;

    // do mierzenia czasu
    time_t start, stop;
    double t = 0;

    // Podawanie wyboru
    while (a != '5')
    {
        cout << "\n|=============|\n";
        cout << "| 1) Dane 1   |\n| 2) Dane 2   |\n| 3) Dane 3   |\n| 4) Dane 4   |\n| 5) Wyjscie  |" << endl;
        cout << "|=============|\n\n >> Twoj wybor: ";
        cin >> a;
        
        if (a != '5')
        {
            Wczytywanie();

            start = clock();
            Algorytm(n, rpq);
            stop = clock();
            
            t += (double_t)(stop - start) / CLOCKS_PER_SEC;
                
            zliczaj += pom1;
            Wyswietlanie();
        }
    }
    
    // Suma z poprzednich dzialan
    // Aby zmierzyc sume wszystkich algorytmow:
    // Wystarczy wpisac 1, 2, 3, 4, 5 w programie 

    cout << "\nWynik z dzialan: " << zliczaj << endl;
    // CZAS WYKONANIA SAMEGO ALGORYTMU/AlGORYTMOW
    cout << "Czas wykonania: " << t << endl;
    
    cin.get();
    return 0;
}