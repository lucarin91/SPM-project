//
// Created by luca on 2/20/16.
//

#ifndef SPM_PROJECT_THREADPOOL_UP_H
#define SPM_PROJECT_THREADPOOL_UP_H


class ThreadPool_up  : public ThreadPool {
    ThreadPool_up(ThreadPool_up const &) = delete;

    ThreadPool_up(ThreadPool_up &) = delete;

    ThreadPool_up(ThreadPool_up &&) = delete;

    ThreadPool_up &operator=(ThreadPool_up const &) = delete;

    vector < vector<function<void()> >> _task;
    vector<mutex> _task_mutex;
    vector<atomic<int>> _task_count;

protected:
    virtual void _body_thread();
    virtual void _start();
public:
    ThreadPool(int n);

    ThreadPool();

    ~ThreadPool(){
        if (!_to_stop)
            wait();
    };

    virtual void wait();

    virtual const int &n_thread;

    virtual void addTask(function<void()> &&);

};


#endif //SPM_PROJECT_THREADPOOL_UP_H
