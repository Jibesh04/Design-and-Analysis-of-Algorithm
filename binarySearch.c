/* Binary Search */
#include <stdio.h>
#include <stdlib.h>
int binarySearch(int arr[], int left, int right, int n){
	if(left > right)
		return -1;
	int mid = (right + left)/2;
	if(arr[mid] == n)
		return mid;
	if(arr[mid] < n)
		return binarySearch(arr, mid + 1, right, n);
	if(arr[mid] > n)
		return binarySearch(arr, left, mid - 1, n);
}/*
int input(char stmt[]){
	printf("%s", stmt);
	int n;
	scanf("%d", &n);
	return n;
}
int* input_arr(int len, char stmt[]){
	printf("%s", stmt);
	int* arr = (int*) malloc(sizeof(int) * len);
	for(int i = 0; i < len; i++)
		scanf("%d", &arr[i]);
	return arr;
}*/
int main(){
	/*int len = input("Enter the size of the array: ");
	int* arr = input_arr(len, "Enter the array: ");
	int num = input("Enter the number to be searched: ");*/
	int len = 100000;
	int arr[100000];
	for(int i = 0; i < len; i++)
		arr[i] = i+1;
	int num = 0;
	int idx = binarySearch(arr, 0, len - 1, num);
	if(idx == -1)
		printf("%d not Found!\n", num);
	else
		printf("%d was found at index(0 based) %d\n", num, idx);
	return 0;
}

/* TERMINAL
cse2102040024@vssutcse-ProLiant-ML350-Gen9:~/DAA$ gcc binarySearch.c 
cse2102040024@vssutcse-ProLiant-ML350-Gen9:~/DAA$ time ./a.out 
Enter the size of the array: 6
Enter the array: 1 2 3 4 5 6
Enter the number to be searched: 3
3 was found at index(0 based) 2

real	0m4.832s
user	0m0.002s
sys	0m0.000s
cse2102040024@vssutcse-ProLiant-ML350-Gen9:~/DAA$ gcc binarySearch.c 
cse2102040024@vssutcse-ProLiant-ML350-Gen9:~/DAA$ time ./a.out 
Enter the size of the array: 5
Enter the array: 1 2 3 4 5
Enter the number to be searched: 7
7 not Found!

real	0m5.664s
user	0m0.002s
sys	0m0.000s
*/
