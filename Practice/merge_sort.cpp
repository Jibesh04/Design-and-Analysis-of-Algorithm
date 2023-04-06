#include <iostream>
using namespace std;

void merge(int arr[], int l, int m, int h){
    int i = l, j = m + 1, k = 0;
    int temp[h - l + 1];
    while(i <= m && j <= h){
        if(arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }
    while(i <= m)
        temp[k++] = arr[i++];
    while(j <= h)
        temp[k++] = arr[j++];
    k = 0;
    for(int m = l; m <= h; m++)
        arr[m] = temp[k++];
}

void mergeSort(int arr[], int l, int h){
    if(l >= h)
        return;
    int m = l + (h - l)/2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, h);
    merge(arr, l, m, h);
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
    mergeSort(arr, 0, len - 1);
    cout<<"Finally, ";
    print_arr(arr, len);
    return 0;
}