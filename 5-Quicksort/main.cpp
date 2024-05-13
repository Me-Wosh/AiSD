// Milosz Samotyjak
// Grupa 235 IC B1
// AISD 5 - quicksort

#include <iostream>
#include <random>

void print_array(int* arr, int start, int end);
void quick_sort(int* arr, int left, int right);

void print_array(int* arr, int start, int end)
{
    for (int i = start; i <= end; i++)
    {
        std::cout << arr[i];

        if (i < end)
        {
            std::cout << " ";
        }
    }
}

void quick_sort(int* arr, int left, int right)
{
    std::cout << "sprawdzana tablica: ";
    print_array(arr, left, right);

    int pivotIndex = (left + right) / 2;
    int pivot = arr[pivotIndex];

    std::cout << ", pivot: " << pivot << std::endl << std::endl;

    int i = left;
    int j = i;

    std::cout << "zamiana ostatniego elementu (" << arr[right] << ") z pivotem (" << pivot << ") zeby pivot nie ";
    std::cout << "przeszkadzal w porownaniach" << std::endl;

    std::swap(arr[pivotIndex], arr[right]);

    while (i < right)
    {
        std::cout << "stan tablicy: ";
        print_array(arr, left, right);
        std::cout << std::endl << std::endl;

        std::cout << "i: " << i << ", j: " << j << std::endl;

        std::cout << "czy arr[i] (" << arr[i] << ") jest mniejsze od pivot (" << pivot << ") ?" << std::endl;
        if (arr[i] < pivot)
        {
            std::cout << "tak, zamien arr[i] (" << arr[i] << ") z arr[j] (" << arr[j] << ")" << std::endl;

            std::swap(arr[i], arr[j]);

            std::cout << "zwieksz j" << std::endl;
            j++;

            std::cout << "zwieksz i" << std::endl << std::endl;
            i++;
        }

        else
        {
            std::cout << "nie" << std::endl;
            std::cout << "zwieksz i" << std::endl << std::endl;
            i++;
        }
    }

    std::cout << "stan tablicy: ";
    print_array(arr, left, right);
    std::cout << std::endl << std::endl;

    arr[right] = arr[j];

    std::cout << "ustaw pivot (" << pivot << ") na jego wlasciwe miejsce zamieniajac go z arr[j] (" << arr[j] << ")";
    std::cout << " czyli pierwszym elementem ktory byl wiekszy badz rowny pivotowi" << std::endl;

    arr[j] = pivot;

    std::cout << "stan tablicy: ";
    print_array(arr, left, right);
    std::cout << std::endl << std::endl;

    std::cout << "czy tablica na lewo od pivot (" << pivot << ") ma wiecej niz 1 element? " << std::endl;

    if (left < j - 1)
    {
        std::cout << "tak, wykonaj poprzednie instrukcje dla lewej czesci tablicy" << std::endl << std::endl;
        quick_sort(arr, left, j - 1);
    }

    else
    {
        std::cout << "nie" << std::endl << std::endl;
    }

    std::cout << "czy tablica na prawo od pivot (" << pivot << ") ma wiecej niz 1 element? " << std::endl;

    if (j + 1 < right)
    {
        std::cout << "tak, wykonaj poprzednie instrukcje dla prawej czesci tablicy" << std::endl << std::endl;
        quick_sort(arr, j + 1, right);
    }

    else
    {
        std::cout << "nie" << std::endl << std::endl;
    }
}

int main()
{
    // niedeterministyczny generator liczb losowych
    std::random_device random_device;

    // generator Mersenne Twister 19937
    std::mt19937 generator(random_device());

    // losuj liczby z przedzialu od 0 do 100
    std::uniform_int_distribution<int> distribution(0, 100);

    int n = 10;

    // utworzenie n elementowej tablicy
    int arr[n];

    // wypelnienie tablicy n losowymi elementami z przedzialu 0-100
    for (int i = 0; i < n; i++)
    {
        arr[i] = distribution(generator);
    }

    std::cout << "przed quicksort: " << std::endl;
    print_array(arr, 0, n - 1);
    std::cout << std::endl << std::endl;

    quick_sort(arr, 0, n - 1);

    std::cout << "po quicksort: " << std::endl;
    print_array(arr, 0, n - 1);

    return 0;
}