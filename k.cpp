#include <bits/stdc++.h>
using namespace std;

class DSU{
    int * parent, *rank;
    public:
        DSU(int n){
            parent = new int[n];
            rank = new int[n];
            for(int i = 0; i < n; i++){
                parent[i] = -1;
                rank[i] = 1;
            }
        }  
        int find(int i){
            if(parent[i] == -1)
                return i;
            return parent[i] = find(parent[i]);
        }
        void unite(int x, int y){
            int s1 = find(x);
            int s2 = find(y);
            if(s1 != s2){
                if(rank[s1] < rank[s2])
                    parent[s1] = s2;
                else if(rank[s1] > rank[s2])
                    parent[s2] = s1;
                else{
                    parent[s2] = s1;
                    rank[s1]++;
                }
            }
        }
};

class Graph{
    int V;
    vector<vector<int>> edgeList;
    public:
        Graph(int V){
            this -> V = V;
        }
        void addEdge(int u, int v, int w){
            edgeList.push_back({w, u, v});
        }
        void kruskalMST(){
            sort(edgeList.begin(), edgeList.end());
            DSU s(V);
            int tc = 0;
            for(auto edge : edgeList){
                int w = edge[0];
                int x = edge[1];
                int y = edge[2];
                if(s.find(x) != s.find(y)){
                    s.unite(x, y);
                    tc += w;
                    cout<<x<<" - "<<y<<", weight: "<<w<<endl;
                }
            }
            cout<<"Total Cost: "<<tc;
        }
};

int main()
{
	Graph g(4);
	g.addEdge(0, 1, 10);
	g.addEdge(1, 3, 15);
	g.addEdge(2, 3, 4);
	g.addEdge(2, 0, 6);
	g.addEdge(0, 3, 5);
	g.kruskalMST();
	return 0;
}