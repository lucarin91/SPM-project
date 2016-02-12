//
// Created by luca on 12/02/2016.
//

#include "ThreadPool.h"

int ThreadPool::N=4;

void ThreadPool::start(){
    for (int i=0; i<N; i++)
        _thread.push_back(thread(&ThreadPool::_thread_body, this));
    for (auto &t : _thread){
        t.detach();
    }
}

void ThreadPool::_thread_body() {
    while(_run){

        _exec_task_mutex.lock();
        if (_exec_task.size()>0){
            auto t = _exec_task.front();
            _exec_task.erase(_exec_task.begin());
            _exec_task_mutex.unlock();
            t();
        }else {
            _exec_task_mutex.unlock();

            _eval_task_mutex.lock();
            if (_eval_task.size() > 0) {
                auto t = _eval_task.front();
                _eval_task.erase(_eval_task.begin());
                _eval_task_mutex.unlock();
                t();
            } else
                _eval_task_mutex.unlock();
        }
    }
}

void ThreadPool::addExecTask(function<void()> &&f) {
    _exec_task_mutex.lock();
    _exec_task.push_back(f);
    _exec_task_mutex.unlock();
}

void ThreadPool::addValueTask(function<void()> &&f) {
    _eval_task_mutex.lock();
    _eval_task.push_back(f);
    _eval_task_mutex.unlock();
}
