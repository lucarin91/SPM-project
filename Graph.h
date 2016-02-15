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

typedef unordered_set<int> t_type_in;
typedef int t_type_out;

typedef vector<Token> t_in;
typedef Token t_out;
typedef function<t_out(t_in)> fun;

struct Statement {
    fun f;
    t_type_in in;
    t_type_out out;
    int miss;
    const int &id;

    Statement(fun f, t_type_in in, t_type_out out) :
            id(_id), _id(_ID++),
            f(f),
            in(in),
            out(out),
            miss(in.size()) { };
private:
    static int _ID;
    int _id;
};

class Graph {
    Graph(const Graph &) = delete;

    Graph &operator=(Graph const &) = delete;

    vector<Statement> _ist;
    t_type_in _t_in;
    t_type_in _t_out;

    static int _ID;
    int _id;

    void _update_t_in_out(const t_type_in&, const t_type_out&);

public:
    Graph(Graph &g): id(_id), ist(_ist), t_in(_t_in), t_out(_t_out),
                           _id(g._id), _ist(g._ist), _t_in(g._t_in), _t_out(g._t_out) { }

    Graph(Graph &&g) : id(_id), ist(_ist), t_in(_t_in), t_out(_t_out),
                       _ist(move(g._ist)),
                       _id(move(g._id)),
                       _t_in(move(g._t_in)),
                       _t_out(move(g._t_out)) { }

    Graph() : id(_id), ist(_ist), _id(_ID++), t_in(_t_in), t_out(_t_out) { }

    Graph(initializer_list<Statement>);

    ~Graph(){

    }

    const int &id;
    const vector<Statement> &ist;
    const t_type_in &t_in;
    const t_type_in &t_out;

    void add(fun, initializer_list<int>, int);
};


#endif //SPM_PROJECT_GRAPH_H
