/*Sima Stefania, grupa 30229, semigrupa 2
* In aceasta tem am implementat algoritmul de sortare QuickSort. Am folosit  metoda de partiotionare Lomuto pentru ca personal mi s a parut 
* mai usor de inteles si implementat chiar daca stiu ca este o idee mai neoptima decat metoda Hoare.
* Quicksort se foloseste de un pivot (in cazul meu am ales ca acesta sa porneasca cu pivotul de la sfarsit). Acesta este utilizat pentru 
a imparti tabloul in doua subtablouri: unul continand elemente mai mici decat pivotul si altul continand elemente mai mari sau egale. Acest algoritm abordeaza
tehnica de divide et impera in care imaprte problema in doua subprobleme mai mici . 
Pentru cazul average (cu tablouri generate random) complexitatea este O (n log n)
Pentru cazul worst (tablouri sortate crescator sau descrescator) complexitatea este O(n ^ 2)
Pentru cazul best (am generat tablouri balansate ) complexitatea este O (n log n)
Pentru comparatia celor doi algoritmi de sortare Heap Sort si Quick sort am observat urmatorul aspect: 
pentru cazul average, ambele au complexitate O (n log n) si au grafice asemanatoare, cel de la heap sort fiind mai constant
Am implementat si varianta de hibrida de quick sort, care sub un anumit prag foloseste insertion sort. 
Datorita graficelor ce masoara numarul operatiilor si timpul , am observat ca dupa pragul 13 pana la 30 pare a fi mai optim din punctul de vedere al 
operatiilor, iar dinn punct de vedere al timpului de la 40
La nivelul de comparatie al Quick sort varianta simpla si Hybrid Quick sort, ambele au pentru cazul average complexitatea O(n log n) pt operatii cat si
pentru timp. Din grafice, se observa o mica diferenta dintre acestea, varianta hybrind parand o idee mai optima din ambele puncte de vedere.
*/

#include <stdlib.h>
#include <stdio.h>
#include "Profiler.h"

Profiler p("QuickSort");

#define MAX_SIZE 10000
#define STEP_SIZE 100
#define TESTS 100
//functie de interschimbare pentru swap
void swap(int* a, int* b) {
    int aux = *a;   
    *a = *b;
    *b = aux;
}
//functie pentru partitionare metoda Lomuto
int partition(int arr[], int low, int high, Operation& operation) {
    int pivot = arr[high]; //alegem ultimul element ca pivot
    int i = low - 1; //initializam i la un index mai mic decat cel mai mic index

    //folsim j pentru a stabili daca fiecare element trebuie sa stea in stanga sau in dreapta pivotului
    for (int j = low; j <= high - 1; j++) {
        operation.count();
        if (arr[j] < pivot) { //daca elementul e mai mic decat pivotul, trebuie sa stea in stanga lui
            i++; //incrementam i pentru a avansa cu elementele < pivot
            operation.count(3);
            swap(&arr[i], &arr[j]); //interschimba pt ca elem mai mic sa fie in partea stanga
        }
    }

    operation.count(3);
    swap(&arr[i + 1], &arr[high]); // pozitioneaza pivotul la indexul i + 1
    return i + 1; // returneaza noua pozitie a pivotului
}

//insertion sort folosit pentru hybrid sort
void insertionSort(int arr[], int low, int high, Operation& operation) {
    for (int i = low + 1; i <= high; i++) {
        int key = arr[i];
        int j = i - 1;

        operation.count();
        while (j >= low ) {
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
                operation.count(1);
            }
            else
                break;
        }
        if (j != i - 1)
        {
            operation.count();
            arr[j + 1] = key;
        }
    }
}

//quick sort varianta simpla
void quickSort(int arr[], int low, int high, Operation& operation) {
    if (low < high) {
        int pi = partition(arr, low, high, operation);
        quickSort(arr, low, pi - 1, operation); // facem quicksort pe subtabloul stang
        quickSort(arr, pi + 1, high, operation); //facem quicksort pe subtabloul drept
    }
}


