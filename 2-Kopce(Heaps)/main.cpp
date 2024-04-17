// Milosz Samotyjak
// Grupa 235 IC B1
// AISD 2 - kopce

#include <iostream>
using namespace std;

// kompilator Clang (https://opensource.apple.com/projects/llvm-clang/)
// koniecznie chce zeby tablica byla przekazana jako referencja mimo ze
// na moj stan wiedzy domyslnie tablice sa typem referencyjnym?
// w przeciwnym razie kod nie dziala prawidlowo, stad zapis int*& array

// flaga ktora kontroluje wyswietlanie prawidlowego kopca zamiast pomocniczego
bool print_flag = false;

void swap_down(int*& heap, int i, int& size);
void heapify(int*& heap, int& size);
void heap_insert(int*& heap, int& size, int element);
void heap_pop(int*& heap, int& size);
void heap_sort(int*& heap, int size);
void array_insert(int*& array, int& size, int value);
void array_pop(int*& array, int& size);
void array_print(int* array, int size);

void swap_down(int*& heap, int i, int& size)
{
    // lewe dziecko ze wzoru indeks * 2 + 1
    int left_child = i * 2 + 1;
    // prawe dziecko ze wzoru indeks * 2 + 2
    int right_child = i * 2 + 2;
    int max = i;

    // szukaj najwiekszego elementu sposrod heap[i] i jego lewego dziecka
    if (left_child < size && heap[left_child] > heap[max])
    {
        max = left_child;
    }

    // szukaj najwiekszego elementu sposrod heap[i], jego lewego i prawego dziecka
    if (right_child < size && heap[right_child] > heap[max])
    {
        max = right_child;
    }

    // jezeli znaleziono dziecko wieksze od heap[i] to zamien miejscami heap[i] z dzieckiem
    if (max != i)
    {
        int temp = heap[i];
        heap[i] = heap[max];
        heap[max] = temp;

        if (!print_flag)
        {
            array_print(heap, size);
        }

        // wywolaj funkcje tym razem zaczynajac od dawnego indeksu znalezionego wiekszego dziecka
        swap_down(heap, max, size);
    }

    // w przeciwnym razie wyjdz z rekurencji
    else
    {
        return;
    }
}

void heapify(int*& heap, int& size)
{
    // wywoluj funkcje swap_down za kazdym razem na o 1 mniejszym indeksie zaczynajac od
    // indeksu rozmiar / 2 az do indeksu 0 celem uporzadkowania kopca wedlug zalozen tej struktury
    for (int i = size / 2; i >= 0; i--)
    {
        swap_down(heap, i, size);
    }
}

void heap_insert(int*& heap, int& size, int element)
{
    array_insert(heap, size, element);
    array_print(heap, size);

    // ostatni indeks kopca
    int i = size - 1;

    // indeks rodzica ostatniego elementu
    int parent = (i - 1) / 2;

    // dopoki znajdowane bedzie dziecko wieksze od rodzica zamieniaj dziecko z
    // rodzicem miejscami
    // poniewaz korzystamy ze struktury max heap - wartosc rodzica zawsze musi byc
    // wieksza od wartosci dziecka
    while (i > 0 && heap[i] > heap[parent])
    {
        int temp = heap[parent];
        heap[parent] = heap[i];
        heap[i] = temp;

        i = parent;
        parent = (i - 1) / 2;

        array_print(heap, size);
    }
}

void heap_pop(int*& heap, int& size)
{
    // ustawienie korzenia na wartosc ostatniego elementu
    heap[0] = heap[size - 1];

    size--;

    // realokacja pamieci dla kopca mniejszego o jeden element
    int* new_heap = (int*)realloc(heap, size * sizeof(int));
    heap = new_heap;

    if (!print_flag)
    {
        array_print(heap, size);
    }

    // wywolanie heapify celem reorganizacji elementow wedlug zalozen struktury
    // danych max heap
    heapify(heap, size);
}

void heap_sort(int*& heap, int size)
{
    print_flag = true;

    // kopia rozmiaru kopca utworzona w celu wyswietlania jego elementow
    // w trakcie dzialania sortowania
    int initial_size = size;

    // pomocniczy kopiec z ktorego beda usuwane elementy
    int* helper_heap = (int*)malloc(size * sizeof(int));

    // przypisanie elementow do pomocniczego kopca
    for (int i = 0; i < size; i++)
    {
        helper_heap[i] = heap[i];
    }

    while (size > 0)
    {
        // ustawianie ostatniego elementu kopca na pierwszy element pomocniczego kopca
        // pierwszy element zawsze bedzie najwiekszym elementem poniewaz taka jest
        // wlasnosc struktury danych max heap
        heap[size - 1] = helper_heap[0];

        array_print(heap, initial_size);

        // usuniecie pierwszego elementu z pomocniczego kopca poniewaz nie jest juz
        // potrzebny i wydluzalby czas poszukiwan
        heap_pop(helper_heap, size);
    }

    print_flag = false;

    // zwolnienie pamieci przeznaczonej na pomocniczy kopiec
    free(helper_heap);
}

