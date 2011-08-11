// Name: Anthony T. Pham
// UF ID: 5038-1111
// Discussion section #: 1079

#ifndef ORTHOGONALLINKEDSPARSEMATRIX_H
#define ORTHOGONALLINKEDSPARSEMATRIX_H

#include <iostream>
#include <fstream>
#include "matrixNode.h"

using namespace std;

// declaration of classes and operator overloads
template<class T>
class OrthogonalLinkedSparseMatrix;
template<class T>
ostream& operator<< (ostream&, OrthogonalLinkedSparseMatrix<T>&);
template<class T>
istream& operator>> (istream&, OrthogonalLinkedSparseMatrix<T>&);

// definition of methods for OrthogonalLinkedSparseMatrix class
template<class T>
class OrthogonalLinkedSparseMatrix
{
	public:
		// constructor and destructor
		OrthogonalLinkedSparseMatrix(){headerNode = new matrixNode<T>();}
		~OrthogonalLinkedSparseMatrix(){}
		friend ostream& operator<< <>(ostream&, OrthogonalLinkedSparseMatrix<T>&);
		friend istream& operator>> <>(istream&, OrthogonalLinkedSparseMatrix<T>&);
		void transpose(OrthogonalLinkedSparseMatrix<T> &b);
		void add(OrthogonalLinkedSparseMatrix<T> &b, OrthogonalLinkedSparseMatrix<T> &c);
	private:
		matrixNode<T> *headerNode;
};

// overload << operator
template<class T>
ostream& operator<<(ostream& out, OrthogonalLinkedSparseMatrix<T>& x)
{
	// matrixNode to go through our matrix node by node
	matrixNode<T> *next = x.headerNode;
	// print out the # of rows, cols and non-zero terms
	out << x.headerNode->row << "  " << x.headerNode->col << "  " << x.headerNode->value << endl;
	// print all the nodes
	for(int i = 0; i < x.headerNode->value; i++)
	{
		next = next->right;
		out << next->row << "  " << next->col << "  " << next->value << endl;
	}
	return out;
}

// overload >> operator
template<class T>
istream& operator>>(istream& in, OrthogonalLinkedSparseMatrix<T>& x)
{
	// fill the headerNode with information from the first line of the file
	in >> x.headerNode->row >> x.headerNode->col >> x.headerNode->value;
	x.headerNode->down = NULL;
	x.headerNode->right = NULL;
	// declare matrixNodes to hold the previos node's information and current node's information
	matrixNode<T> *prevNode = x.headerNode;
	matrixNode<T> *currentNode;

	for(int i = 0; i < x.headerNode->value; i++)
	{
		// matrixNode to hold current node information that we are reading
		currentNode = new matrixNode<T>();
		currentNode->down = NULL;
		currentNode->right = NULL;
		// fill in information from the file for the current node
		in >> currentNode->row >> currentNode->col >> currentNode->value;
		// make previous node's right pointer point to our current node
		prevNode->right = currentNode;
		// shift our previous node one over by making it point to the current node
		prevNode = currentNode;
	}
	prevNode->right = x.headerNode;

	// link the nodes by columns
	matrixNode<T> *linkerNode = x.headerNode;
	currentNode = x.headerNode;
	// search if there is a non-zero term in the location, if there is, add it to the chain
	for(int i = 0; i <= x.headerNode->col; i++)
	{
		for(int j = 0; j <= x.headerNode->row; j++)
		{
			for(int k = 0; k < x.headerNode->value; k++)
			{
				currentNode = currentNode->right;
				if(currentNode->col == i && currentNode->row == j)
				{
					linkerNode->down = currentNode;
					linkerNode = currentNode;
				}
			}
			currentNode = x.headerNode;
		}
	}
	linkerNode->down = x.headerNode;

	// link nodes by row
	linkerNode = x.headerNode;
	currentNode = x.headerNode;
	// search if there is a non-zero term in the location, if there is, add it to the chain
	for(int i = 0; i <= x.headerNode->row; i++)
	{
		for(int j = 0; j <= x.headerNode->col; j++)
		{
			for(int k = 0; k < x.headerNode->value; k++)
			{
				currentNode = currentNode->down;
				if(currentNode->row == i && currentNode->col == j)
				{
					linkerNode->right = currentNode;
					linkerNode = currentNode;
				}
			}
			currentNode = x.headerNode;
		}
	}
	linkerNode->right = x.headerNode;
	return in;
}

