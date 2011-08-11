// Name: Anthony T. Pham
// UF ID: 5038-1111
// Discussion section #: 1079

#include<iostream>
#include<fstream>
#include<stack>

using namespace std;

int main()
{
	// declare variables
	ifstream inFile;
	inFile.open("In2.txt");
	ofstream outFile("Out2.txt");
	int size, value;
	inFile >> size; // get size of the array
	int *data = new int[size];
	int *lastAsBig = new int[size];
	stack<int> stack;

	// fill the data array and initialize lastAsBig to -2 (a value that will never be used)
	for(int i = 0; i < size; i++)
	{
		inFile >> value;
		data[i] = value;
		lastAsBig[i] = -2;
	}

	// push in last value in the array and it's index so we have something to compare in
	// the first iteration of the for-loop
	stack.push(size-1);
	stack.push(data[size-1]);

	// calculate lastAsBig[], starting from the end of the array
	for(int i = size-2; i >= 0; i--)
	{
		// keep popping out the top element in the stack in if it is less than the current element we are at
		// and push in current element regardless
		// at the end of the loop, all values in stack have no value bigger than it to the left
		// and will be assigned value -1 in lastAsBig[]
		while(data[i] >= stack.top())
		{
			// pop out lesser value
			stack.pop();
			lastAsBig[stack.top()] = i;
			stack.pop();

			if(stack.empty())
			{
				break;
			}
		}
		// push in the bigger value and its index
		stack.push(i);
		stack.push(data[i]);
	}

	// put in the -1 values for lastAsBig
	while(!stack.empty())
	{
		stack.pop();
		lastAsBig[stack.top()] = -1;
		stack.pop();
	}

	for(int i = 0; i < size; i++)
	{
		outFile << lastAsBig[i] << endl;
	}
	cout << "Writing to file complete.";

	// free memory to prevent memory leak
	delete [] data;
	delete [] lastAsBig;
	data = NULL;
	lastAsBig = NULL;

	// close file streams
	inFile.close();
	outFile.close();
}
