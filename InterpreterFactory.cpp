//
// Created by luca on 13/02/2016.
//

#include "InterpreterFactory.h"

void InterpreterFactory::start(string name, initializer_list<shared_ptr<Token>> list, Drainer drainer) {
    auto got = _gr->graph.find(name);
    if (got != _gr->graph.end()) {
        auto g = got->second;
        /*_int_thread.push_back(thread([](const Graph &g, initializer_list<shared_ptr<Token>> list, Drainer drainer){
            Interpreter in(g);
            initializer_list<shared_ptr<Token>> l = list;
            in.start(l, drainer);
        }, g, move(list), drainer));*/


        //_int_thread.push_back(thread(&InterpreterFactory::Interpreter::start, move(in), move(v), move(drainer)));

        vector<shared_ptr<Token>> v;
        for (auto &i : list) {
            v.push_back(i);
        }
        auto &tp = ThreadPool::getIstance();

        tp.addValueTask([&g,v,drainer](){
            Interpreter in(g);
            in.start(move(v),move(drainer));
        });
    } else {
        //graph not finded
    }
}

InterpreterFactory::~InterpreterFactory() {
    //cout << "decostructor " << endl << flush;

//    for (auto &item : _int_thread) {
//        auto id = item.get_id();
//        item.join();
//        cout << "Interpreter thread joined: " << id << endl << flush;
//    }
}


