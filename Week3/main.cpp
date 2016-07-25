#include <iostream>
#include "Graph.h"
int main()
{
	std::cout<<"Hello\n";
	Graph g(5,0.5);

	g.displayNodes();
	g.displayEdges();
	std::cout<<"Number of edges "<<g.E()<<std::endl;
	
	std::cout<<"neighbots of 0 \n";
	g.neighbors(0);
	std::cout<<"\n neighbors of 1 \n";
	g.neighbors(1);
}