/* Matrix Chain Multiplication: DP */

// Header files
#include <iostream>
#include <iomanip>
#include <limits.h>

// Namespace definition
using namespace std;

// Generic function to print matrix
template <class T>
void printMatrix(T **matrix, int low, int high){
    for(int i = low; i < high; i++){
        for(int j = low; j < high; j++)
            cout<<setw(8)<<matrix[i][j];
        cout<<endl;
    }
    cout<<endl;
}

// Generic function to initialize matrix with a value
template <class P>
void initialize(P **matrix, int size, P val){
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            matrix[i][j] = val;
}

// Class definition for MCM
class MCM{
        int *p, **m, **d;
        int size;
        int matrixChainOrder();
        void printCostMatrix();
        void printDivMatrix();
        void printParenthesized(int, int);
    public:
        MCM(){}
        MCM(int arr[], int n){
            size = n;
            p = new int[size];
            m = new int*[size];
            d = new int*[size];
            for(int i = 0; i < size; i++){
                p[i] = arr[i];
                m[i] = new int[size];
                d[i] = new int[size];
            }
            initialize(m, size, 0);
            initialize(d, size, 0);
        }
        ~MCM(){
            delete p;
            for(int i = 0; i < size; i++){
                delete m[i];
                delete d[i];
            }
            delete m;
            delete d;
        }
        void display();
};

int MCM::matrixChainOrder(){
    for (int i = 1; i < size; i++)
        m[i][i] = 0;
    for (int len = 2; len < size; len++){
        for (int i = 1; i < size - len + 1; i++){
            int j = i + len - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k < j; k++){
                int cost = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (cost < m[i][j]){
                    m[i][j] = cost;
                    d[i][j] = k;
                }
            }
        }
    }
    return m[1][size - 1];
}

void MCM::printCostMatrix(){
    printMatrix(m, 1, size);
}

void MCM::printDivMatrix(){
    printMatrix(d, 1, size);
}

void MCM::printParenthesized(int i, int j){
    if (i == j)
        cout<<"A"<<i;
    else{
        cout<<"(";
        printParenthesized(i, d[i][j]);
        printParenthesized(d[i][j] + 1, j);
        cout<<")";
    }
}

void MCM::display(){
    cout<<endl<<"Minimum Cost: "<<matrixChainOrder()<<endl<<endl;
    cout<<"Cost Matrix: "<<endl;
    printCostMatrix();
    cout<<"Division Matrix: "<<endl;
    printDivMatrix();
    cout<<endl<<"Multiplication Order: "<<endl;
    printParenthesized(0, size - 1);
    cout<<endl<<endl;
}

// The main function
int main(){
    int arr[] = {1, 3, 4, 1, 2};
    int size = sizeof(arr) / sizeof(arr[0]);
    MCM M1(arr, size);
    M1.display();
    return 0;
}

/* TERMINAL
PS D:\Junior\Study\Design-and-Analysis-of-Algorithm\Lab6> g++ -o mcm_oop.exe .\mcm_oop.cpp
PS D:\Junior\Study\Design-and-Analysis-of-Algorithm\Lab6> .\mcm_oop.exe

Minimum Cost: 17

Cost Matrix: 
       0      12      15      17
       0       0      12      18
       0       0       0       8
       0       0       0       0

Division Matrix: 
       0       1       1       3
       0       0       2       3
       0       0       0       3
       0       0       0       0


Multiplication Order: 
(A0((A1(A2A3))A4))

*/