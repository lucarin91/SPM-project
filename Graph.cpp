//
// Created by luca on 22/12/15.
//

#include "Graph.h"

// PUBLIC
Graph::Graph(initializer_list<shared_ptr<Statement>> in_list) : Graph() {
    for (auto &item : in_list){
        _update_t_in_out(*item);
        _ist.push_back(move(item));
    }
}

//void Graph::add(fun f, initializer_list<int> in_list, int out) {
//    t_type_in in_vec(in_list);
//    Statement stm(move(f), move(in_vec), out);
//    _update_t_in_out(stm);
//    _ist.push_back(move(stm));
//}

// PRIVATE
int Graph::_ID = 1;
int Statement::_ID = 1;

void Graph::_update_t_in_out(const Statement &stm) {
    for (auto& id : stm.in)
        _t_in.emplace(id);
}
