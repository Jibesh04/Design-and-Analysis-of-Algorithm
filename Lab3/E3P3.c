/* Find first 1 in a string of bits in time complexity logn */
#include <stdio.h>
#include <stdlib.h>

// Function to input string length
int input(char * stmt){
    printf("%s", stmt);
    int n;
    scanf("%d", &n);
    return n;
}

// Input the string
char * input_str(int len, char * stmt){
    printf("%s", stmt);
    char * str = (char *)malloc(sizeof(char) * len);
    scanf("%s", str);
    return str;
}

// Search for most significant set bit
void MS_setbit(char * str, int len, int low, int high, int * idx_ref){
    if(low > high)
        return;
    int mid = low + (high - low) / 2;
    if(str[mid] == '0')
        MS_setbit(str, len, mid + 1, high, idx_ref);
    else if(str[mid] == '1'){
        (*idx_ref) = mid;
        MS_setbit(str, len, low, mid - 1, idx_ref);
    }
}

// The main function
int main(){
    int len = input("Enter the length of the string: ");
    char * str = input_str(len, "Enter the sorted binary string: ");
    int ans = -1;
    MS_setbit(str, len, 0, len - 1, &ans);
    if(ans == -1)
        printf("%s doesn't contain '1'\n", str);
    else
        printf("First set bit was found at index (0 - based): %d\n", ans);
    return 0;
}

/* TERMINAL
PS D:\Junior\Study\Design-and-Analysis-of-Algorithm\Lab3> gcc -o E3P3.exe ./E3P3.c
PS D:\Junior\Study\Design-and-Analysis-of-Algorithm\Lab3> ./E3P3.exe
Enter the length of the string: 6
Enter the sorted binary string: 000001
First set bit was found at index (0 - based): 5
PS D:\Junior\Study\Design-and-Analysis-of-Algorithm\Lab3> ./E3P3.exe
Enter the length of the string: 2
Enter the sorted binary string: 00
00 doesn't contain '1'
*/