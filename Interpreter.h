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

using namespace std;
typedef function<void(shared_ptr<Token>)> Drainer;

class Interpreter {
    Interpreter(Interpreter const &) = delete;

    Interpreter(Interpreter &) = delete;

    Interpreter &operator=(Interpreter const &) = delete;

public:
    ~Interpreter() { }

    Interpreter(shared_ptr<Graph> g) : _g(g),
                                   //_t_in(_g.t_in),
                                   _token_mutex(new mutex()),
                                   _t_in_mutex(new mutex()) { }

    Interpreter(Interpreter &&in) : _g(move(in._g)),
                                    //_t_in(move(in._t_in)),
                                    _token(move(in._token)),
                                    _token_mutex(move(in._token_mutex)),
                                    _t_in_mutex(move(in._t_in_mutex)),
                                    _fired_stm(move(in._fired_stm)) { }

    //void start(initializer_list<shared_ptr<Token>>, Drainer);
    void start(t_in, Drainer);

private:
    shared_ptr<Graph> _g;
    //shared_ptr<t_type_in> _t_in;
    unique_ptr<mutex> _t_in_mutex;

    unordered_map<int, shared_ptr<Token>> _token;
    unique_ptr<mutex> _token_mutex;

    //unordered_map<int, vector<int>> _token_to_stm;
    unordered_set<int> _fired_stm;

    void _check_token_mutex(function<void()> f);

    //void _start(Drainer function1);
    //shared_ptr<Token> _get_token_type(int);

    void _body_thread(fun, t_in, Drainer);
};


#endif //SPM_PROJECT_INTERPRETER_H
