//
// Created by luca on 07/02/2016.
//

#include "Interpreter.h"

Interpreter::Interpreter(ThreadPool &tp, shared_ptr<Graph> g, initializer_list<shared_ptr<Token>> &&list, Drainer &&d) :
        _tp(tp),
        _g(g),
        _drainer(d),
        _token_mutex(new mutex()),
        _count_ist_mutex(new mutex()) {
    for (auto &t : list) {
        _token[t->id] = t;
    }

    for (auto &ist : _g->ist) {
        _count_ist.push_back(ist.in.size());
    }
}

void Interpreter::eval() {
#ifndef NO_PRINT
    stringstream msg;
    msg << "graph evalueted by: " << this_thread::get_id();
    SyncCout::println(msg);
#endif

    for (auto &t : _token) {
        _fire_ist(t.second->id);
    }


    /* for (const Statement &stm : _g->ist) {
         if (_fired_ist.find(stm.id) == _fired_ist.end()) {
             bool ready = true;
             t_in in;
             const t_type_in &in_list = stm.in;
             for (const int &id : in_list) {

                 _check_token_mutex([this, &ready, &in, &id]() {
                     auto got = _token.find(id);
                     if (got == _token.end()) { //SYNC
                         ready = false;
                         //break;
                     }*//*else{
                        in.push_back(got->second);
                    }*//*
                });
                if (!ready) break;

            }

            if (ready) {
                _fired_ist.insert(stm.id);
                for (const int &id : in_list) {
                    _check_token_mutex([this, &in, &id, &stm]() {
                        in.push_back(_token[id]);
                    });
                }

                const fun &f = stm.f;
                auto p = shared_from_this();
                _tp.addTask([p, f, in]() {
                    p->_exec_function(f, in);
                });
            }
        }
    }*/

}

void Interpreter::_exec_function(fun f, t_in in) {

    auto t = f(in);

#ifndef NO_PRINT
    stringstream msg;
    msg << "function executed by: " << this_thread::get_id();
    SyncCout::println(msg);
#endif

    int id = t->id;

    _check_token_mutex([this, &id, &t]() {
        _token[id] = move(t); //SYNC
    });

    _fire_ist(id);
/*
    auto got = _g->token_to_ist.find(id);
    if (got == _g->token_to_ist.end()) {
        _drainer(t);
    } else {

        for (auto& ist : got->second){

        }


        _check_token_mutex([this, &id, &t]() {
            _token[id] = move(t); //SYNC
        });

        auto p = shared_from_this();
        _tp.addTask([p]() {
            p->eval();
        });

    }*/
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

void Interpreter::_fire_ist(int t_id) {
    auto got = _g->token_to_ist.find(t_id);
    if (got != _g->token_to_ist.end()) {
        for (auto ist_id : got->second) {
            _count_ist_mutex->lock();
            if (--_count_ist[ist_id] == 0) {
                _count_ist[ist_id] = -1;
                _count_ist_mutex->unlock();

                t_in in;
                const t_type_in &in_list = _g->ist[ist_id].in;
                for (const int &id : in_list) {
                    _check_token_mutex([this, &in, &id]() {
                        in.push_back(_token[id]);
                    });
                }

                const fun &f = _g->ist[ist_id].f;
                auto p = shared_from_this();
                _tp.addTask([p, f, in]() {
                    p->_exec_function(f, in);
                });
            } else {
                _count_ist_mutex->unlock();
            }
        }
    } else
        _drainer(_token[t_id]);
}
