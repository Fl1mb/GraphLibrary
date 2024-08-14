#pragma once
#include "Graph.h"
#include <stdexcept>

template<typename T>
class OrientedGraph : public Graph<T> {
public:
	OrientedGraph();
	OrientedGraph(T data_);
	OrientedGraph(const OrientedGraph& other);
	~OrientedGraph();

	virtual bool AddEdge(const T& from, const T& to) override;
    virtual bool isConnected() override;
    virtual bool removeNode(const T& data) override;
    virtual bool removeEdge(const T& from, const T& to) override;

};

template<typename T>
inline OrientedGraph<T>::OrientedGraph(): Graph<T>()
{}

template<typename T>
inline OrientedGraph<T>::OrientedGraph(T data_) : Graph<T>(data_)
{
}

template<typename T>
inline OrientedGraph<T>::OrientedGraph(const OrientedGraph& other): Graph<T>(other)
{
}

template<typename T>
inline OrientedGraph<T>::~OrientedGraph()
{}

template<typename T>
inline bool OrientedGraph<T>::AddEdge(const T & from, const T & to)
{
    GraphNode<T>* fromNode = Graph<T>::getNode(from);
    GraphNode<T>* toNode = Graph<T>::getNode(to);

    if (fromNode && toNode) {
        if (!fromNode->HasConnection(toNode)) {
            fromNode->MakeConnection(toNode);
        }
        return true;
    }
    return false;
}

template<typename T>
inline bool OrientedGraph<T>::isConnected()
{
    for (auto iter : Graph<T>::Nodes) {
        for (auto other : Graph<T>::Nodes) {
            if (iter != other) {
                if (!iter->HasPathTo(other) || !other->HasPathTo(iter)) {
                    return false;
                }
            }
        }
    }
    return true;
}

template<typename T>
inline bool OrientedGraph<T>::removeNode(const T& data) {
    for (auto iter = Graph<T>::Nodes.begin(); iter != Graph<T>::Nodes.end(); ++iter) {
        if ((*iter)->getData() == data) {
            // Remove connections to this node from other nodes
            for (auto otherIter = Graph<T>::Nodes.begin(); otherIter != Graph<T>::Nodes.end(); ++otherIter) {
                if (*otherIter != *iter) {
                    (*otherIter)->DeleteConnection(*iter);
                }
            }

            // Remove the node from the graph
            delete* iter;
            Graph<T>::Nodes.erase(iter);
            return true;
        }
    }
    return false;
}

template<typename T>
inline bool OrientedGraph<T>::removeEdge(const T& from, const T& to)
{
    GraphNode<T>* fromNode = Graph<T>::getNode(from);
    GraphNode<T>* toNode = Graph<T>::getNode(to);

    if (fromNode && toNode) {
        if (fromNode->HasConnection(toNode)) {
            if (fromNode->DeleteConnection(toNode))
                return true;
        }
    }
    return false;
}
