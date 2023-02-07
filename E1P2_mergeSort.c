/* Merge Sort */
#include <stdio.h>
void merge(int arr[], int low, int mid, int high){
	int i = low, j = mid+1, k = 0;
	int arr_temp[high-low+1];
	while(i <= mid && j <= high){
		if(arr[i] < arr[j])
			arr_temp[k++] = arr[i++];
		else
			arr_temp[k++] = arr[j++];  
	}
	while(i <= mid)
		arr_temp[k++] = arr[i++];
	while(j <= high)
		arr_temp[k++] = arr[j++];
	k = 0;
	for(int l = low; l <= high; l++)
		arr[l] = arr_temp[k++];
}
void mergeSort(int arr[], int low, int high){
	if(low >= high)
		return;
	int mid = low + (high - low)/2;
	mergeSort(arr, low, mid);
	mergeSort(arr, mid+1, high);
	merge(arr, low, mid, high);
}
void display_arr(int arr[], int n){
	for(int i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");
}
int main(){
	int arr[] = {9, 18, 3, 6, 6, 11, 7, 8, 6};
	int size = sizeof(arr)/sizeof(int);
	printf("Before Sorting...\n");
	display_arr(arr, size);
	mergeSort(arr, 0, size-1);
	printf("After Sorting...\n");
	display_arr(arr, size);
	return 0;
}

/* TERMINAL
cse2102040024@vssutcse-ProLiant-ML350-Gen9:~/DAA$ gcc E1P2_mergeSort.c 
cse2102040024@vssutcse-ProLiant-ML350-Gen9:~/DAA$ ./a.out 
Before Sorting...
9 18 3 6 6 11 7 8 
After Sorting...
3 6 6 7 8 9 11 18 
cse2102040024@vssutcse-ProLiant-ML350-Gen9:~/DAA$ time ./a.out 
Before Sorting...
9 18 3 6 6 11 7 8 
After Sorting...
3 6 6 7 8 9 11 18 

real	0m0.002s
user	0m0.002s
sys	0m0.001s
*/
