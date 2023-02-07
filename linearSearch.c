/* Linear Search */
#include <stdio.h>
#include <stdlib.h>
int linearSearch(int arr[], int size, int n){
	for(int i = 0; i < size; i++)
		if(arr[i] == n)
			return i;
	return -1;
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
	int num = input("Enter the number to be searched: ");
	*/
	int len = 100000;
	int arr[100000];
	for(int i = 0; i < len; i++)
		arr[i] = i + 1;
	int num = 0;
	int idx = linearSearch(arr, len, num);
	if(idx == -1)
		printf("%d not Found!\n", num);
	else
		printf("%d was found at index(0 based) %d\n", num, idx);
	return 0;
}

/* TERMINAL
cse2102040024@vssutcse-ProLiant-ML350-Gen9:~/DAA$ gcc linearSearch.c 
cse2102040024@vssutcse-ProLiant-ML350-Gen9:~/DAA$ time ./a.out 
Enter the size of the array: 4
Enter the array: 0 -1 3 4
Enter the number to be searched: 4
4 was found at index(0 based) 3

real	0m8.288s
user	0m0.002s
sys	0m0.001s
cse2102040024@vssutcse-ProLiant-ML350-Gen9:~/DAA$ time ./a.out 
Enter the size of the array: 5    
Enter the array: 8 3 6 0 2
Enter the number to be searched: 1
1 not Found!

real	0m20.191s
user	0m0.002s
sys	0m0.001s
*/
