#pragma once
#include "GraphNode.h"

template<typename T = int>
class Graph {
protected:
	std::unordered_set<GraphNode<T>*> Nodes;


public:
	Graph();
	Graph(T data_);
	Graph(const Graph& other);
    ~Graph();

    Graph& operator=(const Graph& other);
    
    static std::list<T> FromPointersToData(const std::list<GraphNode<T>*>& pointers);

    std::list<GraphNode<T>*> getNodes() const;
    std::list<GraphNode<T>*> getNeighbors(const T& data);
    std::list<GraphNode<T>*> breadthFirstSearch(const T& start);
    std::list<GraphNode<T>*> depthFirstSearch(const T& start);
    std::list<GraphNode<T>*> getShortestPath(const T& start, const T& end);

    GraphNode<T>* getNode(const T& data) const;

    void AddNode(const T& data);
    void clear();
    
    int size();

    virtual bool AddEdge(const T& from, const T& to);
    virtual bool removeNode(const T& data);
    virtual bool removeEdge(const T& from, const T& to);
    virtual bool isConnected();

};

template<typename T>
inline Graph<T>::Graph(): Nodes()
{
}

template<typename T>
inline Graph<T>::Graph(const Graph& other): Nodes() {
    for (auto node : other.Nodes) {
        GraphNode<T>* newNode = new GraphNode<T>(*node);
        Nodes.insert(newNode);

        for (auto connection : node->getConnections()) {
            GraphNode<T>* newConnection = nullptr;
            for (auto otherNode : other.Nodes) {
                if (otherNode->getData() == connection->getData()) {
                    newConnection = otherNode;
                    break;
                }
            }
            if (newConnection) {
                newNode->MakeConnection(newConnection->getData());
                newConnection->MakeConnection(newNode->getData());
            }
        }
    }
}
template<typename T>
inline Graph<T>::~Graph()
{
    this->clear();
}
template<typename T>
inline Graph<T>& Graph<T>::operator=(const Graph<T>& other)
{
    for (auto node : other.Nodes) {
        GraphNode<T>* newNode = new GraphNode<T>(*node);
        Nodes.insert(newNode);

        for (auto connection : node->getConnections()) {
            GraphNode<T>* newConnection = nullptr;
            for (auto otherNode : other.Nodes) {
                if (otherNode->getData() == connection->getData()) {
                    newConnection = otherNode;
                    break;
                }
            }
            if (newConnection) {
                newNode->MakeConnection(newConnection->getData());
                newConnection->MakeConnection(newNode->getData());
            }
        }
    }
}

template<typename T>
inline std::list<T> Graph<T>::FromPointersToData(const std::list<GraphNode<T>*>& pointers)
{
    std::list<T> result;
    
    for (GraphNode<T>* node : pointers) {
        result.push_back(node->getData());
    }
    return result;
}

template<typename T>
inline std::list<GraphNode<T>*> Graph<T>::getNodes() const
{
    std::list<GraphNode<T>*> nodes;
    for (GraphNode<T>* node : Nodes)
        nodes.push_back(node);
    return nodes;
}

template<typename T>
inline std::list<GraphNode<T>*> Graph<T>::getNeighbors(const T& data)
{
    for (auto iter : Nodes) {
        if (iter->getData() == data) {
            return iter->getConnections();
        }
    }
    return std::list<GraphNode<T>*>();
}

template<typename T>
inline std::list<GraphNode<T>*> Graph<T>::breadthFirstSearch(const T& start)
{
    for (auto iter : Nodes) {
        if (iter->getData() == start) {
            return iter->breadthFirstSearch();
        }
    }
    return std::list<GraphNode<T>*>();
}

template<typename T>
inline std::list<GraphNode<T>*> Graph<T>::depthFirstSearch(const T& start)
{
    for (auto node : Nodes) {
        if (node->getData() == start) {
            return node->depthFirstSearch();
        }
    }
    return std::list<GraphNode<T>*>();
}

template<typename T>
inline std::list<GraphNode<T>*> Graph<T>::getShortestPath(const T& start, const T& end)
{   
    GraphNode<T>* StartNode = getNode(start);
    GraphNode<T>* EndNode = getNode(end);
    if ((StartNode && EndNode) && (StartNode != EndNode)) {
        return StartNode->ShortestPath(EndNode);
    }
    return std::list<GraphNode<T>*>();
}

template<typename T>
inline GraphNode<T>* Graph<T>::getNode(const T& data) const
{
    for (auto node : Nodes) {
        if (node->getData() == data)
            return node;
    }
    return nullptr;
}

template<typename T>
inline void Graph<T>::AddNode(const T& data)
{
    for (auto it : Nodes) {
        if (it->getData() == data)return;
    }
    Nodes.insert(new GraphNode<T>(data));
}

template<typename T>
inline void Graph<T>::clear()
{
    for (auto node : Nodes) {
        delete node;
    }
    Nodes.clear();

}

template<typename T>
inline int Graph<T>::size()
{
    return Nodes.size();
}

template<typename T>
inline bool Graph<T>::AddEdge(const T& from, const T& to)
{
    GraphNode<T>* fromNode = getNode(from);
    GraphNode<T>* toNode = getNode(to);

    if (fromNode && toNode) {
        if (!fromNode->HasConnection(toNode)) {
            fromNode->MakeConnection(toNode);
            toNode->MakeConnection(fromNode);
        }
        return true;
    }
    return false;
}

template<typename T>
inline bool Graph<T>::removeNode(const T& data)
{
    for (GraphNode<T>* node : Nodes) {
        if (node->getData() == data) {
            Nodes.erase(Nodes.find(node));
            delete node;
            return true;
        }
    }
    return false;
}

template<typename T>
inline bool Graph<T>::removeEdge(const T& from, const T& to)
{
    GraphNode<T>* fromNode = getNode(from);
    GraphNode<T>* toNode = getNode(to);

    if (fromNode && toNode) {
        if (fromNode->HasConnection(toNode)) {
            if (fromNode->DeleteConnection(toNode) && toNode->DeleteConnection(fromNode))
                return true;
        }
    }
    return false;
}

template<typename T>
inline bool Graph<T>::isConnected()
{
    for (auto iter : Nodes) {
        if (iter->SizeConnectedNodes() == Nodes.size())
            return true;
        return false;
    }
}

template<typename T>
inline Graph<T>::Graph(T data_): Nodes()
{
	Nodes.insert(new GraphNode<T>(data_));
}
