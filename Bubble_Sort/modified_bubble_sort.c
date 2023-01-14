#include <stdio.h>
#include <stdlib.h>
void bubbleSort(int arr[], int size){
    unsigned short int flag;
    for(int i = 0; i < size; i++){
        flag = 1;
        for(int j = 0; j < size - i - 1; j++){
            if(arr[j] > arr[j + 1]){
                flag = 0;
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
        if(flag)
            break;
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
PS D:\Junior\Study\Design-and-Analysis-of-Algorithm\Bubble_Sort> gcc -o .\modified_bubble_sort.exe .\modified_bubble_sort.c
PS D:\Junior\Study\Design-and-Analysis-of-Algorithm\Bubble_Sort> .\modified_bubble_sort.exe
Enter the size of array: 6
Enter the elements: 6 5 4 3 4 5
Before Sorting...
6 5 4 3 4 5
After Sorting...
3 4 4 5 5 6
*/