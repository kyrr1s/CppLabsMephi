#pragma once

#include <vector>
#include <cstdlib>
#include <iostream>
#include <list>
#include <stack>
#include <fstream>



// Forward declaration of Edge class
template <class T>
class Edge;


///     This class represents a general graph. This graph is implemented
///     in an adjacency list format.
template <class T>
class Graph {

protected:
    /// 'Adjacency list'
    std::vector<std::vector<Edge<T>>> adj_list;

    /// Number of nodes
    unsigned int N;

public:
    /// Default constructor and parameterized constructor
    Graph():N(0) { };

    Graph(std::vector<Edge<T>> in_vec, unsigned int size):N(size) {
        adj_list.resize(size);
        for (unsigned int i = 0; i < in_vec.size(); i++) {
            add_edge(in_vec[i]);
        }
    };


    /// Add an edge to the graph (with two additional overloads)
    void add_edge(Edge<T> new_edge) {
        // Due to the adjacency list representation, each 'node' is considered
        // to be an integer between 0 and the length of the adjacency list. The
        // nodes must be continuous, because we cannot leave a gap in our adjacency
        // list, at least as it is currently implemented with vectors.

        // If either node is not included in the adjacency list, resize
        while (new_edge.source >= N || new_edge.destination >= N) {
            adj_list.resize(N + 1);
            N++;
        }

        // Add the new edge
        this->adj_list[new_edge.source].push_back(new_edge);
    }

    void add_edge(unsigned int source, unsigned int destination, T metadata) {
        // If either node is not included in the adjacency list, resize
        while (source >= N || destination >= N) {
            this->adj_list.resize(this->N + 1);
            N++;
        }

        // Add the new edge
        auto* temp = new Edge<T>;
        temp->source = source;
        temp->destination = destination;
        temp->data = metadata;

    }

    /// Search algorithm to find a path through the maze
    std::list<unsigned int> run_algorithm(unsigned int start_node, unsigned int end_node) {
        // CREATE STACK
        std::stack<unsigned int> start_stack;
        start_stack.push(start_node);

        // CREATE LIST OF VISITED NODES ("PATH")
        std::list<unsigned int> path;

        // CALL DFS FUNCTION
        return DFS(start_stack, path, end_node);
    }

    /// Depth first search algorithm
    std::list<unsigned int> DFS(std::stack<unsigned int> in_stack, std::list<unsigned int> path, unsigned int end_node) {
        // Stores current node
        unsigned int curr_node = 0;

        // Check if the stack is empty (occurrs when we reach the end of a path without finding the end node)
        if (in_stack.empty()) {
            return *(new std::list<unsigned int>);
        }

        // Add top stack element to path
        path.push_back(in_stack.top());

        // Check to see if we have reached the end node
        if (in_stack.top() == end_node) {
            return path;
        }

        // Remove top stack element
        curr_node = in_stack.top();
        in_stack.pop();

        int run = 1;
        // Add nodes connected to the node we just removed
        // If we have more than one path, create a new stack for each path so that we can try all of them
        for (auto & i : this->adj_list[curr_node]) {
            // Check to see if we have already seen the node we are about to add
            run = 1;
            for (unsigned int & k : path) {
                if (k == i.destination) {
                    run = 0;
                }
            }
            if (run == 1) {
                // If we have not already visited this node:
                in_stack.push(i.destination);
                std::list<unsigned int> path_temp = DFS(in_stack, path, end_node);

                // If this resursive call found the end node, return this path!
                if (!path_temp.empty()) {
                    return path_temp;
                }
            }
        }

        // If no path is return yet (the maze is unsolvable):
        return *(new std::list<unsigned int>);
    }

    /// Print the graph.
    void print_graph() {
        for (auto & i : this->adj_list) {
            for (auto & j : i) {
                std::cout << "Source: " << j.source << " Destination: " << j.destination << std::endl;
            }
        }
    }
};

/// This class represents the edges of the graph.
template <class T>
class Edge {
public:
    int source, destination;
    std::pair<T,T> data;
};

