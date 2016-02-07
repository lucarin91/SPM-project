//
// Created by luca on 07/02/2016.
//

#include "Interpreter.h"

//PUBLIC
void Interpreter::start(string name, Streamer streamer, Drainer drainer) {
    //start new thread
    streamer(*this);

    //start new thread
    auto got = _gr.graph.find(name);
    _start(got->second, drainer);
}

void Interpreter::add_token(shared_ptr<Token> ptr) {

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

}

//PRIVATE
void Interpreter::_start(const Graph& g, Drainer drainer) {
    while (_token.size() != 0){ //SYNC

        for (const Statement& stm : g.ist){

            bool ready = true;
            t_in in;
            const t_type_in& in_list = stm.in;
            for (const int& id : in_list) {
                auto got = _token.find(id); //SYNC
                if (got == _token.end()) { //SYNC
                    ready = false;
                    break;
                }else{
                    in.push_back(_get_token_type(id));
                }
            }

            if (ready){

                auto t = stm.f(in);

                if (g.t_out.find(t->id) != g.t_out.end()) {

                    //start new thread
                    drainer(t);
                } else{
                    add_token(t);
                }
            }
        }
    }
}

shared_ptr<Token> Interpreter::_get_token_type(int id) {
    auto t = _token[id].front();
    _token[id].erase(_token[id].begin());
    if (_token[id].size()==0)
        _token.erase(id);
    return t;
}
