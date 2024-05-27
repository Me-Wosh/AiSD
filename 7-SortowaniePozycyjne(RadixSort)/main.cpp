// Milosz Samotyjak
// Grupa 235 IC B1
// AISD 7 - sortowanie pozycyjne

#include <iostream>
#include <random>

void print_array(int array[], int size);
int get_max(int array[], int size);
void radix_sort(int array[], int size);
void counting_sort(int array[], int size, int exp);

void print_array(int array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }

    printf("\n");
}

int get_max(int array[], int size)
{
    int max = array[0];

    for (int i = 1; i < size; i++)
    {
        if (array[i] > max)
        {
            max = array[i];
        }
    }

    return max;
}

void radix_sort(int array[], int size)
{
    int max = get_max(array, size);
    printf("number with the most digits: %d\n\n", max);

    for (int i = 1; max / i > 0; i *= 10)
    {
        printf("sorting numbers by their");

        if (i == 10)
        {
            printf(" second");
        }

        else if (i == 100)
        {
            printf(" third");
        }

        printf(" last digit using counting sort\n\n");

        counting_sort(array, size, i);
    }
}

void counting_sort(int array[], int size, int exp)
{
    int output[size];

    printf("empty array for counting occurrences of base-10 numbers: ");
    int count[10] = {};
    print_array(count, 10);

    printf("counting occurrences of base-10 numbers: ");

    for (int i = 0; i < size; i++)
    {
        count[(array[i] / exp) % 10]++;
    }

    print_array(count, 10);

    printf("cumulative sum of base-10 numbers: ");

    for (int i = 1; i < 10; i++)
    {
        count[i] += count[i - 1];
    }

    print_array(count, 10);
    printf("\n");

    printf("placing numbers on correct indexes in helper array (index is the cumulative sum for previous element)\n\n");
    printf("for example number %d, based on its digit %d will be placed in index taken from count[%d] - 1 (%d)\n",
           array[size - 1], (array[size - 1] / exp) % 10, (array[size - 1] / exp) % 10,
           count[(array[size - 1] / exp) % 10] - 1);

    for (int i = size - 1; i >= 0; i--)
    {
        output[count[(array[i] / exp) % 10] - 1] = array[i];
        count[(array[i] / exp) % 10]--;
    }

    printf("now the cumulative sum in count[%d] is subtracted by 1 in case there is another number that needs to be\n"
           "sorted based on the same digit (%d) to make sure that these numbers will stay in the same order as in\n"
           "the original unsorted array - thats what makes radix sort stable\n\n"
           "process continues for other numbers and after it is done the elements of the helper array are copied back\n"
           "to the original array\n\n",
           (array[size - 1] / exp) % 10, (array[size - 1] / exp) % 10);

    for (int i = 0; i < size; i++)
    {
        array[i] = output[i];
    }

    printf("state of the array: \n");
    print_array(array, size);
    printf("\n");
}

int main()
{
    int n = 100;
    int array[n];

    std::random_device random_device;
    std::default_random_engine engine(random_device());
    std::uniform_int_distribution<int> uniform_distribution(1, 110);

    for (int i = 0; i < n; i++)
    {
        array[i] = uniform_distribution(engine);
    }

    printf("before radix sort:\n");
    print_array(array, n);

    printf("\nduring radix sort:\n");
    radix_sort(array, n);

    printf("after radix sort:\n");
    print_array(array, n);

    return 0;
}
