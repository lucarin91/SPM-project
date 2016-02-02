//
// Created by luca on 22/12/15.
//

#ifndef SPM_PROJECT_MACRODATAFLOW_H
#define SPM_PROJECT_MACRODATAFLOW_H

#include <functional>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include "Token.h"

using namespace std;
typedef std::function<void(std::vector<shared_ptr<Token>>,std::shared_ptr<Token>)> fun;
typedef std::vector<std::shared_ptr<Token>> t_in;
typedef std::shared_ptr<Token> t_out;

struct Statement {
    fun f;
    t_in in;
    t_out out;
    bool fired;

    Statement(fun f, t_in in, t_out out) :
            f(f),
            in(in),
            out(out),
            fired(false) { };
};

class MacroDataFlow {
    MacroDataFlow(MacroDataFlow const &) = delete;

    MacroDataFlow(MacroDataFlow &) = delete;

    MacroDataFlow &operator=(MacroDataFlow const &) = delete;

private:
    unordered_map<int, shared_ptr<Token>> token;
    unordered_map<int, vector<int>> token_to_stm;
    unordered_set<int> ready_stm;
    vector<Statement> stm;

    void updateTokenMap(shared_ptr<Token>);
    void updateTokenToStm(int,int);
    bool checkInputToken(t_in&);

public:
    MacroDataFlow() { };

    void add(fun, initializer_list<Token>, Token);

    t_in start();
};


#endif //SPM_PROJECT_MACRODATAFLOW_H
