#include <iostream>
using namespace std;

void bubbleSort(int arr[], int len){
    bool flag;
    for(int i = 0; i < len - 1; i++){
        flag = 1;
        for(int j = 0; j < len - i - 1; j++){
            if(arr[j] > arr[j + 1]){
                flag = 0;
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
            if(flag)
                break;
        }
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
    bubbleSort(arr, len);
    cout<<"Finally, ";
    print_arr(arr, len);
    return 0;
}