// Milosz Samotyjak
// Grupa 235 IC B1
// AISD 6 - kolejka priorytetowa

#include <iostream>

// definicja elementu kolejki
struct queue_node
{
    // integer od przechowywania liczby przypisanej do danego elementu kolejki
    int data;

    // integer od przechowywania priorytetu elementu kolejki
    int priority;

    // wskaznik na nastepny element kolejki, domyslnie wskazuje na null
    // element kolejki ktorego nastepnym elementem jest null jest koncem kolejki
    queue_node* next = nullptr;
};

void push_front(queue_node** head, int number, int priority)
{
    // przydzielenie pamieci nowemu elementowi kolejki
    queue_node* new_node = (queue_node*)malloc(sizeof(queue_node));

    // przypisanie wartosci podanej przez uzytkownika nowemu elementowi kolejki
    new_node->data = number;

    // przypisanie priorytetu podanego przez uzytkownika nowemu elementowi kolejki
    new_node->priority = priority;

    // umieszczenie dotychczasowych elementow za nowym elementem
    new_node->next = *head;

    // head od teraz wskazuje na nowo dodany element
    *head = new_node;
}

void push_by_priority(queue_node** head, int number, int priority)
{
    printf("\nadding element %d of priority %d to the queue\n", number, priority);

    // jezeli kolejka jest pusta lub priorytet pierwszego elementu kolejki jest
    // mniejszy niz priorytet elementu ktory chcemy dodac to dodaj nowy element
    // na poczatek kolejki
    if (*head == nullptr || (*head)->priority > priority)
    {
        push_front(head, number, priority);
        return;
    }

    queue_node* current = *head;

    // przechodzenie przez elementy kolejki az do momentu znalezienia elementu
    // o nizszym priorytecie niz priorytet nowego elementu lub do momentu
    // dotarcia na koniec kolejki
    while (current->next != nullptr && current->next->priority <= priority)
    {
        current = current->next;
    }

    // przydziel pamiec nowemu elementowi
    queue_node* new_node = (queue_node*)malloc(sizeof(queue_node));

    // przypisanie nowemu elementowi danych podanych przez uzytkownika
    new_node->data = number;

    // przypisanie nowemu elementowi priorytetu podanego przez uzytkownika
    new_node->priority = priority;

    // umieszczenie dawnych elementow za nowym elementem
    new_node->next = current->next;

    // current->next zamiast wskazywac na dotychczasowe elementy teraz
    // bedzie wskazywal na nowy element czyli nowy element zostal
    // umieszczony na odpowiednim miejscu
    current->next = new_node;
}

void pull_highest_priority(queue_node** head)
{
    // jezeli kolejka jest pusta zastosuj odpowiedni komunikat
    if (*head == nullptr)
    {
        printf("\ncant pull from an empty queue\n");
        return;
    }

    printf("\npulling element %d with the highest priority %d (first element)\n", (*head)->data, (*head)-> priority);

    // zachowanie elementow ktore byly za pierwszym elementem
    queue_node* temp = (*head)->next;

    // zwolnienie pamieci po pierwszym elemencie
    free(*head);

    // ustawienie wskaznika na elementy ktore byly za pierwszym elementem
    *head = temp;
}

void print_queue(queue_node* head)
{
    // jezeli kolejka jest pusta wyswietl odpowiedni komunikat
    if (head == nullptr)
    {
        printf("priority queue is empty\n");
        return;
    }

    // zmienna pomocnicza do przechodzenia po elementach kolejki
    queue_node* current = head;

    // przejdz przez kolejke i wyswietlaj jej elementy
    while (current != nullptr)
    {
        printf("%d:%d ", current->data, current->priority);
        current = current->next;
    }

    printf("\n");
}

void menu()
{
    printf("+------------------------Menu-------------------------+\n");
    printf("| 1 - push an item to the priority queue              |\n");
    printf("| 2 - pull highest priority item                      |\n");
    printf("| 0 - close the program                               |\n");
    printf("+-----------------------------------------------------+\n");
}

int main()
{
    // zmienna glownej petli programu
    bool main_loop = true;

    // nowa pusta kolejka na ktorej beda wykonywane wszystkie operacje
    queue_node* head = nullptr;

    menu();

    while (main_loop)
    {
        char input;

        printf("\ncurrent queue elements: ");
        print_queue(head);

        printf("instruction: ");
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
                int number, priority;

                printf("element to push: ");
                std::cin >> number;
                printf("of priority: ");
                std::cin >> priority;

                push_by_priority(&head, number, priority);

                break;
            }

            case '2':
            {
                pull_highest_priority(&head);

                break;
            }

            // komunikat dla wybranej instrukcji ktora nie istnieje
            default:
            {
                printf("\ninvalid instruction, try again\n");
                break;
            }
        }
    }

    // zwolnienie pamieci po kolejce
    free(head);

    return 0;
}