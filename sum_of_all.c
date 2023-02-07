/* Sum of all elements of an array */
#include <stdio.h>/*
long int sum_array(int arr[], int len){
	if(len == 1)
		return arr[0];
	return arr[len - 1] + sum_array(arr, len - 1);
}*/
long int sum_array_2(int arr[], int low, int high){
	if(low > high)
		return 0;
	int mid = low + (high - low)/2;
	return sum_array_2(arr, low, mid - 1) + arr[mid] + sum_array_2(arr, mid + 1, high);
}
int main(){
// TESTING CORRECTNESS
/*	int len = 5;
	int arr[] = {1, 2, -1, 0, 5};
	printf("Sum of Elements: %ld\n", sum_array(arr, len));
	printf("Sum of Elements: %ld\n", sum_array_2(arr, 0, len - 1));
*/
	int len = 100000;
	int arr[100000];
	for(int i = 0; i < len; i++)
		arr[i] = i;
// ALGO 1 POSTERIOR ANALYSIS	
//	printf("Sum of Elements: %ld\n", sum_array(arr, len));
// ALGO 2 POSTERIOR ANALYSIS
	printf("Sum of Elements: %ld\n", sum_array_2(arr, 0, len - 1));
	return 0;
}
