
#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "Node.h"
#include <queue>
#include <deque>
#include <iostream>
#include <vector>


template<typename T>
class BinaryTree {
public:
	class TreeIterator;
	
	/// <Rule of 5>
	BinaryTree();
	BinaryTree(T data);
	~BinaryTree();
	BinaryTree(const BinaryTree& other);
	BinaryTree(BinaryTree&& other);
	BinaryTree& operator=(const BinaryTree& other);
	BinaryTree& operator=(BinaryTree&& other);
	/// <end>

	bool operator==(const BinaryTree& other);
	bool operator!=(const BinaryTree& other);

	
	//return vector in chosen traversal
	std::vector<T> preOrderTraversal();
	std::vector<T> InOrderTraversal();
	std::vector<T> postOrderTraversal();
	std::vector<T> levelOrderTraversal();

	//add element to chosen pos
	void AddLeftToRight(T data);
	//add element to chosen pos
	void AddRightToLeft(T data);
	//clear tree
	void clear();
	//method to print tree to terminal
	void PrintTree();
	//delete element by iterator
	void erase(TreeIterator iterator);

	//return true if element is in tree
	bool FindElement(T data);

	
	bool IsEmpty();

	int size();
	int height();

	//return iterator to first element
	TreeIterator begin();
	//return iterator to last element(nullptr)
	TreeIterator end();
	//return iterator to chosen element
	TreeIterator find(T data);
	

protected:
	Node<T>* CopyNode(Node<T>* other);
	int heightRecursively(Node<T>* node);
	
	void preOrder(Node<T>* node, std::vector<T>& vect);
	void InOrder(Node<T>* node, std::vector<T>& vect);
	void postOrder(Node<T>* node, std::vector<T>& vect);
	void levelOrder(Node<T>* node, std::vector<T>& vect);
	

private:
	Node<T>* head;
	int SIZE{ 0 };

};


#endif BINARYTREE_H

template<typename T>
class BinaryTree<T>::TreeIterator {
public:
	using iterator_category = std::forward_iterator_tag;
	using value_type = T;
	using difference_type = std::ptrdiff_t;
	using pointer = Node<T>*;
	using reference = T&;

	TreeIterator(Node<T>* node);
	TreeIterator();

	pointer operator->() const;
	bool operator==(const TreeIterator& iter)const;
	bool operator!=(const TreeIterator& iter)const;

	TreeIterator& operator++();
	TreeIterator operator++(int);
	TreeIterator& operator--();
	TreeIterator operator--(int);

	static TreeIterator end();
	static TreeIterator rbegin(Node<T>* node);
	static TreeIterator rend();


	void SetHead(Node<T>* node);
private:
	Node<T>* current;
	Node<T>* Head;
	bool visited_left{ false };
	bool visited_right{ false };

	friend class BinaryTree<T>;
};


//ITERATOR REALISATION////
template<typename T>
inline BinaryTree<T>::TreeIterator::TreeIterator(Node<T>* node): current(node){}

template<typename T>
inline BinaryTree<T>::TreeIterator::TreeIterator(): current(nullptr){}

template<typename T>
inline Node<T>* BinaryTree<T>::TreeIterator::operator->() const
{
	return current;
}

template<typename T>
inline bool BinaryTree<T>::TreeIterator::operator==(const TreeIterator& iter) const
{
	return current == iter.current;
}

template<typename T>
inline bool BinaryTree<T>::TreeIterator::operator!=(const TreeIterator& iter) const
{
	return !(*this == iter);
}

template<typename T>
typename BinaryTree<T>::TreeIterator& BinaryTree<T>::TreeIterator::operator++()
{
	if (current->getRight()) {
		current = current->getRight();
		while (current->getLeft())
			current = current->getLeft();
	}
	else {
		Node<T>* parent = current->getParent();
		while (parent && parent->getRight() == current) {
			current = parent;
			parent = parent->getParent();
		}

		current = parent;
	}
	return *this;
}

template<typename T>
typename BinaryTree<T>::TreeIterator BinaryTree<T>::TreeIterator::operator++(int)
{
	return ++(*this);
}

