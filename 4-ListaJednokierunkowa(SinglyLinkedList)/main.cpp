// Milosz Samotyjak
// Grupa 235 IC B1
// AISD 4 - lista jednokierunkowa

#include <iostream>

// zmienna do wyswietlania bledow typu nie mozna usunac elementu z pustej listy
std::string error;

// definicja elementu listy
struct list_node
{
    // integer od przechowywania liczby przypisanej do danego elementu listy
    int data;

    // wskaznik na nastepny element listy, domyslnie wskazuje na null
    // element listy ktorego nastepnym elementem jest null jest koncem listy
    list_node* next = nullptr;
};

void push_front(list_node** head, int number)
{
    // przydzielenie pamieci nowemu elementowi listy
    list_node* new_node = (list_node*)malloc(sizeof(list_node));

    // przypisanie wartosci podanej przez uzytkownika nowemu elementowi listy
    new_node->data = number;

    // umieszczenie dotychczasowych elementow za nowym elementem
    new_node->next = *head;

    // head od teraz wskazuje na nowo dodany element
    *head = new_node;
}

void push_back(list_node** head, int number)
{
    list_node* new_node = (list_node*)malloc(sizeof(list_node));
    new_node->data = number;

    // jezeli head wskazuje na pusty wskaznik to po prostu dodaj element na poczatek listy
    if (*head == nullptr)
    {
        *head = new_node;
        return;
    }

    // utworzenie zmiennej pomocniczej do przechodzenia po liscie
    // wynika to ze specyfiki listy - gdybysmy probowali przechodzic po liscie za pomoca zmiennej head to pod koniec
    // wykonywania funkcji zostalibysmy z headem ustawionym na przedostatni element listy zamiast na jej poczatek
    list_node* current = *head;

    // przechodzenie przez elementy listy az dotrzemy do jej konca
    while (current->next != nullptr)
    {
        current = current->next;
    }

    // dodanie elementu na koniec listy
    // z racji ze operujemy na wskaznikach nie musimy sie martwic o to ze ustalamy wartosc next dla zmiennej current
    // zamiast dla head poniewaz current->next jest tym samym miejscem w pamieci i zostanie "odnalezione" przez zmienna
    // head
    current->next = new_node;
}

void show_list(list_node* head)
{
    // jezeli lista jest pusta wyswietl odpowiedni komunikat
    if (head == nullptr)
    {
        std::cout << "list is empty" << std::endl;
        return;
    }

    list_node* current = head;

    // przejdz przez liste i wyswietlaj jej elementy
    while (current != nullptr)
    {
        std::cout << current->data << " ";
        current = current->next;
    }

    std::cout << std::endl;
}

int list_size(list_node* head)
{
    int size = 0;

    list_node* current = head;

    // przejdz przez liste i zwiekszaj odpowiednio zwracany pozniej rozmiar
    while (current != nullptr)
    {
        size++;
        current = current->next;
    }

    return size;
}

void push_by_index(list_node** head, int number, int index)
{
    // jezeli indeks jest poza zasiegiem listy wyswietl odpowiedni komunikat
    // dopuszcza sie dodanie elementu na indeks 0 przy pustej liscie i na indeks rowny dlugosci listy co oznacza dodanie
    // elementu na jej koniec
    if (index < 0 || index > list_size(*head))
    {
        error = "index was outside the bounds of the list";
        return;
    }

    // jezeli jest proba dodania elementu na poczatek listy zastosuj odpowiednia funkcje
    if (index == 0 || *head == nullptr)
    {
        push_front(head, number);
        return;
    }

    int i = 0;

    list_node* current = *head;

    // przechodzenie przez liste do momentu dotarcia do elementu o indeksie poprzedzajacym indeks na ktory chcemy dodac
    // element lub do momentu dotarcia na koniec listy
    while (i < index - 1 && current->next != nullptr)
    {
        i++;
        current = current->next;
    }

    // przydziel pamiec nowemu elementowi
    list_node* new_node = (list_node*)malloc(sizeof(list_node));

    // przypisanie nowemu elementowi danych podanych przez uzytkownika
    new_node->data = number;

    // umieszczenie dawnych elementow za nowym elementem
    new_node->next = current->next;

    // current->next zamiast wskazywac na dotychczasowe elementy teraz bedzie wskazywal na nowy element czyli nowy
    // element zostal umieszczony na wskazanym indeksie poniewaz current->next byl dotychczas wlasnie tym indeksem
    current->next = new_node;
}

