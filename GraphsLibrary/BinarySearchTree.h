#pragma once
#include "Node.h"
#include <queue>
#include <vector>
#include <array>
#include <string>

class BinarySearchTree {
public:
	enum TRAVERSALS {
		INORDER, POSTORDER, PREORDER, LEVELORDER
	};
	
	BinarySearchTree();
	BinarySearchTree(int data);
	~BinarySearchTree();
	BinarySearchTree(const BinarySearchTree& other);
	BinarySearchTree(BinarySearchTree&& other) noexcept;
	
	
	BinarySearchTree& operator=(const BinarySearchTree& other);
	BinarySearchTree& operator=(BinarySearchTree&& other) noexcept;

	//return sorted vec
	std::vector<int> SortedVector();

	//return min value in tree
	int min(); 
	// return max value in tree
	int max(); 
	// return count of nodes
	int size(); 
	// return height of tree
	int height(); 

	//add element to sorted binary tree
	void Add(int data);

	//deleting element 
	void Delete(int data);
	
	//method for print your tree
	void Print();

	
	bool isEmpty();
	bool contains(int data);
	
	

private:
	Node<int>* CopyNode(Node<int>* node);
	Node<int>* FindSmallest(Node<int>* node);
	Node<int>* FindBiggest(Node<int>* node);
	Node<int>* RemoveRecursive(Node<int>* node, int data);
	void InOrder(Node<int>* node, std::vector<int>& arr);
	int heightRecursive(Node<int>* node);

	Node<int>* head;
	int SIZE{ 1 };
};

