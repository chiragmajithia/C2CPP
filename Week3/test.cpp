#include <iostream>
#include "ShortestPath.cpp"
using namespace std;
int main()
{
	ShortestPath s(10,0.5);
	s.djikstras(1,9);
}