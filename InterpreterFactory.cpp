//
// Created by luca on 13/02/2016.
//

#include "InterpreterFactory.h"

void InterpreterFactory::start(string name, initializer_list<shared_ptr<Token>>&& list, Drainer drainer) {
    auto got = _gr->graph.find(name);
    if (got != _gr->graph.end()) {
        auto g = got->second;

        shared_ptr<Interpreter> inter (new Interpreter(_tp, g, move(list), move(drainer)));
        _tp->addTask([inter]() {
            inter->eval();
        });
    } else {
        //graph not finded
    }
}


