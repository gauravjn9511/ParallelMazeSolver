#include <vector>

#define SEED 42L

class Vertex
{
public:
	int x; 
	int y;
	Vertex(int a, int b): x(a), y(b) {};
};


class Edge
{
public:
	Vertex head;
	Vertex tail;
	float weight;
	bool selected;
	Edge(int x1, int y1, int x2, int y2, float wt):head(x1,y1), tail(x2,y2), weight(wt), selected(false) {}
};


class Grid
{
public:
	int num_rows, num_columns;
	std::vector<int> adj;
	std::vector<Edge *> edges;
	std::vector<bool> selected;	// denotes vertices which have been selected in the shortest djikstra path

	Grid(int num_rows, int num_columns);
	~Grid();
	void render(int pixel_size);
	void prim_mst();
	void select_reverse_edge(Vertex &u, Vertex &v);
	void add_edges();
	void dijkstraShortestPath(Vertex src);
};