// transpose method for OrthogonalLinkedSparseMatrix
// b = transpose of *this
template<class T>
void OrthogonalLinkedSparseMatrix<T>::transpose(OrthogonalLinkedSparseMatrix<T> &b)
{
	// nodes to help with transpose
	matrixNode<T> *currentNodeA = this->headerNode->right;
	matrixNode<T> *currentNodeB = b.headerNode;
	matrixNode<T> *fillerNodeB = new matrixNode<T>;
	b.headerNode->row = this->headerNode->col;
	b.headerNode->col = this->headerNode->row;
	b.headerNode->value = this->headerNode->value;
	for(int i = 0; i < this->headerNode->value; i++)
	{
		fillerNodeB = new matrixNode<T>;
		fillerNodeB->row = currentNodeA->col;
		fillerNodeB->col = currentNodeA->row;
		fillerNodeB->value = currentNodeA->value;
		// set currentNode of b to the filler node which is the transpose of the current node of a
		currentNodeB->down = fillerNodeB;
		currentNodeB = fillerNodeB;
		currentNodeA = currentNodeA->right;
	}
	currentNodeB->down = b.headerNode;

	// link nodes by row
	matrixNode<T> *linkerNode = b.headerNode;
	matrixNode<T> *currentNode = b.headerNode;
	// search if there is a non-zero term in the location, if there is, add it to the chain
	for(int i = 0; i <= b.headerNode->row; i++)
	{
		for(int j = 0; j <= b.headerNode->col; j++)
		{
			for(int k = 0; k < b.headerNode->value; k++)
			{
				currentNode = currentNode->down;
				if(currentNode->row == i && currentNode->col == j)
				{
					linkerNode->right = currentNode;
					linkerNode = currentNode;
				}
			}
			currentNode = b.headerNode;
		}
	}
	linkerNode->right = b.headerNode;
}

// add method for OrthogonalLinkedSparseMatrix
// c = *this + b
template<class T>
void OrthogonalLinkedSparseMatrix<T>::add(OrthogonalLinkedSparseMatrix<T> &b, OrthogonalLinkedSparseMatrix<T> &c)
{
	// nodes to help calculate c = *this + b
	matrixNode<T> *currentNodeA = this->headerNode->right;
	matrixNode<T> *currentNodeB = b.headerNode->right;
	matrixNode<T> *currentNodeC = c.headerNode;
	matrixNode<T> *nodeC = new matrixNode<T>();
	int count = 0;
	if(this->headerNode->row != b.headerNode->row || this->headerNode->col != b.headerNode->col)
	{
		cout << "Cannot add matrices of unequal size" << endl;
	}
	else
	{
		c.headerNode->row = this->headerNode->row;
		c.headerNode->col = this->headerNode->col;
		for(int i = 0; i <= c.headerNode->row; i++)
		{
			for(int j = 0; j <= c.headerNode->col; j++)
			{
				nodeC = new matrixNode<T>();
				// if a's location = b's location
				if(currentNodeA->row == i && currentNodeA->col == j && currentNodeB->row == i && currentNodeB->col == j && currentNodeA != this->headerNode && currentNodeB != b.headerNode)
				{
					nodeC->row = i;
					nodeC->col = j;
					nodeC->value = currentNodeA->value + currentNodeB->value;
					currentNodeC->right = nodeC;
					currentNodeC = nodeC;
					currentNodeA = currentNodeA->right;
					currentNodeB = currentNodeB->right;
					count++;
				}
				// if a has a value at the location, but b doesn't have a value at the location
				else if(currentNodeA->row == i && currentNodeA->col == j && currentNodeA != this->headerNode)
				{
					nodeC->row = i;
					nodeC->col = j;
					nodeC->value = currentNodeA->value;
					currentNodeC->right = nodeC;
					currentNodeC = nodeC;
					currentNodeA = currentNodeA->right;
					count++;
				}
				// if b has a value at the location, but a doesn't have a value at the location
				else if(currentNodeB->row == i && currentNodeB->col == j && currentNodeB != b.headerNode)
				{
					nodeC->row = i;
					nodeC->col = j;
					nodeC->value = currentNodeB->value;
					currentNodeC->right = nodeC;
					currentNodeC = nodeC;
					currentNodeB = currentNodeB->right;
					count++;
				}
			}
		}
		currentNodeC->right = c.headerNode;
		c.headerNode->value = count;
	}

	// link the nodes by columns
	matrixNode<T> *linkerNode = c.headerNode;
	matrixNode<T> *currentNode = c.headerNode;
	// search if there is a non-zero term in the location, if there is, add it to the chain
	for(int i = 0; i <= c.headerNode->col; i++)
	{
		for(int j = 0; j <= c.headerNode->row; j++)
		{
			for(int k = 0; k < c.headerNode->value; k++)
			{
				currentNode = currentNode->right;
				if(currentNode->col == i && currentNode->row == j)
				{
					linkerNode->down = currentNode;
					linkerNode = currentNode;
				}
			}
			currentNode = c.headerNode;
		}
	}
	linkerNode->down = c.headerNode;
}
#endif
