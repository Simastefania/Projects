/*
*Sima Stefania, grupa 30229, semigrupa 2
* Am implementat in aceasta tema am implementat un algoritm de generare a k liste ce contin in total n elemente (elementele sunt sortate),
* un  algoritm de interclasare a doua liste si un algoritm ce interclaseaza pe baza propietatii de minheap cele k liste.
* In algoritmul de generare a listelor am creat un tablou de liste. In fiecare lista am inserat la inceput un element (in cazul meu a fost 0
* pentru a fi sigura ca am pastrat elementele din fiecare lista sortate crescator) apoi, pentru ca in practibilitate dimensiunea listelor
* nu o sa fie constanta, am ales cu functia rand() ca numarul de elemente din primele k-1 liste sa fie aleator intre n-k / 2k si n-k /k.
* Apoi ultima lista ramane sa fie umpluta cu restul de elemente ce au ramas nefolosite. Astfel interclasarea lor o sa fie mai uniforma.
Pentru algoritmul de interclasare a k liste: am creat un heap ce va contine cel mai mic element din fiecare lista. Apoi, apelez build 
min heap care asigura propietatea de min heap, adica cel mai mic element va fi in varful heapului. se extrage cel mai mic element din heap
si va fi adaugat la lista finala.Apoi se verifica daca lista din care provine acel element mai are un element disponibil
Daca da, acest element va inlocui cel mai mic element din heap si heapul va fi rearanjat pt a mentine propietatea de minheap
daca lista nu mai contine elemente acest nod va fi eliminat din heap. 
Daca lista nu e goala, se inlocuieste nodul respectiv cu urmatorul element din acea lista si se apeleaza heapify. Daca lista este goala,
nodul este eliminat din heap și k este redus.
Complexitati: constructia heapului este O(k)
Heapify O(log k) - totul se intampla de n ori (n elemente) => Complexitate O(n log k)
Am comparat printr un grafic pentru a numara operatiile pt variatia lui n din 100 in 100 pana la 1000, pentru k1 =5, k2 = 10 si k3 = 100.
Am observat pentru fiecare ca chiar daca variatia n ul face curba sa creasca constant pentru fiecare caz, diferenta drastica dintre
fiecare k se vede chiar de la inceputul variatiunii. Este clar ca graficul difera chiar si intre o diferenta mica cum este k1 si k2, k1 fiind
mai optim. Diferenta dintre cele doua si k3 este una colosala. Se observa influenta polinomiala in defavoare logaritmului. 
Am mai comparat prin grafic si variatiunile lui k din 10 in 10 pana la 500. Am observat influenta logaritmica din complexitatea
O(n log k), deoarece graficul seamana cu cel al logaritmului natural. 

*/

#include <stdlib.h>
#include <stdio.h>
#include "Profiler.h"

Profiler p("MergeKLists");

#define STEP_SIZE 200
#define MAX_SIZE 10000

typedef struct node {
    int data;
    struct node* next;
} node;

typedef struct list {
    node* first;
    node* last;
} list;

typedef struct {
    int data;
    int listIndex;
    node* nextNode;
} HeapNode;

void createList(list* list) {
    list->first = NULL;
    list->last = NULL;
}

