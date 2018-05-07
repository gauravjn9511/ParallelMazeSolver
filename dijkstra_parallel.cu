#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/scatter.h>
#include <thrust/sequence.h>
#include <thrust/execution_policy.h>
#include <thrust/extrema.h>
#include "grid.h"

extern "C"
{

int minDistance(float* dist, int* visited, int size)
{
	float min = __FLT_MAX__;

	thrust::device_vector<float> d_dist(size, min);
	
	thrust::device_vector<int> d_map(size);
	thrust::sequence(d_map.begin(), d_map.end());

	thrust::scatter_if(thrust::device, dist, dist + size, d_map.begin(), visited, d_dist.begin());

	thrust::device_vector<float>::iterator iter = thrust::min_element(d_dist.begin(), d_dist.end());
	
	int min_index = iter - d_dist.begin();
	return min_index;
}


void Grid::dijkstraShortestPath(Vertex src) {
	thrust::device_vector<float> dist(num_rows * num_columns, __FLT_MAX__);	// stores distance of each node from source
	thrust::device_vector<int> visited(num_rows * num_columns, 1);
	float* dist_p = thrust::raw_pointer_cast(&dist[0]);
	int* visited_p = thrust::raw_pointer_cast(&visited[0]);	
	

	thrust::host_vector<int> backtrack(num_rows * num_columns, -1);	// used to backtrack path from source to each node
	
	dist[src.x * num_columns + src.y] = 0;


	for (int i = 0; i < num_columns*num_rows - 1; i++)
	{
		
		int v = minDistance(dist_p, visited_p, num_rows*num_columns);
		
		visited[v] = 0;
		for (int k = adj[v]; k < adj[v+1]; k++)
		{
			if(!edges[k]->selected)
					continue;
			
			Vertex u = edges[k]->head;
			int u_index = u.x * num_columns + u.y;

			if (! (visited[u_index]==0) && dist[v] + edges[k]->weight < dist[u_index]) {
					backtrack[u_index] = v;
					dist[u_index] = edges[k]->weight + dist[v];
			}
		}
	}
	

	/*	Mark nodes along the shortest path using backtracking	*/
	int u = num_columns * num_rows - 1;
	while (u != -1) {
		selected[u] = true;
		u = backtrack[u];
	}
}

}