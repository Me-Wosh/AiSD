/*
 Milosz Samotyjak
 Grupa 235 IC B1
 Algorytmy sortowania:
    - sortowanie babelkowe,
    - sortowanie przez selekcje,
    - sortowanie przez wstawianie,
    - sortowanie przez scalanie
*/

#include <iostream>
using namespace std;

void PrintArray(int tab[], int n, int start = 0)
{
    for (int i = start; i < n; i++)
    {
        cout << tab[i] << " ";
    }

    cout << endl;
}

// Sortowanie babelkowe
void BubbleSort(int tab[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (tab[i] > tab[j])
            {
                int temp = tab[i];
                tab[i] = tab[j];
                tab[j] = temp;

                PrintArray(tab, n);
            }

            else
            {
                PrintArray(tab, n);
            }
        }
    }
}

// Sortowanie przez selekcje
void SelectionSort(int tab[], int n)
{
    for (int j = 0; j < n - 1; j++)
    {
        int minIndex = j;

        for (int i = j; i < n; i++)
        {
            if (tab[minIndex] > tab[i])
            {
                minIndex = i;
            }
        }

        int temp = tab[minIndex];
        tab[minIndex] = tab[j];
        tab[j] = temp;

        PrintArray(tab, n);
    }
}

// Sortowanie przez wstawianie
void InsertionSort(int tab[], int n)
{
    for (int j = n - 2; j >= 0; j--)
    {
        int temp = tab[j];
        int i = j + 1;

        while (i < n && temp > tab[i])
        {
            tab[i - 1] = tab[i];
            i++;
            PrintArray(tab, n);
        }

        tab[i - 1] = temp;
        PrintArray(tab, n);
    }
}

// Sortowanie przez scalanie
void MergeSort(int tab[], int pom[], int poczatek, int koniec)
{
    int srodek = (poczatek + koniec + 1) / 2;

    cout << "Sprawdzanie podzielnosci tablicy: ";
    PrintArray(tab, srodek, poczatek);

    if(srodek - poczatek > 1){
        cout << "Dzielenie na pol tablicy: ";
        PrintArray(tab, koniec + 1, poczatek);

        MergeSort(tab, pom, poczatek, srodek - 1);
    }

    else if (srodek - poczatek <= 1)
    {
        cout << "Brak potrzeby dzielenia" << endl;
    }

    cout << "Sprawdzana tablica: ";
    PrintArray(tab, koniec + 1, srodek);

    if(koniec - srodek > 0){
        cout << "Dzielenie na pol tablicy: ";
        PrintArray(tab, koniec + 1, srodek);

        MergeSort(tab, pom, srodek, koniec);
    }

    else if (koniec - srodek <= 0)
    {
        cout << "Brak potrzeby dzielenia" << endl;
    }

    int i1 = poczatek;
    int i2 = srodek;

    cout << "Scalenie tablicy: ";
    PrintArray(tab, srodek, poczatek);
    cout << "i tablicy: ";
    PrintArray(tab, koniec + 1, srodek);

    for(int i = poczatek; i <= koniec; i++){
        if ((i1 == srodek) || ((i2 <= koniec) && (tab[i1] > tab[i2]))){
            pom[i] = tab[i2];
            i2++;
        }

        else{
            pom[i] = tab[i1];
            i1++;
        }
    }

    for(int i = poczatek; i <= koniec; i++){
        tab[i] = pom[i];
    }

    cout << "Utworzenie posortowanej tablicy: ";
    PrintArray(tab, koniec + 1, poczatek);
}

int main()
{
    int n, x;

    cout << "Podaj liczbe elementow: ";
    cin >> n;

    int originalArray[n], tab[n];
    cout << "Podaj elementy tablicy: ";

    for (int i = 0; i < n; i++)
    {
        cin >> originalArray[i];
    }

    copy(originalArray, originalArray+n, tab);

    cout << "=======Menu=======" << endl;
    cout << "0 - wyjscie z programu" << endl;
    cout << "1 - sortowanie babelkowe" << endl;
    cout << "2 - sortowanie przez selekcje" << endl;
    cout << "3 - sortowanie przez wstawianie" << endl;
    cout << "4 - sortowanie przez scalanie" << endl;

    while (true)
    {
        cout << "Wybierz numer: ";
        cin >> x;

        switch (x)
        {
            case 1:
            {
                cout << "Sortowanie babelkowe" << endl;

                cout << "Przed posortowaniem:" << endl;
                PrintArray(tab, n);

                cout << "W trakcie sortowania:" << endl;
                BubbleSort(tab, n);

                cout << "Po posortowaniu:" << endl;
                PrintArray(tab, n);

                copy(originalArray, originalArray + n, tab);

                break;
            }

            case 2:
            {
                cout << "Sortowanie przez selekcje" << endl;

                cout << "Przed posortowaniem:" << endl;
                PrintArray(tab, n);

                cout << "W trakcie sortowania:" << endl;
                SelectionSort(tab, n);

                cout << "Po posortowaniu:" << endl;
                PrintArray(tab, n);

                copy(originalArray, originalArray + n, tab);

                break;
            }

            case 3:
            {
                cout << "Sortowanie przez wstawianie" << endl;

                cout << "Przed posortowaniem:" << endl;
                PrintArray(tab, n);

                cout << "W trakcie sortowania:" << endl;
                InsertionSort(tab, n);

                cout << "Po posortowaniu:" << endl;
                PrintArray(tab, n);

                copy(originalArray, originalArray + n, tab);

                break;
            }

            case 4:
            {
                int pom[n];

                cout << "Sortowanie przez scalanie" << endl;

                cout << "Przed posortowaniem:" << endl;
                PrintArray(tab, n);

                cout << "W trakcie sortowania:" << endl;
                MergeSort(tab, pom, 0, n - 1);

                cout << "Po posortowaniu:" << endl;
                PrintArray(tab, n);

                copy(originalArray, originalArray + n, tab);

                break;
            }

            case 0:
            {
                exit(0);
            }

            default:
            {
                cout << "Wybrano zly numer" << endl;
                break;
            }
        }
    }
}
