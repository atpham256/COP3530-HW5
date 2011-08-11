// Name: Anthony T. Pham
// UF ID: 5038-1111
// Discussion section #: 1079

#ifndef MATRIXNODE_H
#define MATRIXNODE_H

template <class T>
struct matrixNode
{
   int row, col;
   T value;
   matrixNode<T> *down;
   matrixNode<T> *right;

   operator T() const {return value;}
      // type conversion from matrixNode to T
};

#endif

