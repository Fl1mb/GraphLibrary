#pragma once
#include <unordered_set>
#include <vector>
#include <queue>
#include <stack>
#include <list>


template<typename T = int>
class GraphNode {
private:
	T data;
	std::unordered_set<GraphNode*> connections;


public:
	GraphNode(T data_);
	GraphNode(const GraphNode& other);
	~GraphNode();
	GraphNode& operator=(const GraphNode& other);
	
	bool operator==(const GraphNode& other);
	bool operator!=(const GraphNode& other);
	bool DeleteConnection(const T& data);
	bool DeleteConnection(GraphNode* other);
	bool HasConnection(const T& data_);
	bool HasConnection(GraphNode* other);
	bool HasPathTo(GraphNode* other);

	void MakeConnection(const T& data);
	void MakeConnection(GraphNode* other);
	void setData(T data_);

	T getData();
	std::list<GraphNode*> getConnections();
	std::list<GraphNode*> breadthFirstSearch();
	std::list<GraphNode*> depthFirstSearch();
	std::list<GraphNode*> ShortestPath(GraphNode* end);

	int SizeConnectedNodes();

};

template<typename T>
inline GraphNode<T>::GraphNode(T data_): data(data_)
{
}

template<typename T>
inline GraphNode<T>::GraphNode(const GraphNode& other)
{
	this->data = other.data;
	
	std::stack<GraphNode*> nodes;
	for (auto node : other.connections)
		nodes.push(node);

	while (!nodes.empty()) {
		GraphNode* node = nodes.top();
		nodes.pop();
		if(node)
			this->connections->insert(new GraphNode(*node));
	}
}

template<typename T>
inline GraphNode<T>::~GraphNode()
{
	connections.clear();
}

template<typename T>
inline GraphNode<T>& GraphNode<T>::operator=(const GraphNode& other)
{
	this->data = other.data;

	std::stack<GraphNode*> nodes;
	for (auto node : other.connections)
		nodes.push(node);

	while (!nodes.empty()) {
		GraphNode* node = nodes.top();
		nodes.pop();
		if (node)
			this->connections->insert(new GraphNode(*node));
	}

	return *this;
}

template<typename T>
inline bool GraphNode<T>::operator==(const GraphNode& other)
{
	if (this == &other) return true; // self-comparison

	if (data != other.data) return false; // data mismatch

	if (connections.size() != other.connections.size()) return false; // connection count mismatch

	for (auto it = connections.begin(); it != connections.end(); ++it) {
		bool found = false;
		for (auto otherIt = other.connections.begin(); otherIt != other.connections.end(); ++otherIt) {
			if (**it == **otherIt) {
				found = true;
				break;
			}
		}
		if (!found) return false; // connection not found
	}

	return true; // all checks passed
}

template<typename T>
inline bool GraphNode<T>::operator!=(const GraphNode& other)
{
	return !(*this == other);
}

template<typename T>
inline void GraphNode<T>::MakeConnection(const T& data)
{
	GraphNode* new_conn = new GraphNode(data);
	this->connections.insert(new_conn);
	new_conn->connections.insert(this);
}

template<typename T>
inline void GraphNode<T>::MakeConnection(GraphNode* other)
{
	this->connections.insert(other);
}

template<typename T>
inline bool GraphNode<T>::DeleteConnection(const T& data_)
{
	for (auto node : connections) {
		if (node->data == data_) {
			connections.erase(std::find(connections.begin(), connections.end(), node));
			return true;
		}
	}
	return false;
}

template<typename T>
inline bool GraphNode<T>::DeleteConnection(GraphNode* other)
{
	auto iter = std::find(connections.begin(), connections.end(), other);
	if (iter != connections.end()) {
		connections.erase(iter);
		return true;
	}
	return false;
}

template<typename T>
inline bool GraphNode<T>::HasConnection(const T& data_)
{
	for (auto node : connections) {
		if (node->data == data_)
			return true;
	}
	return false;
}

