// Fractional KnapSack Problem solution using HeapSort

#include <iostream>
using namespace std;

template <class T>
void swap_elem(T &a, T &b)
{
    T temp;
    temp = a;
    a = b;
    b = temp;
}

class Array
{
    int len, weight_lim;
    int *weight, *profit;
    float *p_per_w;
    void heapify(float *, int *, int *, int, int);

public:
    Array() {}
    Array(int N, int *W, int *P, int lim)
    {
        len = N;
        weight = new int[len];
        profit = new int[len];
        p_per_w = new float[len];
        for (int i = 0; i < len; i++)
            weight[i] = W[i];
        for (int i = 0; i < len; i++)
            profit[i] = P[i];
        for (int i = 0; i < len; i++)
            p_per_w[i] = (float)P[i] / (float)W[i];
        weight_lim = lim;
    }
    ~Array()
    {
        delete weight;
        delete profit;
        delete p_per_w;
    }
    // void input_arr();
    void heapSort();
    void print_arr();
    float maxProfit();
};

// Heapify() : helper function
void Array::heapify(float *a1, int *a2, int *a3, int len, int i)
{
    // Realization of heap
    int largest_idx = i;
    int left_idx = 2 * i + 1;
    int right_idx = 2 * i + 2;

    // Find the index of largest element among D, L, R
    if (left_idx < len && a1[left_idx] > a1[largest_idx])
        largest_idx = left_idx;
    if (right_idx < len && a1[right_idx] > a1[largest_idx])
        largest_idx = right_idx;

    // If largest element index is not same as parent element index
    // Swap the value and recursively call heapify for child
    if (largest_idx != i)
    {
        swap_elem(a1[i], a1[largest_idx]);
        swap_elem(a2[i], a2[largest_idx]);
        swap_elem(a3[i], a3[largest_idx]);
        heapify(a1, a2, a3, len, largest_idx);
    }
}

// The heapsort function
void Array::heapSort()
{
    // Max heap
    for (int i = len / 2 - 1; i >= 0; i--)
        heapify(p_per_w, profit, weight, len, i);

    // Placing maximum element and eliminating from array to be hepified
    for (int i = len - 1; i >= 0; i--)
    {
        swap_elem(p_per_w[0], p_per_w[i]);
        swap_elem(profit[0], profit[i]);
        swap_elem(weight[0], weight[i]);
        heapify(p_per_w, profit, weight, i, 0);
    }
}

/*
// Function to input the array
void Array::input_arr(){
cout<<"Enter the length: ";
cin>>len;
arr = new int[len];
cout<<"Enter the array: ";
for(int i = 0; i < len; i++)
cin>>arr[i];
}
*/

// Function to print the array
void Array::print_arr()
{
    cout << "The profit array is..." << endl;
    for (int i = 0; i < len; i++)
        cout << profit[i] << " ";
    cout << endl;
    cout << "The weight array is..." << endl;
    for (int i = 0; i < len; i++)
        cout << weight[i] << " ";
    cout << endl;
    cout << "The profit per weight array is..." << endl;
    for (int i = 0; i < len; i++)
        cout << p_per_w[i] << " ";
    cout << endl;
}

// Function to calculate maximum profit
float Array::maxProfit()
{
    float max_profit = 0;
    int lim = weight_lim;
    for (int i = len - 1; i >= 0; i--)
    {
        if (lim == 0)
            break;
        if (weight[i] > lim)
        {
            max_profit += (float)lim * p_per_w[i];
            cout << " + Rs. " << profit[i] << " of remaining weight " << lim << " kg" << endl;
            break;
        }
        max_profit += profit[i];
        lim -= weight[i];
        cout << " + Rs. " << profit[i] << " of weight " << weight[i] << " kg" << endl;
    }
    return max_profit;
}

int main()
{
    int len, weight_lim;
    cout << "Enter the number of elements: ";
    cin >> len;
    int W[len], P[len];
    cout << "Enter the weight of elements: ";
    for (int i = 0; i < len; i++)
        cin >> W[i];
    cout << "Enter the profit of elements: ";
    for (int i = 0; i < len; i++)
        cin >> P[i];
    cout << "Enter the weight limit of the knapsack: ";
    cin >> weight_lim;
    Array A(len, W, P, weight_lim);
    A.print_arr();
    A.heapSort();
    float ans = A.maxProfit();
    cout << "Maximum obtainable profit is: Rs. " << ans << endl;
    return 0;
}

/* TERMINAL
PS D:\Junior\Study\Design-and-Analysis-of-Algorithm\Lab4> g++ -o E4P2.exe ./E4P2.cpp
PS D:\Junior\Study\Design-and-Analysis-of-Algorithm\Lab4> ./E4P2.exe
Enter the number of elements: 4
Enter the weight of elements: 4 2 3 5
Enter the profit of elements: 10 5 15 3
Enter the weight limit of the knapsack: 10
The profit array is...
10 5 15 3
The weight array is...
4 2 3 5
The profit per weight array is...
2.5 2.5 5 0.6
 + Rs. 15 of weight 3 kg
 + Rs. 5 of weight 2 kg
 + Rs. 10 of weight 4 kg
 + Rs. 3 of remaining weight 1 kg
Maximum obtainable profit is: Rs. 30.6
*/