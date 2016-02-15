//
// Created by luca on 07/02/2016.
//

#ifndef SPM_PROJECT_INTERPRETER_H
#define SPM_PROJECT_INTERPRETER_H

#include <thread>
#include <iostream>
#include <mutex>
#include <atomic>
#include "GraphRepository.h"
#include "InterpreterFactory.h"
#include "ThreadPool.h"

using namespace std;
typedef function<void(Token&)> Drainer;

class Interpreter : public enable_shared_from_this<Interpreter> {
    Interpreter(Interpreter const &) = delete;

    Interpreter(Interpreter &) = delete;
    Interpreter(Interpreter &&) = delete;

    Interpreter &operator=(Interpreter const &) = delete;

public:
    ~Interpreter() {

    }

    Interpreter(ThreadPool& _tp, shared_ptr<Graph> g, initializer_list<Token>&&, Drainer&& d);

//    Interpreter(Interpreter &&in) : _g(move(in._g)),
//                                    _tp(move(in._tp)),
//                                    _drainer(move(in._drainer)),
//                                    _token(move(in._token)),
//                                    _token_mutex(move(in._token_mutex)),
//                                    _fired_stm(move(in._fired_stm)) { }

    //void start(initializer_list<shared_ptr<Token>>, Drainer);
    //void start(t_in);

    void eval();


private:
    ThreadPool& _tp;
    shared_ptr<Graph> _g;
    Drainer _drainer;

    unordered_map<int, Token> _token;
    unique_ptr<mutex> _token_mutex;

    //unordered_map<int, vector<int>> _token_to_stm;
    unordered_set<int> _fired_stm;

    void _check_token_mutex(function<void()> f);
    //shared_ptr<Token> _get_token_type(int);

    void _exec_function(fun, t_in);
};


#endif //SPM_PROJECT_INTERPRETER_H
