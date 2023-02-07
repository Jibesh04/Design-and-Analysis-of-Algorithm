/* Quick Sort implementation */
#include <stdio.h>
int partition(int arr[], int low, int high){
	int pivot = high, j = low;
	for(int i = low+1; i < high; i++){
		if(arr[i] <= arr[pivot]){
			int temp = arr[i];
			arr[i] = arr[j];
			arr[j++] = temp;
		}
	}
	int temp = arr[j];
	arr[j] = arr[pivot];
	arr[pivot] = temp;
	return j;
}
void quickSort(int arr[], int low, int high){
	if(low >= high)
		return;
	int pi = partition(arr, low, high);
	quickSort(arr, low, pi-1);
	quickSort(arr, pi+1, high);
}
void display_arr(int arr[], int n){
	for(int i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");
}
int main(){
	int arr[] = {20, 25, 15, 10};
	int size = sizeof(arr)/sizeof(int);
	printf("Before Sorting...\n");
	display_arr(arr, size);
	quickSort(arr, 0, size-1);
	printf("After Sorting...\n");
	display_arr(arr, size);
	return 0;
}

/* TERMINAL
cse2102040024@vssutcse-ProLiant-ML350-Gen9:~/DAA$ gcc E1P1.c 
cse2102040024@vssutcse-ProLiant-ML350-Gen9:~/DAA$ time ./a.out 
Before Sorting...
20 25 15 10 
After Sorting...
10 15 20 25 

real	0m0.002s
user	0m0.003s
sys	0m0.000s
*/
