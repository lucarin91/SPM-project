//
// Created by luca on 22/12/15.
//

#include "Graph.h"

// PUBLIC
Graph::Graph(initializer_list<Statement> in_list) : Graph() {
    for (auto &item : in_list){
        _ist.push_back(move(item));
    }
}

void Graph::add(fun f, initializer_list<int> in_list, int out) {
    t_type_in in_vec;
    for (auto item : in_list){
        in_vec.push_back(item);
    }

    _ist.push_back(Statement(move(f), move(in_vec), out));
}

// PRIVATE
int Graph::_ID = 1;
