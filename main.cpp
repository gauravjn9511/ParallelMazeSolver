#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <sys/time.h>

#include "grid.h"

using namespace std;

class Timer
{
	struct timeval timecheck;
	long t_start, t_end;
public:
	void start() {
	    gettimeofday(&timecheck, NULL);
	    t_start = (long)timecheck.tv_sec * 1000000 + (long)timecheck.tv_usec;
	}

	void stop() {
		gettimeofday(&timecheck, NULL);
    	t_end = (long)timecheck.tv_sec * 1000000 + (long)timecheck.tv_usec;
	}

	double getTime() {
		return (double)(t_end - t_start)/1000;
	} 
}timer;

int main(int argc, char const *argv[])
{
	if(argc <= 3) {
		cout<<"usage: "<<argv[0]<<" <num_rows> <num_columns> <pixel_size>"<<endl;
		exit(0);
	}
	int num_rows = atoi(argv[1]);
	int num_columns = atoi(argv[2]);
	int pixel_size = atoi(argv[3]);

	Grid grid(num_rows, num_columns);
	cout<<"Grid created"<<endl;
	cout<<"Running Prim's algorithm to generate maze"<<endl;

	timer.start();
	grid.prim_mst();
	timer.stop();
	cout<<"Time taken = "<<timer.getTime()<<" ms"<<endl;
	
	grid.add_edges();

	cout<<"Running Dijkstra's algorithm to solve maze"<<endl;
	timer.start();
	Vertex src(0,0);
	grid.dijkstraShortestPath(src);
	timer.stop();
	cout<<"Time taken = "<<timer.getTime()<<" ms"<<endl;
	
	if(pixel_size > 0) {
		grid.render(pixel_size);
		cout<<"Grid rendered"<<endl;
	}
	return 0;
}