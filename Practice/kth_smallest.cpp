#include <iostream>
using namespace std;

 struct heap{
    unsigned size, capacity;
    int * arr;
    heap(int c){
        this -> size = 0;
        this -> capacity = c;
        this -> arr = new int[c];
    }
};

void minHeapify(heap * mH, int i){
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int n = mH -> size;
    if(left < n && mH -> arr[left] < mH -> arr[smallest])
        smallest = left;
    if(right < n && mH -> arr[right] < mH -> arr[smallest])
        smallest = right;
    if(smallest != i){
        swap(mH -> arr[smallest], mH -> arr[i]);
        minHeapify(mH, smallest);
    }
}

int extractMin(heap * mH){
    int r = mH -> arr[0];
    mH -> arr[0] = mH -> arr[mH -> size - 1];
    --(mH -> size);
    minHeapify(mH, 0);
    return r;
}

int kth_smallest(int arr[], int n, int k){
    heap * mH = new heap(n);
    for(int i = 0; i < n; i++){
        ++(mH -> size);
        mH -> arr[i] = arr[i];
    }
    for(int i = n/2 - 1; i >= 0; i--)
        minHeapify(mH, i);
    for(int i = 0; i < k - 1; i++)
        extractMin(mH);
    return extractMin(mH);
}

int main(){
    int arr[] = {5, 4, 2, 2, 1};
    int len = sizeof(arr)/sizeof(arr[0]);
    int k = 3;
    cout<<"kth Smallest number: "<<kth_smallest(arr, len, k)<<endl;
    return 0;
}