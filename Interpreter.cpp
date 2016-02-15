//
// Created by luca on 07/02/2016.
//

#include "Interpreter.h"

Interpreter::Interpreter(ThreadPool &tp, shared_ptr<Graph> g, initializer_list<Token>&& list, Drainer&& d) :
        _tp(tp),
        _g(g),
        _drainer(d),
        _token_mutex(new mutex()) {


    for (const Token &t : list) {
        Token t1(t);
        auto id = t.id;
        _token.insert(make_pair<int,Token>(move(id),move(t1)));
    }
}

void Interpreter::eval() {

    stringstream msg;
    msg << "graph evalueted by: " << this_thread::get_id();
    SyncCout::println(msg);

    for (const Statement &stm : _g->ist) {
        if (_fired_stm.find(stm.id) == _fired_stm.end()) {
            bool ready = true;
            t_in in;
            const t_type_in &in_list = stm.in;
            for (const int &id : in_list) {

                _check_token_mutex([this, &ready, &in, &id]() {
                    auto got = _token.find(id);
                    if (got == _token.end()) { //SYNC
                        ready = false;
                        //break;
                    }/*else{
                        in.push_back(got->second);
                    }*/
                });
                if (!ready) break;

            }

            if (ready) {
                _fired_stm.insert(stm.id);
                for (const int &id : in_list) {
                    _check_token_mutex([this, &in, &id, &stm]() {
                        Token t1 (_token[id]);
                        in.push_back(move(t1));
                    });
                }

                const fun &f = stm.f;
                auto p = shared_from_this();
                _tp.addTask([p, f, in]() {
                    p->_exec_function(f, move(in));
                });
            }
        }
    }

}

void Interpreter::_exec_function(fun f, t_in in) {

    auto t = f(in);

    stringstream msg;
    msg << "function executed by: " << this_thread::get_id();
    SyncCout::println(msg);

    int id = t.id;
    if (_g->t_in.find(id) == _g->t_in.end()) {
        _drainer(t);
    } else {
        _check_token_mutex([this, &id, &t]() {
            _token[id] = move(t); //SYNC
            //auto id = t.id;
            //_token.insert(make_pair(move(id),move(t)));
        });

        auto p = shared_from_this();
        _tp.addTask([p]() {
            p->eval();
        });

    }
}

void Interpreter::_check_token_mutex(function<void()> f) {
    _token_mutex->lock();
    f();
    _token_mutex->unlock();
}
