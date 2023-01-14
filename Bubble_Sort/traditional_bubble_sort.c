#include <stdio.h>
#include <stdlib.h>
void bubbleSort(int arr[], int size){
    for(int i = 0; i < size - 1; i++){
        for(int j = 0; j < size - i - 1; j++){
            if(arr[j] > arr[j + 1]){
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
int* input_arr(int size){
    int *arr = (int*)malloc(size * sizeof(int));
    printf("Enter the elements: ");
    for(int i = 0; i < size; i++)
        scanf("%d", &arr[i]);
    return arr;
}
int input_size(){
    int n;
    printf("Enter the size of array: ");
    scanf("%d", &n);
    return n;
}
void display_arr(int arr[], int size){
    for(int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
int main(){
    int size = input_size();
    int *arr = input_arr(size);
    printf("Before Sorting...\n");
    display_arr(arr, size);
    bubbleSort(arr, size);
    printf("After Sorting...\n");
    display_arr(arr, size);
    return 0;
}

/* TERMINAL
PS D:\Junior\Study\Design-and-Analysis-of-Algorithm\Bubble_Sort> gcc -o .\traditional_bubble_sort.exe .\traditional_bubble_sort.c
PS D:\Junior\Study\Design-and-Analysis-of-Algorithm\Bubble_Sort> .\traditional_bubble_sort.exe
Enter the size of array: 5
Enter the elements: 3 1 2 6 1
Before Sorting...
3 1 2 6 1
After Sorting...
1 1 2 3 6
*/