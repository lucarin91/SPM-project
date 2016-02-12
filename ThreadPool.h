//
// Created by luca on 12/02/2016.
//

#ifndef SPM_PROJECT_THREADPOOL_H
#define SPM_PROJECT_THREADPOOL_H

#include <memory>
#include <future>
#include <vector>

using namespace std;

class ThreadPool {
    ThreadPool() : _run(true){ }

    ~ThreadPool(){
        _run=false;
        for(auto& t : _thread){
            t.join();
        }
    }

    ThreadPool(ThreadPool const &) = delete;

    ThreadPool(ThreadPool &) = delete;

    ThreadPool(ThreadPool &&) = delete;

    ThreadPool &operator=(ThreadPool const &) = delete;

    vector<function<void()>> _exec_task;
    mutex _exec_task_mutex;
    vector<function<void()>> _eval_task;
    mutex _eval_task_mutex;
    atomic<bool> _run;
    vector<thread> _thread;

    void _thread_body();
public:
    static int N;

    static ThreadPool& getIstance(){
        static ThreadPool instance;
        return instance;
    }

    void addExecTask(function<void()>&&);
    void addValueTask(function<void()>&&);

    void start();
};


#endif //SPM_PROJECT_THREADPOOL_H
