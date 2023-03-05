/*
Sashmit Kabi
Tanmaya Kumar Naik
Basant Xalxo
Mohammed Swalleh Aman
Sarthak Priyadarshi Mahanta
Bibek Kumar Meher
Prem Prabhujeet
Subhranshu Sekhar Panda
Soumya Ranjan Padhi
Mitradev Rana
Debraj Swain
Prerit Kumar Jain
Anshu Agrawal
Ashish Kumar Mishra
Sandeep Kumar Nayak
Jyotiraditya Biswal
Jibesh Kumar Panda
Prerit Agrawal
*/
#include <iostream>
#include <iomanip>
#include <limits.h>
// #include <cmath>
// #include <bits/stdc++.h>
// #define INT_MAX 2147483647
using namespace std;

int m[100][100];
int d[100][100];

void printCombination(int p[], int i, int j)
{
    if (i == j)
        cout << "A" << i;
    else
    {
        cout << "(";
        printCombination(p, i, d[i][j]);
        printCombination(p, d[i][j] + 1, j);
        cout << ")";
    }
}

void printCostMatrix(int n)
{
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < n; j++)
            cout << setw(8) << m[i][j];
        cout << endl;
    }
}

void printDivMatrix(int n)
{
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < n; j++)
            cout << setw(8) << d[i][j];
        cout << endl;
    }
}

int matrixChainOrder(int p[], int n)
{
    for (int i = 1; i < n; i++)
        m[i][i] = 0;
    for (int len = 2; len < n; len++)
    {
        for (int i = 1; i < n - len + 1; i++)
        {
            int j = i + len - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k < j; k++)
            {
                int cost = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (cost < m[i][j])
                {
                    m[i][j] = cost;
                    d[i][j] = k;
                }
            }
        }
    }
    cout << "Cost Matrix" << endl;
    printCostMatrix(n);
    cout << "Division Matrix" << endl;
    printDivMatrix(n);
    cout << "Multiplication Order: ";
    printCombination(p, 0, n - 1);
    cout << endl;
    return m[1][n - 1];
}

int main()
{
    // cout<<(int)(pow(2, 31) - 1)<<endl;
    // 2.14748e+09
    // cout<<(int)(pow(2, 31) - 1)<<endl;
    // 2147483647
    // cout<<INT_MAX<<endl;
    // 2147483647
    int arr[] = {1, 3, 4, 1, 2};
    int size = sizeof(arr) / sizeof(int);
    cout << "Minimum Cost: " << matrixChainOrder(arr, size) << endl;
    return 0;
}
/*
int MatrixChainOrder(int p[], int n)
{
*/
/* For simplicity of the program, one
extra row and one extra column are
allocated in m[][]. 0th row and 0th
column of m[][] are not used */
/*    int m[n][n];

    int i, j, k, L, q;

*/
/* m[i, j] = Minimum number of scalar
multiplications needed to compute the
matrix A[i]A[i+1]...A[j] = A[i..j] where
dimension of A[i] is p[i-1] x p[i] */

// cost is zero when multiplying
// one matrix.
/*    for (i = 1; i < n; i++)
        m[i][i] = 0;
*/
// L is chain length.
/*    for (L = 2; L < n; L++)
    {
        for (i = 1; i < n - L + 1; i++)
        {
            j = i + L - 1;
            m[i][j] = INT_MAX;
            for (k = i; k <= j - 1; k++)
            {
                // q = cost/scalar multiplications
                q = m[i][k] + m[k + 1][j]
                    + p[i - 1] * p[k] * p[j];
                if (q < m[i][j])
                    m[i][j] = q;
            }
        }
    }

    return m[1][n - 1];
}
*/
// Driver Code
/*
int main()
{
    int arr[] = { 1, 2, 3, 4 };
    int size = sizeof(arr) / sizeof(arr[0]);

    cout << "Minimum number of multiplications is "
         << MatrixChainOrder(arr, size);

    getchar();
    return 0;
}
*/

/* TERMINAL 
PS D:\Junior\Study\Design-and-Analysis-of-Algorithm\Lab6> g++ .\MCM.cpp
PS D:\Junior\Study\Design-and-Analysis-of-Algorithm\Lab6> .\a.exe      
Minimum Cost: Cost Matrix
       0      12      15      17
       0       0      12      18
       0       0       0       8
       0       0       0       0
Division Matrix
       0       1       1       3
       0       0       2       3
       0       0       0       3
       0       0       0       0
Multiplication Order: (A0((A1(A2A3))A4))
17
*/