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
typedef function<void(shared_ptr<Token>)> Drainer;

class Interpreter : public enable_shared_from_this<Interpreter> {
    Interpreter(Interpreter const&) = delete;
    Interpreter(Interpreter &&) = delete;

    Interpreter &operator=(Interpreter const &) = delete;

public:
    ~Interpreter() { }

    Interpreter(ThreadPool& _tp, shared_ptr<Graph> g, initializer_list<shared_ptr<Token>>&&, Drainer&& d);

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

    unordered_map<int, shared_ptr<Token>> _token;
    unique_ptr<mutex> _token_mutex;

    vector<int> _count_ist;
    unique_ptr<mutex> _count_ist_mutex;
    //unordered_set<int> _fired_ist;

    void _check_token_mutex(function<void()> f);
    void _check_ready_ist_mutex(function<void()> f);
    void _fire_ist(int);

    void _exec_function(fun, t_in);
};


#endif //SPM_PROJECT_INTERPRETER_H
