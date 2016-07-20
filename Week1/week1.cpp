//Convert this program to C++
//change to C++ io
//change to one line comments
//change defines of constants to const
//change array to vector<>
//inline any short function


#include <iostream>
#include <vector>
using namespace std;
const int N = 40;

template <class Num>	//For generic vector  which will have numeric values
inline void sum(Num& sum, const vector<Num> data)
{
	//Sum Function :: Input Parameters: Num& sum  - A referenced (generic) variable which will be modified to contain the value of sum of the vector 'data'.
	//             ::                 : vector<Num> data - A generic vector which will contain a list of numerical values which require to be summed
	sum = 0;
	for(int i = 0; i < data.size(); ++i)
	{
		sum = sum + data[i];
	}
}

int main()
{
	//Main Function :: The program to sum first N whole numbers

	int accum = 0;	// stores the accumulated value or sum of the values stored in vector data
	vector<int> data(N,0);	// stores the first N whole numbers 
	for(int i = 0; i < N; ++i)
	{
		data[i] = i;	//Assigning first N whole numbers to the 'data'
	}
	sum(accum, data);	//Calling the function to compute sum
	cout<<"sum is "<<accum<<endl;	//Output the value to screen
	return 0;
}