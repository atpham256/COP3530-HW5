// Name: Anthony T. Pham
// UF ID: 5038-1111
// Discussion section #: 1079

#include<iostream>
#include<fstream>
#include "OrthogonalLinkedSparseMatrix.h"

using namespace std;

int main()
{
	// declare variables
	OrthogonalLinkedSparseMatrix<int> a, a_prime, b, c;
	// open file streams
	ifstream inFile;
	inFile.open("In1.txt");
	ofstream outFile("Out1.txt");

	// create OrthogonalLinkedSparseMatrix a
	inFile >> a;
	// create OrthogonalLinkedSparseMatrix b
	inFile >> b;
	// transpose a = a'
	a.transpose(a_prime);
	// calculate c = a' + b
	a_prime.add(b,c);
	// write c to file
	outFile << c;

	cout << "Writing to file complete." << endl;

	// close file streams
	inFile.close();
	outFile.close();

}
