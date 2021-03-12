// Zadanie01.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <fstream>

using namespace std;
int main()
{

    int n, R[100], P[100], Q[100];

    ifstream plik;
    plik.open("data.txt");
    
    string s;
    while (s != "data.1")
    {
        plik >> s;
    }
    plik >> n;
    
    for (int i = 0; i < n; i++)
    {
        plik >> R[i] >> P[i] >> Q[i];
    }
    plik.close();

    cout << "n = " << n << endl;
    for (int i = 0; i < n; i++)
    {
        cout << R[i] << " " << P[i] << " " << Q[i] << endl;
    }
   
}
