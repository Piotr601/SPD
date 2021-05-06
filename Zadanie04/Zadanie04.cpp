// Zadanie04.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#define MAKS	1000

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

using namespace std;

// zmienna wczytujaca ilosc danych w pliku
int n;

// do obslugi wczytywania z pliku
string s;
ifstream plik;

// struktura wczytanych plikow
typedef struct dane {
public:
	int x;
	int r;
	int p;
	int q;
}dane;

//****************************************//
//               FUNKCJE
//****************************************//

// Wczytywanie
void Wczytywanie(string nazwa, dane rpq[MAKS])
{
	plik.open("data.txt");

	while (s != nazwa)
		plik >> s;
	
	plik >> n;

	// wczytanie danych z pliku
	for (int i = 0; i < n; i++)
	{
		rpq[i].x = i;
		plik >> rpq[i].r >> rpq[i].p >> rpq[i].q;

	}

	plik.close();

	// Wyswietlanie ilosci danych
	//cout << " >>> n = " << n << " <<<\n\n";

	// Wyswietlenie procesow ( danych )
	//for (int i = 0; i < n; i++)
	//{
	//	cout << " " << rpq[i].x << ") " << rpq[i].r << " " << rpq[i].p << " " << rpq[i].q << " " << endl;
	//}
}

// Wyswietlanie wynikow
void Wyswietlanie(dane rpq[MAKS])
{
	// Wyświetlanie kolejności
	cout << "\n Kolejnosc: \n ";

	for (int i = 0; i < n; i++)
	{
		cout << rpq[i].x + 1 << " ";
	}
	cout << endl;
}

// Algorytm Schrage
void Schrage(dane rpq[MAKS], int krok)
{
	//=======================================//
	// Stan == 0  | Zadanie do rozpatrzenia  //
	// Stan == 1  | Zadanie do wykonania     //
	// Stan == 2  | Zadanie wykonane         //
	//=======================================//

	int Stan[MAKS];
	int czas = 0;
	int cmax = 0;

	// Zadanie niedostępne
	for (int i = 0; i < n; i++)
	{
		Stan[i] = 0;
	}

	for(int j = 0; j < n; j++)
	{ 	
		int maxQ = 0;
		int maxI = 0;
		int l_zadan = 0;

		// Wyznaczenie zadan dostepnych
		for (int i = 0; i < n; i++)
		{
			if ((rpq[i].r <= czas) && (Stan[i] != 2))
			{
				Stan[i] = 1;
				l_zadan++;
			}
		}
		
		// jezeli wystepuje brak zadan
		if (l_zadan == 0)
		{
			czas = 99999999;

			for (int i = 0; i < n; i++)
			{
				if (Stan[i] == 0)
				{
					czas = min(czas, rpq[i].r);
				}
			}

			// wyznaczanie zadan dostepnych
			for (int i = 0; i < n; i++)
			{
				if ((rpq[i].r <= czas) && (Stan[i] != 2))
					Stan[i] = 1;
			}
		}

		maxQ = -1;
		
		// szukanie zadania o najwiekszym q
		for (int i = 0; i < n; i++)
		{
			if (Stan[i] == 1)
			{
				if (rpq[i].q > maxQ)
				{
					maxI = i;
					maxQ = rpq[i].q;
				}
			}
		}

		rpq[j].x = maxI;
		czas += rpq[maxI].p ;

		Stan[maxI] = 2;
		cmax = max(cmax, czas + rpq[maxI].q);
	}

	if (krok == 0)
	{
		cout << "\n Schrange: " << cmax << endl;
	}
}

/*
void SchragePodzial(int n, dane rpq[MAKS])
{
	//=======================================//
	// Stan == 0  | Zadanie do rozpatrzenia  //
	// Stan == 1  | Zadanie do wykonania     //
	// Stan == 2  | Zadanie wykonane         //
	//=======================================//

	int Stan[MAKS];
	int czas = 0;
	int cmax = 0;
	int k = 0;


	cout << "\n Szrange podzial: " << cmax << endl;
}
*/

int main()
{
	// tablica obiektow
	dane rpq[MAKS];

	// OBSLUGA DANYCH
	string nazwa;
	int ilosc = 8;

	int powt = 100000;
	time_t start, stop;
	long double t = 0.00000;

	for (int i = 0; i <= ilosc; i++)
	{
		nazwa = "data.00" + to_string(i) + ':';

		cout << "\n (#) " <<nazwa << endl;
		// Wczytywanie danych
		Wczytywanie(nazwa, rpq);

		// Algorytm
		for (int krok = 0; krok < powt; krok++)
		{
			start = clock();
			Schrage(rpq, krok);
			stop = clock();
		
			t += (double_t)(stop - start) / CLOCKS_PER_SEC;
		}

		// Algorytm 2
		//SchragePodzial(n,rpq);

		// Wyswietlanie kolejnosci
		Wyswietlanie(rpq);

		cout << "\n (-) Czas: " << t / powt << endl << endl;
		cout << "-----------------------------------------------------------------------------------------------------------\n";
	}

	cout << "\n";
	return 0;
}