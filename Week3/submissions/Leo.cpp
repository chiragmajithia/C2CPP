#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

/*The algorithm brief explain

    -The graph is an adjacent matrix
    -Has an array that represent the nodes (vertex), storing
        -If it is out to the shortest path algorithm
        -The actual value (if is not visited yet, is -1)
        -The path to print when the algorithm end
    -The graph is created like the specification, using density to decide if a edge will exist, and a random float to the value

    -The priority queue is a linked queue, where each node has a next and a previous node.
    -Bigger priority values stay in the beginning of the queue, smaller stay in the end the minimum pointer points to the smaller, maximum to bigger
    -Each node on the queue is a vertex's value, waiting to be tested

*/


class Graph{
    private:
        double** matrix;
        const int vertex_count;
        const int density;
        int edges_count;

        struct node {
            bool out;               //if the node is out or not
            double actual_value;   //the actual value of the node, the min path to it
            int* path;              //the others nodes used in the path until arrive in this node
        };

        node* nodes;

        //1.0 to 10.0
        double edge_rand_value(){
            double random = (rand() % 9001 + 1000);//1000 to 10000
            return random/1000;
        }

        //density is 0 to 100
        bool edge_test(){
            int random = rand() % 100;//0 to 99
            if(random < density)return true;
            else return false;
        }


    public:
        //Create the graph
        Graph(int size, double density_param):vertex_count(size), density(density_param){
            if(size <= 100 && size >= 0 && density_param >= 0 && density_param <= 100){
                //create the graph matrix
                matrix = new double*[vertex_count];
                for (int i = 0; i < vertex_count; ++i){
                    matrix[i] = new double[vertex_count];
                    for(int j = 0; j < vertex_count; j++)matrix[i][j] = 0.0;
                }

                //create nodes
                nodes = new node[vertex_count];
                for (int i = 0; i < vertex_count; ++i){
                    nodes[i].actual_value = -1.0;
                    nodes[i].out = false;
                    nodes[i].path = new int[vertex_count];
                    for (int j = 0; j < vertex_count; ++j)nodes[i].path[j] = -1;
                }

                //create edges
                for(int i = 0; i < vertex_count; i++)
                    for(int j = i+1; j < vertex_count; j++)
                        add(i, j);
            }
        }

        ~Graph(){
            for(int i = 0; i < vertex_count; i++){
                delete[] nodes[i].path;
            }
            delete[] nodes;
            for(int i = 0; i < vertex_count; i++){
                delete[] matrix[i];
            }
            delete [] matrix;
        }

        //adds to graph the edge from x to y, if it is not there.
        //x and y [0, 100]
        void add(int y, int x){
            if(x < vertex_count && y < vertex_count && x >= 0 && y >= 0){
                if(edge_test() == true){
                    double num = edge_rand_value();
                    matrix[y][x] = num;
                    matrix[x][y] = num;
                    edges_count++;
                }
            }else exit(EXIT_FAILURE);
        }

        //returns the number of vertices in the graph
        int V(){
            return vertex_count;
        }

        //returns the number of edges in the graph
        int E(){
            return  edges_count;
        }

        //print
        void printout(){
            for(int i = 0; i < vertex_count; i++)
                for(int j = i+1; j < vertex_count; j++)
                    cout << i << " to " << j << " = " <<matrix[i][j]<< endl;
        }

        //lists all nodes y such that there is an edge from x to y.
        bool* getNeighbors(int y){
            if(y < vertex_count && y >= 0){
                bool* neighbors = new bool[vertex_count];
                for(int i = 0; i < vertex_count; i++){
                    if(matrix[y][i] > 0)neighbors[i] = true;
                    else neighbors[i] = false;
                }
                return neighbors;
            }
            else exit(EXIT_FAILURE);
        }

        //removes the edge from x to y, if it is there.
        void delete_edge(int x, int y){
            if(y < vertex_count && x < vertex_count && x >= 0 && y >= 0){
                edges_count--;
                matrix[y][x] = 0;
                matrix[x][y] = 0;
            }else exit(EXIT_FAILURE);
        }

        //returns the value associated to the edge (x,y).
        double get_edge_value(int x, int y){
            if(y < vertex_count && x < vertex_count && x >= 0 && y >= 0)
                return matrix[y][x];
            else exit(EXIT_FAILURE);
        }

        //sets the value associated to the edge (x,y) to v
        void set_edge_value(int x, int y, double value){
            if(y < vertex_count && x < vertex_count && x >= 0 && y >= 0){
                matrix[y][x] = value;
                matrix[x][y] = value;
            }
            else exit(EXIT_FAILURE);
        }

        //get_node_value (G, x): returns the value associated with the node x.
        double get_node_value(int x){
            if(x >= 0 && x < vertex_count)
                return nodes[x].actual_value;
            else exit(EXIT_FAILURE);
        }

        //sets the value associated with the node x to a.
        void set_node_value(int x, double new_value){
            if(x >= 0 && x < vertex_count)
                nodes[x].actual_value = new_value;
            else exit(EXIT_FAILURE);
        }

        //verify if the node is out to the algorithm
        bool isOut(int x){
            if(x >= 0 && x < vertex_count)
                return nodes[x].out;
            else exit(EXIT_FAILURE);
        }

        //sets the value associated with the node x to true.
        void setOut(int x){
            if(x >= 0 && x < vertex_count)
                nodes[x].out = true;
            else exit(EXIT_FAILURE);
        }

        //The target node receive the actual path and add the actual itself
        void setPath(int actual, int target){
            int i;
            for(i = 0; nodes[actual].path[i] != -1; i++)
                nodes[target].path[i] = nodes[actual].path[i];

            nodes[target].path[i] = actual;
        }

