#include "BinarySearchTree.h"
#include <iostream>
#include <algorithm>

BinarySearchTree::BinarySearchTree()
{
	head = nullptr;
}

BinarySearchTree::BinarySearchTree(int data)
{
	head = new Node<int>(data);
	SIZE++;
}

BinarySearchTree::~BinarySearchTree()
{
	if (head != nullptr) {
		std::queue<Node<int>*> que;
		que.push(head);
		while (!que.empty()) {
			Node<int>* node = que.front();
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

BinarySearchTree::BinarySearchTree(const BinarySearchTree& other)
{
	if (this == &other) {
		return;
	}
	else {
		this->head = CopyNode(other.head);
		this->SIZE = other.SIZE;
	}
}

BinarySearchTree::BinarySearchTree(BinarySearchTree&& other) noexcept
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

BinarySearchTree& BinarySearchTree::operator=(const BinarySearchTree& other)
{
	if (&other == this) {
		return *this;
	}
	else {
		this->head = CopyNode(other.head);
		this->SIZE = other.SIZE;
	}
	return *this;
}

BinarySearchTree& BinarySearchTree::operator=(BinarySearchTree&& other) noexcept
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

std::vector<int> BinarySearchTree::SortedVector()
{
	std::vector<int> result;
	InOrder(head, result);
	return result;

}


int BinarySearchTree::min()
{
	return FindSmallest(head)->getData();
}

int BinarySearchTree::max()
{
	return FindBiggest(head)->getData();
}

int BinarySearchTree::size()
{
	return SIZE;
}

int BinarySearchTree::height()
{
	return heightRecursive(head);
}

void BinarySearchTree::Add(int data)
{
	if (contains(data))return;
	if (!head) {	
		head = new Node<int>(data);
		SIZE++;
		return;
		
	}
	Node<int>* current = head;
	Node<int>* parent = nullptr;
	while (current) {
		parent = current;
		if (data < current->getData()) {
			current = current->getLeft();
		}
		else
			current = current->getRight();
	}
	if (data < parent->getData())
		parent->SetLeft(new Node<int>(data));
	else
		parent->SetRight(new Node<int>(data));
	SIZE++;
}

void BinarySearchTree::Delete(int data)
{
	if(contains(data))
		head = RemoveRecursive(head, data);
}

void BinarySearchTree::Print()
{
	std::queue<std::pair<Node<int>*, int>> nodes;
	nodes.push({ head, 0 });

	int level = 0;
	while (!nodes.empty()) {
		Node<int>* node = nodes.front().first;
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

bool BinarySearchTree::isEmpty()
{
	return !head;
}

bool BinarySearchTree::contains(int data)
{
	Node<int>* current = head;
	while (current) {
		if (current->getData() == data)return true;
		else if (current->getData() < data)current = current->getLeft();
		else current = current->getRight();
	}
	return false;
}

Node<int>* BinarySearchTree::CopyNode(Node<int>* node)
{
	if (node == nullptr) {
		return nullptr;
	}

	Node<int>* newNode = node;
	Node<int>* left = newNode->getLeft();
	Node<int>* right = newNode->getRight();
	left = CopyNode(node->getLeft());
	right = CopyNode(node->getRight());
	return newNode;
}

Node<int>* BinarySearchTree::FindSmallest(Node<int>* node)
{
	Node<int>* cur = node;
	while (cur->getLeft())
		cur = cur->getLeft();
	return cur;
}

Node<int>* BinarySearchTree::FindBiggest(Node<int>* node)
{
	Node<int>* cur = node;
	while (cur->getRight())
		cur = cur->getRight();
	return cur;
}

Node<int>* BinarySearchTree::RemoveRecursive(Node<int>* node, int data)
{
	if (!node)return node;

	if (data < node->getData()) {
		node->SetLeft(RemoveRecursive(node->getLeft(), data));
		return node;
	}
	else if (data > node->getData()) {
		node->SetRight(RemoveRecursive(node->getRight(), data));
		return node;
	}	
	else {
		if (!node->getLeft() && !node->getRight()) {
			delete node;
			node = nullptr;
		}
		else if (!node->getLeft()) {
			Node<int>* temp = node;
			node = node->getRight();
			delete temp;
		}
		else {
			Node<int>* smallest = FindSmallest(node->getRight());
			node->SetData(smallest->getData());
			node->SetRight(RemoveRecursive(node->getRight(), smallest->getData()));
		}
	}
	SIZE--;
	return node;
}

void BinarySearchTree::InOrder(Node<int>* node, std::vector<int>& arr)
{
	if (!node)return;

	InOrder(node->getLeft(), arr);
	arr.push_back(node->getData());
	InOrder(node->getRight(), arr);
}

int BinarySearchTree::heightRecursive(Node<int>* node)
{
	if (node == nullptr) {
		return 0;
	}

	int leftHeight = heightRecursive(node->getLeft());
	int rightHeight = heightRecursive(node->getRight());

	return std::max(leftHeight, rightHeight) + 1;
}
