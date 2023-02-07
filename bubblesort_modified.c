#include <stdio.h>
#include <stdlib.h>
void bubblesort(int arr[], int size){
	int flag = 0;
/*	for(int i = 0; i < size-1; i++){
		if(arr[i] > arr[i+1]){
			flag = 1;
			break;
		}
	}
	if(!flag)
		printf("ALREADY SORTED: O(N)\n");
	if(flag){ */
		for(int i = 0; i < size - 1; i++){
			// flag = 0;
			for(int j = 0; j < size - 1 - i; j++){
				if(arr[j] > arr[j+1]){	
					flag = 1;
					int temp = arr[j];
					arr[j] = arr[j+1];
					arr[j+1] = temp;
				}
			}
			if(!flag)
				break;
		}
//	}
}
int* input(int size){
	int *arr;
	arr = (int*)malloc(size*sizeof(int));
	printf("Enter the elements: ");
	for(int i = 0; i < size; i++)
		scanf("%d", &arr[i]);
	return arr;
}
void display(int arr[], int size){
	for(int i = 0; i < size; i++)
		printf("%d\t", arr[i]);
	printf("\n");
}
int main(){
	int size;
	printf("Enter size of array: ");
	scanf("%d", &size);
	int *arr = input(size);
	printf("Entered Array...\n");
	display(arr, size);
	bubblesort(arr, size);
	printf("Sorted Array...\n");
	display(arr, size);
	return 0;
}
