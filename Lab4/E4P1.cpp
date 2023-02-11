// Heap Sort Algorithm Implementation

#include <iostream>
using namespace std;

template <class T>
void swap_elem(T &a, T &b)
{
    T temp;
    temp = a;
    a = b;
    b = temp;
}

class Array
{
    int len;
    int *arr;
    void heapify(int *, int, int);

public:
    Array() {}
    Array(int N, int *A)
    {
        len = N;
        arr = new int[len];
        for (int i = 0; i < len; i++)
            arr[i] = A[i];
    }
    ~Array()
    {
        delete arr;
    }
    // void input_arr();
    void heapSort();
    void print_arr();
};

// Heapify() : helper function
void Array::heapify(int *arr, int len, int i)
{
    // Realization of heap
    int largest_idx = i;
    int left_idx = 2 * i + 1;
    int right_idx = 2 * i + 2;

    // Find the index of largest element among D, L, R
    if (left_idx < len && arr[left_idx] > arr[largest_idx])
        largest_idx = left_idx;
    if (right_idx < len && arr[right_idx] > arr[largest_idx])
        largest_idx = right_idx;

    // If largest element index is not same as parent element index
    // Swap the value and recursively call heapify for child
    if (largest_idx != i)
    {
        swap_elem(arr[i], arr[largest_idx]);
        heapify(arr, len, largest_idx);
    }
}

// The heapsort function
void Array::heapSort()
{
    // Max heap
    for (int i = len / 2 - 1; i >= 0; i--)
        heapify(arr, len, i);

    // Placing maximum element and eliminating from array to be hepified
    for (int i = len - 1; i >= 0; i--)
    {
        swap_elem(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

/*
// Function to input the array
void Array::input_arr(){
cout<<"Enter the length: ";
cin>>len;
arr = new int[len];
cout<<"Enter the array: ";
for(int i = 0; i < len; i++)
cin>>arr[i];
}
*/

// Function to print the array
void Array::print_arr()
{
    cout << "The array is..." << endl;
    for (int i = 0; i < len; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main()
{
    int len;
    cout << "Enter the size of the array: ";
    cin >> len;
    int arr[len];
    cout << "Enter the array: ";
    for (int i = 0; i < len; i++)
        cin >> arr[i];
    Array A(len, arr);
    cout << "Before Sorting..." << endl;
    A.print_arr();
    A.heapSort();
    cout << "After Sorting..." << endl;
    A.print_arr();
    return 0;
}

/* TERMINAL
cse2102040024@vssutcse-ProLiant-ML350-Gen9:~/DAA$ g++ -o E4P1.exe ./E4P1.cpp
cse2102040024@vssutcse-ProLiant-ML350-Gen9:~/DAA$ ./E4P1.exe
Enter the size of the array: 5
Enter the array: 9 1 3 10 0
Before Sorting...
The array is...
9 1 3 10 0
After Sorting...
The array is...
0 1 3 9 10
*/
