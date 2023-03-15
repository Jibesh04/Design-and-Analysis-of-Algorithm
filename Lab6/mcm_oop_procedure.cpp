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
                cout<<"FOR i = "<<i<<", j = "<<j<<" & k = "<<k<<endl;
                cout<<"M["<<i<<", "<<j<<"] = "<<"M["<<i<<", "<<k<<"] + M["<<(k+1)<<", "<<j<<"] + P"<<(i - 1)<<" * P"<<k<<" * P"<<j<<endl;
                cout<<setw(8)<<" = "<<m[i][k]<<" + "<<m[k + 1][j]<<" + "<<p[i - 1]<<" * "<<p[k]<<" * "<<p[j]<<endl;
                cout<<setw(8)<<" = "<<m[i][k]<<" + "<<m[k + 1][j]<<" + "<<p[i - 1] * p[k] * p[j]<<endl;
                cout<<setw(8)<<" = "<<cost<<endl<<endl;
                if (cost < m[i][j]){
                    m[i][j] = cost;
                    d[i][j] = k;
                }
            }
            cout<<"Minimum cost: "<<m[i][j]<<" with Partition: "<<d[i][j]<<endl;
            cout<<"_________________________________________"<<endl<<endl;
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
    cout<<endl<<matrixChainOrder()<<" is the minimum cost"<<endl<<endl;
    cout<<"Cost Matrix: "<<endl;
    printCostMatrix();
    cout<<"Division Matrix: "<<endl;
    printDivMatrix();
    cout<<endl<<"Multiplication Order: "<<endl;
    printParenthesized(1, size - 1);
    cout<<endl<<endl;
}

// The main function
int main(){
    int arr[] = {30, 35, 15, 5, 10, 20, 25};
    int size = sizeof(arr) / sizeof(arr[0]);
    MCM M1(arr, size);
    M1.display();
    return 0;
}