//functie de exemplificare pe un exemplu mic al corectitudinii algoritmului
void demo() {
    int arr[] = { 4, 9, 1, 3, 2, 5, 6, 8, 7 };
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Array before quicksort:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    Operation operation = p.createOperation("DemoQuickSort", n);
    int value = 1;
  
     quickSort(arr, 0, n - 1, operation);

    printf("Array after quicksort:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

//functie de generare a graficului pentru cazul average, complexitate O(n log n)
void perfQuickAverage() {
    int arr[MAX_SIZE];

    for (int n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE) {
        Operation operation = p.createOperation("QuickSortOperation", n);
        FillRandomArray(arr, n);
        quickSort(arr, 0, n - 1, operation);
    }

    p.showReport();
}
/*functie de generare a graficului pentru cazul worst
cazul worst este cand tabloul este sortat crescator sau descresctor si are complexitate O(n^2)*/
void perfQuickWorst() {
    int arr[MAX_SIZE];

    for (int n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE) {
        Operation operation = p.createOperation("QuickSortOperation", n);
        FillRandomArray(arr, n, 0, 10000, true, ASCENDING);
        quickSort(arr, 0, n - 1, operation);
    }
    p.showReport();
}
/*functie de generare a graficului pentru cazul best
cazul best este atunci cand tabloul este balansat*/
void generateBalancedArray(int arr[], int start, int end)
{
    if (start > end) return; //daca startul e mai mare decat sfarsitul inseamna ca nu mai sunt elemente de balansat
    int mid = start + (end - start) / 2; // mediana sirului
    generateBalancedArray(arr, start, mid - 1); // balanseaza pe partea stanga
    generateBalancedArray(arr, mid + 1, end); //balanseaza pe partea dreapta

    swap(&arr[mid], &arr[end]); //interschimba elementul din mijloc cu ultimul element

}
//complexitate O( n log n)
void perfQuickBest()
{
    int arr[MAX_SIZE];

    for (int n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE) {
        Operation operation = p.createOperation("QuickSortBestCase", n);
        FillRandomArray(arr, n, 10, 50000, false, ASCENDING);
        generateBalancedArray(arr, 0, n - 1);
        quickSort(arr, 0, n - 1, operation);
    }
    p.showReport();
}

//functie de heapify, folosita pt bottom up
void Heapify(int a[], int n, int i, Operation& opHeapsort) {
    int largest = i; // radacina
    int l = 2 * i + 1; //copilul stang
    int r = 2 * i + 2; //copilul drept 

    opHeapsort.count();
    if (l < n && a[l] > a[largest]) //verifica daca inca n am ajuns la sfarsit si daca copilul stang e mai mare decat radacina
        largest = l; //daca e, radacina devine copilul stang
    opHeapsort.count();
    //la fel si pt copilul drept
    if (r < n && a[r] > a[largest])
        largest = r;

    if (largest != i) { //daca radacina nu mai este i, adica cea de la inceput inseamna ca s a gasit un copil mai mare
        opHeapsort.count(1);
        swap(&a[largest], &a[i]); //se interschimba pentru a pastra propietatea de max heap
        Heapify(a, n, largest, opHeapsort); //apel recursiv pentru a pastra max heapul
    }
}

void BottomUp(int a[], int n, Operation& opHeapsort) {
    for (int i = n / 2 - 1; i >= 0; i--) //se itereaza pe nodurile ce nu s frunze incepand de la parintele cu indexul n / 2 - 1
        Heapify(a, n, i, opHeapsort); //apeleaza heapify pe fiecare nod ce nu e frunza de la dreapta la stanga
}
//heap sort
void HeapSort(int a[], int n, Operation& opHeapsort) {
    BottomUp(a, n, opHeapsort); // construieste max heapul , iar cel mai amre el este pe a[0]
    for (int i = n - 1; i > 0; i--) {
        opHeapsort.count(3);
        swap(&a[0], &a[i]); // interschimba primul element (cel mai mare) cu fiecare element pe rand pentru a ajunge pe ultima pozitie, aranjandu-se astfel sortate

        Heapify(a, i, 0, opHeapsort); // se pastreaza propietatea de max heap
    }
}
//functie pt a exemplifica corectitudinea heap sort
void demoHeapSort() {
    int arr[] = { 12, 11, 13, 5, 6, 7 };
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Unsorted array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    Operation opHeapsort = p.createOperation("HeapSortOperation", n);
    HeapSort(arr, n, opHeapsort);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

//functie de comparare a heap sort si quicksort
void perfQuickVsHeapSort() {
    int arrQuick[MAX_SIZE];
    int arrHeap[MAX_SIZE];

    for (int n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE) {
        for (int i = 0; i < 5; i++) {
            FillRandomArray(arrQuick, n);
            memcpy(arrHeap, arrQuick, n * sizeof(int));

            Operation operation = p.createOperation("QuickSortOperation", n);
            Operation opHeapsort = p.createOperation("HeapSortOperation", n);

            quickSort(arrQuick, 0, n - 1, operation);
            HeapSort(arrHeap, n, opHeapsort);
        }
    }
    p.divideValues("QuickSortOperation", 5);
    p.divideValues("HeapSortOperation", 5);
    p.createGroup("QuickSortVsHeapSort", "QuickSortOperation", "HeapSortOperation");
    p.showReport();
}



//quick sort varianta hibridizata
void hybridQuickSort(int arr[], int low, int high, int threshold, Operation& operation) {
    if (low < high) { // verificam daca subtabloul are mai mult de un element
        if (high - low < threshold) { //se verifica daca subtabloul curent e mai mic decat pragul dat, iar daca este se va folosi insertion sort pentru o performanta mai buna
            insertionSort(arr, low, high, operation);
        }
        else {
            int pi = partition(arr, low, high, operation);
            hybridQuickSort(arr, low, pi - 1, threshold, operation);
            hybridQuickSort(arr, pi + 1, high, threshold, operation);
        }
    }
}

//functie de demonstrare a corectitudinii lui hybrid sort
void demoHybryd() {
    
    int arr[] = { 3, 6, 9, 8, 6, 0, 2};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Array before hybrid quicksort:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    
    Operation operation = p.createOperation("DemoHybridQuickSort", n);

    hybridQuickSort(arr, 0, n - 1, 3, operation);

    printf("Array after hybrid quicksort:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}



//functie de verificare a pragului
void perfHybridQuickSort() {
    int arr[MAX_SIZE];
   

    for (int threshold = 5; threshold <= 50; threshold++)
    {
        Operation operation = p.createOperation("HybridQuickSort", threshold);
        
      
        for (int i = 0; i < TESTS; i++)
        {
           
            FillRandomArray(arr, MAX_SIZE);
           
            hybridQuickSort(arr, 0, MAX_SIZE - 1, threshold, operation);
          
        }

        
        p.startTimer("Hybrid_timer", threshold);
        for (int i = 0; i <= TESTS; i++)
        {
            FillRandomArray(arr, MAX_SIZE);
            hybridQuickSort(arr, 0, MAX_SIZE - 1, threshold, operation);
        }
       
        p.stopTimer("Hybrid_timer", threshold);
        
    }
    p.divideValues("HybridQuickSort", TESTS);
    p.showReport();
}


//functie pentru comparatie intre quick sort varianta simpla si hybrid sort 
void QuickSort_vs_HybrydQuick()
{
    int arr1[MAX_SIZE];
    int arr2[MAX_SIZE];
    int** matrix1 = (int**)malloc(TESTS * sizeof(int*));
    int** matrix2 = (int**)malloc(TESTS * sizeof(int*));

    for (int t = 0; t < TESTS; t++) {
        matrix1[t] = (int*)malloc(MAX_SIZE * sizeof(int));
        matrix2[t] = (int*)malloc(MAX_SIZE * sizeof(int));
    }

    for (int n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE)
    {
        Operation operationQuick = p.createOperation("QuickSortOp", n);
        Operation operationHybrid = p.createOperation("HybridQuick", n);

        for (int i = 0; i < TESTS; i++) {
           
            FillRandomArray(arr1, n);
            memcpy(arr2, arr1, n * sizeof(int));

            
            memcpy(matrix1[i], arr1, n * sizeof(int));
            memcpy(matrix2[i], arr2, n * sizeof(int));

           
            quickSort(arr1, 0, n - 1, operationQuick);
            hybridQuickSort(arr2, 0, n - 1, 5, operationHybrid);
        }

       
        p.startTimer("QuickSort", n);
        for (int t = 0; t < TESTS; t++) {
            quickSort(matrix1[t], 0, n - 1, operationQuick);
        }
        p.stopTimer("QuickSort", n);

       
        p.startTimer("HybridSort", n);
        for (int t = 0; t < TESTS; t++) {
            hybridQuickSort(matrix2[t], 0, n - 1, 5, operationHybrid);
        }
        p.stopTimer("HybridSort", n);
    }

   
    for (int t = 0; t < TESTS; t++) {
        free(matrix1[t]);
        free(matrix2[t]);
    }
    free(matrix1);
    free(matrix2);

   
    p.divideValues("QuickSortOp", TESTS);
    p.divideValues("HybridQuick", TESTS);

    p.createGroup("QuickVsHybrid", "QuickSortOp", "HybridQuick");
    p.createGroup("Timer", "QuickSort", "HybridSort");

  
    p.showReport();
}


int partitionRandom(int arr[], int low, int high) {
    int pivotIndex = low + rand() % (high - low + 1); //aici se genereaza un indice aleator pentru pivot, astfel inact sa fie inclus în intervalul [low, high]
    int pivot = arr[pivotIndex];
    swap(&arr[pivotIndex], &arr[high]);
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}


void quickSelect(int arr[], int low, int high) {
    if (low < high) {
        int pivotIndex = partitionRandom(arr, low, high);
        quickSelect(arr, low, pivotIndex - 1);  
        quickSelect(arr, pivotIndex + 1, high);
    }
}

void demoRandom()
{
    int arr[] = { 3, 7, 9, 0, 1, 4, 5, 2, 6, 8 };
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Tabloul nesortat:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    quickSelect(arr, 0, n - 1);
    printf("\nTabloul sortat:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

}
int main() {
   // demo();
   // perfQuickAverage();
   // perfQuickWorst();
  // perfQuickBest();
  //  demoHeapSort();
   // perfQuickVsHeapSort();
    //demoHybryd();
   //perfHybridQuickSort();
    QuickSort_vs_HybrydQuick();
    //demoRandom();
    return 0;
}
