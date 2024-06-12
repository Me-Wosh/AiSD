#include <iostream>
#include <vector>
#include <cmath>

// definicja węzła
struct node
{
    // wskaźnik na lewe dziecko węzła
    node* left_child;

    // wskaźnik na prawe dziecko węzła
    node* right_child;

    // wartość przypisana do węzła
    int value;
};

// funkcja do wyświetlania wizualnie drzewa
void print_tree(std::vector<node> nodes)
{
    int j = 0;

    // szukanie głębokości drzewa
    for (int i = 0; i < nodes.size(); i++)
    {
        if (i + 1 == pow(2, j))
        {
            j++;
        }
    }

    int jj = j;
    j = 0;

    for (int i = 0; i < nodes.size(); i++)
    {
        // przechodzenie do następnej głębokości drzewa
        if (i + 1 == pow(2, j))
        {
            printf("\n\n");
            j++;
            jj--;
        }

        // oddzielenie węzłów spacjami
        for (int k = 0; k <= jj + (nodes.size() - i) / 10; k++)
        {
            printf(" ");
        }

        // wyświetlenie wartości obecnego węzła
        printf("%d", nodes[i].value);
    }
}

// funkcja do przeszukiwania drzewa sposobem pre-order (najpierw rodzic, potem lewe dziecko, potem
// prawe dziecko)
void print_pre_order(node* root)
{
    // jeżeli natrafimy na węzeł o wartości null to zaprzestajemy poszukiwania następnych węzłów w
    // danym kierunku (lewym lub prawym) i wychodzimy z jednego stopnia rekurencji
    if (root == nullptr)
    {
        return;
    }

    // wypisanie wartości obecnego węzła - w tym przypadku najpierw rodzica, potem lewego dziecka
    // potem prawego dziecka
    printf("%d ", root->value);

    // szukanie lewego dziecka dla danego rodzica
    print_pre_order(root->left_child);

    // szukanie prawego dziecka dla danego rodzica
    print_pre_order(root->right_child);
}

// funkcja do przeszukiwania drzewa sposobem in-order (najpierw lewe dziecko, potem rodzic,
// potem prawe dziecko)
void print_in_order(node* root)
{
    // jeżeli natrafimy na węzeł o wartości null to zaprzestajemy poszukiwania następnych węzłów w
    // danym kierunku (lewym lub prawym) i wychodzimy z jednego stopnia rekurencji
    if (root == nullptr)
    {
        return;
    }

    // szukanie lewego dziecka dla danego rodzica
    print_in_order(root->left_child);

    // wypisanie wartości obecnego węzła - w tym przypadku najpierw lewego dziecka, potem rodzica,
    // potem prawego dziecka
    printf("%d ", root->value);

    // szukanie prawego dziecka dla danego rodzica
    print_in_order(root->right_child);
}

// funkcja do przeszukiwania drzewa sposobem post-order (najpierw lewe dziecko, potem prawe dziecko,
// potem rodzic)
void print_post_order(node* root)
{
    // jeżeli natrafimy na węzeł o wartości null to zaprzestajemy poszukiwania następnych węzłów w
    // danym kierunku (lewym lub prawym) i wychodzimy z jednego stopnia rekurencji
    if (root == nullptr)
    {
        return;
    }

    // szukanie lewego dziecka dla danego rodzica
    print_post_order(root->left_child);

    // szukanie prawego dziecka dla danego rodzica
    print_post_order(root->right_child);

    // wypisanie wartości obecnego węzła - w tym przypadku najpierw lewego dziecka, potem prawego
    // dziecka, potem rodzica
    printf("%d ", root->value);
}

int main()
{
    // utworzenie liści - węzłów, które nie mają potomków i znajdują się w najniższej warstwie drzewa

    node twelve = { nullptr, nullptr, 12 };
    node eleven = { nullptr, nullptr, 11 };
    node ten    = { nullptr, nullptr, 10 };
    node nine   = { nullptr, nullptr, 9 };
    node seven  = { nullptr, nullptr, 7 };
    node six    = { nullptr, nullptr, 6 };

    // utworzenie gałęzi/ojców - węzłów, które mają jakichś potomków

    node eight  = { &eleven, &twelve, 8 };
    node five   = { &nine, &ten, 5 };
    node four   = { &eight, nullptr, 4 };
    node three  = { &six, &seven, 3 };
    node two    = { &four, &five, 2 };

    // utworzenie korzenia drzewa - wyróżnionego węzła początkowego, od którego wychodzą pozostałe węzły
    node one    = { &two, &three, 1 };

    // utworzenie zbioru zawierającego wszystkie węzły
    std::vector<node> wezly = { one, two, three, four, five, six, seven, eight, nine, ten, eleven, twelve };

    print_tree(wezly);

    printf("\n\nprzeszukiwanie pre-order:\n");
    print_pre_order(&one);

    printf("\n\nprzeszukiwanie in-order:\n");
    print_in_order(&one);

    printf("\n\nprzeszukiwanie post-order:\n");
    print_post_order(&one);

    printf("\n");

    return 0;
}
