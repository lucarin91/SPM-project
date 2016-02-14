//
// Created by luca on 12/02/2016.
//

#include "ThreadPool.h"

int ThreadPool::_n_eval = 0;
int ThreadPool::_n_exec = 0;
const int &ThreadPool::n_exec( _n_exec);
const int &ThreadPool::n_eval (_n_eval);

void ThreadPool::start(){
    for (int i=0; i < _n_eval; i++)
        _thread.push_back(thread(&ThreadPool::_thread_eval, this));

    for (int i=0; i < _n_exec; i++)
        _thread.push_back(thread(&ThreadPool::_thread_exec, this));

//    for (auto &t : _thread){
//        t.detach();
//    }
}

void ThreadPool::_thread_eval() {
    while(!_to_stop || _n_task>0){

        _eval_task_mutex.lock();
        if (_eval_task.size() > 0) {
            auto t = _eval_task.front();
            _eval_task.erase(_eval_task.begin());
            _eval_task_mutex.unlock();
            t();
            --_n_task;
        } else {
            _eval_task_mutex.unlock();
        }
    }
}

void ThreadPool::_thread_exec() {
    while(!_to_stop || _n_task>0){
        _exec_task_mutex.lock();
        if (_exec_task.size()>0){
            auto t = _exec_task.front();
            _exec_task.erase(_exec_task.begin());
            _exec_task_mutex.unlock();
            t();
            --_n_task;
        }else {
            _exec_task_mutex.unlock();
        }
    }
}

void ThreadPool::addExecTask(function<void()> &&f) {
    ++_n_task;
    _exec_task_mutex.lock();
    _exec_task.push_back(f);
    _exec_task_mutex.unlock();
}

void ThreadPool::addValueTask(function<void()> &&f) {
    ++_n_task;
    _eval_task_mutex.lock();
    _eval_task.push_back(f);
    _eval_task_mutex.unlock();
}

ThreadPool::~ThreadPool() {
    _to_stop = true;
    for (auto &t : _thread) {
        t.join();
    }
}

void ThreadPool::_set_num_thread() {
    auto N = thread::hardware_concurrency();
    if (N==0) N = sysconf( _SC_NPROCESSORS_ONLN );
    if (N==0) N = 2;
    _n_eval = ceil((N * 25) / 100);
    _n_exec = N - _n_eval;
}
