//
// Created by luca on 07/02/2016.
//

#include "Interpreter.h"

//
//void Interpreter::start(initializer_list<shared_ptr<Token>> list, Drainer drainer){
//    vector<shared_ptr<Token>> v;
//    for (auto& item : list){
//        v.push_back(item);
//    }
//
//    start(move(v), drainer);
//}

void Interpreter::start(t_in list, Drainer drainer) {
    //_fired_stm.clear();
    //_token.clear();

    for (auto &item : list) {
        _token[item->id] = item;
    }

    //vector<thread> pt;
    //bool con = false;
    //_check_token_mutex([this,&con](){con = _token.size() != 0;});
    stringstream msg;
    msg << "graph evalueted by: " << this_thread::get_id() << " ";
    SyncCout::println(msg);
    while (_fired_stm.size() != _g->ist.size() /*|| *_n_thread>0*/) { //SYNC

        for (const auto &stm : _g->ist) {
            if (_fired_stm.find(stm->id) == _fired_stm.end()) {
                bool ready = true;
                t_in in;
                const t_type_in &in_list = stm->in;
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
                    _fired_stm.insert(stm->id);
                    for (const int &id : in_list) {
                        _check_token_mutex([this, &in, &id, &stm]() {
                            in.push_back(_token[id]);
                            //_token.erase(id);
                        });
                    }

                    //++*_n_thread;
                    //pt.push_back(thread(&Interpreter::_body_thread, this, stm.f, in, drainer));

                    auto &tp = ThreadPool::getIstance();
                    const fun &f = stm->f;
                    shared_ptr<Interpreter> i = shared_from_this();
                    tp.addExecTask(move(exec_task(i,f,in,drainer)));
                    /*tp.addExecTask([this, f, in, drainer]() {
                        this->_body_thread(f, in, drainer);
                    });*/
//
                    //thread t (&Interpreter::_test, this, g, stm.f);
//                auto t = stm.f(in);
//
//                if (g.t_out.find(t->id) != g.t_out.end()) {
//                    drainer(t);
//                } else{
//                    _token[t->id] = move(t);
//                }

                }
            }
            //_check_token_mutex([this, &con]() { con = _token.size() != 0; });
        }
    }


//    for (auto &t : pt) {
//        auto id = t.get_id();
//        t.join();
//        stringstream s;
//        s << "Worker thread joined: " << id;
//        SyncCout::println(s);
//    }
}

/*
void Interpreter::execute(shared_ptr<Token> ptr) {

    //SYNC
    auto got = _token.find(ptr->id);
    if (got == _token.end()){
        auto v = vector<shared_ptr<Token>>();
        v.push_back(ptr);
        _token[ptr->id] = move(v);
    }else{
        got->second.push_back(ptr);
    }
    //SYNC

}*/

/*shared_ptr<Token> Interpreter::_get_token_type(int id) {
    auto t = _token[id].front();
    _token[id].erase(_token[id].begin());
    if (_token[id].size()==0)
        _token.erase(id);
    return t;
}*/

void Interpreter::_body_thread(fun f, t_in in, Drainer drainer) {
    //this_thread::sleep_for(chrono::milliseconds(1000));
    auto t = f(in);
    stringstream msg;
    msg << "function executed by: " << this_thread::get_id() << " ";
    SyncCout::println(msg);
    int id = t->id;
    //_t_in_mutex->lock();
    const auto &end = _g->t_in.end();
    const auto &got = _g->t_in.find(id);
    //_t_in_mutex->unlock();
    if (got == end) {
        drainer(t);
    } else {
        _check_token_mutex([this, &id, &t]() {
            _token[id] = move(t); //SYNC
        });
    }
    //--*_n_thread;
}

void Interpreter::_check_token_mutex(function<void()> f) {
    _token_mutex->lock();
    f();
    _token_mutex->unlock();
}