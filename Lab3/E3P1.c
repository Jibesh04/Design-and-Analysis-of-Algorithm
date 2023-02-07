/* Find the number of inversion pairs in an array
with time complexity nlogn */
#include <stdio.h>
#include <stdlib.h>

// Function to input the length
int input(char * stmt){
    int n;
    printf("%s", stmt);
    scanf("%d", &n);
    return n;
}

// Function to input the array
int * input_arr(int len, char * stmt){
    int * arr = (int*)malloc(sizeof(int) * len);
    printf("%s", stmt);
    for(int i = 0; i < len; i++)
        scanf("%d", &arr[i]);
    return arr;
}

// Functions to count inversion pairs
void merge(int arr[], int low, int mid, int high, int * cnt_ref){
    int i = low, j = mid + 1, k = 0;
    int arr_temp[high - low + 1];
    while(i <= mid && j <= high){
        if(arr[i] <= arr[j])
            arr_temp[k++] = arr[i++];
        else{
            arr_temp[k++] = arr[j++];
            printf("(%d, %d)\n", arr[i], arr[j - 1]);
            (*cnt_ref)++;
        }
    }
    while(i <= mid)
        arr_temp[k++] = arr[i++];
    while(j <= high)
        arr_temp[k++] = arr[j++];
    k = 0;
    for(int l = low; l <= high; l++)
        arr[l] = arr_temp[k++];
}

void helper(int arr[], int low, int high, int * cnt_ref){
    if(low >= high)
        return;
    int mid = low + (high - low)/2;
    helper(arr, low, mid, cnt_ref);
    helper(arr, mid + 1, high, cnt_ref);
    merge(arr, low, mid, high, cnt_ref);
}

int count_inv_pairs(int arr[], int len){
    int count = 0;
    helper(arr, 0, len - 1, &count);
    return count;
}

// The main function
int main(){
    int len = input("Enter the size of the array: ");
    int * arr = input_arr(len, "Enter the elements: ");
    printf("The array contains %d inversion pairs\n", count_inv_pairs(arr, len));
    return 0;
}

/* TERMINAL
PS D:\Junior\Study\Design-and-Analysis-of-Algorithm\Lab3> gcc -o E3P1.exe ./E3P1.c
PS D:\Junior\Study\Design-and-Analysis-of-Algorithm\Lab3> ./E3P1.exe
Enter the size of the array: 5
Enter the elements: 3 1 5 4 2
(3, 1)
(4, 2)
(3, 2)
(5, 4)
The array contains 4 inversion pairs
*/