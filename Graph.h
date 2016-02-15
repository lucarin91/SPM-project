//
// Created by luca on 22/12/15.
//

#ifndef SPM_PROJECT_GRAPH_H
#define SPM_PROJECT_GRAPH_H

#include <functional>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include "Token.h"

using namespace std;

typedef vector<shared_ptr<Token>> t_in;
typedef shared_ptr<Token> t_out;

typedef unordered_set<int> t_type_in;
typedef int t_type_out;

typedef std::function<t_out(t_in)> fun;

struct Statement {
    fun f;
    t_type_in in;
    t_type_out out;
    const int &id;

    Statement(fun f, t_type_in in, t_type_out out) :
            id(_id), _id(_ID++),
            f(f),
            in(in),
            out(out) { };

    Statement &operator=(const Statement &s) {
        f = s.f;
        in = s.in;
        out = s.out;
        return *this;
    }

private:
    static int _ID;
    int _id;
};

class Graph {
    Graph(const Graph &) = delete;

    Graph &operator=(Graph const &) = delete;

    vector<Statement> _ist;
    unordered_map<int, vector<int>> _token_to_ist;
    t_type_in _t_in;
    t_type_in _t_out;


    static int _ID;
    int _id;

    void _update_t_in_out(const t_type_in &, const t_type_out &);
    void _update_token_to_ist(int stm_id, t_type_in in);

public:
    Graph(Graph &g) : Graph() {
        _ist = g._ist;
        _id = g._id;
        _t_in = g._t_in;
        _t_out = g._t_out;
        _token_to_ist = g._token_to_ist;
    }

    Graph(Graph &&g) : Graph() {
        _ist = move(g._ist);
        _id = move(g._id);
        _t_in = move(g._t_in);
        _t_out = move(g._t_out);
        _token_to_ist = move(g._token_to_ist);
    }

    Graph() : id(_id), ist(_ist), _id(_ID++), t_in(_t_in), t_out(_t_out), token_to_ist(_token_to_ist) { }

    Graph(initializer_list<Statement>);

    ~Graph() {

    }

    const int &id;
    const vector<Statement> &ist;
    const unordered_map<int, vector<int>> &token_to_ist;
    const t_type_in &t_in;
    const t_type_in &t_out;

    void add(fun, initializer_list<int>, int);
};


#endif //SPM_PROJECT_GRAPH_H
