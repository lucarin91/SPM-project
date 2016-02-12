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

using namespace std;
//class Interpreter;

//typedef function<void(Interpreter&)> Streamer;
typedef function<void(shared_ptr<Token>)> Drainer;

class InterpreterFactory {
    InterpreterFactory(InterpreterFactory const &) = delete;

    InterpreterFactory(InterpreterFactory &) = delete;

    InterpreterFactory(InterpreterFactory &&) = delete;

    InterpreterFactory &operator=(InterpreterFactory const &) = delete;

    vector<thread> _int_thread;

    const GraphRepository &_gr;

public:
    InterpreterFactory(const GraphRepository &g) : _gr(g) { }

    void start(string name, initializer_list<shared_ptr<Token>>, Drainer);

    ~InterpreterFactory();

    class Interpreter {
        Interpreter(Interpreter const &) = delete;

        Interpreter(Interpreter &) = delete;

        Interpreter &operator=(Interpreter const &) = delete;

    public:
        Interpreter(const Graph &_g) : _g(_g),
                                       _n_thread(new atomic<int>(0)),
                                       _token_mutex(new mutex()) { }

        Interpreter(Interpreter &&in) : _g(move(in._g)),
                                        _token(move(in._token)),
                                        _token_mutex(move(in._token_mutex)),
                                        _fired_stm(move(in._fired_stm)),
                                        _n_thread(move(in._n_thread)) { }

        //void start(initializer_list<shared_ptr<Token>>, Drainer);
        void start(t_in, Drainer);

    private:
        const Graph &_g;

        unordered_map<int, shared_ptr<Token>> _token;
        unique_ptr<mutex> _token_mutex;

        //unordered_map<int, vector<int>> _token_to_stm;
        unordered_set<int> _fired_stm;

        unique_ptr<atomic<int>> _n_thread;

        void _check_token_mutex(function<void()> f);

        //void _start(Drainer function1);
        //shared_ptr<Token> _get_token_type(int);

        void _body_thread(fun, t_in, Drainer);
    };


};

#endif //SPM_PROJECT_INTERPRETER_H
