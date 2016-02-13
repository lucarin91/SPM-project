//
// Created by luca on 07/02/2016.
//

#ifndef SPM_PROJECT_GRAPHREPOSITORY_H
#define SPM_PROJECT_GRAPHREPOSITORY_H


#include <string>
#include "Graph.h"
using namespace std;

class GraphRepository {
    GraphRepository(GraphRepository const &) = delete;

    GraphRepository(GraphRepository &) = delete;

    GraphRepository &operator=(GraphRepository const &) = delete;

    unordered_map<string, shared_ptr<Graph>> _graph;


public:
    GraphRepository() : graph(_graph) { }

    void add(string, shared_ptr<Graph>);

    void add(string, initializer_list<Statement>);

    const unordered_map<string, shared_ptr<Graph>> &graph;
    ~GraphRepository(){

    }
};


#endif //SPM_PROJECT_GRAPHREPOSITORY_H
