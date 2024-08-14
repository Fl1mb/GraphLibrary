#pragma once
#include <cassert>
#include "OrientedGraph.h"

namespace COMMON_GRAPH {
    void testGraphConstruction() {
        Graph<int> graph;
        assert(graph.size() == 0);

        Graph<int> graph2(1);
        assert(graph2.size() == 1);
        assert(graph2.getNode(1) != nullptr);
    }

    void testAddNode() {
        Graph<int> graph;
        graph.AddNode(1);
        assert(graph.size() == 1);
        assert(graph.getNode(1) != nullptr);

        graph.AddNode(2);
        assert(graph.size() == 2);
        assert(graph.getNode(2) != nullptr);
    }

    void testAddEdge() {
        Graph<int> graph;
        graph.AddNode(1);
        graph.AddNode(2);
        assert(graph.AddEdge(1, 2));
        assert(graph.getNode(1)->HasConnection(graph.getNode(2)));
        assert(graph.getNode(2)->HasConnection(graph.getNode(1)));
    }

    void testGetNeighbors() {
        Graph<int> graph;
        graph.AddNode(1);
        graph.AddNode(2);
        graph.AddNode(3);
        graph.AddEdge(1, 2);
        graph.AddEdge(1, 3);

        std::list<GraphNode<int>*> neighbors = graph.getNeighbors(1);
        assert(neighbors.size() == 2);
        assert(std::find(neighbors.begin(), neighbors.end(), graph.getNode(2)) != neighbors.end());
        assert(std::find(neighbors.begin(), neighbors.end(), graph.getNode(3)) != neighbors.end());
    }

    void testBreadthFirstSearch() {
        Graph<int> graph;
        graph.AddNode(1);
        graph.AddNode(2);
        graph.AddNode(3);
        graph.AddNode(4);
        graph.AddEdge(1, 2);
        graph.AddEdge(1, 3);
        graph.AddEdge(2, 4);

        std::list<GraphNode<int>*> bfs = graph.breadthFirstSearch(1);
        assert(bfs.size() == 4);
        assert(std::find(bfs.begin(), bfs.end(), graph.getNode(1)) != bfs.end());
        assert(std::find(bfs.begin(), bfs.end(), graph.getNode(2)) != bfs.end());
        assert(std::find(bfs.begin(), bfs.end(), graph.getNode(3)) != bfs.end());
        assert(std::find(bfs.begin(), bfs.end(), graph.getNode(4)) != bfs.end());
    }

    void testDepthFirstSearch() {
        Graph<int> graph;
        graph.AddNode(1);
        graph.AddNode(2);
        graph.AddNode(3);
        graph.AddNode(4);
        graph.AddEdge(1, 2);
        graph.AddEdge(1, 3);
        graph.AddEdge(2, 4);

        std::list<GraphNode<int>*> dfs = graph.depthFirstSearch(1);
        assert(dfs.size() == 4);
        assert(std::find(dfs.begin(), dfs.end(), graph.getNode(1)) != dfs.end());
        assert(std::find(dfs.begin(), dfs.end(), graph.getNode(2)) != dfs.end());
        assert(std::find(dfs.begin(), dfs.end(), graph.getNode(3)) != dfs.end());
        assert(std::find(dfs.begin(), dfs.end(), graph.getNode(4)) != dfs.end());
    }

    void testGetShortestPath() {
        Graph<int> graph;
        graph.AddNode(1);
        graph.AddNode(2);
        graph.AddNode(3);
        graph.AddNode(4);
        graph.AddEdge(1, 2);
        graph.AddEdge(1, 3);
        graph.AddEdge(2, 4);

        std::list<GraphNode<int>*> shortestPath = graph.getShortestPath(1, 4);
        assert(shortestPath.size() == 3);
        assert(std::find(shortestPath.begin(), shortestPath.end(), graph.getNode(1)) != shortestPath.end());
        assert(std::find(shortestPath.begin(), shortestPath.end(), graph.getNode(2)) != shortestPath.end());
        assert(std::find(shortestPath.begin(), shortestPath.end(), graph.getNode(4)) != shortestPath.end());
    }

    void testRemoveNode() {
        Graph<int> graph;
        graph.AddNode(1);
        graph.AddNode(2);
        graph.AddEdge(1, 2);

        assert(graph.removeNode(1));
        assert(graph.size() == 1);
        assert(graph.getNode(1) == nullptr);
    }

    void testRemoveEdge() {
        Graph<int> graph;
        graph.AddNode(1);
        graph.AddNode(2);
        graph.AddEdge(1, 2);

        assert(graph.removeEdge(1, 2));
        assert(!graph.getNode(1)->HasConnection(graph.getNode(2)));
    }

    void MakeTest() {
        testGraphConstruction();
        testAddNode();
        testAddEdge();
        testGetNeighbors();
        testBreadthFirstSearch();
        testDepthFirstSearch();
        testGetShortestPath();
        testRemoveNode();
        testRemoveEdge();
    }
}


namespace ORIENTED_GRAPH {
    void testOrientedGraphConstruction() {
        OrientedGraph<int> graph;
        assert(graph.size() == 0);

        OrientedGraph<int> graph2(1);
        assert(graph2.size() == 1);
        assert(graph2.getNode(1) != nullptr);
    }

    void testAddEdge() {
        OrientedGraph<int> graph;
        graph.AddNode(1);
        graph.AddNode(2);
        assert(graph.AddEdge(1, 2));
        assert(graph.getNode(1)->HasConnection(graph.getNode(2)));
        assert(!graph.getNode(2)->HasConnection(graph.getNode(1)));
    }

    void testIsConnected() {
        OrientedGraph<int> graph;
        graph.AddNode(1);
        graph.AddNode(2);
        graph.AddNode(3);
        graph.AddEdge(1, 2);
        graph.AddEdge(2, 3);
        graph.AddEdge(3, 1);
        assert(graph.isConnected());

        graph.AddNode(4);
        assert(!graph.isConnected());
    }

    void testRemoveNode() {
        OrientedGraph<int> graph;
        graph.AddNode(1);
        graph.AddNode(2);
        graph.AddEdge(1, 2);
        assert(graph.removeNode(1));
        assert(graph.size() == 1);
        assert(graph.getNode(1) == nullptr);
    }

    void testRemoveEdge() {
        OrientedGraph<int> graph;
        graph.AddNode(1);
        graph.AddNode(2);
        graph.AddEdge(1, 2);
        assert(graph.removeEdge(1, 2));
        assert(!graph.getNode(1)->HasConnection(graph.getNode(2)));
    }

    void testGraphTraversal() {
        OrientedGraph<int> graph;
        graph.AddNode(1);
        graph.AddNode(2);
        graph.AddNode(3);
        graph.AddNode(4);
        graph.AddNode(5);
        graph.AddEdge(1, 2);
        graph.AddEdge(1, 3);
        graph.AddEdge(2, 4);
        graph.AddEdge(3, 4);
        graph.AddEdge(4, 5);

        std::list<int> expectedOrder = { 1, 2, 4, 5, 3 };
        std::list<int> actual = Graph<int>::FromPointersToData(graph.depthFirstSearch(1));
        assert(actual == expectedOrder);
    }

    void MAKE_TEST() {
        testOrientedGraphConstruction();
        testAddEdge();
        testIsConnected();
        testRemoveNode();
        testRemoveEdge();
    }
}