//
// Created by luca on 22/12/15.
//

#ifndef SPM_PROJECT_MACRODATAFLOW_H
#define SPM_PROJECT_MACRODATAFLOW_H

#include <functional>
#include <vector>
#include <memory>
#include <unordered_map>
#include "Token.h"

using namespace std;
typedef std::function<Token(std::vector<shared_ptr<Token>>,shared_ptr<Token>)> fun;
typedef std::vector<shared_ptr<Token>> t_vec;

struct Statement {
    fun f;
    t_vec in;
    shared_ptr<Token> out;

    Statement(fun f, t_vec in, shared_ptr<Token> out) :
            f(f),
            in(in),
            out(out) { };
};

class MacroDataFlow {
    MacroDataFlow(MacroDataFlow const &) = delete;

    MacroDataFlow(MacroDataFlow &) = delete;

    MacroDataFlow &operator=(MacroDataFlow const &) = delete;

private:
    unordered_map<int, shared_ptr<Token>> token;
    unordered_map<int, Statement> stm;

    void updateMap(Token&);

public:
    MacroDataFlow() { };

    void add(fun, vector<shared_ptr<Token>>, shared_ptr<Token>);

    t_vec start();
};


#endif //SPM_PROJECT_MACRODATAFLOW_H
