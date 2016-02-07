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

typedef vector<int> t_type_in;
typedef int t_type_out;

typedef std::function<t_out(t_in)> fun;

struct Statement {
    fun f;
    t_type_in in;
    t_type_out out;
    int miss;

    Statement(fun f, t_type_in in, t_type_out out) :
            f(f),
            in(in),
            out(out),
            miss(in.size()) { };
};

class Graph {
    Graph(Graph const &) = delete;
    Graph(Graph &) = delete;
    Graph &operator=(Graph const &) = delete;

    vector<Statement> _ist;
    static int _ID;
    int _id;

public:
    Graph(Graph&& g) : id(_id), ist(_ist),
                       _ist(move(g._ist)),
                      _id(move(g._id)) { }

    Graph(): id(_id), ist(_ist), _id(_ID++){ }
    Graph(initializer_list<Statement>);

    const int &id;
    const vector<Statement> &ist;

    void add(fun, initializer_list<int>, int);
};


#endif //SPM_PROJECT_GRAPH_H