/* TERMINAL
PS D:\Junior\Study\Design-and-Analysis-of-Algorithm\Lab6> g++ -o mcm_oop_procedure.exe .\mcm_oop_procedure.cpp
PS D:\Junior\Study\Design-and-Analysis-of-Algorithm\Lab6> .\mcm_oop_procedure.exe

FOR i = 1, j = 2 & k = 1
M[1, 2] = M[1, 1] + M[2, 2] + P0 * P1 * P2
      = 0 + 0 + 30 * 35 * 15
      = 0 + 0 + 15750
      = 15750

Minimum cost: 15750 with Partition: 1
_________________________________________

FOR i = 2, j = 3 & k = 2
M[2, 3] = M[2, 2] + M[3, 3] + P1 * P2 * P3
      = 0 + 0 + 35 * 15 * 5
      = 0 + 0 + 2625
      = 2625

Minimum cost: 2625 with Partition: 2
_________________________________________

FOR i = 3, j = 4 & k = 3
M[3, 4] = M[3, 3] + M[4, 4] + P2 * P3 * P4
      = 0 + 0 + 15 * 5 * 10
      = 0 + 0 + 750
      = 750

Minimum cost: 750 with Partition: 3
_________________________________________

FOR i = 4, j = 5 & k = 4
M[4, 5] = M[4, 4] + M[5, 5] + P3 * P4 * P5
      = 0 + 0 + 5 * 10 * 20
      = 0 + 0 + 1000
      = 1000

Minimum cost: 1000 with Partition: 4
_________________________________________

FOR i = 5, j = 6 & k = 5
M[5, 6] = M[5, 5] + M[6, 6] + P4 * P5 * P6
      = 0 + 0 + 10 * 20 * 25
      = 0 + 0 + 5000
      = 5000

Minimum cost: 5000 with Partition: 5
_________________________________________

FOR i = 1, j = 3 & k = 1
M[1, 3] = M[1, 1] + M[2, 3] + P0 * P1 * P3
      = 0 + 2625 + 30 * 35 * 5
      = 0 + 2625 + 5250
      = 7875

FOR i = 1, j = 3 & k = 2
M[1, 3] = M[1, 2] + M[3, 3] + P0 * P2 * P3
      = 15750 + 0 + 30 * 15 * 5
      = 15750 + 0 + 2250
      = 18000

Minimum cost: 7875 with Partition: 1
_________________________________________

FOR i = 2, j = 4 & k = 2
M[2, 4] = M[2, 2] + M[3, 4] + P1 * P2 * P4
      = 0 + 750 + 35 * 15 * 10
      = 0 + 750 + 5250
      = 6000

FOR i = 2, j = 4 & k = 3
M[2, 4] = M[2, 3] + M[4, 4] + P1 * P3 * P4
      = 2625 + 0 + 35 * 5 * 10
      = 2625 + 0 + 1750
      = 4375

Minimum cost: 4375 with Partition: 3
_________________________________________

FOR i = 3, j = 5 & k = 3
M[3, 5] = M[3, 3] + M[4, 5] + P2 * P3 * P5
      = 0 + 1000 + 15 * 5 * 20
      = 0 + 1000 + 1500
      = 2500

FOR i = 3, j = 5 & k = 4
M[3, 5] = M[3, 4] + M[5, 5] + P2 * P4 * P5
      = 750 + 0 + 15 * 10 * 20
      = 750 + 0 + 3000
      = 3750

Minimum cost: 2500 with Partition: 3
_________________________________________

FOR i = 4, j = 6 & k = 4
M[4, 6] = M[4, 4] + M[5, 6] + P3 * P4 * P6
      = 0 + 5000 + 5 * 10 * 25
      = 0 + 5000 + 1250
      = 6250

FOR i = 4, j = 6 & k = 5
M[4, 6] = M[4, 5] + M[6, 6] + P3 * P5 * P6
      = 1000 + 0 + 5 * 20 * 25
      = 1000 + 0 + 2500
      = 3500

Minimum cost: 3500 with Partition: 5
_________________________________________

FOR i = 1, j = 4 & k = 1
M[1, 4] = M[1, 1] + M[2, 4] + P0 * P1 * P4
      = 0 + 4375 + 30 * 35 * 10
      = 0 + 4375 + 10500
      = 14875

FOR i = 1, j = 4 & k = 2
M[1, 4] = M[1, 2] + M[3, 4] + P0 * P2 * P4
      = 15750 + 750 + 30 * 15 * 10
      = 15750 + 750 + 4500
      = 21000

FOR i = 1, j = 4 & k = 3
M[1, 4] = M[1, 3] + M[4, 4] + P0 * P3 * P4
      = 7875 + 0 + 30 * 5 * 10
      = 7875 + 0 + 1500
      = 9375

Minimum cost: 9375 with Partition: 3
_________________________________________

FOR i = 2, j = 5 & k = 2
M[2, 5] = M[2, 2] + M[3, 5] + P1 * P2 * P5
      = 0 + 2500 + 35 * 15 * 20
      = 0 + 2500 + 10500
      = 13000

FOR i = 2, j = 5 & k = 3
M[2, 5] = M[2, 3] + M[4, 5] + P1 * P3 * P5
      = 2625 + 1000 + 35 * 5 * 20
      = 2625 + 1000 + 3500
      = 7125

FOR i = 2, j = 5 & k = 4
M[2, 5] = M[2, 4] + M[5, 5] + P1 * P4 * P5
      = 4375 + 0 + 35 * 10 * 20
      = 4375 + 0 + 7000
      = 11375

Minimum cost: 7125 with Partition: 3
_________________________________________

FOR i = 3, j = 6 & k = 3
M[3, 6] = M[3, 3] + M[4, 6] + P2 * P3 * P6
      = 0 + 3500 + 15 * 5 * 25
      = 0 + 3500 + 1875
      = 5375

FOR i = 3, j = 6 & k = 4
M[3, 6] = M[3, 4] + M[5, 6] + P2 * P4 * P6
      = 750 + 5000 + 15 * 10 * 25
      = 750 + 5000 + 3750
      = 9500

FOR i = 3, j = 6 & k = 5
M[3, 6] = M[3, 5] + M[6, 6] + P2 * P5 * P6
      = 2500 + 0 + 15 * 20 * 25
      = 2500 + 0 + 7500
      = 10000

Minimum cost: 5375 with Partition: 3
_________________________________________

FOR i = 1, j = 5 & k = 1
M[1, 5] = M[1, 1] + M[2, 5] + P0 * P1 * P5
      = 0 + 7125 + 30 * 35 * 20
      = 0 + 7125 + 21000
      = 28125

FOR i = 1, j = 5 & k = 2
M[1, 5] = M[1, 2] + M[3, 5] + P0 * P2 * P5
      = 15750 + 2500 + 30 * 15 * 20
      = 15750 + 2500 + 9000
      = 27250

FOR i = 1, j = 5 & k = 3
M[1, 5] = M[1, 3] + M[4, 5] + P0 * P3 * P5
      = 7875 + 1000 + 30 * 5 * 20
      = 7875 + 1000 + 3000
      = 11875

FOR i = 1, j = 5 & k = 4
M[1, 5] = M[1, 4] + M[5, 5] + P0 * P4 * P5
      = 9375 + 0 + 30 * 10 * 20
      = 9375 + 0 + 6000
      = 15375

Minimum cost: 11875 with Partition: 3
_________________________________________

FOR i = 2, j = 6 & k = 2
M[2, 6] = M[2, 2] + M[3, 6] + P1 * P2 * P6
      = 0 + 5375 + 35 * 15 * 25
      = 0 + 5375 + 13125
      = 18500

FOR i = 2, j = 6 & k = 3
M[2, 6] = M[2, 3] + M[4, 6] + P1 * P3 * P6
      = 2625 + 3500 + 35 * 5 * 25
      = 2625 + 3500 + 4375
      = 10500

FOR i = 2, j = 6 & k = 4
M[2, 6] = M[2, 4] + M[5, 6] + P1 * P4 * P6
      = 4375 + 5000 + 35 * 10 * 25
      = 4375 + 5000 + 8750
      = 18125

FOR i = 2, j = 6 & k = 5
M[2, 6] = M[2, 5] + M[6, 6] + P1 * P5 * P6
      = 7125 + 0 + 35 * 20 * 25
      = 7125 + 0 + 17500
      = 24625

Minimum cost: 10500 with Partition: 3
_________________________________________

FOR i = 1, j = 6 & k = 1
M[1, 6] = M[1, 1] + M[2, 6] + P0 * P1 * P6
      = 0 + 10500 + 30 * 35 * 25
      = 0 + 10500 + 26250
      = 36750

FOR i = 1, j = 6 & k = 2
M[1, 6] = M[1, 2] + M[3, 6] + P0 * P2 * P6
      = 15750 + 5375 + 30 * 15 * 25
      = 15750 + 5375 + 11250
      = 32375

FOR i = 1, j = 6 & k = 3
M[1, 6] = M[1, 3] + M[4, 6] + P0 * P3 * P6
      = 7875 + 3500 + 30 * 5 * 25
      = 7875 + 3500 + 3750
      = 15125

FOR i = 1, j = 6 & k = 4
M[1, 6] = M[1, 4] + M[5, 6] + P0 * P4 * P6
      = 9375 + 5000 + 30 * 10 * 25
      = 9375 + 5000 + 7500
      = 21875

FOR i = 1, j = 6 & k = 5
M[1, 6] = M[1, 5] + M[6, 6] + P0 * P5 * P6
      = 11875 + 0 + 30 * 20 * 25
      = 11875 + 0 + 15000
      = 26875

Minimum cost: 15125 with Partition: 3
_________________________________________

15125 is the minimum cost

Cost Matrix:
       0   15750    7875    9375   11875   15125
       0       0    2625    4375    7125   10500
       0       0       0     750    2500    5375
       0       0       0       0    1000    3500
       0       0       0       0       0    5000
       0       0       0       0       0       0

Division Matrix:
       0       1       1       3       3       3
       0       0       2       3       3       3
       0       0       0       3       3       3
       0       0       0       0       4       5
       0       0       0       0       0       5
       0       0       0       0       0       0


Multiplication Order:
((A1(A2A3))((A4A5)A6))

*/