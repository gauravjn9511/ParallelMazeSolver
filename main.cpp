#include <iostream>

#include "grid.h"

using namespace std;

int main(int argc, char const *argv[])
{
	Grid grid(100, 100);
	cout<<"Grid created"<<endl;
	grid.kruskalMST();
	grid.render(5);
	cout<<"Grid rendered"<<endl;
	return 0;
}