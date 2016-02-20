//
// Created by luca on 12/02/2016.
//

#include "ThreadPool.h"

void ThreadPool::start() {
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

void ThreadPool::addTask(function<void()> &&f) {
    //++_n_task;
    _task_mutex.lock();
    _task.push_back(f);
    _task_mutex.unlock();
}

void ThreadPool::wait() {
    //cout << endl << "destructur ThreadPool" << endl << endl;
    _to_stop = true;
    for (auto &t : _thread) {
        //cout << "join..." << endl;
        t.join();
        //cout << "...join executed!" << endl;
    }
    //cout << "END!" << endl;
}

int ThreadPool::_get_num_thread() {
    int n = thread::hardware_concurrency();
    if (n == 0) n = sysconf(_SC_NPROCESSORS_ONLN);
    if (n == 0) n = 1;
    return n;
}

ThreadPool::ThreadPool(int n) : _to_stop(false), /*_n_task(0),*/ n_thread(_n_thread) {
    _n_thread = n >= 1 ? n : _get_num_thread();
    //start();
}

ThreadPool::ThreadPool() : ThreadPool(0) { }

