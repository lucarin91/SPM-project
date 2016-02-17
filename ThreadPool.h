//
// Created by luca on 12/02/2016.
//

#ifndef SPM_PROJECT_THREADPOOL_H
#define SPM_PROJECT_THREADPOOL_H

#include <iostream>
#include <memory>
#include <vector>
#include <cmath>
#include <thread>
#include <atomic>

using namespace std;

class ThreadPool {
    ThreadPool(ThreadPool const &) = delete;

    ThreadPool(ThreadPool &) = delete;

    ThreadPool(ThreadPool &&) = delete;

    ThreadPool &operator=(ThreadPool const &) = delete;

    int _n_thread;

    vector<function<void()>> _task;
    mutex _task_mutex;

    atomic<bool> _to_stop;
    //atomic<int> _n_task;
    vector<thread> _thread;

    void _body_thread();
    int _get_num_thread();
    void _start();

public:
    ThreadPool(int n);

    ThreadPool();

    ~ThreadPool();

    const int &n_thread;

    void addTask(function<void()> &&);
    
};


#endif //SPM_PROJECT_THREADPOOL_H
