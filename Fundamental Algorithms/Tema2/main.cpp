/*
Sima Stefania, grupa 30229, semigrupa 2

Am implementat 2 variante ale algoritmului de sortare Insertion sort si le-am comparat din punct de vedere al performantei operatiilor cat si din punctul de vedere al 
timpului de executare.
Din punct de vedere al numarului de operatii, in cazul average, pentru alg recursiv se face pentru fiecare apel al functiei recursive un numar de operatii, acestea adunate rezulta
un numar mult mai mare fata de varianta iterativa. Complexitati: iterativ O(n^2) recursiv O(n^2)
Din punct de vedere al timpului, varianta iterativa ii este net superioara celei recursive ,aceasta apropiindu-se de axa Ox, in timp ce varianta recursiva fiind mai liniara;
De asemenea am implementat si 2 abordari ale algoritmului de construire al unu Max Heap: Top Down si Bottom Up.
In abordarea Top Down, heapul se construieste prin inserarea elemntelor unul cate unul.Fiecare eleemnt nou
este adaugat la finalul heapului si apoi este urcat (in sus) catre pozitia sa corecta.
Inserarea unui element are complexitatea de O(log n) (urcarea elementului necesita verificarea tuturor nivelurilor
arborelui. Pentru n elemente, construirea heapului are complexitatea totala O (n log n)
In abordarea bottomp-up, ideea principala este a ajusta treptat pozitia elementelor astfel incat sa satisfaca
propietatea de heap. se incepe de la jumatatea arrayului si se aplica operatia de heapify pe fiecare sub arbore
Are complexitatea de O(n)
Din grafic, se poate observa la nivelul operatiilor ca varianta de bottom up este mai optima
Pentru Worst case, pentru abordarea top down este un tablou care este sortat crescator, acesta trebuind 
sa compare fiecare element si sa l urce cel mai sus cu fiecare inserare O(n log n)
Pentru bottom up este un tablou sortat descrescator acesta trebuind sa coboare de fiecare data
elementul O(n)
Din grafic se observa ca bottom up este mai optim.
Heap Sort se bazează pe construirea unui max-heap și pe extragerea repetată a celui mai mareelement pentru a construi un array sortat.
construim un max-heap din tabloul nesortat. 
Acest pas se face in O(n) folosind algoritmul de construire bottom-up.
Extragem elementul maxim și rearanjam heapul
Dupa ce max-heapul a fost construit, elementul de la radacine este mutat la finalul tabloului.
Apoi, heap-ul este redus (cu un el in minus) si se aplica din nou "heapify".
Acest pas se repetă n−1 ori, până când toate elementele sunt sortate.
Are complexitate O(n logn)
*/


#include <stdlib.h> 
#include <stdio.h>
#include "Profiler.h"

Profiler p("Heap");

#define left(i) 2*(i) + 1
#define right(i) 2*(i) + 2
#define MAX_SIZE 10000
#define STEP_SIZE 100
#define NR_TESTS_TIME 100

void swap(int* a, int* b)
{
    int aux = *a;
    *a = *b;
    *b = aux;
}


void insertion_sort_iterative(int arr[], int n)
{
    Operation operation = p.createOperation("operation_insertion_iterative", n);

    for (int i = 1; i < n; i++)
    {
        operation.count();
        int aux = arr[i];
        int  j = i - 1;

        while (j >= 0)
        {
            operation.count();
            if (arr[j] > aux)
            {
                operation.count();
                arr[j + 1] = arr[j];
                j--;
            }
            else
                break;
        }

        if (j != i - 1)
        {
            operation.count();
            arr[j + 1] = aux;
        }
    }
}

void insertion_sort_recursive(int v[], int n)
{
    Operation operation = p.createOperation("operation_insertion_recursive", n);

    if (n <= 1)
        return;

    insertion_sort_recursive(v, n - 1);

    operation.count();
    int last = v[n - 1];
    int j = n - 2;

    while (j >= 0)
    {
        operation.count();
        if (v[j] > last)
        {
            operation.count();
            v[j + 1] = v[j];
            j--;
        }
        else
            break;
    }
    operation.count();
    v[j + 1] = last;
}

