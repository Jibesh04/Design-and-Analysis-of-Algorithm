#include <iostream>
using namespace std;
void swap(int& a, int& b){
    int temp = a;
    a = b;
    b = temp;
}
void bubbleSort(int arr[], int N){
    for(int i = 0; i < N - 1; i++)
        for(int j = 0; j < N - i - 1; j++)
            if(arr[j] > arr[j+1])
                swap(arr[j], arr[j + 1]);
}
void print_array(int arr[], int N){
    cout<<"The array of size "<<N<<" is: ";
    for(int i = 0; i < N; i++)
        cout<<arr[i]<<" ";
    cout<<endl;
}
int main(){
    int N = 100;
    int arr[N];
    cout<<"Sorted Array...\n";
    for(int i = 0; i < N; i++)
        arr[i] = i + 1;
    bubbleSort(arr, N);
    print_array(arr, N);
    cout<<"Inverse Sorted Array...\n";
    for(int i = 0; i < N; i++)
        arr[i] = N - i;
    bubbleSort(arr, N);
    print_array(arr, N);
    return 0;
}

/* TERMINAL
PS D:\Junior\Study\Design-and-Analysis-of-Algorithm\Bubble_Sort> g++ -o .\traditional_bubble_sort.exe .\traditional_bubble_sort.cpp
PS D:\Junior\Study\Design-and-Analysis-of-Algorithm\Bubble_Sort> .\traditional_bubble_sort.exe
Sorted Array...
The array of size 100 is: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48
 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100
Inverse Sorted Array...
The array of size 100 is: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48
 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100
 */