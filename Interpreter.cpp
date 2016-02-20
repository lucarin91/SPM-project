//
// Created by luca on 07/02/2016.
//

#include "Interpreter.h"

Interpreter::Interpreter(shared_ptr<ThreadPool> tp, shared_ptr<Graph> g, initializer_list<shared_ptr<Token>> &&list, Drainer &&d) :
        _tp(tp),
        _g(g),
        _drainer(d),
        _token_mutex(new mutex()),
        _count_ist_mutex(new mutex()) {
    for (auto &t : list) {
        _token[t->type] = t;
    }

    for (auto &ist : _g->ist) {
        _count_ist.push_back(ist.in.size());
        for (auto &t : ist.in){
            if (_token.find(t) != _token.end()){
                --_count_ist[_count_ist.size()-1];
            }
        }
    }
}

void Interpreter::eval() {
#ifndef NO_PRINT
    stringstream msg;
    msg << "start a new graph evaluetion by: " << this_thread::get_id();
    SyncCout::println(msg);
#endif

    _count_ist_mutex->lock();
    for (int i=0; i<_count_ist.size(); i++) {
        if (_count_ist[i]==0) {
            _fire_ist(i);
        }
    }
    _count_ist_mutex->unlock();
}

void Interpreter::_exec_function(Statement ist, t_in in) {

    auto t = ist.f(in);

#ifndef NO_PRINT
    stringstream msg;
    msg << "new instruction evalueted by: " << this_thread::get_id();
    SyncCout::println(msg);
#endif
    int id = ist.out;
    t->set_type(ist.out);

    _check_token_mutex([this, &id, &t]() {
        _token[id] = move(t); //SYNC
    });

    _find_fireble_ist(id);
}

void Interpreter::_check_token_mutex(function<void()> f) {
    _token_mutex->lock();
    f();
    _token_mutex->unlock();
}

void Interpreter::_check_ready_ist_mutex(function<void()> f) {
    _count_ist_mutex->lock();
    f();
    _count_ist_mutex->unlock();
}

void Interpreter::_find_fireble_ist(int t_id) {

    auto got = _g->token_to_ist.find(t_id);
    if (got != _g->token_to_ist.end()) {
        for (auto ist_id : got->second) {

            _count_ist_mutex->lock();
            if (--_count_ist[ist_id] == 0) {
                _count_ist[ist_id] = -1;
                _count_ist_mutex->unlock();

                _fire_ist(ist_id);

            } else {
                _count_ist_mutex->unlock();
            }
        }
    } else {
        _token_mutex->lock();
        auto t = _token[t_id];
        _token_mutex->unlock();
        _drainer(t);
    }

}

void Interpreter::_fire_ist(int ist_id) {
    t_in in;
    const t_type_in &in_list = _g->ist[ist_id].in;
    for (const int &id : in_list) {
        _check_token_mutex([this, &in, &id]() {
            in.push_back(_token[id]);
        });
    }

    const Statement &ist = _g->ist[ist_id];
    auto p = shared_from_this();
    _tp->addTask([p, ist, in]() {
        p->_exec_function(ist, in);
    });
}
