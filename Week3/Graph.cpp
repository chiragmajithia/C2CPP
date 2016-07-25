#include "Graph.h"
#include <ctime>
#include <iomanip>  

const int MAX_EDGE_COST = 10;
const int MIN_EDGE_COST = 1; //Should always be > 0

void display1DVector(std::vector<int> v)
{
	//Helper function to display 1-D array
	int indx = 0;
	for(std::vector<int>::iterator it = v.begin();it!=v.end();++it)
	{
		std::cout<<"["<<indx++<<"] = "<<*it<<"\n";
	}
}

Graph::Graph(int num_of_nodes, double density)
{
	if(num_of_nodes <= 0)
	{
		std::cout<<"Invalid Number of nodes = "<<num_of_nodes<<std::endl;
		exit(EXIT_FAILURE);
	}
	if(density < 0)
	{
		std::cout<<"Invalid Graph density = "<<density<<std::endl;
		exit(EXIT_FAILURE);
	}
	//Creating nodes with value = 0, indicating the node is not visited
	nodes.resize(num_of_nodes,0);
	//Creating edges (Adjacency Matrix) for open graph (with no nodes connected)
	edges.resize(num_of_nodes,std::vector<int> (num_of_nodes,0));
	connectGraph(density);
}

void Graph::connectGraph(double d)
{
	srand (time(NULL));
	for(int i = 0;i < edges.size();++i)
	{
		for(int j = 0; j < edges[i].size();++j)
		{
			//if random number falls below the density, we add a edge with cost between 1 to 10
			// also, a node cannot point to itself
			double r = ((double) rand() / (RAND_MAX));
			if(r <= d && i!=j)
			{
				edges[i][j] = rand() % 10+1;
			}
		}
	}
	
}

std::vector<int> Graph::V()
{
	return nodes;	
}

std::vector<std::vector<int> >  Graph::E()
{
	return edges;
}

int Graph::adjacent(int n1,int n2)
{
	//returns cost of the edge, if cost = 0, there is no edge.s
	return edges[n1][n2];
}

std::vector<int> Graph::neighbors(int n1)
{
	std::vector<int> neighbors;
	for(int indx = 0; indx < edges[n1].size(); ++indx)
	{
		int edge = edges[n1][indx];
		if (edge!=0)
			neighbors.push_back(indx);
	}
	display1DVector(neighbors);
	return neighbors;
}

void Graph::add(int n1,int n2,int cost = 1)
{
	edges[n1][n2] = cost;
}

void Graph::del(int n1,int n2)
{
	edges[n1][n2] = 0;
}

int Graph::get_node_value(int n)
{
	return nodes[n];
}

void Graph::set_node_value(int n,int val)
{
	nodes[n] = val;
}

int Graph::get_edge_cost(int n1,int n2)
{
	return edges[n1][n2];
}

void Graph::set_edge_cost(int n1,int n2,int cost)
{
	if(cost < 0)
	{
		std::cout<<"Invalid cost assigned!"<<std::endl;
		exit(EXIT_FAILURE);
	}
	edges[n1][n2] = cost;
}

void Graph::displayNodes()
{
	int indx = 0;
	for(std::vector<int>::iterator it = nodes.begin();it!=nodes.end();++it)
	{
		std::cout<<"["<<indx++<<"] = "<<*it<<"\n";
	}
}

void Graph::displayEdges()
{
	int indx = 0;
	for(int i = 0;i < edges.size();++i)
	{
		std::cout<<"["<<i<<"] : ";
		for(int j = 0; j < edges[i].size();++j)
			std::cout<<std::setw(3)<<edges[i][j]<<" ";
		std::cout<<"\n";
	}
}

Graph::~Graph()
{
	std::cout<<"Bye! \n";
}