void demo_insert()
{
    int arr[] = { 12, 11, 13, 5, 6, 7 };
    int n = sizeof(arr) / sizeof(arr[0]);
    int copie[6];

    printf("Tabloul original:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
        copie[i] = arr[i];
    }
    printf("\n");

    insertion_sort_recursive(arr, n);
    insertion_sort_iterative(copie, n);

    printf("Tabloul sortat recursiv:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    printf("Tabloul sortat iterativ:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", copie[i]);
    printf("\n");
}
void timer()
{
    int arr[MAX_SIZE];
    int arr_copy[MAX_SIZE];
    int** matrix_iterative;   
    int** matrix_recursive;   

    for (int n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE)
    {

        FillRandomArray(arr, n);
        for (int i = 0; i < n; i++)
        {
            arr_copy[i] = arr[i];
        }



        matrix_iterative = (int**)malloc(NR_TESTS_TIME * sizeof(int*));
        matrix_recursive = (int**)malloc(NR_TESTS_TIME * sizeof(int*));

        for (int t = 0; t < NR_TESTS_TIME; t++)
        {
            matrix_iterative[t] = (int*)malloc(n * sizeof(int));
            matrix_recursive[t] = (int*)malloc(n * sizeof(int));


            memcpy(matrix_iterative[t], arr, n * sizeof(int));
            memcpy(matrix_recursive[t], arr_copy, n * sizeof(int));

            insertion_sort_iterative(arr, n);
            insertion_sort_recursive(arr_copy, n);
        }

        
        p.startTimer("Insertion_iterative_timer", n);
        for (int t = 0; t < NR_TESTS_TIME; t++)
        {
            insertion_sort_iterative(matrix_iterative[t], n);
        }
        p.stopTimer("Insertion_iterative_timer", n);

        
        p.startTimer("Insertion_recursive_timer", n);
        for (int t = 0; t < NR_TESTS_TIME; t++)
        {
            insertion_sort_recursive(matrix_recursive[t], n);
        }
        p.stopTimer("Insertion_recursive_timer", n);

        
        for (int t = 0; t < NR_TESTS_TIME; t++)
        {
            free(matrix_iterative[t]);
            free(matrix_recursive[t]);
        }
        free(matrix_iterative);
        free(matrix_recursive);
    }

    p.divideValues("operation_insertion_iterative", NR_TESTS_TIME);
    p.divideValues("operation_insertion_recursive", NR_TESTS_TIME);
    p.createGroup("Insertion_Iterative_vs_Recursive_Time", "Insertion_iterative_timer", "Insertion_recursive_timer");
    p.createGroup("Performance_operation_insertion", "operation_insertion_iterative", "operation_insertion_recursive");

    p.showReport();
}
void heapify(int a[], int i, int n)
{
   
    int l = left(i);
    int r = right(i);
    int largest = i;

   
    if (l < n && a[l] > a[i])
    {
        largest = l;
    }

  
    if (r < n && a[r] > a[largest])
    {
        largest = r;
    }

    if (largest != i)
    {
       
        swap(&a[i], &a[largest]);
        heapify(a, largest, n);
    }
}

void build_heap_top_down(int a[], int n)
{
    Operation opTopDown = p.createOperation("Operation_TopDown", n);

    for (int i = 1; i < n; i++)
    {
        opTopDown.count();
        int current = i;
        int parent = (current - 1) / 2;

        while (current > 0)
        {
            opTopDown.count();
            if (a[current] > a[parent])
            {
                opTopDown.count(3);
                swap(&a[current], &a[parent]);
                opTopDown.count(2);
                current = parent;
                parent = (current - 1) / 2;
            }
            else
                break;
        }
    }
}

void build_heap_bottom_up(int arr[], int n) //  bottom-up
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, i, n3);
    }
}

void heapsort(int a[], int n)
{
    build_heap_bottom_up(a, n);

    int heapSize = n;
    for (int i = n - 1; i >= 1; i--)
    {
        swap(&a[0], &a[i]);
        heapSize--;
        heapify(a, 0, heapSize);
    }
}

void demo_heap()
{
    int arr[] = { 5, 13, 2, 25, 7, 17, 20, 8, 4 };
    int copie[9];
    int copie2[9];
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Tabloul original:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
        copie[i] = arr[i];
        copie2[i] = arr[i];
    }
    printf("\n");

    printf("dupa bottom up:\n");
    build_heap_bottom_up(arr, n);

    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    printf("dupa top down:\n");
    build_heap_top_down(copie, n);

    for (int i = 0; i < n; i++)
        printf("%d ", copie[i]);
    printf("\n");

    printf("dupa heapsort:\n");
    build_heap_bottom_up(copie2, n);

    for (int i = 0; i < n; i++)
        printf("%d ", copie2[i]);
    printf("\n");
}

void perf_average_heap()
{
    int arr_tp[MAX_SIZE];
    int arr_bu[MAX_SIZE];
    for (int n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE)
    {
        for (int i = 0; i <= 5; i++) {
            FillRandomArray(arr_tp, n);
            for (int i = 0; i < n; i++)
            {
                arr_bu[i] = arr_tp[i];
            }

            build_heap_bottom_up(arr_bu, n);
            build_heap_top_down(arr_tp, n);
            

        }
    }
    p.divideValues("Operation_TopDown", 5);
    p.divideValues("BottomUp_operation", 5);
    p.createGroup("BottomUp_vs_TopDown", "Operation_TopDown", "BottomUp_operation");
    p.showReport();

}

void perf_heap_worst()
{
    int arr_tp[MAX_SIZE];
    int arr_bu[MAX_SIZE];

    for (int n = STEP_SIZE; n < MAX_SIZE; n += STEP_SIZE)
    {
        FillRandomArray(arr_tp,n, 1, 10000, false, ASCENDING);
        FillRandomArray(arr_bu,n, 1, 1000, false, DESCENDING);

        build_heap_bottom_up(arr_bu, n);
        build_heap_top_down(arr_tp, n);
        
    }
    p.createGroup("BottomUp_vs_TopDown", "Operation_TopDown", "BottomUp_operation");
    p.showReport();
}

int main()
{
    //demo_heap();  
     //timer();
   //perf_average_heap();
    perf_heap_worst();
    return 0;
}