template<typename T>
typename BinaryTree<T>::TreeIterator& BinaryTree<T>::TreeIterator::operator--()
{
	if (current == nullptr) {
		Node<T>* cur = Head;
		while (cur->getRight())
			cur = cur->getRight();
		while (cur->getLeft())
			cur = cur->getLeft();

		current = cur;
	}
	else {
		if (current->getLeft()) {
			current = current->getLeft();
			while (current->getRight())
				current = current->getRight();
		}
		else {
			Node<T>* parent = current->getParent();
			while (parent && parent->getLeft() == current) {
				current = parent;
				parent = parent->getParent();
			}
			current = parent;
		}
	}
	return *this;
}

template<typename T>
typename BinaryTree<T>::TreeIterator BinaryTree<T>::TreeIterator::operator--(int)
{
	return --(*this);
}

template<typename T>
typename BinaryTree<T>::TreeIterator BinaryTree<T>::TreeIterator::end()
{
	return TreeIterator();
}

template<typename T>
typename BinaryTree<T>::TreeIterator BinaryTree<T>::TreeIterator::rbegin(Node<T>* node)
{
	if (!node) { return end(); }
	TreeIterator it(node);
	while (it.current->getRight())
		it.current = it.current->getRight();
	return it;
}

template<typename T>
typename BinaryTree<T>::TreeIterator BinaryTree<T>::TreeIterator::rend()
{
	return end();
}
template<typename T>
inline void BinaryTree<T>::TreeIterator::SetHead(Node<T>* node)
{
	this->Head = node;
}
//ITERATOR REALISATION END////

//Realisation of methods

template<typename T>
inline BinaryTree<T>::BinaryTree()
{
	head = nullptr;
	head->SetParent(nullptr);
}

template<typename T>
inline BinaryTree<T>::BinaryTree(T data)
{
	head = new Node<T>(data);
	head->SetParent(nullptr);
	SIZE++;
}

template<typename T>
inline BinaryTree<T>::~BinaryTree()
{
	if (head != nullptr) {
		std::queue<Node<T>*> que;
		que.push(head);
		while (!que.empty()) {
			Node<T>* node = que.front();
			que.pop();

			if (node == nullptr) {
				continue;
			}
			else {
				que.push(node->getLeft());
				que.push(node->getRight());

				delete node;
			}

		}
	}
	
}

template<typename T>
inline BinaryTree<T>::BinaryTree(const BinaryTree& other)
{
	if (this == &other) {
		return;
	}
	else {
		this->head = CopyNode(other.head);
		this->SIZE = other.SIZE;
	}

}

template<typename T>
inline BinaryTree<T>::BinaryTree(BinaryTree&& other)
{
	if (other.head == nullptr) {
		this->head = nullptr;
	}
	else {
		this->head = other.head;
		this->SIZE = other.SIZE;
		other.head = nullptr;
		other.SIZE = 0;

	}
}

template<typename T>
inline BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T>& other)
{
	if (&other == this) {
		return *this;	
	}
	else {
		this->head = CopyNode(other.head);
		this->SIZE = other.SIZE;
	}
}

template<typename T>
inline BinaryTree<T>& BinaryTree<T>::operator=(BinaryTree<T>&& other)
{
	if (other.head == this->head) {
		other.head = nullptr;
		return *this;
	}
	else {
		this->head = CopyNode(other.head);
		other.head = nullptr;
		this->SIZE = other.SIZE;
		other.head = nullptr;
		other.SIZE = 0;
		return *this;
	}
}

template<typename T>
inline bool BinaryTree<T>::operator==(const BinaryTree& other)
{
	if (this->head->getData() != other.head->getData())
		return false;
	
	std::queue<Node<T>*> node1;
	std::queue<Node<T>*> node2;

	node1.push(this->head);
	node2.push(other.head);

	while (!node1.empty() && !node2.empty()) {
		Node<T>* nd1 = node1.front();
		node1.pop();

		Node<T>* nd2 = node2.front();
		node2.pop();

		if (nd1->getData() != nd2->getData())
			return false;

		node1.push(nd1->getLeft());
		node2.push(nd2->getLeft());

		node1.push(nd1->getRight());
		node2.push(nd2->getLeft());
	}

	if (node1.empty() && node2.empty())
		return true;
	return false;
}

template<typename T>
inline bool BinaryTree<T>::operator!=(const BinaryTree& other)
{
	return !(*this == other);
}

template<typename T>
inline std::vector<T> BinaryTree<T>::preOrderTraversal()
{
	std::vector<T> result;
	preOrder(head, result);
	return result;
}

