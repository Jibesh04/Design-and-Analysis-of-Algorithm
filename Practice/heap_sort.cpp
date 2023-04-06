#include <iostream>
using namespace std;

// struct heap{
//     unsigned size, capacity;
//     int * arr;
//     heap(int c){
//         this -> size = 0;
//         this -> capacity = c;
//         this -> arr = new int[c];
//     }
// };

void maxHeapify(int arr[], int size, int idx){
    int largest = idx;
    int left = 2*idx + 1;
    int right = 2*idx + 2;
    
    if(left < size && arr[largest] < arr[left])
        largest = left;
    if(right < size && arr[largest] < arr[right])
        largest = right;
    if(largest != idx){
        int temp = arr[largest];
        arr[largest] = arr[idx];
        arr[idx] = temp;
        maxHeapify(arr, size, largest);
    }
}

void heapSort(int arr[], int len){
    for(int i = len/2 - 1; i >= 0; i--)
        maxHeapify(arr, len, i);
    for(int i = len - 1; i >= 0; i--){
        int temp = arr[i];
        arr[i] = arr[0];
        arr[0] = temp;
        maxHeapify(arr, i, 0);
    }
}
void print_arr(int arr[], int len){
    for(int i = 0; i < len; i++)
        cout<<" "<<arr[i];
    cout<<endl;
}

int main(){
    int arr[] = {5, 4, 3, 2, 1};
    int len = sizeof(arr)/sizeof(arr[0]);
    cout<<"Initially, ";
    print_arr(arr, len);
    heapSort(arr, len);
    cout<<"Finally, ";
    print_arr(arr, len);
    return 0;
}