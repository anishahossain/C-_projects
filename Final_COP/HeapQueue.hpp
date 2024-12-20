/*Anisha Hossain (U43189731), Alina Pineda (U79400432), Tanisha Dutta (U31690052), Brielle Ashmeade (U38424858) 
File description:
This header file implements a priority queue using a binary heap structure. The VectorCompleteTree class 
manages a complete binary tree with vector-based storage and 1-based indexing, while HeapQueue provides 
standard priority queue operations (insert, removeMin, min). The implementation includes a custom CompareNodes comparator for vertex-distance pairs, supporting Dijkstra's algorithm implementation. 
*/
#ifndef HEAPQUEUE_H
#define HEAPQUEUE_H

#include <vector>

// Template class for a complete binary tree implemented as a vector 
template <typename E>
class VectorCompleteTree
{
private:
  std::vector<E> V; //Vector to store elements of the tree (1-based indexing)
public:
  typedef typename std::vector<E>::iterator Position; //Alias for a position in the vector 
protected:
  Position pos(int i) //Returns an iterator pointing to the position corresponding to index i
  {
    return V.begin() + i;
  }

  //Returns the index corresponding to an iterator
  int idx(const Position &p) const
  {
    return p - V.begin();
  }

public:
  VectorCompleteTree() : V(1) {} //Constructor: intializes the vector with a placeholder at index 0 for 1-based indexing
  int size() const { return V.size() - 1; } //Returns the number of elements in the tree
  Position left(const Position &p) { return pos(2 * idx(p)); } //Returns the left chid of the given position
  Position right(const Position &p) { return pos(2 * idx(p) + 1); } //Returns the right chid of the given position
  Position parent(const Position &p) { return pos(idx(p) / 2); } // Returns the parent of the given position
  bool hasLeft(const Position &p) const { return 2 * idx(p) <= size(); } //Checks if the given position has a left child
  bool hasRight(const Position &p) const { return 2 * idx(p) + 1 <= size(); } //Checks if the given position has a right child
  bool isRoot(const Position &p) const { return idx(p) == 1; } //Checks if the given position is the root
  Position root() { return pos(1); } //Returns the root position of the tree
  Position last() { return pos(size()); } //Returns the last position in the tree
  void addLast(const E &e) { V.push_back(e); } //Adds an element to the end of the tree
  void removeLast() { V.pop_back(); } //Removes the last element of the tree

  void swap(const Position &p, const Position &q) //Swaps the elements at two positions
  {
    E e = *q;
    *q = *p;
    *p = e;
  }
};

//Template class for a priority queue implemented using a heap
template <typename E, typename C>
class HeapQueue
{
public:
  int size() const; //Returns the size of the heap
  bool empty() const; //Checks if the heap is empty 
  void insert(const E &e); //Inserts an element into the heap
  const E &min(); //Returns the minimum element in the heap
  void removeMin(); //Removes the minimum element from the heap

private:
  VectorCompleteTree<E> T; //Underlying complete binary tree structure
  C isLess; //Comparator function to determine heap order

  typedef typename VectorCompleteTree<E>::Position Position; //Alias for a tree position
  void upheap(Position v);   // Helper function for upheap bubbling
  void downheap(Position u); // Helper function for downheap bubbling
};

//Returns the size of the map
template <typename E, typename C> 
int HeapQueue<E, C>::size() const {
    return T.size();
}

//Checks if the heap is empty
template <typename E, typename C>
bool HeapQueue<E, C>::empty() const {
    return size() == 0;
}

//Returns the minimum element (at the root of the heap)
template <typename E, typename C>
const E& HeapQueue<E, C>::min() {
    return *(T.root());
}


//Inserts a new element into the heap
template <typename E, typename C>
void HeapQueue<E, C>::insert(const E& e) {
    T.addLast(e); //Add the new element to the end of the tree
    upheap(T.last()); //Restore the heap property
}


//Removes the minimum element (at the root of the heap)
template <typename E, typename C>
void HeapQueue<E, C>::removeMin() {
    if (size() == 1) {
        T.removeLast(); //If there's only one element, just remove it
    } else {
        T.swap(T.root(), T.last()); //Swap the root with the last element
        T.removeLast(); //Remove the last element
        downheap(T.root()); //Restore the heap property
    }
}

//Helper function to restore heap property by bubbling up
template <typename E, typename C>
void HeapQueue<E, C>::upheap(Position v) {
    while (!T.isRoot(v)) { //Continue until the root is reached
        Position u = T.parent(v); //Get the parent position
        if (!isLess(*v, *u)) { //If the current value is not less than the parent then stop
            break;
        }
        T.swap(v, u); //Swap the current position with its parent
        v = u; //Move up to the parent
    }
}

//Helper function to restore heap property by bubbling down
template <typename E, typename C>
void HeapQueue<E, C>::downheap(Position u) {
    while (T.hasLeft(u)) { //Continue until a leaf is reached
        Position v = T.left(u); //Start with the left child
        if (T.hasRight(u) && isLess(*(T.right(u)), *v)) { //If the right child is smaller, choose it
            v = T.right(u);
        }
        if (isLess(*v, *u)) { //If the child is smaller, swap with the parent
            T.swap(u, v);
            u = v; //Move down to the child
        } else {
            break; //If the heap property is satisfied then stop
        }
    }
}

//Comparator for custom types, comparing based on the first element of a pair
struct CompareNodes {
    bool operator()(const std::pair<unsigned long, std::string>& a, const std::pair<unsigned long, std::string>& b) {
        return a.first < b.first;
    }
};

#endif