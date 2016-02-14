//
// Created by luca on 12/02/2016.
//

#ifndef SPM_PROJECT_THREADPOOL_H
#define SPM_PROJECT_THREADPOOL_H

#include <memory>
#include <future>
#include <vector>
#include <cmath>

using namespace std;

class ThreadPool {
    ThreadPool() : _to_stop(false) { }

    ~ThreadPool();

    ThreadPool(ThreadPool const &) = delete;

    ThreadPool(ThreadPool &) = delete;

    ThreadPool(ThreadPool &&) = delete;

    ThreadPool &operator=(ThreadPool const &) = delete;

    static int _n_eval;
    static int _n_exec;

    vector<function<void()>> _exec_task;
    mutex _exec_task_mutex;
    vector<function<void()>> _eval_task;
    mutex _eval_task_mutex;

    atomic<bool> _to_stop;
    atomic<int> _n_task;
    vector<thread> _thread;

    void _thread_eval();
    void _thread_exec();
    static void _set_num_thread();

    static ThreadPool &_create(){
        static ThreadPool instance;
        return instance;
    }

public:

    static const int &n_eval;
    static const int &n_exec;

    static ThreadPool &getIstance() {
        if (!_n_eval && !_n_exec)
            _set_num_thread();
        return _create();
    }

    static ThreadPool &getIstance(int e, int x) {
        if (e>=1 && x>=1) {
            _n_eval = e;
            _n_exec = x;
        }else
            _set_num_thread();
        return _create();
    }

    void addExecTask(function<void()> &&);

    void addValueTask(function<void()> &&);

    void start();
};


#endif //SPM_PROJECT_THREADPOOL_H