template<typename T>
inline bool GraphNode<T>::HasConnection(GraphNode* other)
{
	return std::find(connections.begin(), connections.end(), other) != connections.end();
}

template<typename T>
inline bool GraphNode<T>::HasPathTo(GraphNode<T>* other) {
	std::stack<GraphNode<T>*> stack;
	std::unordered_set<GraphNode<T>*> visited;

	stack.push(this);
	visited.insert(this);

	while (!stack.empty()) {
		GraphNode<T>* node = stack.top();
		stack.pop();

		if (node == other) {
			return true;
		}

		for (auto neighbor : node->getConnections()) {
			if (visited.find(neighbor) == visited.end()) {
				stack.push(neighbor);
				visited.insert(neighbor);
			}
		}
	}

	return false;
}

template<typename T>
inline void GraphNode<T>::setData(T data_)
{
	this->data = data_;
}

template<typename T>
inline T GraphNode<T>::getData()
{
	return data;
}

template<typename T>
inline std::list<GraphNode<T>*> GraphNode<T>::getConnections()
{
	std::list<GraphNode<T>*> nodes;
	for (auto iter : connections)
		nodes.push_back(iter);

	return nodes;
}

template<typename T>
inline std::list<GraphNode<T>*> GraphNode<T>::breadthFirstSearch()
{
	std::list<GraphNode<T>*> result;
	std::queue<GraphNode<T>*> queue;
	std::unordered_set<GraphNode<T>*> set;

	queue.push(this);
	set.insert(this);

	while (!queue.empty()) {
		GraphNode<T>* node = queue.front();
		queue.pop();

		result.push_back(node);
		for (auto neighbor : node->getConnections()) {
			if (set.find(neighbor) == set.end()) {
				queue.push(neighbor);
				set.insert(neighbor);
			}
		}
		
	}
	return result;

}

template<typename T>
inline std::list<GraphNode<T>*> GraphNode<T>::depthFirstSearch()
{
	std::list<GraphNode<T>*> result;
	std::stack<GraphNode<T>*> stack;
	std::unordered_set<GraphNode<T>*> visited;

	stack.push(this);
	visited.insert(this);

	while (!stack.empty()) {
		GraphNode<T>* node = stack.top();
		stack.pop();

		result.push_back(node);

		for (auto neighbor : node->getConnections()) {
			if (visited.find(neighbor) == visited.end()) {
				stack.push(neighbor);
				visited.insert(neighbor);
			}
		}
	}
	return result;
}

	template<typename T>
inline std::list<GraphNode<T>*> GraphNode<T>::ShortestPath(GraphNode* end)
{
	std::list<GraphNode<T>*> result;
	std::queue<std::pair<GraphNode<T>*, std::list<GraphNode<T>*>>> queue;
	std::unordered_set<GraphNode<T>*> visited;

	std::list<GraphNode<T>*> initialPath;
	initialPath.push_back(this);
	queue.push(std::make_pair(this, initialPath));
	visited.insert(this);

	while (!queue.empty()) {
		std::pair<GraphNode<T>*, std::list<GraphNode<T>*>> current = queue.front();
		queue.pop();

		if (current.first == end) {
			result = current.second;
			break;
		}

		for (auto neighbor : current.first->getConnections()) {
			if (visited.find(neighbor) == visited.end()) {
				std::list<GraphNode<T>*> newPath = current.second;
				newPath.push_back(neighbor);
				queue.push(std::make_pair(neighbor, newPath));
				visited.insert(neighbor);
			}
		}
	}

	return result;
}

template<typename T>
inline int GraphNode<T>::SizeConnectedNodes()
{
	std::unordered_set<GraphNode<T>*> visited;
	std::stack<GraphNode<T>*> stack;

	stack.push(this);
	visited.insert(this);

	while (!stack.empty()) {
		GraphNode<T>* node = stack.top();
		stack.pop();

		for (auto neighbor : node->getConnections()) {
			if (visited.find(neighbor) == visited.end()) {
				stack.push(neighbor);
				visited.insert(neighbor);
			}
		}
	}
	return visited.size();
}
