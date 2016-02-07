//
// Created by luca on 07/02/2016.
//


#include "GraphRepository.h"

void GraphRepository::add(string name, Graph g){
    _graph.insert(make_pair(move(name), move(g)));
}

void GraphRepository::add(string name, initializer_list<Statement> in_list){
    Graph g(in_list);
    _graph.insert(make_pair(move(name), move(g)));
}