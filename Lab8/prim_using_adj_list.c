// C / C++ program for Prim's MST for adjacency list
// representation of graph

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

// A structure to represent a node in adjacency list
typedef struct AdjListNode {
	int dest;
	int weight;
	struct AdjListNode* next;
}AdjListNode;

// A structure to represent an adjacency list
typedef struct AdjList {
	struct AdjListNode*
		head; // pointer to head node of list
}AdjList;

// A structure to represent a graph. A graph is an array of
// adjacency lists. Size of array will be V (number of
// vertices in graph)
typedef struct Graph {
	int V;
	struct AdjList* array;
}Graph;

// A utility function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest, int weight)
{
	struct AdjListNode* newNode
		= (struct AdjListNode*)malloc(
			sizeof(struct AdjListNode));
	newNode->dest = dest;
	newNode->weight = weight;
	newNode->next = NULL;
	return newNode;
}

// A utility function that creates a graph of V vertices
struct Graph* createGraph(int V)
{
	struct Graph* graph
		= (struct Graph*)malloc(sizeof(struct Graph));
	graph->V = V;

	// Create an array of adjacency lists. Size of array
	// will be V
	graph->array = (struct AdjList*)malloc(
		V * sizeof(struct AdjList));

	// Initialize each adjacency list as empty by making
	// head as NULL
	for (int i = 0; i < V; ++i)
		graph->array[i].head = NULL;

	return graph;
}

// Adds an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest,
			int weight)
{
	// Add an edge from src to dest. A new node is added to
	// the adjacency list of src. The node is added at the
	// beginning
	struct AdjListNode* newNode
		= newAdjListNode(dest, weight);
	newNode->next = graph->array[src].head;
	graph->array[src].head = newNode;

	// Since graph is undirected, add an edge from dest to
	// src also
	newNode = newAdjListNode(src, weight);
	newNode->next = graph->array[dest].head;
	graph->array[dest].head = newNode;
}

// Structure to represent a min heap node
typedef struct MinHeapNode {
	int v;
	int key;
}MinHeapNode;

// Structure to represent a min heap
typedef struct MinHeap {
	int size; // Number of heap nodes present currently
	int capacity; // Capacity of min heap
	int* pos; // This is needed for decreaseKey()
	struct MinHeapNode** array;
}MinHeap;

// A utility function to create a new Min Heap Node
struct MinHeapNode* newMinHeapNode(int v, int key)
{
	struct MinHeapNode* minHeapNode
		= (struct MinHeapNode*)malloc(
			sizeof(struct MinHeapNode));
	minHeapNode->v = v;
	minHeapNode->key = key;
	return minHeapNode;
}

// A utility function to create a Min Heap
struct MinHeap* createMinHeap(int capacity)
{
	struct MinHeap* minHeap
		= (struct MinHeap*)malloc(sizeof(struct MinHeap));
	minHeap->pos = (int*)malloc(capacity * sizeof(int));
	minHeap->size = 0;
	minHeap->capacity = capacity;
	minHeap->array = (struct MinHeapNode**)malloc(
		capacity * sizeof(struct MinHeapNode*));
	return minHeap;
}

// A utility function to swap two nodes of min heap. Needed
// for min heapify
void swapMinHeapNode(struct MinHeapNode** a,
					struct MinHeapNode** b)
{
	struct MinHeapNode* t = *a;
	*a = *b;
	*b = t;
}

// A standard function to heapify at given idx
// This function also updates position of nodes when they
// are swapped. Position is needed for decreaseKey()
void minHeapify(struct MinHeap* minHeap, int idx)
{
	int smallest, left, right;
	smallest = idx;
	left = 2 * idx + 1;
	right = 2 * idx + 2;

	if (left < minHeap->size
		&& minHeap->array[left]->key
			< minHeap->array[smallest]->key)
		smallest = left;

	if (right < minHeap->size
		&& minHeap->array[right]->key
			< minHeap->array[smallest]->key)
		smallest = right;

	if (smallest != idx) {
		// The nodes to be swapped in min heap
		MinHeapNode* smallestNode
			= minHeap->array[smallest];
		MinHeapNode* idxNode = minHeap->array[idx];

		// Swap positions
		minHeap->pos[smallestNode->v] = idx;
		minHeap->pos[idxNode->v] = smallest;

		// Swap nodes
		swapMinHeapNode(&minHeap->array[smallest],
						&minHeap->array[idx]);

		minHeapify(minHeap, smallest);
	}
}

// A utility function to check if the given minHeap is empty
// or not
int isEmpty(struct MinHeap* minHeap)
{
	return minHeap->size == 0;
}

// Standard function to extract minimum node from heap
struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{
	if (isEmpty(minHeap))
		return NULL;

	// Store the root node
	struct MinHeapNode* root = minHeap->array[0];

	// Replace root node with last node
	struct MinHeapNode* lastNode
		= minHeap->array[minHeap->size - 1];
	minHeap->array[0] = lastNode;

	// Update position of last node
	minHeap->pos[root->v] = minHeap->size - 1;
	minHeap->pos[lastNode->v] = 0;

	// Reduce heap size and heapify root
	--minHeap->size;
	minHeapify(minHeap, 0);

	return root;
}

