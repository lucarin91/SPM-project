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

    unordered_map<string, Graph> _graph;


public:
    GraphRepository() : graph(_graph) { }

    void add(string, Graph);

    void add(string, initializer_list<Statement>);

    const unordered_map<string, Graph> &graph;

};


#endif //SPM_PROJECT_GRAPHREPOSITORY_H
