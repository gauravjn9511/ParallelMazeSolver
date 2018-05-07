#include <iostream>
#include <vector>
#include <algorithm>
#include "grid.h"
using namespace std;

int get_closest_node(std::vector<float> &dist, std::vector<bool> &included)
{
	float min = __FLT_MAX__;
	int min_index = -1;

	for (int v = 0; v < dist.size(); v++) {
		if (included[v] == false && dist[v] <= min) {
			min = dist[v];
			min_index = v;
		}
	}

	return min_index;
}

void Grid::prim_mst()
{
	int num_vertices = num_rows * num_columns;
	std::vector<float> dist(num_vertices, __FLT_MAX__);	// stores distance of each node from set
	std::vector<bool> included(num_vertices, false);
	std::vector<int> backtrack(num_vertices, -1);	// used to backtrack path from source to each node
	dist[0] = 0;

	for (int i = 0; i < num_vertices-1; i++)
	{
		int v = get_closest_node(dist, included);
		included[v] = true;

		for (int k = adj[v]; k < adj[v+1]; k++) {

			Vertex u = edges[k]->head;
			int u_index = u.x * num_columns + u.y;
			if (! included[u_index] && edges[k]->weight < dist[u_index]) {
				// backtrack[u_index] = v;
				dist[u_index] = edges[k]->weight;
				backtrack[u_index] = v;
            	// cout << "("<< u.x <<","<<u.y<<")" << " -- " << "("<< u.x <<","<<u.y<<")" << endl;
			}
		}
	}
	
	for(int u = 0; u < backtrack.size(); u++)
	{
		int v = backtrack[u];	// we must add an edge from u to v in the MST
		Vertex u1(u/num_columns, u%num_columns);
		Vertex v1(v/num_columns, v%num_columns);
		select_reverse_edge(u1, v1);
		select_reverse_edge(v1, u1);
	}
}