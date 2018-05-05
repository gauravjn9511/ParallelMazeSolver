#include <vector>

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
	// __host__ __device__
	Edge(int x1, int y1, int x2, int y2, float wt):head(x1,y1), tail(x2,y2), weight(wt), selected(false) {}
};


class Grid
{
public:
	int num_rows, num_columns;
	std::vector<int> adj;
	std::vector<Edge *> edges;
	std::vector<bool> selected;
	Grid(int num_rows, int num_columns);
	~Grid();
	void render(int pixel_size);
	void kruskalMST();
	void select_reverse_edge(Vertex u, Vertex v);
	void dijkstraShortestPath(Vertex src);
};