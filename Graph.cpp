//
// Created by luca on 22/12/15.
//

#include "Graph.h"

// PUBLIC
Graph::Graph(initializer_list<Statement> in_list) : Graph() {
    for (auto &item : in_list){
        _update_t_in_out(item.in, item.out);
        _ist.push_back(move(item));
    }
}

void Graph::add(fun f, initializer_list<int> in_list, int out) {
    t_type_in in_vec(in_list);

    _update_t_in_out(t_type_in(in_list), out);

    _ist.push_back(Statement(move(f), move(in_vec), out));
}

// PRIVATE
int Graph::_ID = 1;

void Graph::_update_t_in_out(const t_type_in &in, const t_type_out &out) {
//    auto got = _t_in.find(out);
//    if (got != _t_in.end())
//        _t_in.erase(out);
//    _t_out.insert(out);
//
//    for (const auto& item : in){
//        auto got = _t_out.find(item);
//        if (got != _t_out.end())
//            _t_out.erase(item);
//        _t_in.insert(item);
//    }

    for (const auto& item : in){
        _t_in.insert(item);
        _t_out.erase(item);
    }
    _t_out.insert(out);
}
