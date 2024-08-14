#pragma once



template<typename T>
class BinaryTree;

template<typename T>
class Node
{
private:
	T data;
	Node* left;
	Node* right;
	Node* parent;

	

	friend class BinaryTree<T>;


public:
	Node() : left(nullptr), right(nullptr), parent(nullptr) {}
	Node(T data_): data(data_), left(nullptr), right(nullptr), parent(nullptr) {}
	~Node() {}

	T getData();
	Node* getLeft();
	Node* getRight();
	Node* getParent();

	void SetData(T data_);
	void SetLeft(Node* left_);
	void SetRight(Node* right_);
	void SetParent(Node* prnt);

};


template<typename T>
T Node<T>::getData()
{
	return data;
}

template<typename T>
Node<T>* Node<T>::getLeft()
{
	return this->left;
}

template<typename T>
Node<T>* Node<T>::getRight()
{
	return this->right;
}

template<typename T>
inline Node<T>* Node<T>::getParent()
{
	return parent;
}

template<typename T>
void Node<T>::SetData(T data_)
{
	this->data = data_;
}

template<typename T>
void Node<T>::SetLeft(Node<T>* left_)
{
	this->left = left_;
}

template<typename T>
void Node<T>::SetRight(Node<T>* right_)
{
	this->right = right_;
}

template<typename T>
inline void Node<T>::SetParent(Node* prnt)
{
	this->parent = prnt;
}



