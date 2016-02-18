//
// Created by luca on 22/12/15.
//

#include "Graph.h"

// PUBLIC
Graph::Graph(initializer_list<Statement> in_list) : Graph() {
    for (auto &item : in_list) {
        _update_t_in_out(item.in, item.out);
        _ist.push_back(move(item));
        _update_token_to_ist(_ist.size() - 1, item.in);
    }
}

void Graph::add(fun f, initializer_list<int> in_list, int out) {
    t_type_in in_vec(in_list);
    _update_t_in_out(t_type_in(in_list), out);
    _ist.push_back(Statement(move(f), move(in_vec), out));
    _update_token_to_ist(_ist.size() - 1, in_vec);
}

// PRIVATE
int Graph::_ID = 1;
int Statement::_ID = 1;

void Graph::_update_t_in_out(const t_type_in &in, const t_type_out &out) {
    _t_out.insert(out);
    for (const auto &item : in) {
        _t_in.insert(item);
        _t_out.erase(item);
    }

}

void Graph::_update_token_to_ist(int stm_id, t_type_in in) {
    for (auto &t : in) {
        auto got = _token_to_ist.find(t);
        if (got == _token_to_ist.end()) {
            auto v = vector<int>();
            v.push_back(stm_id);
            _token_to_ist[t] = move(v);
        } else {
            got->second.push_back(stm_id);
        }
    }
}
