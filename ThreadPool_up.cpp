//
// Created by luca on 2/20/16.
//

#include "ThreadPool_up.h"

void ThreadPool::_start() {
    for (int i = 0; i < _n_thread; i++)
        _thread.push_back(thread(&ThreadPool::_body_thread, this));
}

void ThreadPool::_body_thread() {
    _task_mutex.lock();
    while (!_to_stop || _task.size() > 0) {
        //_task_mutex.lock();
        if (_task.size() > 0) {
            auto t = _task.front();
            _task.erase(_task.begin());
            _task_mutex.unlock();
            t();
            //--_n_task;
        } else {
            _task_mutex.unlock();
        }
        //cout << endl << "...task... " << _to_stop << " " << _n_task << endl << endl;
        _task_mutex.lock();
    }
    _task_mutex.unlock();

    //cout << endl << "...end--_body_thread.." << endl << endl;
}

virtual void ThreadPool_up::addTask(function<void()> &&f) {
    for (auto &m : _task_mutex) {
        _task_mutex.lock();
        _task.push_back(f);
        _task_mutex.unlock();
    }
}

ThreadPool_up::ThreadPool_up(int n) : ThreadPool(n) { }

ThreadPool_up::ThreadPool_up() : ThreadPool(0) { }

