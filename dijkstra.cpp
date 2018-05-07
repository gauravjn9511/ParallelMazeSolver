#include <vector>
#include "grid.h"

/*	Finds unvisited node with minimum distance from source	*/
int get_min_node(std::vector<float> &dist, std::vector<bool> &visited)
{
	float min = __FLT_MAX__;
	int min_index = -1;

	for (int v = 0; v < dist.size(); v++) {
		if (visited[v] == false && dist[v] <= min) {
			min = dist[v];
			min_index = v;
		}
	}

	return min_index;
}

void Grid::dijkstraShortestPath(Vertex src)
{
	int num_vertices = num_rows * num_columns;
	std::vector<float> dist(num_vertices, __FLT_MAX__);	// stores distance of each node from source
	std::vector<bool> visited(num_vertices, false);
	std::vector<int> backtrack(num_vertices, -1);	// used to backtrack path from source to each node

	dist[src.x * num_columns + src.y] = 0;

	for (int i = 0; i < num_vertices-1; i++)
	{
		int v = get_min_node(dist, visited);

		visited[v] = true;
		for (int k = adj[v]; k < adj[v+1]; k++) {
			if(!edges[k]->selected)
				continue;
			Vertex u = edges[k]->head;
			int u_index = u.x * num_columns + u.y;
			if (! visited[u_index] && dist[v] + edges[k]->weight < dist[u_index]) {
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