template<typename T>
inline std::vector<T> BinaryTree<T>::InOrderTraversal()
{
	std::vector<T> result;
	InOrder(head, result);
	return result;
}

template<typename T>
inline std::vector<T> BinaryTree<T>::postOrderTraversal()
{
	std::vector<T> result;
	postOrder(head, result);
	return result;
}

template<typename T>
inline std::vector<T> BinaryTree<T>::levelOrderTraversal()
{
	std::vector<T> result;
	levelOrder(head, result);
	return result;
}

template<typename T>
inline void BinaryTree<T>::AddLeftToRight(T data)
{
	std::deque<Node<T>*> nodes;
	nodes.push_back(head);
	while (!nodes.empty()) {
		Node<T>* node = nodes.front();
		nodes.pop_front();

		if (node->getLeft() == nullptr) {
			node->SetLeft(new Node<T>(data));
			Node<T>* nd = node->getLeft();
			nd->SetParent(node);
			SIZE++;
			return;
		}
		else if (node->getRight() == nullptr) {
			node->SetRight(new Node<T>(data));
			Node<T>* nd = node->getRight();
			nd->SetParent(node);
			SIZE++;
			return;
		}
		else {
			nodes.push_back(node->getLeft());
			nodes.push_back(node->getRight());
		}
	}
}

template<typename T>
inline void BinaryTree<T>::AddRightToLeft(T data)
{
	std::deque<Node<T>*> nodes;
	nodes.push_back(head);
	while (!nodes.empty()) {
		Node<T>* node = nodes.back();
		nodes.pop_back();

		if (node->getRight() == nullptr) {
			node->SetRight(new Node<T>(data));
			Node<T>* nd = node->getRight();
			nd->SetParent(node);
			SIZE++;
			return;
		}
		else if (node->getLeft() == nullptr) {
			node->SetLeft(new Node<T>(data));
			Node<T>* nd = node->getLeft();
			nd->SetParent(node);
			SIZE++;
			return;
		}
		else {
			nodes.push_front(node->getRight());
			nodes.push_front(node->getLeft());
		}
	}
}

template<typename T>
inline void BinaryTree<T>::clear()
{
	std::queue<Node<T>*> nodes;
	nodes.push(head);

	while (!nodes.empty()) {
		Node<T>* node = nodes.front();
		nodes.pop();

		if (node == nullptr)continue;
		else {
			nodes.push(node->getLeft());
			nodes.push(node->getRight());

			delete node;
		}
	}

	head = nullptr;
	SIZE = 0;
}

template<typename T>
inline void BinaryTree<T>::PrintTree()
{
	std::queue<std::pair<Node<T>*, int>> nodes;
	nodes.push({ head, 0 });

	int level = 0;
	while (!nodes.empty()) {
		Node<T>* node = nodes.front().first;
		int nodeLevel = nodes.front().second;
		nodes.pop();

		if (node == nullptr) continue;

		if (nodeLevel > level) {
			std::cout << std::endl;
			level = nodeLevel;
		}

		std::cout << node->getData() << " ";

		nodes.push({ node->getLeft(), nodeLevel + 1 });
		nodes.push({ node->getRight(), nodeLevel + 1 });
	}
	std::cout << std::endl;
}

template<typename T>
inline void BinaryTree<T>::erase(BinaryTree<T>::TreeIterator iterator)
{
	Node<T>* node = iterator.current;
	if (!node) {
		throw std::runtime_error("cannot remove nullptr");
		return;
	}
	Node<T>* parent = node->getParent();
	bool isLeftChild = parent && parent->getLeft() == node;

	if(node->getLeft() == nullptr && node->getRight() == nullptr){
		if (isLeftChild) {
			parent->SetLeft(nullptr);
		}
		else {
			parent->SetRight(nullptr);
		}
	}
	else if (node->getLeft() == nullptr) {
		if (isLeftChild) {
			parent->SetLeft(node->getRight());
		}
		else {
			parent->SetRight(node->getLeft());
		}
		node->getRight()->SetParent(parent);
	}
	else if (node->getRight() == nullptr) {
		if (isLeftChild) {
			parent->SetLeft(node->getLeft());
		}
		else {
			parent->SetRight(node->getLeft());
		}
		node->getLeft()->SetParent(parent);
	}
	else {
		Node<T>* successor = node->getRight();
		while (successor->getLeft())
			successor = successor->getLeft();

		node->SetData(successor->getData());

		if (successor->getRight()) {
			successor->getRight()->SetParent(successor->getParent());
		}
		if (successor->getParent()->getLeft() == successor) {
			successor->getParent()->SetLeft(successor->getRight());
		}
		else {
			successor->getParent()->SetRight(successor->getRight());
		}
	}

	iterator.current = nullptr;
}