        //print the target node path
        void printPath(int target){
            for(int i = 0; nodes[target].path[i] != -1 && i < vertex_count; i++)
                cout << nodes[target].path[i] << " ";
            cout << target << endl;
        }
};

//--Linked Queue
class PriorityQueue{

    private:

        int size_queue;

        struct queue_node{
            int node;
            double priority;
            queue_node* next;
            queue_node* prev;
        };

        queue_node* minimum;
        queue_node* maximum;

        //search in the queue
        //given the priority, return the first smaller queue's node
        queue_node* get_by_priority(double priority){
            queue_node* paux;
            for(paux = maximum; paux != minimum && paux->priority >= priority; paux = paux->next);
            return paux;
        }

    public:
        PriorityQueue():size_queue(0), minimum(NULL), maximum(NULL){}

        ~PriorityQueue(){
            while(!minPrioirity());
        }

        //insert a node to the queue, sorted by priority
        void insert_node(int index, double priority){

            queue_node* new_node = new queue_node();
            new_node->node = index;
            new_node->priority = priority;

            if(size_queue > 0){

                //get the first with smaller priority, or the null
                queue_node* paux = get_by_priority(new_node->priority);

                if(paux == maximum){
                    //new maximum
                    if(new_node->priority > paux->priority){
                        paux->prev = new_node;
                        new_node->prev = NULL;
                        new_node->next = paux;
                        maximum = new_node;
                    }else{
                        new_node->next = NULL;
                        new_node->prev = paux;
                        paux->next = new_node;

                        //new minimum
                        if(paux == minimum)minimum = new_node;
                    }
                }else if(paux == minimum){
                    //new minimum
                    if(new_node->priority < paux->priority){
                        paux->next = new_node;
                        new_node->next = NULL;
                        new_node->prev = paux;
                        minimum = new_node;
                    }else{
                        new_node->prev = paux->prev;
                        new_node->next = paux;
                        paux->prev->next = new_node;
                        paux->prev = new_node;
                    }
                }else{
                    new_node->next = paux;
                    new_node->prev = paux->prev;
                    paux->prev->next = new_node;
                    paux->prev = new_node;
                }

            }else {
                minimum = new_node;
                maximum = new_node;
                new_node->next = NULL;
                new_node->prev = NULL;
            }
            size_queue++;
        }

        //delete the minimum priority
        bool minPrioirity(){
            //if is the last
            if(size_queue==1){
                delete maximum;
                maximum = NULL;
                minimum = NULL;
                size_queue--;
                return true;
            }
            else{
                queue_node* paux;
                paux = minimum->prev;
                paux->next = NULL;
                delete minimum;
                minimum = paux;
                size_queue--;
                return false;
            }
        }

        int getSize(){
            return size_queue;
        }

        //returns the value of the min value edge on queue
        int top(){
            return minimum->node;
        }

};


class ShortestPath{

    private:
        Graph* graph;
        PriorityQueue *pq;
        bool* neighbors;
        double total_distance;

    public:
        double getShortestPath(int actual, int target, int dim, int dens){
            //size and density of the graph
            total_distance = 0.0;
            graph = new Graph(dim, dens);
            pq = new PriorityQueue();
            neighbors = NULL;

            pq->insert_node(0, -1.0);
            graph->set_node_value(0, 0.0);

            while(true){

                int actual_node = actual;
                double actual_node_value = 0.0;
                double edge_value = 0.0;
                double new_target_node_value = 0.0;

                //get the more prioritary node
                actual_node = pq->top();
                pq->minPrioirity();
                actual_node_value = graph->get_node_value(actual_node);

                //get it adjacents nodes
                neighbors = graph->getNeighbors(actual_node);
                for(int target_node = 0; target_node < graph->V(); target_node++){

                    if(neighbors[target_node] == true && !graph->isOut(target_node)){

                        //for each neighbor, sum the new value and insert into the queue
                        edge_value = graph->get_edge_value(actual_node, target_node);

                        new_target_node_value = edge_value+actual_node_value;

                        if(new_target_node_value < graph->get_node_value(target_node) || graph->get_node_value(target_node) == -1){
                            graph->set_node_value(target_node, new_target_node_value);
                            pq->insert_node(target_node, new_target_node_value);
                            graph->setPath(actual_node, target_node);
                        }
                        if(target_node == target){
                            //graph->printPath(target); //print the path
                            return graph->get_node_value(target);
                        }
                    }
                }

                graph->setOut(actual_node);
                if(pq->getSize() == 0){
                    return 0.0;
                }
            }
        }

        ~ShortestPath(){
            delete[] neighbors;
            delete graph;
            delete neighbors;
            delete pq;
        }

        double getDistance(){
            return total_distance;
        }
};

int main()
{
    srand (time(NULL));
    double total = 0.0;
    double number;
    int count = 0;
    ShortestPath *sp = new ShortestPath();
    for(int i = 1; i < 50; i++){
        //params: start vertex, end vertex, graph's size, density
        number = sp->getShortestPath(0, i, 50, 20);
        total += number;
        if(number > 0)count++;
    }
    cout << "Graph's vertices: 50 Density: 20"<< endl;
    cout << "average path length: " <<total/count << endl;
    cout << "no path:" << 49 - count<< endl<< endl;

    delete sp;

    total = 0.0;
    count = 0;
    sp = new ShortestPath();
    for(int i = 1; i < 50; i++){
        //params: start vertex, end vertex, graph's size, density
        number = sp->getShortestPath(0, i, 50, 40);
        total += number;
        if(number > 0)count++;
    }
    cout << "Graph's vertices: 50 Density: 40" << endl;
    cout << "average path length: " <<total/count << endl;
    cout << "no path:" << 49 - count<< endl;

    delete sp;

    return 0;
}
