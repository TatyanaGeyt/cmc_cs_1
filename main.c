#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 10
#define R 3

int count_swap1 = 0, count_swap2 = 0;
int count_comp1 = 0, count_comp2 = 0;

void sorted_fill(long long* a, int n);
void unsorted_fill(long long* a, int n);
int is_sorted(long long* a, int n);
long long* make_copy(long long* a, int n);
void rand_fill(long long* a, int n);
void print_array(long long* a, int n);
long long llabs(long long a);

void bubble_sort(long long* a, int n){
    int count_swap = 1; // счётчик количества перестановок. Мы должны производить алгоритм до тех пор,
                        // пока все элементы не будет упорядоченными, то есть перестановок элементов не будет.
    while(count_swap){
        count_swap = 0;
        for (int i = 0; i < n - 1; i++){
            count_comp1++;
            if (llabs(a[i]) > llabs(a[i + 1])){     // если предыдущий элемент больше следующего, меняем их местами.
                count_swap1++;
                long long tmp = a[i];
                a[i] = a[i + 1];
                a[i + 1] = tmp;
                count_swap += 1; // увеличиваем счётчик перестановок
            }
        }
        n = n - 1; // уменьшаем длину массива на 1.
        // с каждой итерацией алгоритма самый большой по модулю элемент окажется в конце массива,
        // больше перестановок с ним не будет, таким образом можем уменьшить количество стравниваемых элементов на 1.
    }
}
void selection_sort(long long* a, int n){
    int index_min; // индекс минимального элемента на каждой итерации.
    for (int i = 0; i < n;i++){
        index_min = i; // предполагаем, что текущий минимальный элемент стоит на позиции i.
        for (int j = i + 1; j < n; j++){ // проверяем все элементы массива от i до n-1,
                                         // т. к. элементы от 0 до i уже отсортированы.
            count_comp2++;
            if (llabs(a[j]) < llabs(a[index_min])){ // если элемент массива, стоящий в позиции i, не оказался минимальным
                index_min = j;   //по модулю среди элементов массива от i до n - 1, то меняем индекс минимального элемента.
            }
        }
        if (index_min == i){ // если минимальный элемент стоит на позиции i, переходим к следующей итерации алгоритма.
            continue;
        }
        else{
            long long tmp = a[index_min]; // иначе перемещаем минимальный элемент на позицию i.
            count_swap2++;
            a[index_min] = a[i];
            a[i] = tmp;
        }
    }
}
int main(void)
{
    long long *a = malloc(N * sizeof(long long));

    if (R == 1)
        sorted_fill(a, N);
    else if (R == 2)
        unsorted_fill(a, N);
    else
        rand_fill(a, N);

    print_array(a, N);
    long long *a_copy = make_copy(a, N);

    bubble_sort(a, N);
    printf("Bubble sort:\n");
    print_array(a, N);
    printf("comparisons: %d\nassignments: %d\n", count_comp1, count_swap1);
    if (!is_sorted(a, N)) printf("\nError\n");

    selection_sort(a_copy, N);
    printf("Selection sort:\n");
    print_array(a_copy, N);
    printf("comparisons: %d\nassignments: %d\n", count_comp2, count_swap2);
    if (!is_sorted(a_copy, N)) printf("\nError\n");
}

int is_sorted(long long* a, int n){
    for (int i = 0; i < n - 1; i++){
        if (llabs(a[i]) > llabs(a[i + 1])){
            return 0;
            break;
        }
    }
    return 1;
}
void sorted_fill(long long* a, int n){
    for (int i = 0; i < n; i++){
        a[i] = pow( -1, (i + 1) % 2) * (i + 1);
    }
}
void unsorted_fill(long long* a, int n){
    for (int i = n; i > 0; i++){
        a[i] = pow( -1, i % 2) * i;
    }
}
long long* make_copy(long long* a, int n){
    long long *a_copy = malloc(n * sizeof(long long));
    for (int i = 0; i < n; i++){
        a_copy[i] = a[i];
    }
    return a_copy;
}
void rand_fill(long long* a, int n){
    for (int i = 0; i < n; i++){
        a[i] = pow( -1, rand() % 2) * rand() * rand();
    }
}
void print_array(long long* a, int n){
    for (int i = 0; i < n; i++){
        printf("%lld ", a[i]);
    }
    printf("\n");
}
long long llabs(long long a){
    return (a > 0 ? a : -1 * a);
}
