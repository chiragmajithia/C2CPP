#include <iostream>
#include <vector>

class Graph
{
	public:
		Graph(int num_of_nodes, double density);
		void connectGraph(double d); //randonly generates graph based on density
		std::vector<int> V(); //returns number of vertices in Graph
		std::vector<std::vector<int> > E(); //returns number of edges in Graph
		int adjacent(int n1,int n2); //returns if there is a edge between node 1 and node 2
		std::vector<int> neighbors(int n1); //returns list of all the neighbors of the node
		void add(int n1,int n2, int cost); //adds to G the edge from n1 to n2, if it is not there.
		void del(int n1, int n2);// removes the edge from n1 to n2, if it is there.
		int get_node_value(int n); //returns the value associated with the node n.
		void set_node_value( int n, int val);// sets the value associated with the node n to val.
		int get_edge_cost( int n1, int n2);//returns the value associated to the edge (n1,n2).
		void set_edge_cost (int n1, int n2, int cost);//sets the value associated to the edge (n1,n2) to cost.
		void displayNodes();
		void displayEdges();
		~Graph();
	private:
		std::vector<int> nodes;
		std::vector<std::vector<int> > edges;
};
 
void display1DVector(std::vector<int>);