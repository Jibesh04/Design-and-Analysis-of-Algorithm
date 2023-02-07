#include <stdio.h>
int arr_sum(int arr[], int len){
    if(len == 0)
        return 0;
    return arr[len-1] + arr_sum(arr, len - 1);        
}
int main(){
    int arr[] = {1, 3, 3, 1};
    int len = 4;
    printf("%d\n", arr_sum(arr, len));
    return 0;
}