void pop_front(list_node** head)
{
    // jezeli lista jest pusta zastosuj odpowiedni komunikat
    if (*head == nullptr)
    {
        error = "cant pop from an empty list";
        return;
    }

    // zachowanie elementow ktore byly za pierwszym elementem
    list_node* temp = (*head)->next;

    // zwolnienie pamieci pierwszego elementu
    free(*head);

    // ustawienie wskaznika na elementy ktore byly za pierwszym elementem
    *head = temp;
}

void pop_back(list_node** head)
{
    // jezeli lista jest pusta zastosuj odpowiedni komunikat
    if (*head == nullptr)
    {
        error = "cant pop from an empty list";
        return;
    }

    // jezeli lista jest 1-elementowa usun jedyny element
    if ((*head)->next == nullptr)
    {
        *head = nullptr;
        free(*head);
        return;
    }

    list_node* current = *head;

    // przechodz przez elementy listy do momentu dotarcia do przedostatniego elementu
    while (current->next->next != nullptr)
    {
        current = current->next;
    }

    // usun wszystko za przedostatnim elementem i zwolnij pamiec
    current->next = nullptr;
    free(current->next);
}

void pop_by_index(list_node** head, int index)
{
    // jezeli jest proba usuniecia elementu z poczatku listy zastosuj odpowiednia funkcje
    if (index == 0 || *head == nullptr)
    {
        pop_front(head);
        return;
    }

    // jezeli jest proba usuniecia elementu z konca listy zastosuj odpowiednia funkcje
    if (index == list_size(*head) - 1)
    {
        pop_back(head);
        return;
    }

    // jezeli indeks jest poza zasiegiem listy wyswietl odpowiedni komunikat
    if (index < 0 || index > list_size(*head) - 1)
    {
        error = "index was outside the bounds of the list";
        return;
    }

    int i = 0;

    list_node* current = *head;

    // przechodzenie przez liste do momentu dotarcia do elementu o indeksie poprzedzajacym indeks z ktorego chcemy
    // usunac element lub do momentu dotarcia na koniec listy
    while (i < index - 1 && current->next != nullptr)
    {
        i++;
        current = current->next;
    }

    // wskaznik na nastepny element
    list_node* temp = current->next;

    // ustaw wskaznik na element ktory byl za nastepnym elementem
    current->next = temp->next;

    // zwolnij pamiec po dawnym nastepnym elemencie
    free(temp);
}

void menu()
{
    std::cout << "+------------------------Menu-------------------------+" << std::endl;
    std::cout << "| 1 - push an item to the head of the list            |" << std::endl;
    std::cout << "| 2 - push an item to the tail of the list            |" << std::endl;
    std::cout << "| 3 - push an item to the specific index of the list  |" << std::endl;
    std::cout << "| 4 - pop an item from the head of the list           |" << std::endl;
    std::cout << "| 5 - pop an item from the tail of the list           |" << std::endl;
    std::cout << "| 6 - pop an item from the specific index of the list |" << std::endl;
    std::cout << "| 0 - close the program                               |" << std::endl;
    std::cout << "+-----------------------------------------------------+" << std::endl;
}

int main()
{
    // zmienna glownej petli programu
    bool main_loop = true;

    // nowy pusta lista na ktorej beda wykonywane wszystkie operacje
    list_node* head = nullptr;

    while (main_loop)
    {
        char input;

        menu();

        // wyswietl blad jezeli jakikolwiek zaistnial
        if (error != "")
        {
            std::cout << error << std::endl;
            error = "";
        }

        std::cout << "current list elements: ";
        show_list(head);

        std::cout << "instruction: ";
        std::cin >> input;

        // odpowiednie wywolywanie funkcji przyporzadkowanym okreslonym cyfrom z menu
        switch (input)
        {
            case '0':
            {
                main_loop = false;

                break;
            }

            case '1':
            {
                int number;
                std::cout << "element to push: ";
                std::cin >> number;

                push_front(&head, number);

                break;
            }

            case '2':
            {
                int number;

                std::cout << "element to push: ";
                std::cin >> number;

                push_back(&head, number);

                break;
            }

            case '3':
            {
                int number, index;

                std::cout << "element to push: ";
                std::cin >> number;

                std::cout << "index: ";
                std::cin >> index;

                push_by_index(&head, number, index);

                break;
            }

            case '4':
            {
                pop_front(&head);

                break;
            }

            case '5':
            {
                pop_back(&head);

                break;
            }

            case '6':
            {
                int index;

                std::cout << "index: ";
                std::cin >> index;

                pop_by_index(&head, index);

                break;
            }

            // komunikat dla wybranej instrukcji ktora nie istnieje
            default:
            {
                error = "invalid instruction, try again";
                break;
            }
        }
    }

    // zwolnienie pamieci po liscie
    free(head);

    return 0;
}