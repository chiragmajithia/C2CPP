#include "Graph.cpp"
#include "PriorityQueue.cpp"
class ShortestPath
{
public:
	ShortestPath(int num_ver,double den):g(num_ver,den),pq(num_ver)
	{
		g.displayEdges();	
	}

	~ShortestPath()
	{
	}

	void djikstras(int s,int d)
	{
		std::vector<int> v = g.V();
		display1DVector(v);
	}
	
private:
	Graph g;
	PriorityQueue pq;
	int *path;
};