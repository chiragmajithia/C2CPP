#include <iostream>
#include <queue>

class PriorityQueue
{
	public:
		void chgPriority(int id,int priority); //changes priority of the node (using its id)
		void pop(); //removes the top element of the queue;
		bool contains(int queue_element);
		void insert(int queue_element);
		int top();
		int size(); //returns top element of the queue
		struct Node
		{
			int id;
			int cost;
		};
		struct comparator
		{
			bool operator()(Node const& n1, Node const& n2) 
			{
				return n1.cost < n2.cost
    		}
		};

	private:
		std::priority_queue<Node, std::vector<Node>, comparator> queue;
};

/** TO DO : use templates for Node