#include <iostream>
using namespace std;

struct node{
    char s;
    int f;
    node * left, * right;
    node(char s, int f){
        this -> s = s;
        this -> f = f;
        this -> left = this -> right = NULL;
    }
};

struct minHeap{
    unsigned size, capacity;
    node ** arr;
    minHeap(int c){
        this -> size = 0;
        this -> capacity = c;
        this -> arr = new node*[c];
    }
};

void minHeapify(minHeap * mH, int i){
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int n = mH -> size;
    if(left < n && mH -> arr[left] -> f < mH -> arr[smallest] -> f)
        smallest = left;
    if(right < n && mH -> arr[right] -> f < mH -> arr[smallest] -> f)
        smallest = right;
    if(smallest != i){
        swap(mH -> arr[smallest], mH -> arr[i]);
        minHeapify(mH, smallest);
    }
}

node* extractMin(minHeap* mH){
    node* r = mH -> arr[0];
    mH -> arr[0] = mH -> arr[mH -> size - 1];
    --(mH -> size);
    minHeapify(mH, 0);
    return r;
}

void insert(minHeap * mH, node * n){
    mH -> arr[mH -> size] = n;
    ++(mH -> size);
    int i = mH -> size - 1;
    while(i && mH -> arr[(i - 1)/2] -> f < mH -> arr[i] -> f){
        swap(mH -> arr[(i - 1) / 2], mH -> arr[i]);
        i = (i - 1)/2;
    }
}

minHeap* createAndBuildMinHeap(char * s, int * f, int n){
    minHeap * mH = new minHeap(n);
    for(int i = 0; i < n; i++){
        node * temp = new node(s[i], f[i]);
        mH -> arr[i] = temp;
        ++(mH -> size);
    }
    minHeapify(mH, 0);
    return mH;
}

node * createHuffmanTree(char * s, int * f, int c){
    minHeap * mH = createAndBuildMinHeap(s, f, c);
    while(mH -> size > 1){
        node * left = extractMin(mH);
        node * right = extractMin(mH);
        node * n = new node('$', left -> f + right -> f);
        n -> left = left;
        n -> right = right;
        insert(mH, n);
    }
    return extractMin(mH);
}

void print_freq(node * root, string s){
    if(!root)
        return;
    if(root -> s != '$')
        cout<<(root -> s)<<" "<<s<<endl;
    print_freq(root -> left, s + '0');
    print_freq(root -> right, s + '1');
}

int main(){
    char s[] = {'A', 'B', 'C', 'D'};
	int f[] = {5, 1, 6, 3};
    int c = 4;
    node * root = createHuffmanTree(s, f, c);
    print_freq(root, "");
    return 0;
}