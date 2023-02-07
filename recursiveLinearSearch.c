/* Linear Search */
#include <stdio.h>
#include <stdlib.h>
int linearSearch(int arr[], int size, int n){
	if(size == 0)
		return -1;
	if(arr[size - 1] == n)
		return size;
	return linearSearch(arr, size - 1, n);
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
		arr[i] = i + 1;
	int num = 0;
	int idx = linearSearch(arr, len, num);
	if(idx == -1)
		printf("%d not Found!\n", num);
	else
		printf("%d was found at index(1 based) %d\n", num, idx);
	return 0;
}

/* TERMINAL
cse2102040024@vssutcse-ProLiant-ML350-Gen9:~/DAA$ gcc recursiveLinearSearch.c 
cse2102040024@vssutcse-ProLiant-ML350-Gen9:~/DAA$ time ./a.out 
Enter the size of the array: 6   
Enter the array: 0 1 4 2 5 3
Enter the number to be searched: 7
7 not Found!

real	0m17.807s
user	0m0.002s
sys	0m0.000s
cse2102040024@vssutcse-ProLiant-ML350-Gen9:~/DAA$ time ./a.out 
Enter the size of the array: 6
Enter the array: 0 1 4 2 5 3
Enter the number to be searched: 2
2 was found at index(1 based) 4

real	0m9.408s
user	0m0.002s
sys	0m0.000s
*/
