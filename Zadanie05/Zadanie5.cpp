// Zadanie5.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// do obslugi wczytywania z pliku
string s;
ifstream plik;

void Blok(int N, int* R, int* P, int* Q, int* X, int& J, int& JR, int& JQ)
{
	int cMax = 0;
	int m = 0;
	int pos = -1;
	J = -1;

	int* tmp = new int[N];

	for (int i = 0; i < N; i++)
	{
		int j = X[i];
		//m = max(m, R[j]) + P[j];
		if (m < R[j])
		{
			m = R[j] + P[j];
			tmp[i] = 0;
		}
		else
		{
			m = m + P[j];
			tmp[i] = 1;
		}

		if (cMax < m + Q[j])
		{
			cMax = m + Q[j];
			pos = i;
		}

	}

	int qB = Q[X[pos]];
	int rB = R[X[pos]];
	int pB = P[X[pos]];


	while(tmp[pos] == 1)
	{
		//cout << pos+1 << " ";
		if (Q[X[--pos]] < qB)
		{
			J = X[pos];
			break;
		}

		rB = min(rB, R[X[pos]]);
		pB = pB + P[X[pos]];
	}
	//cout << rB << " " << pB << " " << qB << " " << endl;
	
	JR = rB + pB;
	JQ = qB + pB;

	delete[] tmp;
}

// Algorytm Schrage
int Schrage(int N, int* R, int* P, int* Q, int* X)
{
	//=======================================//
	// Stan == 0  | Zadanie do rozpatrzenia  //
	// Stan == 1  | Zadanie do wykonania     //
	// Stan == 2  | Zadanie wykonane         //
	//=======================================//

	int Stan[100];
	int czas = 0;
	int cmax = 0;

	// Zadanie niedostępne
	for (int i = 0; i < N; i++)
	{
		Stan[i] = 0;
	}

	for (int j = 0; j < N; j++)
	{
		int maxQ = 0;
		int maxI = 0;
		int l_zadan = 0;

		// Wyznaczenie zadan dostepnych
		for (int i = 0; i < N; i++)
		{
			if ((R[i] <= czas) && (Stan[i] != 2))
			{
				Stan[i] = 1;
				l_zadan++;
			}
		}

		// jezeli wystepuje brak zadan
		if (l_zadan == 0)
		{
			czas = 99999999;

			for (int i = 0; i < N; i++)
			{
				if (Stan[i] == 0)
				{
					czas = min(czas, R[i]);
				}
			}

			// wyznaczanie zadan dostepnych
			for (int i = 0; i < N; i++)
			{
				if ((R[i] <= czas) && (Stan[i] != 2))
					Stan[i] = 1;
			}
		}

		maxQ = -1;

		// szukanie zadania o najwiekszym q
		for (int i = 0; i < N; i++)
		{
			if (Stan[i] == 1)
			{
				if (Q[i] > maxQ)
				{
					maxI = i;
					maxQ = Q[i];
				}
			}
		}

		X[j] = maxI;
		czas += P[maxI];

		Stan[maxI] = 2;
		cmax = max(cmax, czas + Q[maxI]);
	}

	return cmax;
}


int SchrageP(int N, int* R, int* P, int* Q)
{
	int t = 0;
	int NO = -1;
	int cmax = 0;
	int inf = 99999999;

	int pomN = N;

	int* pomP = new int[N];
	int* temp = new int[N];
	
	for (int i = 0; i < N; i++)
	{
		pomP[i] = P[i];
		temp[i] = 0;
	}

	while (pomN != 0)
	{
		int oper = inf;

		int* zbior = new int[2];
		zbior[0] = zbior[1] = 0;

		for (int i = 0; i < N; i++)
		{
			if ((R[i] <= t) && (temp[i] != inf))
			{
				temp[i] = 2;
				zbior[0]++;
			}
			if (temp[i] == 0) 
				zbior[1]++;
		}

		if (zbior[1] != 0)
		{
			for (int i = 0; i < N; i++)
			{
				if (temp[i] == 0)
					oper = min(oper, R[i]);
			}
		}
		else
		{
			oper = inf;
		}

		if (zbior[0] != 0)
		{
			int tempQ = -inf;
			int tempP = -inf;

			for (int i = 0; i < N; i++)
			{
				if ((temp[i] == 2) && (tempQ < Q[i]))
				{
					tempQ = Q[i]; tempP = pomP[i];
					NO = i;
				}
			}

			int sumt = t + tempP;

			if (oper < sumt)
			{
				tempP = tempP - (oper - t);
				pomP[NO] = tempP;
				t = oper;
			}
			else
			{
				temp[NO] = inf;
				pomN--;	
				t = sumt;

				cmax = max(cmax, tempQ + t);
			}
		}
		else
		{
			t = oper;
		}

		delete[] zbior;
	}

	delete[] pomP;
	delete[] temp;

	return cmax;
}


void Carier(int N, int* R, int* P, int* Q, int& UB)
{
	int sCmax;
	int sPerm[100];

	// TUTAJ DAC ALGORYTM SCHRANGE Z PODZIALEM
	if (SchrageP(N, R, P, Q) >= UB)
		return;

	sCmax = Schrage(N, R, P, Q, sPerm);

	if (sCmax < UB)
	{
		UB = sCmax;
	}

	int j, jr, jq;
	Blok(N, R, P, Q, sPerm, j, jr, jq);

	if (j == -1)
		return;

	int tmpR = R[j];
	R[j] = jr;
	Carier(N, R, P, Q, UB);
	R[j] = tmpR;

	int tmpQ = Q[j];
	Q[j] = jq;
	Carier(N, R, P, Q, UB);
	Q[j] = tmpQ;


}


/// MAIN
int main()
{
    int N, R[100], P[100], Q[100], X[100];

	// WCZYTYWANIE

	string nazwa;

	for (int i = 0; i < 9; i++)
	{
		plik.open("data.txt");
		nazwa = "data.00" + to_string(i) + ':';

		while (s != nazwa)
			plik >> s;

		plik >> N;

		for (int i = 0; i < N; i++)
		{
			X[i] = i;
			plik >> R[i] >> P[i] >> Q[i];

		}
		plik.close();
		// KONIEC WCZYTYWANIA

		int cmax;

		//cout << N << endl;

		Carier(N, R, P, Q, cmax = 999999999);

		cout << nazwa;
		cout << "\nCmax: " << cmax << endl << endl;
	}

	return 0;
}

