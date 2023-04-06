#include <iostream>
using namespace std;

int partition(int arr[], int l, int h){
    int i = l, pi = h;
    for(int j = l + 1; j < h; j++){
        if(arr[j] < arr[pi]){
            swap(arr[j], arr[i]);
            i++;
        }
    }
    swap(arr[i], arr[pi]);
    return i;
}

void quickSort(int arr[], int l, int h){
    if(l >= h)
        return;
    int pi = partition(arr, l, h);
    quickSort(arr, l, pi - 1);
    quickSort(arr, pi + 1, h);
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
    quickSort(arr, 0, len - 1);
    cout<<"Finally, ";
    print_arr(arr, len);
    return 0;
}