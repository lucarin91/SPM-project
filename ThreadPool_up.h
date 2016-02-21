//
// Created by luca on 2/20/16.
//

#ifndef SPM_PROJECT_THREADPOOL_UP_H
#define SPM_PROJECT_THREADPOOL_UP_H

#include <functional>
#include <thread>
#include <vector>
#include <atomic>
#include <mutex>
#include <limits.h>
#include "ThreadPool.h"
#include <sstream>
#include "SyncCout.h"

using namespace std;

class ThreadPool_up : public ThreadPool {
    ThreadPool_up(ThreadPool_up const &) = delete;

    ThreadPool_up(ThreadPool_up &) = delete;

    ThreadPool_up(ThreadPool_up &&) = delete;

    ThreadPool_up &operator=(ThreadPool_up const &) = delete;

    vector<vector<function<void()> >> _task;
    vector<unique_ptr<mutex>> _task_mutex;
    vector<unique_ptr<atomic<int>>> _task_count;

    void _body_thread(int);

public:
    ThreadPool_up(int);

    ThreadPool_up();

    virtual void start();

    virtual void addTask(function<void()> &&);

};

#endif //SPM_PROJECT_THREADPOOL_UP_H
