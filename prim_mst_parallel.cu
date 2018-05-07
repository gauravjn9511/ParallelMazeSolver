#include <iostream>
#include <vector>
#include <algorithm>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/scatter.h>
#include <thrust/sequence.h>
#include <thrust/execution_policy.h>
#include <thrust/extrema.h>
#include "grid.h"
using namespace std;

extern "C"
{

int get_closest_node(float* dist, int* included, int size)
{
	float min = __FLT_MAX__;

	thrust::device_vector<float> d_dist(size, min);

	thrust::device_vector<int> d_map(size);
	thrust::sequence(d_map.begin(), d_map.end());

	thrust::scatter_if(thrust::device, dist, dist + size, d_map.begin(), included, d_dist.begin());

	thrust::device_vector<float>::iterator iter = thrust::min_element(d_dist.begin(), d_dist.end());
	
	int min_index = iter - d_dist.begin();

	return min_index;
}

void Grid::prim_mst()
{
	int num_vertices = num_rows * num_columns;
	thrust::device_vector<float> dist(num_vertices, __FLT_MAX__);	// stores distance of each node from set
	thrust::device_vector<int> included(num_vertices, 1);

	float* dist_p = thrust::raw_pointer_cast(&dist[0]);
	int* included_p = thrust::raw_pointer_cast(&included[0]);	
	
	std::vector<int> backtrack(num_vertices, -1);	// used to backtrack path from source to each node
	dist[0] = 0;

	for (int i = 0; i < num_vertices-1; i++)
	{
		int v = get_closest_node(dist_p, included_p, num_vertices);
		included[v] = 0;

		for (int k = adj[v]; k < adj[v+1]; k++) {

			Vertex u = edges[k]->head;
			int u_index = u.x * num_columns + u.y;
			if (! (included[u_index]==0) && edges[k]->weight < dist[u_index]) {
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

}