template<typename T>
inline bool BinaryTree<T>::FindElement(T data)
{
	std::queue<Node<T>*> nodes;
	nodes.push(head);

	while (!nodes.empty()) {
		Node<T>* node = nodes.front();
		nodes.pop();
		if (node == nullptr)continue;
		else {
			if (node->getData() == data) {
				return true;
			}
		}

		nodes.push(node->getLeft());
		nodes.push(node->getRight());
	}
	return false;
}

template<typename T>
inline bool BinaryTree<T>::IsEmpty()
{
	return head == nullptr;
}

template<typename T>
inline int BinaryTree<T>::size()
{
	return SIZE;
}

template<typename T>
inline int BinaryTree<T>::height()
{
	return heightRecursively(head);
}

template<typename T>
typename BinaryTree<T>::TreeIterator BinaryTree<T>::begin()
{
	if (head == nullptr)
		return TreeIterator(nullptr);

	Node<T>* it = head;
	while (it->getLeft()) {
		it = it->getLeft();
	}
	TreeIterator iter(it);
	iter.SetHead(head);

	return iter;
}

template<typename T>
typename BinaryTree<T>::TreeIterator BinaryTree<T>::end()
{
	TreeIterator iter(nullptr);
	iter.SetHead(head);
	return iter;
}

template<typename T>
typename BinaryTree<T>::TreeIterator BinaryTree<T>::find(T data)
{
	if (!FindElement(data)) { return TreeIterator(nullptr); }

	std::queue<Node<T>*> nodes;
	nodes.push(head);
	while (!nodes.empty()) {
		Node<T>* node = nodes.front();
		nodes.pop();

		if (node == nullptr)continue;
		if (node->getData() == data)return TreeIterator(node);

		nodes.push(node->getLeft());
		nodes.push(node->getRight());
	}
}


template<typename T>
inline Node<T>* BinaryTree<T>::CopyNode(Node<T>* other)
{
	if (other == nullptr) {
		return nullptr;
	}

	Node<T>* newNode = other;
	Node<T>* left = newNode->getLeft();
	Node<T>* right = newNode->getRight();
	left = CopyNode(other->getLeft());
	right = CopyNode(other->getRight());
	return newNode;
}

template<typename T>
inline int BinaryTree<T>::heightRecursively(Node<T>* node)
{
	if (node == nullptr) {
		return 0;
	}

	int leftHeight = heightRecursively(node->getLeft());
	int rightHeight = heightRecursively(node->getRight());

	return std::max(leftHeight, rightHeight) + 1;
}

template<typename T>
inline void BinaryTree<T>::preOrder(Node<T>* node, std::vector<T>& vect)
{
	if (node == nullptr)return;
	else {
		vect.push_back(node->getData());
	}

	preOrder(node->getLeft(), vect);
	preOrder(node->getRight(), vect);
}

template<typename T>
inline void BinaryTree<T>::InOrder(Node<T>* node, std::vector<T>& vect)
{
	if (!node)return;

	InOrder(node->getLeft(), vect);
	vect.push_back(node->getData());
	InOrder(node->getRight(), vect);
}

template<typename T>
inline void BinaryTree<T>::postOrder(Node<T>* node, std::vector<T>& vect)
{
	if (!node)return;

	postOrder(node->getLeft(), vect);
	postOrder(node->getRight(), vect);
	vect.push_back(node->getData());
}

template<typename T>
inline void BinaryTree<T>::levelOrder(Node<T>* node, std::vector<T>& vect)
{
	std::queue<Node<T>*> nodes;
	nodes.push(node);

	while (!nodes.empty()) {
		Node<T>* node = nodes.front();
		nodes.pop();

		if (node) {
			vect.push_back(node->getData());
			nodes.push(node->getLeft());
			nodes.push(node->getRight());
		}
	}
}





