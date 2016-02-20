//
// Created by luca on 13/02/2016.
//

#include "InterpreterFactory.h"

void InterpreterFactory::start(string name, initializer_list<shared_ptr<Token>> &&list, Drainer drainer) {
    auto got = _gr->graph.find(name);
    if (got != _gr->graph.end()) {
        auto g = got->second;

        shared_ptr<Interpreter> inter(new Interpreter(_tp, g, move(list), move(drainer)));
        _tp->addTask([inter]() {
            inter->eval();
        });
    } else {
        //graph not finded
    }
}


InterpreterFactory::InterpreterFactory(shared_ptr<GraphRepository> g, int n, QueueType t) : _gr(g) {
    if (t == QueueType::SINGLE)
        _tp = make_shared<ThreadPool>(n);
    else
        _tp = make_shared<ThreadPool_up>(n);
    _tp->start();

#ifndef NO_PRINT
    stringstream msg;
    msg << "InterpreterGraph created with " << _tp->n_thread << " threads and " << ((t == QueueType::SINGLE)?"single queue":"multiplies queue") << " system";
    SyncCout::println(msg);
#endif
}