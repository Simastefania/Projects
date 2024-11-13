/*
Sima Stefania, grupa 30229 semigrupa 2

Am implementat 3 algoritmi de sortare: Selection  Sort, Insertion Sort si Bubble sort.
Selection sort este un algoritm de sortare bazat pe comparatii. El sorteaza un sir de elemente (un tablou) prin
selectarea celui mai mic element din partea nesortata si interschimbandu-l cu primul element nesortat pe care-l gaseste.
Procesul continua pana cand tot tabloul este sortat. ~complexitate in toate cazurile (average, best, worst) O(n^2)
Insertion sort functioneaza pe principiul ca se imparte in doua sub-siruri. Un sub sir este sortat, iar celalalt nu.
Se considera primul element ca fiind primul sub-sir sortat, apoi compara cu al doilea element si se interschimba daca 
acesta e mai mic.Apoi, trece la al treilea element si il compara cu celalte doua elemente din sirul sortat.Procedeul
se repeta pana cand sirul este sortat. Best case: O(n). Average case: O(n^2). Worst case: O(n^2) 
Bubble sort functioneaza pe principiul ca interschimba elementele adiacente ce nu sunt in ordine. Dupa prima iteratie
elementul maxim ajunge pe ultima pozitie. Acesta este cel mai ineficient dintre cele trei.
~complexitate in toate cazurile (average, best, worst) O(n^2)
In average case (sir de numere random) putem observa urmatoarele aspecte:
-La nivelul comparatiilor insertion sort are cele mai putine, apoi bubble sort si selection sunt asemanatoare
cu o diferenta foarte mica
-La nivelul atribuirilor selection sort are semnificativ mai putine, insertion fiind pe locul 2, iar bubble 
avand semnificativ mai multe
-Facand suma intre cele doua operatii, selection si insertion sunt asemanatoare fiind o diferenta mica intre cele
doua, iar bubble sort contine mai multe operatii clasandu-l ca fiind mai neoptim fata de cele doua
-In concluzie, pentru average case selection sort si insertion sunt mai optime ca bubble sort
In best case (sir sortat crescator):
-In privinta numarului de comparatii, selection sort are mai multe comparativ cu bubble sort si insertion sort.
-Doar in cazul insertion sort au loc operatii de atribuire, pentru celelate doua sortari nefiind 
nevoie pentru cazul favorabil.
-In concluzie, pentru best case, bubble sort pare mai optim
- Valoarea sumei operatiilor este egala pentru selection si insertion sort, pentru bubble fiind semnificativ mai mica.
In worst case (sir sortat descrescator pentru bubble si insertion, iar pentru selection fiind un sir ce contine maximul
pe prima pozitie, apoi restul elementelor fiind sortate crescator)
-In cazul comparatiilor cele 3 sunt egale
-In cazul atribuirilor selection sort are cea mai buna performanta, pe locul doi fiind insertion, iar bubble depasindu-le 
cu mult
-Pentru suma operatiilor selection sort are cea mai buna performanta, pe locul doi fiind insertion, iar bubble depasindu-le 
cu mult
-In concluzie, pentru worst case selection sort pare a fi algoritmul mai optim

Desi, pentru fiecare caz in parte cate unul dintre cei trei algoritmi are performate mai bune, per total cel mai optim 
dintre cele trei este insertion sort, pe locul doi fiind selection sort, iar ultimul fiind bubble sort.
*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include "Profiler.h"

#define STEP_SIZE 100
#define MAX_SIZE 10000
#define NR_TEST 5

Profiler p("Sorting_lab1");

void selection_sort(int arr[], int n)
{
	Operation opComp = p.createOperation("comp_selection", n);
	Operation opAssig = p.createOperation("assig_selection", n);
	for (int i = 0; i < n - 1; i++)
	{
		int min = i;
		for (int j = i + 1; j < n; j++)
		{
			opComp.count();
			if (arr[j] < arr[min])
				min = j;
		}
		if (i != min)
		{
			
			opAssig.count(3);
			int aux = arr[i];
			arr[i] = arr[min];
			arr[min] = aux;
		}

	}
}


void insertion_sort(int arr[], int n)
{
	Operation opComp2 = p.createOperation("comp_insertion", n);
	Operation opAssig2 = p.createOperation("assig_insertion", n);

	for (int i = 1; i < n; i++)
	{
		opAssig2.count();
		int aux = arr[i];
		int  j = i - 1;

		while (j >= 0)
		{
			opComp2.count();
			if (arr[j] > aux)
			{
				opAssig2.count();
				arr[j + 1] = arr[j];
				j--;
			}
			else
				break;

		}


		if (j != i - 1)
		{
			opAssig2.count();
			arr[j + 1] = aux;
		}

	}


}

void bubble_sort(int arr[], int n)
{
	Operation opComp3 = p.createOperation("comp_bubble", n);
	Operation opAssig3 = p.createOperation("assig_bubble", n);

	int sorted = 0;
	int j = 1;
	while (sorted == 0)
	{
		sorted = 1;
		for (int i = 0; i < n - j; i++)
		{
			opComp3.count();
			if (arr[i] > arr[i + 1])
			{
				
				opAssig3.count(3);
				int aux = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = aux;
				sorted = 0;
			}

		}
		j++;
	}

}

void demo()
{
	int n = 5;
	int arr[5] = { 3, 1, 3, 4, 7 };
	int copie1[5];

	for (int i = 0; i < n; i++)
	{
		copie1[i] = arr[i];
	}

	selection_sort(arr, n);
	printf("Dupa selection sort: ");
	for (int i = 0; i < n; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");

	for (int i = 0; i < n; i++)
	{
		arr[i] = copie1[i];
	}

	insertion_sort(arr, n);
	printf("Dupa insertion sort: ");
	for (int i = 0; i < n; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");

	for (int i = 0; i < n; i++)
	{
		arr[i] = copie1[i];
	}

	bubble_sort(arr, n);
	printf("Dupa bubble sort: ");
	for (int i = 0; i < n; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void perf()
{
	int arr_s[MAX_SIZE];
	int arr_i[MAX_SIZE];
	int arr_b[MAX_SIZE];
	int n;

	for (n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE) {
		for (int test = 0; test < NR_TEST; test++)
		{
			FillRandomArray(arr_s, n);
			for (int j = 0; j < n; j++)
			{
				arr_i[j] = arr_s[j];
				arr_b[j] = arr_s[j];
			}
			selection_sort(arr_s, n);
			insertion_sort(arr_i, n);
			bubble_sort(arr_b, n);
		}
	}
	p.divideValues("comp_selection", NR_TEST);
	p.divideValues("assig_selection", NR_TEST);
	p.divideValues("comp_insertion", NR_TEST);
	p.divideValues("assig_insertion", NR_TEST);
	p.divideValues("comp_bubble", NR_TEST);
	p.divideValues("assig_bubble", NR_TEST);

	p.addSeries("selection", "comp_selection" ,"assig_selection");
	p.addSeries("insertion", "comp_insertion", "assig_insertion");
	p.addSeries("bubble", "comp_bubble", "assig_bubble");

	p.createGroup("all_three_average_comp", "comp_selection", "comp_insertion", "comp_bubble");
	p.createGroup("all_three_average_comp_sel_bub", "comp_selection", "comp_bubble");
	p.createGroup("all_three_average_assig", "assig_selection", "assig_insertion", "assig_bubble");
	p.createGroup("all_three_average_sum", "selection", "insertion", "bubble");
	p.createGroup("all_three_average_sum_sel_ins", "selection", "insertion");

}

void perf_fav(int order)
{
	int arr[MAX_SIZE];


	for (int n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE) {
		FillRandomArray(arr, n, 100, 10000, false, order);
			
			selection_sort(arr, n);
			insertion_sort(arr, n);
			bubble_sort(arr, n);
		
	}
	
	p.addSeries("selection", "comp_selection", "assig_selection");
	p.addSeries("insertion", "comp_selection", "assig_selection");
	p.addSeries("bubble", "comp_bubble", "assig_bubble");

	p.createGroup("all_three_best_comp", "comp_selection", "comp_insertion", "comp_bubble");
	p.createGroup("all_three_best_assig", "assig_selection", "assig_insertion", "assig_bubble");
	p.createGroup("all_three_best_sum", "selection", "insertion", "bubble");

	
}
void perf_defav(int order)
{
	int arr_sel[MAX_SIZE];
	int arr_ins[MAX_SIZE];
	int arr_bub[MAX_SIZE];

	for (int n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE) {
		FillRandomArray(arr_ins,n, 100, 10000, false, order);
		for (int i = 0; i < n; i++)
		{
			arr_bub[i] = arr_ins[i];
		}
		arr_sel[0] = n - 1;
		for (int j = 1; j < n-1; j++)
		{
			arr_sel[j] = j;
		}

		selection_sort(arr_sel , n);
		insertion_sort(arr_ins, n);
		bubble_sort(arr_bub, n);

	}

	p.addSeries("selection", "comp_selection", "assig_selection");
	p.addSeries("insertion", "comp_insertion", "assig_insertion");
	p.addSeries("bubble", "comp_bubble", "assig_bubble");

	p.createGroup("all_three_worst_comp", "comp_selection", "comp_insertion", "comp_bubble");
	p.createGroup("all_three_worst_assig", "assig_selection", "assig_insertion", "assig_bubble");
	p.createGroup("all_three_worst_sum", "selection", "insertion", "bubble");

	
}



void perf_show()
{
	perf();
	p.reset("best");
	perf_fav(ASCENDING);
	p.reset("worst");
	perf_defav(DESCENDING);
	p.showReport();


}

int main()
{
	perf_show();
	//demo();
	return 0;
}
