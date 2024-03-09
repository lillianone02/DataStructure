#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class UnionFind {
public: 
    vector<int> parent; 
    UnionFind(int n){
        parent.resize(n);
        for(int i=0;i<n;i++)
            parent[i] = i; 
    }
    
    int findParent(int p) {
        return parent[p] == p ? p : parent[p] = findParent(parent[p]); 
    }
    
    void Union(int u , int v) {
        int pu = findParent(u) , pv = findParent(v); 
        parent[pu] = pv;
    }    
};

class Solution {
public:    
    static bool cmp(vector<int>&a , vector<int>&b) {
        return a[2] < b[2]; 
    }
    
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        vector<int> critical ,  pscritical ;
        //1
        for(int i=0;i<edges.size();i++)
            edges[i].push_back(i); 
        
        //2 
        sort(edges.begin() , edges.end() , cmp) ;
        
        int mstwt = findMST(n,edges,-1,-1); //3
        for(int i=0;i<edges.size();i++){
            if(mstwt< findMST(n,edges,i,-1)) //5
                critical.push_back(edges[i][3]); 
            else if(mstwt == findMST(n,edges,-1,i))  //6
                pscritical.push_back(edges[i][3]);
        }
        return {critical , pscritical};         
    }
    
    int findMST(int &n ,  vector<vector<int>>& edges , int block , int e) {
        UnionFind uf(n); 
        int weight = 0 ;
        if(e != -1) {
            weight += edges[e][2]; 
            uf.Union(edges[e][0] , edges[e][1]); 
        }
        
        for(int i=0;i<edges.size();i++){
            if(i == block) 
                continue; 
            if(uf.findParent(edges[i][0]) == uf.findParent(edges[i][1])) //4
                continue; 
            uf.Union(edges[i][0] , edges[i][1]); 
            weight += edges[i][2]; 
        }
        
        //Check if all vertices are included then only it is MST. 
        for(int i=0;i<n;i++){
            if(uf.findParent(i) != uf.findParent(0))
                return INT_MAX;
        }    
        
        return weight; 
    }
    
};

int main() {
    int N, E;
    cin >> N >> E;

    vector<vector<int>> edges(E);
    for (int i = 0; i < E; i++) {
        int A, B, W;
        cin >> A >> B >> W;
        edges[i] = {A, B, W};
    }

    Solution solution;
    vector<vector<int>> result = solution.findCriticalAndPseudoCriticalEdges(N, edges);

    // Output the cost of the minimal-cost connectivity route
    int mstwt = solution.findMST(N, edges, -1, -1);
    cout << mstwt << endl;

    // Output the number of essential links
    cout << result[0].size() << endl;

    // Output the number of secondary links
    cout << result[1].size() << endl;


    return 0;
}
/*using namespace std;

struct Edge {
    int to, cost;
    bool operator<(const Edge& other) const {
        if (to != other.to) return to < other.to;  // Sort by to vertex first
        return cost > other.cost;  // Then sort by cost within each to vertex group
    }
};

int main() {
    int N, E;
    cin >> N >> E;

    vector<vector<Edge>> graph(N);  // Adjacency list representation
    for (int i = 0; i < E; i++) {
        int A, B, W;
        cin >> A >> B >> W;
        graph[A].push_back({B, W});
        graph[B].push_back({A, W});  // Undirected graph
    }

    // Prim's algorithm without priority queue
    vector<bool> visited(N, false);
    vector<int> mstCost(N, 0);
    int totalCost = 0, essentialLinks = 0, secondaryLinks = 0;

    vector<Edge> edgesToExplore;  // Replace priority queue
    edgesToExplore.push_back({0, 0});  // Start from city 0

    while (!edgesToExplore.empty() && count(visited.begin(), visited.end(), true) < N) {
        // Sort edgesToExplore by to vertex and cost
        sort(edgesToExplore.begin(), edgesToExplore.end());

        Edge edge = edgesToExplore.back();
        edgesToExplore.pop_back();

        if (visited[edge.to]) continue;
        visited[edge.to] = true;

        totalCost += edge.cost;
        mstCost[edge.to] = edge.cost;

        for (Edge neighbor : graph[edge.to]) {
            if (!visited[neighbor.to]) {
                edgesToExplore.push_back(neighbor);
            }
        }
    }

    // Count essential and secondary links (corrected)
    for (int i = 1; i < N; i++) {  // Start from 1 to avoid counting edges from vertex 0
        for (Edge edge : graph[i]) {
            // Count all edges connected to vertices 1 and above
            if (edge.to > 0 && mstCost[i] + edge.cost == mstCost[edge.to]) {
                essentialLinks++;
            } else {
                secondaryLinks++;
            }
        }
    }

    // Output results
    cout << totalCost << endl;
    cout << essentialLinks / 2 << endl;  // Divide by 2 to avoid double-counting
    cout << secondaryLinks / 2 << endl;

    return 0;
}
*/