void array_insert(int*& array, int& size, int value)
{
    // zwiekszenie rozmiaru tablicy
    size++;

    // alokacja pamieci dla tablicy wiekszej o jeden element
    int* new_array = (int*)realloc(array, size * sizeof(int));
    array = new_array;

    // dodanie nowego elementu na koniec tablicy
    array[size - 1] = value;
}

void array_pop(int*& array, int& size)
{
    // przesuniecie elementow w lewo
    for (int i = 0; i < size - 1; i++)
    {
        array[i] = array[i + 1];
    }

    size--;
    // alokacja pamieci dla tablicy mniejszej o 1 element spowoduje "uciecie" ostatniego elementu
    int* new_array = (int*)realloc(array, size * sizeof(int));
    array = new_array;
}

void array_print(int* array, int size)
{
    // wypisywanie elementow tablicy
    for (int i = 0; i < size; i++)
    {
        cout << array[i] << " ";
    }

    cout << endl;
}

int main()
{
    // =============== tablica dynamiczna ===============
    const int array[] = {1, 2, 3, 4, 5};

    // sizeof(array) pobiera rozmiar tablicy w bajtach dlatego trzeba dodatkowo podzielic
    // przez rozmiar integera w bajtach zeby uzyskac liczbe elementow
    int arr_size = sizeof(array) / sizeof(int);

    int* dynamic_array = (int *)malloc(arr_size * sizeof(int));

    for (int i = 0; i < arr_size; i++)
    {
        dynamic_array[i] = array[i];
    }

    cout << "======= tablica dynamiczna =======" << endl;

    cout << "na poczatku: " << endl;
    array_print(dynamic_array, arr_size);
    cout << endl;

    array_insert(dynamic_array, arr_size, 6);
    cout << "array_insert: " << endl;
    array_print(dynamic_array, arr_size);
    cout << endl;

    cout << "array_insert: " << endl;
    array_insert(dynamic_array, arr_size, 7);
    array_print(dynamic_array, arr_size);
    cout << endl;

    cout << "array_insert: " << endl;
    array_insert(dynamic_array, arr_size, 8);
    array_print(dynamic_array, arr_size);
    cout << endl;

    cout << "array_insert: " << endl;
    array_insert(dynamic_array, arr_size, 9);
    array_print(dynamic_array, arr_size);
    cout << endl;

    cout << "array_pop: " << endl;
    array_pop(dynamic_array, arr_size);
    array_print(dynamic_array, arr_size);
    cout << endl;

    cout << "array_pop: " << endl;
    array_pop(dynamic_array, arr_size);
    array_print(dynamic_array, arr_size);
    cout << endl;

    // czyszczenie pamieci przeznaczonej na tablice dynamiczna
    free(dynamic_array);

    // =============== kopiec ===============
    const int helper_array[12] =
        { 5, 17, 12, 13, 6, 9, 10, 7, 11, 4, 2, 8 };
    int heap_size = sizeof(helper_array) / sizeof(int);
    int* heap = (int*)malloc(heap_size * sizeof(int));

    for (int i = 0; i < heap_size; i++)
    {
        heap[i] = helper_array[i];
    }

    cout << "============= kopiec =============" << endl;

    cout << "na poczatku: " << endl;
    array_print(heap, heap_size);
    cout << endl;

    cout << "swap_down: " << endl;
    swap_down(heap, 0, heap_size);
    cout << endl;


    const int heapify_helper_array[] =
        { 6, 4, 7, 13, 6, 9, 10, 15, 11, 12, 2, 20 };

    for (int i = 0; i < heap_size; i++)
    {
        heap[i] = heapify_helper_array[i];
    }

    cout << "na poczatku: " << endl;
    array_print(heap, heap_size);
    cout << endl;

    cout << "heapify: " << endl;
    heapify(heap, heap_size);
    cout << endl;


    const int heap_insert_helper_array[] =
        { 13, 11, 12, 8, 6, 9, 10, 7, 5, 4, 2 };

    array_pop(heap, heap_size);

    for (int i = 0; i < heap_size; i++)
    {
        heap[i] = heap_insert_helper_array[i];
    }

    cout << "na poczatku: " << endl;
    array_print(heap, heap_size);
    cout << endl;

    cout << "heap_insert: " << endl;
    heap_insert(heap, heap_size, 15);
    cout << endl;


    const int heap_pop_helper_array[] =
            { 15, 13, 12, 11, 6, 9, 10, 7, 5, 4, 2, 8 };

    for (int i = 0; i < heap_size; i++)
    {
        heap[i] = heap_pop_helper_array[i];
    }

    cout << "na poczatku: " << endl;
    array_print(heap, heap_size);
    cout << endl;

    cout << "heap_pop: " << endl;
    heap_pop(heap, heap_size);
    cout << endl;

    cout << "na poczatku: " << endl;
    array_print(heap, heap_size);
    cout << endl;

    cout << "heap_sort: " << endl;
    heap_sort(heap, heap_size);
    cout << endl;

    // czyszczenie pamieci przeznaczonej na kopiec
    free(heap);

    return 0;
}