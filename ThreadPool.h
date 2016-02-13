//
// Created by luca on 12/02/2016.
//

#ifndef SPM_PROJECT_THREADPOOL_H
#define SPM_PROJECT_THREADPOOL_H

#include <iostream>
#include <memory>
#include <future>
#include <vector>
#include "InterpreterFactory.h"
#include "Interpreter.h"
#include "Token.h"
#include "Graph.h"

using namespace std;
typedef function<void(shared_ptr<Token>)> Drainer;

struct eval_task{
    shared_ptr<Interpreter> inter;
    t_in input;
    Drainer drainer;

    eval_task(shared_ptr<Interpreter> i, t_in in, Drainer d) : inter(i),
                                                   input(in),
                                                   drainer(d) { }

    eval_task(eval_task&& t) : inter(move(t.inter)),
                               input(move(t.input)),
                               drainer(move(t.drainer)) { }
};

struct exec_task{
    shared_ptr<Interpreter> inter;
    fun f;
    t_in input;
    Drainer drainer;

    exec_task(shared_ptr<Interpreter> i, fun _f, t_in in, Drainer d) : inter(i),
                                                           f(_f),
                                                           input(in),
                                                           drainer(d) { }

    exec_task(exec_task&& t) : inter(move(t.inter)),
                               f(move(t.f)),
                               input(move(t.input)),
                               drainer(move(t.drainer)) { }
};


class ThreadPool {
    ThreadPool() : _run(true), _to_stop(false) { }

    ~ThreadPool();

    ThreadPool(ThreadPool const &) = delete;

    ThreadPool(ThreadPool &) = delete;

    ThreadPool(ThreadPool &&) = delete;

    ThreadPool &operator=(ThreadPool const &) = delete;

    vector<exec_task> _exec_task;
    mutex _exec_task_mutex;
    vector<eval_task> _eval_task;
    mutex _eval_task_mutex;
    atomic<bool> _run;
    atomic<bool> _to_stop;
    atomic<int> _n_task;
    vector<thread> _thread;

    void _thread_eval();
    void _thread_exec();

public:
    static int N_eval;
    static int N_exec;

    static ThreadPool &getIstance() {
        static ThreadPool instance;
        return instance;
    }

    void addExecTask(exec_task &&);

    void addValueTask(eval_task &&);

    void start();
};


#endif //SPM_PROJECT_THREADPOOL_H
