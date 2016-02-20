//
// Created by luca on 13/02/2016.
//

#ifndef SPM_PROJECT_INTERPRETERFACTORY_H
#define SPM_PROJECT_INTERPRETERFACTORY_H

#include <thread>
#include <iostream>
#include <sstream>
#include <mutex>
#include <atomic>
#include "GraphRepository.h"
#include "Interpreter.h"
#include "SyncCout.h"
#include "ThreadPool.h"
#include "ThreadPool_up.h"

using namespace std;
typedef function<void(shared_ptr<Token>)> Drainer;

enum class QueueType {
    SINGLE, MULTY
};

class InterpreterFactory {
    InterpreterFactory(InterpreterFactory const &) = delete;

    InterpreterFactory(InterpreterFactory &) = delete;

    InterpreterFactory(InterpreterFactory &&) = delete;

    InterpreterFactory &operator=(InterpreterFactory const &) = delete;

    shared_ptr<GraphRepository> _gr;
    shared_ptr<ThreadPool> _tp;

public:
    InterpreterFactory(shared_ptr<GraphRepository> g, int n, QueueType t = QueueType::SINGLE);

    InterpreterFactory(shared_ptr<GraphRepository> g) : InterpreterFactory(g, 0) { }

    void start(string, initializer_list<shared_ptr<Token>> &&, Drainer);

    int get_n_thread() const {
        return _tp->n_thread;
    };

    void wait() {
        _tp->wait();
    }

};

#endif //SPM_PROJECT_INTERPRETERFACTORY_H
