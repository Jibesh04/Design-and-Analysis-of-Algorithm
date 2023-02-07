// Largest Element of an Array

#include <stdio.h>
// #include <math.h>
#define INT_MIN -2147483648
int max(int a, int b){
	return a > b ? a : b;
}
int largestNum(int arr[], int len){
	if(len == 0)
		return INT_MIN;
	return max(arr[len - 1], largestNum(arr, len - 1));
}
int main(){
	//int len = 100000;
	//int arr[100000];
/*	printf("Size of INT: %lu\n", sizeof(int));
	printf("INT_MIN: -%f\n", pow(2, 31));*/
//	printf("%d\n", INT_MIN);
//    TEST CASE 1
/*	for(int i = 0; i < len; i++)
		arr[i] = -(i + 1);*/
//    TEST CASE 2
/*	for(int i = 0; i < len; i++)
		arr[i] = i;*/
//    TEST CASE 3
	int len = 5;
	int arr[] = {-1, 0, 3, 2, -4};
	printf("Largest element: %d\n", largestNum(arr, len));
	return 0;
}

/* TERMINAL
cse2102040024@vssutcse-ProLiant-ML350-Gen9:~/DAA$ gcc largest_num.c 
cse2102040024@vssutcse-ProLiant-ML350-Gen9:~/DAA$ time ./a.out 
Largest element: 99999

real	0m0.010s
user	0m0.010s
sys	0m0.000s
*/
