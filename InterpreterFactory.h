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

using namespace std;
typedef function<void(shared_ptr<Token>)> Drainer;

class InterpreterFactory {
    InterpreterFactory(InterpreterFactory const &) = delete;

    InterpreterFactory(InterpreterFactory &) = delete;

    InterpreterFactory(InterpreterFactory &&) = delete;

    InterpreterFactory &operator=(InterpreterFactory const &) = delete;

    shared_ptr<GraphRepository> _gr;
    ThreadPool _tp;

public:
    InterpreterFactory(shared_ptr<GraphRepository> g, int n) : _gr(g), _tp(n), n_thread(_tp.n_thread){ }

    InterpreterFactory(shared_ptr<GraphRepository> g): InterpreterFactory(g,0) { }

    void start(string name, initializer_list<Token>&& , Drainer);

    const int &n_thread;

    void wait(){
        _tp.stop();
    }

};

#endif //SPM_PROJECT_INTERPRETERFACTORY_H
