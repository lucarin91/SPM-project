//
// Created by luca on 2/20/16.
//

#include "ThreadPool_up.h"

void ThreadPool_up::start() {
    for (int i = 0; i < _n_thread; i++)
        _thread.push_back(thread(&ThreadPool_up::_body_thread, this, i));
}

void ThreadPool_up::_body_thread(int index) {
    _task_mutex[index]->lock();
    while (!_to_stop || _task[index].size() > 0) {
        //_task_mutex.lock();
        if (_task[index].size() > 0) {
            auto t = _task[index].front();
            _task[index].erase(_task[index].begin());
            _task_mutex[index]->unlock();
            t();
            --*_task_count[index];
            //--_n_task;
        } else {
            _task_mutex[index]->unlock();
        }
        //cout << endl << "...task... " << _to_stop << " " << _n_task << endl << endl;
        _task_mutex[index]->lock();
    }
    _task_mutex[index]->unlock();

    //cout << endl << "...end--_body_thread.." << endl << endl;
}

void ThreadPool_up::addTask(function<void()> &&f) {
    int min=INT_MAX;
    int index=0;
    for (int i=0;i<_task_count.size();i++) {
        if (*_task_count[i] < min){
            min = *_task_count[i];
            index=i;
            if (min == 0) break;
        }
    }
#ifndef NO_PRINT
    stringstream msg;
    msg << "add new task to thread " << index;
    SyncCout::println(msg);
#endif
    ++*_task_count[index];
    _task_mutex[index]->lock();
    _task[index].push_back(f);
    _task_mutex[index]->unlock();
}

ThreadPool_up::ThreadPool_up(int n) : ThreadPool(n) {
    for (int i=0;i<_n_thread;i++){
        _task.push_back(vector<function<void()>>());
        _task_count.push_back(unique_ptr<atomic<int>>(new atomic<int>(0)));
        _task_mutex.push_back(unique_ptr<mutex>(new mutex()));
    }
}

ThreadPool_up::ThreadPool_up() : ThreadPool(0) { }

