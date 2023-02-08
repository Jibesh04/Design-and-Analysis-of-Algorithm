/* Write a program to find the kth smallest element
in an array with time complexity less than nlogn */

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

// Function to find count of smaller numbers
int count_smaller_num(int arr[], int len, int mid){
    int count = 0;
    for(int i = 0; i < len; i++)
        if(arr[i] <= mid)
            count++;
    return count;
}

// Function to find kth-smallest element
int kth_smallest(int arr[], int len, int k){
    int low = INT_MAX, high = INT_MIN;

    // Minimum and Maximum element
    for(int i = 0; i < len; i++){
        low = arr[i] < low ? arr[i] : low;
        high = arr[i] > high ? arr[i] : high;
    }

    // Binary Search applied
    while(low < high){
        int mid = low + (high - low) / 2;
        if(count_smaller_num(arr, len, mid) < k)
            low = mid + 1;
        else
            high = mid;
    }
    return low;
}

// The main funcntion
int main(){
    int len = input("Enter the size of the array: ");
    int * arr = input_arr(len, "Enter the array: ");
    int k = input("\nTo find kth smallest element,\nEnter the value of k: ");
    printf("\nThe kth smallest element is: %d\n", kth_smallest(arr, len, k));
    return 0;
}

/* TERMINAL
PS D:\Junior\Study\Design-and-Analysis-of-Algorithm\Lab3> gcc -o E3P2.exe .\E3P2.c
PS D:\Junior\Study\Design-and-Analysis-of-Algorithm\Lab3> ./E3P2.exe
Enter the size of the array: 5
Enter the array: 1 9 4 2 6

To find kth smallest element,
Enter the value of k: 3

The kth smallest element is: 4
PS D:\Junior\Study\Design-and-Analysis-of-Algorithm\Lab3> ./E3P2.exe
Enter the size of the array: 3
Enter the array: 1 2 3

To find kth smallest element,
Enter the value of k: 3

The kth smallest element is: 3
 */