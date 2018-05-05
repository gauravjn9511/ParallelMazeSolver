#include <iostream>
#include <vector>
#include <algorithm>
#include "grid.h"
using namespace std;

class UnionFind {
    std::vector<int> arr;
    std::vector<int> size;
public:
    UnionFind(int N) {
        arr.assign(N, 0);
        size.assign(N, 1);
        for(int i=1; i<N; i++)  {
            arr[i] = i; // Initially all sets contain only one element
        }
    }

    int findRoot(int p) {
        int root = p;
        while (root != arr[root])
            root = arr[root];
        return root;
    }

    // Return the set of component corresponding to object p.
    int find(int p) {
        int root = findRoot(p);
        while (p != root) {
            int newp = arr[p];
            arr[p] = root;
            p = newp;
        }
        return root;
    }
    // Replace sets containing x and y with their union.
    void merge(int x, int y) {
        int i = find(x);
        int j = find(y);
        if (i == j) return;
        
        // make smaller root point to larger one
        if(size[i] < size[j]) { 
            arr[i] = j; 
            size[j] += size[i]; 
        }
        else { 
            arr[j] = i; 
            size[i] += size[j]; 
        }
    }
};

bool edge_comparator(Edge *u, Edge *v)
{
    return u->weight < v->weight;
}

/*  Selects the edge corresponding to v-->u  */
void Grid::select_reverse_edge(Vertex u, Vertex v)
{
    int v_index = v.x * num_columns + v.y;
    for (int k = adj[v_index]; k < adj[v_index+1]; ++k) {
        if(edges[k]->head.x == u.x && edges[k]->head.y == u.y) {
            edges[k]->selected = true;
            break;
        }
    }
}

/*  Selects edges corresponding to MST using Kruskal's algorithm */
void Grid::kruskalMST()
{    
    std::vector<Edge *> edges(this->edges);
    // Sort edges in order of weight
    sort(edges.begin(), edges.end(), edge_comparator);
 
    UnionFind uf(num_rows * num_columns);
    for (vector<Edge*>::iterator it=edges.begin(); it!=edges.end(); it++)
    {
        Vertex v = (*it)->head;
        Vertex u = (*it)->tail;
 
        int u_set = uf.find(u.x * num_columns + u.y);
        int v_set = uf.find(v.x * num_columns + v.y);

        if (u_set != v_set)
        {
            // Select the edge if u and v belong to different sets
            (*it)->selected = true;
            select_reverse_edge(u, v);

            cout << "("<< u.x <<","<<u.y<<")" << " -- " << "("<< v.x <<","<<v.y<<")" << endl;
            uf.merge(u_set, v_set);
        }
    }
}