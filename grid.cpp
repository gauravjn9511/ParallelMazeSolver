#include <random>
#include <iostream>
#include "grid.h"
#include "pgm.h"

using namespace std;

Grid::Grid(int nr, int nc)
{
	num_rows = nr;
	num_columns = nc;
	int count = 0;

	std::default_random_engine generator(42L);
	std::uniform_real_distribution<float> distribution(0.0,1.0);

	for (int i = 0; i < num_rows; ++i)
	{
		for (int j = 0; j < num_columns; ++j)
		{
			adj.push_back(count);


			if(i >= 1) {
				edges.push_back(new Edge(i-1, j, i, j, (float)distribution(generator)));
				count++;
			}
			if(j >= 1) {
				edges.push_back(new Edge(i, j-1, i, j, (float)distribution(generator)));
				count++;
			}
			if(j < num_columns - 1) {
				edges.push_back(new Edge(i, j+1, i, j, (float)distribution(generator)));
				count++;
			}
			if(i < num_rows - 1) {
				edges.push_back(new Edge(i+1, j, i, j, (float)distribution(generator)));
				count++;
			}
		}
	}
	adj.push_back(count);
	selected.assign(num_rows*num_columns, false);
}

Grid::~Grid()
{
	for (std::vector<Edge *>::iterator i = edges.begin(); i != edges.end(); ++i)
	{
		delete *i;
	}
}

void Grid::render(int pixel_size)
{
	image_t *img;

	img = pgm_create(2*num_rows+1, 2*num_columns+1, pixel_size, BLACK);
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_columns; ++j) {
			int v = i*num_columns + j;
			pgm_set_pixel(img, 2*i+1, 2*j+1, selected[v]? GREY:WHITE);
			
			for (int k = adj[v]; k < adj[v+1]; ++k) {
				Vertex u = edges[k]->head;
				Vertex v = edges[k]->tail;
				int u_index = u.x * num_columns + u.y;
				int v_index = v.x * num_columns + v.y;

				int color = (selected[u_index] && selected[v_index])? GREY :
					(edges[k]->selected ? WHITE : BLACK);
				// cout << "("<< i <<","<<j<<")" << " - " << "("<< u.x <<","<<u.y<<")" << edges[k]->selected << endl;
				pgm_set_pixel(img, (2*(i+u.x)+2)/2, (2*(j+u.y)+2)/2, color);
			}
		}
	}
	pgm_save(img, "img.pgm");
	pgm_destroy(img);
}