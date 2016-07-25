
#include <iostream>
using namespace std;
class PriorityQueue
{
	private:
		struct Node
		{
			//Each Node used in queue consists of 'edgeTo' id and cost
			int id;
			int cost;
		};


		const int MAX_N; //maximum size of the queue - equals to number of nodes used in Graph
		Node *queue; //array pointer used for storing node
		int size; //number of nodes currently stored in queue

		
	public:

	   
	    PriorityQueue(int MAX_N):MAX_N(MAX_N)
		{
			size = 0;
			queue = new Node[MAX_N];
		}

		~PriorityQueue()
		{
			delete [] queue;
			cout<<"Bye\n";
		}

		int pop()
		{
			//returns the id with minimum cost, and deletes from the queue
			// A Max queue with poping last element would be faster implementation
			Node n = queue[0];
			for(int i = 0; i < size-1; i++)
			{
				queue[i] = queue[i+1];
			}
			size--;
			return n.id;
		}

		int top()
		{
			//returns top element without deleting 
			return queue[0].id;
		}

		void changePriority(int id, int cost)
		{
			int indx = find(id);
			cout<<"id found at indx = "<<indx<<"\n";
			if(indx != -1)
			{
				for(int i = indx; i < size-1; i++)
				{
					queue[i] = queue[i+1];
				}
				size--;
				insert(id,cost);
			}
		}

		void insert(int id, int cost)
		{
			//insert new element in sorted list
			int indx = size - 1;
			while(queue[indx].cost > cost && indx >= 0)
			{
				queue[indx+1] = queue[indx];
				indx--; 
			}
			
			queue[++indx].id = id;
			queue[indx].cost = cost;
			size++;
		}

		int len()
		{	
			//returns number of elements in queue
			return size;
		}

		int find(int id1)
		{
			//searches for id in the queue and returns index. -1, if the id not found
			for(int i = 0; i < size; i++)
			{
				if(queue[i].id == id1)
					return i;
			}
			return -1;
		}
		
		void swap(int id1, int id2) 
		{
			//swaps to id in priority queue, without considering priorities
			int indx1 = find(id1);
			int indx2 = find(id2);
			Node temp = queue[indx1];
			queue[indx1] = queue[indx2];
			queue[indx2] = temp;
    	}
    	
    	std::ostream& operator<<(std::ostream& out)
    	{
    		//outstream operator overload
			for(int i = 0; i < size; i++)
			{
				out<<"["<<i<<"] "<<queue[i].id<<" ("<<queue[i].cost<<")\n";
			}
			return out;
		}
};

