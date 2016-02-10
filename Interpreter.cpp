//
// Created by luca on 07/02/2016.
//

#include "Interpreter.h"

void InterpreterFactory::Interpreter::start(initializer_list<shared_ptr<Token>> list, Drainer drainer) {
    _fired_stm.clear();
    _token.clear();

    for (auto& item : list){
        _token[item->id] = item;
    }

    vector<thread> pt;
    bool con = false;
    //_check_token_mutex([this,&con](){con = _token.size() != 0;});
    while (_fired_stm.size() != _g.ist.size() || _n_thread>0){ //SYNC

        for (const Statement& stm : _g.ist) {
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

                    for (const int &id : in_list) {
                        //_check_token_mutex([this, &in, &id, &stm]() {
                        in.push_back(_token[id]);
                        _fired_stm.insert(stm.id);
                        //_token.erase(id);
                        //});
                    }

                    ++*_n_thread;
                    pt.push_back(thread(&Interpreter::_body_thread, this, stm.f, in, drainer));

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
            _check_token_mutex([this, &con]() { con = _token.size() != 0; });
        }
    }


    for (auto &t : pt){
        cout << "join: " << t.get_id() << endl << flush;
        t.join();
        cout << "join: " << t.get_id() << endl << flush;
    }
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


void InterpreterFactory::Interpreter::_body_thread(fun f, t_in in, Drainer drainer) {

    auto t = f(in);
    int id = t->id;
    if (_g.t_in.find(id) == _g.t_in.end()) {
        cout << "id: " << this_thread::get_id() << " ";
        drainer(t);
    } else {
        _check_token_mutex([this,&id,&t](){
            _token[id] = move(t); //SYNC
        });
    }
    --*_n_thread;
}


void InterpreterFactory::Interpreter::_check_token_mutex(function<void()> f){
    _token_mutex->lock();
    f();
    _token_mutex->unlock();
}

void InterpreterFactory::start(string name, initializer_list<shared_ptr<Token>> list, Drainer drainer) {
    auto got = _gr.graph.find(name);
    if (got != _gr.graph.end()){
        const Graph& g = got->second;
        _int_thread.push_back(thread([](const Graph &g, initializer_list<shared_ptr<Token>> list, Drainer drainer){
            Interpreter in(g);
            in.start(list,drainer);
        }, g, list, drainer));
    }else{

    }
}

InterpreterFactory::~InterpreterFactory(){
    cout << "decostructor " << endl << flush;

    for (auto& item : _int_thread){
        cout << "joined: " << item.get_id() << endl << flush;
        item.join();
        cout << "joined: " << item.get_id() << endl << flush;
    }
}


