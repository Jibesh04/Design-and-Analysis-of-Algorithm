// C / C++ program for Dijkstra's
// shortest path algorithm for adjacency
// list representation of graph
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// A structure to represent a
// node in adjacency list
typedef struct AdjListNode
{
	int dest;
	int weight;
	struct AdjListNode* next;
}AdjListNode;

// A structure to represent
// an adjacency list
typedef struct AdjList
{
	
// Pointer to head node of list
AdjListNode *head;
}AdjList;

// A structure to represent a graph.
// A graph is an array of adjacency lists.
// Size of array will be V (number of
// vertices in graph)
typedef struct Graph
{
	int V;
	AdjList* array;
}Graph;

// A utility function to create
// a new adjacency list node
AdjListNode* newAdjListNode(
				int dest, int weight)
{
	AdjListNode* newNode =
			(AdjListNode*)
	malloc(sizeof(AdjListNode));
	newNode->dest = dest;
	newNode->weight = weight;
	newNode->next = NULL;
	return newNode;
}

// A utility function that creates
// a graph of V vertices
Graph* createGraph(int V)
{
	Graph* graph = (Graph*)
			malloc(sizeof(Graph));
	graph->V = V;

	// Create an array of adjacency lists.
	// Size of array will be V
	graph->array = (AdjList*)
	malloc(V * sizeof(AdjList));

	// Initialize each adjacency list
	// as empty by making head as NULL
	for (int i = 0; i < V; ++i)
		graph->array[i].head = NULL;

	return graph;
}

// Adds an edge to an undirected graph
void addEdge(Graph* graph, int src,
				int dest, int weight)
{
	// Add an edge from src to dest.
	// A new node is added to the adjacency
	// list of src. The node is
	// added at the beginning
	AdjListNode* newNode =
			newAdjListNode(dest, weight);
	newNode->next = graph->array[src].head;
	graph->array[src].head = newNode;

	// Since graph is undirected,
	// add an edge from dest to src also
	newNode = newAdjListNode(src, weight);
	newNode->next = graph->array[dest].head;
	graph->array[dest].head = newNode;
}

// Structure to represent a min heap node
typedef struct MinHeapNode
{
	int v;
	int dist;
}MinHeapNode;

// Structure to represent a min heap
struct MinHeap
{
	
	// Number of heap nodes present currently
	int size;	

	// Capacity of min heap
	int capacity;

	// This is needed for decreaseKey()
	int *pos;
	MinHeapNode **array;
};

// A utility function to create a
// new Min Heap Node
MinHeapNode* newMinHeapNode(int v,
								int dist)
{
	MinHeapNode* minHeapNode =
		(MinHeapNode*)
	malloc(sizeof(MinHeapNode));
	minHeapNode->v = v;
	minHeapNode->dist = dist;
	return minHeapNode;
}

// A utility function to create a Min Heap
struct MinHeap* createMinHeap(int capacity)
{
	struct MinHeap* minHeap =
		(struct MinHeap*)
	malloc(sizeof(struct MinHeap));
	minHeap->pos = (int *)malloc(
			capacity * sizeof(int));
	minHeap->size = 0;
	minHeap->capacity = capacity;
	minHeap->array =
		(MinHeapNode**)
				malloc(capacity *
	sizeof(MinHeapNode*));
	return minHeap;
}

// A utility function to swap two
// nodes of min heap.
// Needed for min heapify
void swapMinHeapNode(MinHeapNode** a,
					MinHeapNode** b)
{
	MinHeapNode* t = *a;
	*a = *b;
	*b = t;
}

// A standard function to
// heapify at given idx
// This function also updates
// position of nodes when they are swapped.
// Position is needed for decreaseKey()
void minHeapify(struct MinHeap* minHeap,
								int idx)
{
	int smallest, left, right;
	smallest = idx;
	left = 2 * idx + 1;
	right = 2 * idx + 2;

	if (left < minHeap->size &&
		minHeap->array[left]->dist <
		minHeap->array[smallest]->dist )
	smallest = left;

	if (right < minHeap->size &&
		minHeap->array[right]->dist <
		minHeap->array[smallest]->dist )
	smallest = right;

	if (smallest != idx)
	{
		// The nodes to be swapped in min heap
		MinHeapNode *smallestNode =
			minHeap->array[smallest];
		MinHeapNode *idxNode =
				minHeap->array[idx];

		// Swap positions
		minHeap->pos[smallestNode->v] = idx;
		minHeap->pos[idxNode->v] = smallest;

		// Swap nodes
		swapMinHeapNode(&minHeap->array[smallest],
						&minHeap->array[idx]);

		minHeapify(minHeap, smallest);
	}
}

// A utility function to check if
// the given minHeap is empty or not
int isEmpty(struct MinHeap* minHeap)
{
	return minHeap->size == 0;
}

// Standard function to extract
// minimum node from heap
MinHeapNode* extractMin(struct MinHeap*
								minHeap)
{
	if (isEmpty(minHeap))
		return NULL;

	// Store the root node
	MinHeapNode* root =
				minHeap->array[0];

	// Replace root node with last node
	MinHeapNode* lastNode =
		minHeap->array[minHeap->size - 1];
	minHeap->array[0] = lastNode;

	// Update position of last node
	minHeap->pos[root->v] = minHeap->size-1;
	minHeap->pos[lastNode->v] = 0;

	// Reduce heap size and heapify root
	--minHeap->size;
	minHeapify(minHeap, 0);

	return root;
}

