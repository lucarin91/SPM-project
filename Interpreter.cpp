//
// Created by luca on 07/02/2016.
//

#include "Interpreter.h"

Interpreter::Interpreter(ThreadPool &tp, shared_ptr<Graph> g, initializer_list<Token> &&list, Drainer &&d) :
        _tp(tp),
        _g(g),
        _drainer(d),
        _token_mutex(new mutex()),
        _count_ist_mutex(new mutex()) {
    for (auto t : list) {
        auto &t1 = static_cast<Token_value<int>&>(t);
        cout << "id " <<t1.id<<endl;
        cout << "value "<< t1.value<<endl;

        _token[t.id] = t.clone();

        Token_value<int> *t2 = static_cast<Token_value<int>*>(_token[t.id]);
        cout << "id " <<t2->id<<endl;
        cout << "value "<< t2->value<<endl;
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
    msg << "graph evalueted by: " << this_thread::get_id();
    SyncCout::println(msg);
#endif

    _count_ist_mutex->lock();
    for (int i=0; i<_count_ist.size(); i++) {
        if (_count_ist[i]==0) {
            _fire_ist(i);
        }
    }
    _count_ist_mutex->unlock();

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

void Interpreter::_exec_function(Statement ist, t_in in) {

    auto t = ist.f(in);

#ifndef NO_PRINT
    stringstream msg;
    msg << "function executed by: " << this_thread::get_id();
    SyncCout::println(msg);
#endif
    int id = ist.out;
    t->set_id(ist.out);

    _check_token_mutex([this, &id, &t]() {
        _token[id] = t; //SYNC
    });

    _find_fireble_ist(id);
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
    _tp.addTask([p, ist, in]() {
        p->_exec_function(ist, in);
    });
}