node* createNode(int data) {
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void addElement(list* list, int data) {
    node* newElement = createNode(data);
    if (list->first == NULL) {
        list->first = newElement;
        list->last = newElement;
    }
    else {
        list->last->next = newElement;
        list->last = newElement;
    }
}

void printList(list* l) {
    node* current = l->first;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void swapHeapNodes(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(HeapNode heap[], int i, int n, Operation &operation) {
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    
    int smallest = i;

    if (l < n)
    {
        operation.count();
        if(heap[l].data < heap[smallest].data)
        smallest = l;
    }

    if (r < n)
    {
        operation.count();
        if(heap[r].data < heap[smallest].data)
        smallest = r;
    }

    operation.count();
    if (smallest != i) {
        operation.count(3);
        swapHeapNodes(&heap[i], &heap[smallest]);
        heapify(heap, smallest, n, operation);
    }
}

void buildMinHeap(HeapNode heap[], int n, Operation &operation) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(heap, i, n, operation);
    }
}

list* kWayMerge(list* A[], int k, Operation& operation) {
    HeapNode* heap = (HeapNode*)malloc(k * sizeof(HeapNode));

    // initializam heapul cu primul element din fiecare lista
    for (int i = 0; i < k; i++) {
        operation.count();
        heap[i].data = A[i]->first->data;
        heap[i].listIndex = i;
        operation.count();
        heap[i].nextNode = A[i]->first->next;
    }

    buildMinHeap(heap, k, operation);

    list* mergedList = (list*)malloc(sizeof(list));
    createList(mergedList);

    while (k > 0) {
        addElement(mergedList, heap[0].data);

        // inlocuim radacina heapului cu urmatorul element din lista lui daca exista
        operation.count();
        if (heap[0].nextNode != NULL) {
            operation.count(2);
            heap[0].data = heap[0].nextNode->data;
            heap[0].nextNode = heap[0].nextNode->next;
        }
        else {
            operation.count();
            heap[0] = heap[k - 1];
            k--;
        }

        heapify(heap, 0, k, operation);
    }

    free(heap);
    return mergedList;
}

list** generateKLists(int k, int n) {
    list** array = (list**)malloc(k * sizeof(list*));

    for (int i = 0; i < k; i++) {
        array[i] = (list*)malloc(sizeof(list));
        createList(array[i]);
        addElement(array[i],0);
    }

    int remaining = n;

    for (int i = 0; i < k - 1; i++) {
        int minSize = (n-k) / (2 * k);
        int maxSize = (n-k) / k;
        int listSize = rand() % (maxSize - minSize + 1) + minSize;
        remaining -= listSize;

        int* tempArray = (int*)malloc(listSize * sizeof(int));
        FillRandomArray(tempArray, listSize, 1, 10000, false, ASCENDING);

        for (int j = 0; j < listSize; j++) {
            addElement(array[i], tempArray[j]);
        }
        free(tempArray);
    }

    int* tempArray = (int*)malloc(remaining * sizeof(int));
    FillRandomArray(tempArray, remaining, 1, 10000, false, ASCENDING);

    for (int j = 0; j < remaining; j++) {
        addElement(array[k - 1], tempArray[j]);
    }
    free(tempArray);

    /*for (int i = 0; i < k; i++) {
        printf("list %d: ", i + 1);
        printList(array[i]);
    }*/

    return array;
}

list* mergeTwoLists(list* l1, list* l2) {
    list* merged = (list*)malloc(sizeof(list));
    createList(merged);

    node* p1 = l1->first;
    node* p2 = l2->first;

    while (p1 != NULL && p2 != NULL) {
        if (p1->data <= p2->data) {
            addElement(merged, p1->data);
            p1 = p1->next;
        }
        else {
            addElement(merged, p2->data);
            p2 = p2->next;
        }
    }

    while (p1 != NULL) {
        addElement(merged, p1->data);
        p1 = p1->next;
    }
    while (p2 != NULL) {
        addElement(merged, p2->data);
        p2 = p2->next;
    }

    return merged;
}

void demoGenerateKLists()
{
    int k = 4;
    int n = 20;
    list** list = generateKLists(k, n);

    for (int i = 0; i < k; i++) {
        node* current = list[i]->first;
        while (current) {
            node* temp = current;
            current = current->next;
            free(temp);
        }
        free(list[i]);
    }
    free(list);
}
void demoMergeTwoLists()
{
    list** lists = generateKLists(2, 20);
    list* mergedLists = mergeTwoLists(lists[0], lists[1]);
    printf("\nlistele interclasate:\n");
    printList(mergedLists);

    for (int i = 0; i < 2; i++) {
        node* current = lists[i]->first;
        while (current) {
            node* temp = current;
            current = current->next;
            free(temp);
        }
        free(lists[i]);
    }
    free(lists);

    node* current = mergedLists->first;
    while (current) {
        node* temp = current;
        current = current->next;
        free(temp);
    }
    free(mergedLists);


}
void demoKWayMerge()
{
    int k = 4, n = 100;
    list** lists = generateKLists(k, n);

    Operation operation = p.createOperation("MergeListOperation", n);
    list* mergedList = kWayMerge(lists, k, operation);
    printf("\nlistele interclasate: ");
    printList(mergedList);


    for (int i = 0; i < k; i++) {
        node* current = lists[i]->first;
        while (current) {
            node* temp = current;
            current = current->next;
            free(temp);
        }
        free(lists[i]);
    }
    free(lists);

    node* current = mergedList->first;
    while (current) {
        node* temp = current;
        current = current->next;
        free(temp);
    }
    free(mergedList);
}

void freeMemory(list** lists, int k, list* mergedlist)
{
    node* current;
    for (int i = 0; i < k; i++)
    {
        current = lists[i]->first;
        while (current)
        {
            node* temp = current;
            current = current->next;
            free(temp);
        }
        free(lists[i]);
    }
    free(lists);
    current = mergedlist->first;
    while (current) {
        node* temp = current;
        current = current->next;
        free(temp);
    }
    free(mergedlist);
}
void perfN() {
    for (int n = 100; n <= MAX_SIZE; n += STEP_SIZE) {
        // Test pentru k = 5
        list** lists1 = generateKLists(5, n);
        Operation operation1 = p.createOperation("FiveMergedLists", n);
        list* mergedList1 = kWayMerge(lists1, 5, operation1);

        // Eliberare memorie pentru listele generate
        freeMemory(lists1, 5, mergedList1);

        // Test pentru k = 10
        list** lists2 = generateKLists(10, n);
        Operation operation2 = p.createOperation("TenMergedLists", n);
        list* mergedList2 = kWayMerge(lists2, 10, operation2);
        freeMemory(lists2, 10, mergedList2);

        // Test pentru k = 100
        list** lists3 = generateKLists(100, n);
        Operation operation3 = p.createOperation("HundredMergedLists", n);
        list* mergedList3 = kWayMerge(lists3, 100, operation3);
        freeMemory(lists3, 100, mergedList3);

    }
    p.createGroup("OperationsCompared", "FiveMergedLists", "TenMergedLists", "HundredMergedLists");
    p.createGroup("FiveAndTen", "FiveMergedLists", "TenMergedLists" );
    p.showReport();
}

void perfK()
{
    int n = 10000;
    int k;
    for (k = 10; k <= 500; k += 10)
    {
        list** lists = generateKLists(k, n);
        Operation operation = p.createOperation("MergedLists", k);
        list* mergedList = kWayMerge(lists, k, operation);
        freeMemory(lists, k, mergedList);

    }
    p.showReport();
}


int main() {

  // demoGenerateKLists();
  // demoKWayMerge();
  //  demoMergeTwoLists();
   // perfN();
    perfK();
    return 0;
}