// Function to decreasekey dist value
// of a given vertex v. This function
// uses pos[] of min heap to get the
// current index of node in min heap
void decreaseKey(struct MinHeap* minHeap,
						int v, int dist)
{
	// Get the index of v in heap array
	int i = minHeap->pos[v];

	// Get the node and update its dist value
	minHeap->array[i]->dist = dist;

	// Travel up while the complete
	// tree is not heapified.
	// This is a O(Logn) loop
	while (i && minHeap->array[i]->dist <
		minHeap->array[(i - 1) / 2]->dist)
	{
		// Swap this node with its parent
		minHeap->pos[minHeap->array[i]->v] =
									(i-1)/2;
		minHeap->pos[minHeap->array[
							(i-1)/2]->v] = i;
		swapMinHeapNode(&minHeap->array[i],
				&minHeap->array[(i - 1) / 2]);

		// move to parent index
		i = (i - 1) / 2;
	}
}

// A utility function to check if a given vertex
// 'v' is in min heap or not
int isInMinHeap(struct MinHeap *minHeap, int v)
{
if (minHeap->pos[v] < minHeap->size)
	return 1;
return 0;
}

void print_parents(int parent[], int u, int src){
    if(u == src){
        printf("%d", u);
        return;
    }
        print_parents(parent, parent[u], src);
    printf(" -> %d", u);
}

// A utility function used to print the solution
void printArr(int dist[], int n, int parent[], int src)
{
	printf("Vertex Distance from Source\n");
	for (int i = 0; i < n; ++i){
		printf("%d \t %d \t", i, dist[i]);
        print_parents(parent, i, src);
        printf("\n");
    }
}

// The main function that calculates
// distances of shortest paths from src to all
// vertices. It is a O(ELogV) function
void dijkstra(Graph* graph, int src)
{
	
	// Get the number of vertices in graph
	int V = graph->V;

	// dist values used to pick
	// minimum weight edge in cut
	int dist[V];
    int parent[V];

	// minHeap represents set E
	struct MinHeap* minHeap = createMinHeap(V);

	// Initialize min heap with all
	// vertices. dist value of all vertices
	for (int v = 0; v < V; ++v)
	{
		dist[v] = INT_MAX;
		minHeap->array[v] = newMinHeapNode(v,
									dist[v]);
		minHeap->pos[v] = v;
	}

	// Make dist value of src vertex
	// as 0 so that it is extracted first
	minHeap->array[src] =
		newMinHeapNode(src, dist[src]);
	minHeap->pos[src] = src;
	dist[src] = 0;
	decreaseKey(minHeap, src, dist[src]);

	// Initially size of min heap is equal to V
	minHeap->size = V;

	// In the following loop,
	// min heap contains all nodes
	// whose shortest distance
	// is not yet finalized.
	while (!isEmpty(minHeap))
	{
		// Extract the vertex with
		// minimum distance value
		MinHeapNode* minHeapNode =
					extractMin(minHeap);
	
		// Store the extracted vertex number
		int u = minHeapNode->v;

		// Traverse through all adjacent
		// vertices of u (the extracted
		// vertex) and update
		// their distance values
		AdjListNode* pCrawl =
					graph->array[u].head;
		while (pCrawl != NULL)
		{
			int v = pCrawl->dest;

			// If shortest distance to v is
			// not finalized yet, and distance to v
			// through u is less than its
			// previously calculated distance
			if (isInMinHeap(minHeap, v) &&
					dist[u] != INT_MAX &&
			pCrawl->weight + dist[u] < dist[v])
			{
				dist[v] = dist[u] + pCrawl->weight;
                parent[v] = u;
				// update distance
				// value in min heap also
				decreaseKey(minHeap, v, dist[v]);
			}
			pCrawl = pCrawl->next;
		}
	}

	// print the calculated shortest distances
	printArr(dist, V, parent, src);
}


// Driver program to test above functions
int main()
{
	// create the graph given in above figure
	int V, E, src;
	printf("Enter the number of vertices: ");
	scanf("%d", &V);
    printf("Enter the source vertex: ");
    scanf("%d", &src);
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
	dijkstra(graph, src);

	return 0;
}


/* TERMINAL
PS D:\Junior\Study\Design-and-Analysis-of-Algorithm\Lab9> gcc -o dijkstra_adj_list.exe .\dijkstra_adj_list.c
PS D:\Junior\Study\Design-and-Analysis-of-Algorithm\Lab9> .\dijkstra_adj_list.exe
Enter the number of vertices: 9
Enter the source vertex: 0
Enter the number of edges: 14 
Enter the edges in the following format:
 Source Vertex <space> Destination Vertex <space> Weight
For Edge 1: 0 1 4
For Edge 2: 0 7 8
For Edge 3: 1 2 8
For Edge 4: 1 7 11
For Edge 5: 2 3 7
For Edge 6: 2 8 2
For Edge 7: 2 5 4
For Edge 8: 3 4 9
For Edge 9: 3 5 14
For Edge 10: 4 5 10
For Edge 11: 5 6 2
For Edge 12: 6 7 1
For Edge 13: 6 8 6
For Edge 14: 7 8 7
Vertex Distance from Source
0        0      0
1        4      0 -> 1
2        12     0 -> 1 -> 2
3        19     0 -> 1 -> 2 -> 3
4        21     0 -> 7 -> 6 -> 5 -> 4
5        11     0 -> 7 -> 6 -> 5
6        9      0 -> 7 -> 6
7        8      0 -> 7
8        14     0 -> 1 -> 2 -> 8
*/