// Function to decrease key value of a given vertex v. This
// function uses pos[] of min heap to get the current index
// of node in min heap
void decreaseKey(struct MinHeap* minHeap, int v, int key)
{
	// Get the index of v in heap array
	int i = minHeap->pos[v];

	// Get the node and update its key value
	minHeap->array[i]->key = key;

	// Travel up while the complete tree is not heapified.
	// This is a O(Logn) loop
	while (i
		&& minHeap->array[i]->key
				< minHeap->array[(i - 1) / 2]->key) {
		// Swap this node with its parent
		minHeap->pos[minHeap->array[i]->v] = (i - 1) / 2;
		minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i;
		swapMinHeapNode(&minHeap->array[i],
						&minHeap->array[(i - 1) / 2]);

		// move to parent index
		i = (i - 1) / 2;
	}
}

// A utility function to check if a given vertex
// 'v' is in min heap or not
int isInMinHeap(struct MinHeap* minHeap, int v)
{
	if (minHeap->pos[v] < minHeap->size)
		return 1;
	return 0;
}

// A utility function used to print the constructed MST
void printMST(int arr[], int weight[], int n)
{
	printf("u - v - weight\n--------------\n");
	for (int i = 1; i < n; ++i)
		printf("%d - %d - %d\n", arr[i], i, weight[i]);
}

// The main function that constructs Minimum Spanning Tree
// (MST) using Prim's algorithm
void PrimMST(struct Graph* graph)
{
	int V = graph->V; // Get the number of vertices in graph
	int parent[V]; // Array to store constructed MST
	int key[V]; // Key values used to pick minimum weight
				// edge in cut

	int min_wt = 0;

	// minHeap represents set E
	struct MinHeap* minHeap = createMinHeap(V);

	// Initialize min heap with all vertices. Key value of
	// all vertices (except 0th vertex) is initially
	// infinite
	for (int v = 1; v < V; ++v) {
		parent[v] = -1;
		key[v] = INT_MAX;
		minHeap->array[v] = newMinHeapNode(v, key[v]);
		minHeap->pos[v] = v;
	}

	// Make key value of 0th vertex as 0 so that it
	// is extracted first
	key[0] = 0;
	minHeap->array[0] = newMinHeapNode(0, key[0]);
	minHeap->pos[0] = 0;

	// Initially size of min heap is equal to V
	minHeap->size = V;

	// In the following loop, min heap contains all nodes
	// not yet added to MST.
	while (!isEmpty(minHeap)) {
		// Extract the vertex with minimum key value
		struct MinHeapNode* minHeapNode
			= extractMin(minHeap);
		int u
			= minHeapNode
				->v; // Store the extracted vertex number

		// Traverse through all adjacent vertices of u (the
		// extracted vertex) and update their key values
		struct AdjListNode* pCrawl = graph->array[u].head;
		while (pCrawl != NULL) {
			int v = pCrawl->dest;

			// If v is not yet included in MST and weight of
			// u-v is less than key value of v, then update
			// key value and parent of v
			if (isInMinHeap(minHeap, v)
				&& pCrawl->weight < key[v]) {
				key[v] = pCrawl->weight;
				min_wt += key[v];
				parent[v] = u;
				decreaseKey(minHeap, v, key[v]);
			}
			pCrawl = pCrawl->next;
		}
	}

	printf("\nThe MST will have weight: %d\nIt will contain the following edges:\n", min_wt);
	// print edges of MST
	printMST(parent, key, V);
}

// Driver program to test above functions
int main()
{
	// Let us create the graph given in above figure
	int V, E;
	printf("Enter the number of vertices: ");
	scanf("%d", &V);
	struct Graph* graph = createGraph(V);
	printf("Enter the number of edges: ");
	scanf("%d", &E);
	printf("Enter the edges in the following format:\n Source Vertex <space> Destination Vertex <space> Weight\n");
	for(int i = 0; i < E; i++){
		int u, v, w;
		printf("For Edge %d: ", i+1);
		scanf("%d%d%d", &u, &v, &w);
		addEdge(graph, u, v, w);
	}
	PrimMST(graph);

	return 0;
}


/* TERMINAL
PS D:\Junior\Study\Design-and-Analysis-of-Algorithm\Lab8> gcc -o prim_using_adj_list.exe .\prim_using_adj_list.c
PS D:\Junior\Study\Design-and-Analysis-of-Algorithm\Lab8> .\prim_using_adj_list.exe
Enter the number of vertices: 5
Enter the number of edges: 7
Enter the edges in the following format:
 Source Vertex <space> Destination Vertex <space> Weight
For Edge 1: 0 1 2
For Edge 2: 0 3 6
For Edge 3: 1 2 3 
For Edge 4: 1 3 8
For Edge 5: 1 4 5
For Edge 6: 2 4 7
For Edge 7: 3 4 9

The MST will have weight: 16
It will contain the following edges:
u - v - weight
--------------
0 - 1 - 2
1 - 2 - 3
0 - 3 - 6
1 - 4 - 5
*/