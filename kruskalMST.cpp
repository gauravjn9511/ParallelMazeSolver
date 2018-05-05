// C++ program for Kruskal's algorithm to find Minimum
// Spanning Tree of a given connected, undirected and
// weighted graph
#include <iostream>
#include <vector>
#include <algorithm>
#include "grid.h"
using namespace std;
 
// // Creating shortcut for an integer pair
// typedef  pair<int, int> iPair;
 
// // Structure to represent a graph
// struct Graph
// {
//     int V, E;
//     vector< pair<int, iPair> > edges;
 
//     // Constructor
//     Graph(int V, int E)
//     {
//         this->V = V;
//         this->E = E;
//     }
 
//     // Utility function to add an edge
//     void addEdge(int u, int v, int w)
//     {
//         edges.push_back({w, {u, v}});
//     }
 
//     // Function to find MST using Kruskal's
//     // MST algorithm
//     int kruskalMST();
// };
 
// // To represent Disjoint Sets
// class DisjointSets
// {
//     vector<int> parent, rnk;
//     int n;
//  public:
//     // Constructor.
//     DisjointSets(int n)
//     {
//         // Allocate memory
//         this->n = n;
//         parent.assign(n+1, 0);
//         rnk.assign(n+1, 0);
 
//         // Initially, all vertices are in
//         // different sets and have rank 0.
//         for (int i = 0; i <= n; i++)
//         {
//             //every element is parent of itself
//             parent[i] = i;
//         }
//     }
 
//     // Find the parent of a node 'u'
//     // Path Compression
//     int find(int u)
//     {
//          Make the parent of the nodes in the path
//            from u--> parent[u] point to parent[u] 
//         cout<<"find:"<<u<<endl;
//         if (u != parent[u])
//             parent[u] = find(parent[u]);
//         return u;
//     }
 
//     // Union by rank
//     void merge(int x, int y)
//     {
//         x = find(x), y = find(y);
//         /* Make tree with smaller height
//            a subtree of the other tree  */
//         if (rnk[x] > rnk[y])
//             parent[y] = x;
//         else // If rnk[x] <= rnk[y]
//             parent[x] = y;
 
//         if (rnk[x] == rnk[y])
//             rnk[y]++;

//     }
// };

class UnionFind    {
    int *id, cnt, *sz;
public:
    // Create an empty union find data structure with N isolated sets.
    UnionFind(int N)   {
        cnt = N;
    id = new int[N];
    sz = new int[N];
        for(int i=0; i<N; i++)  {
            id[i] = i;
        sz[i] = 1;
    }
    }
    ~UnionFind()   {
    delete [] id;
    delete [] sz;
    }
    // Return the id of component corresponding to object p.
    int find(int p) {
        int root = p;
        while (root != id[root])
            root = id[root];
        while (p != root) {
            int newp = id[p];
            id[p] = root;
            p = newp;
        }
        return root;
    }
    // Replace sets containing x and y with their union.
    void merge(int x, int y)    {
        int i = find(x);
        int j = find(y);
        if (i == j) return;
        
        // make smaller root point to larger one
        if   (sz[i] < sz[j])    { 
        id[i] = j; 
        sz[j] += sz[i]; 
    } else  { 
        id[j] = i; 
        sz[i] += sz[j]; 
    }
        cnt--;
    }
    // Are objects x and y in the same set?
    bool connected(int x, int y)    {
        return find(x) == find(y);
    }
    // Return the number of disjoint sets.
    int count() {
        return cnt;
    }
};

bool edge_comparator(Edge *u, Edge *v)
{
    return u->weight < v->weight;
}

void Grid::select_reverse_edge(int u_x, int u_y, int v_x, int v_y)
{
    int v = v_x * num_columns + v_y;
    for (int k = adj[v]; k < adj[v+1]; ++k) {
        if(edges[k]->head.x == u_x && edges[k]->head.y == u_y) {
            edges[k]->selected = true;
        }
    }
}
 
 /* Functions returns weight of the MST*/
 
void Grid::kruskalMST()
{    
    std::vector<Edge *> edges(this->edges);
    // Sort edges in increasing order on basis of cost
    sort(edges.begin(), edges.end(), edge_comparator);
 
    // Create disjoint sets
    UnionFind ds(num_rows * num_columns);
 
    // Iterate through all sorted edges
    vector<Edge *>::iterator it;
    for (it=edges.begin(); it!=edges.end(); it++)
    {
        Vertex v = (*it)->head;
        Vertex u = (*it)->tail;
 
        // cout << "("<< u.x <<","<<u.y<<")" << " - " << "("<< v.x <<","<<v.y<<")" << endl;
        int set_u = ds.find(u.x * num_columns + u.y);
        int set_v = ds.find(v.x * num_columns + v.y);
 
        // Check if the selected edge is creating
        // a cycle or not (Cycle is created if u
        // and v belong to same set)
        if (set_u != set_v)
        {
            // Current edge will be in the MST
            // so print it
            (*it)->selected = true;
            select_reverse_edge(u.x, u.y, v.x, v.y);
            cout << "("<< u.x <<","<<u.y<<")" << " -- " << "("<< v.x <<","<<v.y<<")" << endl;

            // Merge two sets
            ds.merge(set_u, set_v);
        }
    }
}