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
#include <mutex>
#include <unistd.h>

using namespace std;

class ThreadPool {
    ThreadPool(ThreadPool const &) = delete;

    ThreadPool(ThreadPool &) = delete;

    ThreadPool(ThreadPool &&) = delete;

    ThreadPool &operator=(ThreadPool const &) = delete;

    vector<function<void()>> _task;
    mutex _task_mutex;
    void _body_thread();

protected:
    vector<thread> _thread;
    int _n_thread;
    atomic<bool> _to_stop;
    int _get_num_thread();

public:
    ThreadPool(int n);

    ThreadPool();

    ~ThreadPool(){
        if (!_to_stop)
            wait();
    };

    void wait();

    const int &n_thread;

    virtual void addTask(function<void()> &&);
    virtual void start();
    
};


#endif //SPM_PROJECT_THREADPOOL_H
