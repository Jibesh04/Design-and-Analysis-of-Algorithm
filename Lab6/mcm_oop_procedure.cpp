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
    printParenthesized(0, size - 1);
    cout<<endl<<endl;
}

// The main function
int main(){
    int arr[] = {30, 35, 50, 5, 10, 20, 25};
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
      = 0 + 0 + 30 * 35 * 50
      = 0 + 0 + 52500
      = 52500

Minimum cost: 52500 with Partition: 1
_________________________________________

FOR i = 2, j = 3 & k = 2
M[2, 3] = M[2, 2] + M[3, 3] + P1 * P2 * P3
      = 0 + 0 + 35 * 50 * 5
      = 0 + 0 + 8750
      = 8750

Minimum cost: 8750 with Partition: 2
_________________________________________

FOR i = 3, j = 4 & k = 3
M[3, 4] = M[3, 3] + M[4, 4] + P2 * P3 * P4
      = 0 + 0 + 50 * 5 * 10
      = 0 + 0 + 2500
      = 2500

Minimum cost: 2500 with Partition: 3
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
      = 0 + 8750 + 30 * 35 * 5
      = 0 + 8750 + 5250
      = 14000

FOR i = 1, j = 3 & k = 2
M[1, 3] = M[1, 2] + M[3, 3] + P0 * P2 * P3
      = 52500 + 0 + 30 * 50 * 5
      = 52500 + 0 + 7500
      = 60000

Minimum cost: 14000 with Partition: 1
_________________________________________

FOR i = 2, j = 4 & k = 2
M[2, 4] = M[2, 2] + M[3, 4] + P1 * P2 * P4
      = 0 + 2500 + 35 * 50 * 10
      = 0 + 2500 + 17500
      = 20000

FOR i = 2, j = 4 & k = 3
M[2, 4] = M[2, 3] + M[4, 4] + P1 * P3 * P4
      = 8750 + 0 + 35 * 5 * 10
      = 8750 + 0 + 1750
      = 10500

Minimum cost: 10500 with Partition: 3
_________________________________________

FOR i = 3, j = 5 & k = 3
M[3, 5] = M[3, 3] + M[4, 5] + P2 * P3 * P5
      = 0 + 1000 + 50 * 5 * 20
      = 0 + 1000 + 5000
      = 6000

FOR i = 3, j = 5 & k = 4
M[3, 5] = M[3, 4] + M[5, 5] + P2 * P4 * P5
      = 2500 + 0 + 50 * 10 * 20
      = 2500 + 0 + 10000
      = 12500

Minimum cost: 6000 with Partition: 3
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
      = 0 + 10500 + 30 * 35 * 10
      = 0 + 10500 + 10500
      = 21000

FOR i = 1, j = 4 & k = 2
M[1, 4] = M[1, 2] + M[3, 4] + P0 * P2 * P4
      = 52500 + 2500 + 30 * 50 * 10
      = 52500 + 2500 + 15000
      = 70000

FOR i = 1, j = 4 & k = 3
M[1, 4] = M[1, 3] + M[4, 4] + P0 * P3 * P4
      = 14000 + 0 + 30 * 5 * 10
      = 14000 + 0 + 1500
      = 15500

Minimum cost: 15500 with Partition: 3
_________________________________________

FOR i = 2, j = 5 & k = 2
M[2, 5] = M[2, 2] + M[3, 5] + P1 * P2 * P5
      = 0 + 6000 + 35 * 50 * 20
      = 0 + 6000 + 35000
      = 41000

FOR i = 2, j = 5 & k = 3
M[2, 5] = M[2, 3] + M[4, 5] + P1 * P3 * P5
      = 8750 + 1000 + 35 * 5 * 20
      = 8750 + 1000 + 3500
      = 13250

FOR i = 2, j = 5 & k = 4
M[2, 5] = M[2, 4] + M[5, 5] + P1 * P4 * P5
      = 10500 + 0 + 35 * 10 * 20
      = 10500 + 0 + 7000
      = 17500

Minimum cost: 13250 with Partition: 3
_________________________________________

FOR i = 3, j = 6 & k = 3
M[3, 6] = M[3, 3] + M[4, 6] + P2 * P3 * P6
      = 0 + 3500 + 50 * 5 * 25
      = 0 + 3500 + 6250
      = 9750

FOR i = 3, j = 6 & k = 4
M[3, 6] = M[3, 4] + M[5, 6] + P2 * P4 * P6
      = 2500 + 5000 + 50 * 10 * 25
      = 2500 + 5000 + 12500
      = 20000

FOR i = 3, j = 6 & k = 5
M[3, 6] = M[3, 5] + M[6, 6] + P2 * P5 * P6
      = 6000 + 0 + 50 * 20 * 25
      = 6000 + 0 + 25000
      = 31000

Minimum cost: 9750 with Partition: 3
_________________________________________

FOR i = 1, j = 5 & k = 1
M[1, 5] = M[1, 1] + M[2, 5] + P0 * P1 * P5
      = 0 + 13250 + 30 * 35 * 20
      = 0 + 13250 + 21000
      = 34250

FOR i = 1, j = 5 & k = 2
M[1, 5] = M[1, 2] + M[3, 5] + P0 * P2 * P5
      = 52500 + 6000 + 30 * 50 * 20
      = 52500 + 6000 + 30000
      = 88500

FOR i = 1, j = 5 & k = 3
M[1, 5] = M[1, 3] + M[4, 5] + P0 * P3 * P5
      = 14000 + 1000 + 30 * 5 * 20
      = 14000 + 1000 + 3000
      = 18000

FOR i = 1, j = 5 & k = 4
M[1, 5] = M[1, 4] + M[5, 5] + P0 * P4 * P5
      = 15500 + 0 + 30 * 10 * 20
      = 15500 + 0 + 6000
      = 21500

Minimum cost: 18000 with Partition: 3
_________________________________________

FOR i = 2, j = 6 & k = 2
M[2, 6] = M[2, 2] + M[3, 6] + P1 * P2 * P6
      = 0 + 9750 + 35 * 50 * 25
      = 0 + 9750 + 43750
      = 53500

FOR i = 2, j = 6 & k = 3
M[2, 6] = M[2, 3] + M[4, 6] + P1 * P3 * P6
      = 8750 + 3500 + 35 * 5 * 25
      = 8750 + 3500 + 4375
      = 16625

FOR i = 2, j = 6 & k = 4
M[2, 6] = M[2, 4] + M[5, 6] + P1 * P4 * P6
      = 10500 + 5000 + 35 * 10 * 25
      = 10500 + 5000 + 8750
      = 24250

FOR i = 2, j = 6 & k = 5
M[2, 6] = M[2, 5] + M[6, 6] + P1 * P5 * P6
      = 13250 + 0 + 35 * 20 * 25
      = 13250 + 0 + 17500
      = 30750

Minimum cost: 16625 with Partition: 3
_________________________________________

FOR i = 1, j = 6 & k = 1
M[1, 6] = M[1, 1] + M[2, 6] + P0 * P1 * P6
      = 0 + 16625 + 30 * 35 * 25
      = 0 + 16625 + 26250
      = 42875

FOR i = 1, j = 6 & k = 2
M[1, 6] = M[1, 2] + M[3, 6] + P0 * P2 * P6
      = 52500 + 9750 + 30 * 50 * 25
      = 52500 + 9750 + 37500
      = 99750

FOR i = 1, j = 6 & k = 3
M[1, 6] = M[1, 3] + M[4, 6] + P0 * P3 * P6
      = 14000 + 3500 + 30 * 5 * 25
      = 14000 + 3500 + 3750
      = 21250

FOR i = 1, j = 6 & k = 4
M[1, 6] = M[1, 4] + M[5, 6] + P0 * P4 * P6
      = 15500 + 5000 + 30 * 10 * 25
      = 15500 + 5000 + 7500
      = 28000

FOR i = 1, j = 6 & k = 5
M[1, 6] = M[1, 5] + M[6, 6] + P0 * P5 * P6
      = 18000 + 0 + 30 * 20 * 25
      = 18000 + 0 + 15000
      = 33000

Minimum cost: 21250 with Partition: 3
_________________________________________

21250 is the minimum cost

Cost Matrix:
       0   52500   14000   15500   18000   21250
       0       0    8750   10500   13250   16625
       0       0       0    2500    6000    9750
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
(A0((A1(A2A3))((A4A5)A6)))

*/