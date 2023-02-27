/* Huffman code */
#include <iostream>
#include <cstdlib>
using namespace std;

template <class T>
void swapNode(T &a, T &b){
	// cout<<"Swap called"<<endl;
	T c = a;
	a = b;
	b = c;
	// cout<<"Swapped successfully"<<endl;
}

struct Node{
	char symbol;
	unsigned int freq;
	Node *left, *right;
	Node(char s, int f){
		this -> symbol = s;
		this -> freq = f;
		left = right = NULL;
	}
};

struct minHeap{
	unsigned int size, capacity;
	Node ** arr;
	minHeap(int c){
		this -> size = 0;
		this -> capacity = c;
		arr = (Node**)malloc(c * sizeof(Node*));
	}
};

void heapify(minHeap *mH, int i){
	// cout<<"Heapify called"<<endl;
	int smallest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	if(left < mH -> size && mH -> arr[left] -> freq < mH -> arr[smallest] -> freq)
		smallest = left;
	if(right < mH -> size && mH -> arr[right] -> freq < mH -> arr[smallest] -> freq)
		smallest = right;
	if(smallest != i){
		swapNode(mH -> arr[smallest], mH -> arr[i]);
		heapify(mH, smallest);
	}
	// cout<<"Heapify Success"<<endl;
}

Node * extractMin(minHeap * mH){
	// cout<<"Extract Min called"<<endl;
	Node * min = mH -> arr[0];
	// cout<<"Min Heap Size: "<<mH -> size<<endl;
	// cout<<"Line 54 executed"<<endl;
	mH -> arr[0] = mH -> arr[mH -> size - 1];
	// cout<<"Line 56 executed"<<endl;
	--(mH -> size);
	// cout<<"Line 58 executed"<<endl;
	heapify(mH, 0);
	// cout<<"Extract Min success"<<endl;
	return min;
}

void insertNode(minHeap * mH, Node * node){
	// cout<<"Insert Node called"<<endl;
	++(mH -> size);
	int i = mH -> size;
	mH -> arr[i - 1] = node;
	while(i){
		i = (i - 1)/2;
		// cout<<"Parent Index: "<<i<<endl;
		heapify(mH, i);		
	}
	heapify(mH, 0);
	// cout<<"Insert Node success"<<endl;
}

/* bool isLeaf(Node* node){
	cout<<"Checking for leaf node"<<endl;
	return !(node -> left || node -> right);
} */

minHeap *createAndBuildMinHeap(char *s, int *f, int n){
	minHeap * mH = new minHeap(n);
	// cout<<"Creating tree"<<endl;
	for(int i = 0; i < (int)n; i++)
	// {
		mH -> arr[i] = new Node(s[i], f[i]);
		// cout<<s[i]<<" "<<f[i]<<" pushed"<<endl;
	// }
	mH -> size = n;
	heapify(mH, 0);
	return mH;
}

Node *createHuffmanTree(char *s, int *f, int n){
	// cout<<"Creating Huffman Tree"<<endl;
	// cout<<n<<endl;
	minHeap * mH = createAndBuildMinHeap(s, f, n);
	while(mH -> size > 1){
		Node * left = extractMin(mH);
		Node * right = extractMin(mH);
		Node * newNode = new Node('$', left -> freq + right -> freq);
		newNode -> left = left;
		newNode -> right = right;
		insertNode(mH, newNode);
	}
	// cout<<"Huffman Tree Success"<<endl;
	return extractMin(mH);
}

void traverse(Node* node){
	if(node){
		cout<<(node -> symbol)<<" "<<(node -> freq)<<endl;
		traverse(node -> left);
		traverse(node -> right);
	}
}

void printHuffmanCodes(Node * node, string str){
	if(!node)
		return;
	if(node -> symbol != '$')
		cout<<" "<<(node -> symbol)<<"\t "<<str<<endl;
	printHuffmanCodes(node -> left, str + '0');
	printHuffmanCodes(node -> right, str + '1');
}

int main(){
	unsigned int capacity;
	cout<<"Enter the number of distinct characters: ";
	cin>>capacity;
	char s[capacity];
	int f[capacity];
	cout<<"Enter the character and its frequency (row wise)"<<endl;
	for(int i = 0; i < capacity; i++)
		cin>>s[i]>>f[i];
	/*char s[] = {'A', 'B', 'C', 'D'};
	int f[] = {5, 1, 6, 3};*/
	Node * huffmanTree = createHuffmanTree(s, f, capacity);
	// traverse(huffmanTree);
	cout<<"Symbol\t"<<"Code"<<endl;
	printHuffmanCodes(huffmanTree, "");
	return 0;
}

/* TERMINAL
cse2102040024@vssutcse-ProLiant-ML350-Gen9:~/DAA$ g++ E5P1.cpp 
cse2102040024@vssutcse-ProLiant-ML350-Gen9:~/DAA$ ./a.out 
Enter the number of distinct characters: 4
Enter the character and its frequency (row wise)
A 5
B 1
C 6
D 3
4
Symbol	Code
 C	 0
 B	 100
 D	 101
 A	 11
*/
