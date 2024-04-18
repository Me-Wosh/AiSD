// Milosz Samotyjak
// Grupa 235 IC B1
// AISD 3 - stos

#include <iostream>
#include <random>

// flaga blokujaca wyswietlanie komunikatow o dodaniu elementow do stosu
// przy inicjalizacji stosu z 10 losowymi elementami
bool initialize_flag = true;

struct stack
{
    int max_size;
    int top_index;
    int* items;
};

stack* new_stack(int);
int size(stack*);
bool is_full(stack*);
bool is_empty(stack*);
void push(stack*, int);
void pop(stack*);
std::pair<int, bool> top(stack*);

stack* new_stack(int capacity)
{
    // alokacja pamieci dla stosu
    stack* new_stack = (stack*)malloc(sizeof(stack));

    // ustawienie maksymalnego rozmiaru na podany przez uzytkownika
    new_stack->max_size = capacity;

    // ustawienie indeksu pierwszego elementu na -1 (brak pierwszego elementu)
    new_stack->top_index = -1;

    // alokacja pamieci dla elementow stosu
    new_stack->items = (int*)malloc(capacity * sizeof(int));

    return new_stack;
}

int size(stack* stack)
{
    // skoro przy dodawaniu elementow na stos kazdorazowo zwiekszamy wartosc
    // top_index o 1 to top_index + 1 zwroci nam ilosc wszystkich elementow
    return stack->top_index + 1;
};

bool is_full(stack* stack)
{
    // sprawdzenie czy obecna ilosc elementow jest rowna maksymalnej
    return (size(stack)) == stack->max_size;
}

bool is_empty(stack* stack)
{
    // czy ilosc elementow wynosi 0
    return (size(stack)) == 0;
}

void push(stack* stack, int x)
{
    // jezeli stos jest przepelniony powiadom o tym i wyjdz z funkcji
    if (is_full(stack))
    {
        std::cout << "stos jest przepelniony, nie mozna dodac elementu" << std::endl;
        return;
    }

    // zwieksz indeks wierzchniego elementu o jeden
    stack->top_index++;

    // dodaj element do stosu
    stack->items[stack->top_index] = x;

    // jezeli jest inicjalizowany stos o 10 losowych elementach pomin wyswietlanie
    // komunikatu o dodaniu elementu
    if (initialize_flag)
    {
        return;
    }

    std::cout << "stos nie jest przepelniony, dodano element" << std::endl;
    std::cout << "stack->top_index = " << stack->top_index << std::endl;
    std::cout << "stack->items[stack->top_index] = " << top(stack).first << std::endl;
}

void pop(stack* stack)
{
    // jezeli stos jest pusty powiadom o tym i wyjdz z funkcji
    if (is_empty(stack))
    {
        std::cout << "stos jest pusty, nie mozna usunac elementu" << std::endl;
        return;
    }

    // zmniejsz indeks wierzchniego elementu o jeden
    stack->top_index--;

    std::cout << "stos nie jest pusty, usunieto element" << std::endl;

    // sprawdzenie czy stos jest pusty (funkcja top() zwroci pare { NULL, true }
    int error = top(stack).second;

    if (error)
    {
        std::cout << "teraz stos jest pusty" << std::endl;
        return;
    }

    // jezeli nie jest pusty wypisz wierzchni element
    int result = top(stack).first;

    std::cout << "stack->top_index = " << stack->top_index << std::endl;
    std::cout << "stack->items[stack->top_index] = " << result << std::endl;
}

std::pair<int, bool> top(stack* stack)
{
    // jezeli jest pusty zwroc pare { wynik = NULL, blad = true }
    if (is_empty(stack))
    {
        return std::pair(NULL, true);
    }

    // w przeciwnym razie zwroc element na szczycie stosu i brak bledu
    return std::pair(stack->items[stack->top_index], false);
}

void menu()
{
    std::cout << "+-------Menu-------+" << std::endl;
    std::cout << "| 1 - push an item |" << std::endl;
    std::cout << "| 2 - pop an item  |" << std::endl;
    std::cout << "| 3 - get top item |" << std::endl;
    std::cout << "| 4 - exit         |" << std::endl;
    std::cout << "+------------------+" << std::endl;
}

int main()
{
    bool main_loop = true;
    int capacity = 20;

    stack* stack = new_stack(capacity);

    // niedeterministyczny generator liczb losowych
    std::random_device random_device;

    // generator Mersenne Twister 19937
    std::mt19937 generator(random_device());

    // losuj liczby z przedzialu od 1 do 10
    std::uniform_int_distribution<int> distribution(1, 10);

    for (int i = 0; i < capacity / 2; i++)
    {
        // losuj liczbe
        int random_number = distribution(generator);
        push(stack, random_number);
    }

    initialize_flag = false;

    menu();

    while (main_loop)
    {
        char command;

        std::cout << "wypelnienie/maksymalna pojemnosc: " << size(stack) << "/" << stack->max_size << std::endl;
        std::cout << "polecenie: ";
        std::cin >> command;

        switch (command)
        {
            case '1':
            {
                int element;

                std::cout << "element do dodania: ";
                std::cin >> element;

                std::cout << "sprawdzenie przepelnienia: ";

                push(stack, element);

                break;
            }

            case '2':
            {
                std::cout << "sprawdzenie czy stos jest pusty: ";

                pop(stack);

                break;
            }

            case '3':
            {
                std::cout << "sprawdzenie czy stos jest pusty: ";

                int error = top(stack).second;

                if (error)
                {
                    std::cout << "stos jest pusty, nie mozna odczytac elementu" << std::endl;
                    break;
                }

                int result = top(stack).first;

                std::cout << "stos nie jest pusty" << std::endl;
                std::cout << "stack->top_index = " << stack->top_index << std::endl;
                std::cout << "stack->items[stack->top_index] = " << result << std::endl;

                break;
            }

            case '4':
            {
                main_loop = false;

                break;
            }

            default:
            {
                std::cout << "nieznane polecenie" << std::endl;

                break;
            }
        }

        std::cout << "-----------------------------------------------------------------------------" << std::endl;
    }

    free(stack->items);
    free(stack);

    return 0;
}