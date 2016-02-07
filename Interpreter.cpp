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
    _start(got->second);
}

void Interpreter::add_token(shared_ptr<Token> ptr) {

    //SYNC
    auto got = token.find(ptr->id);
    if (got == token.end()){
        auto v = vector<shared_ptr<Token>>();
        v.push_back(ptr);
        token[ptr->id] = move(v);
    }else{
        got->second.push_back(ptr);
    }
    //SYNC

}

//PRIVATE
void Interpreter::_start(const Graph& g) {
    while (token.size()!=0){ //SYNC

        for (const Statement& item : g.ist){

            bool ready = true;
            t_in in;
            for (const int id : item.in) {
                auto got = token.find(id);
                if (got == token.end()) {
                    ready = false;
                }else{
                    in.push_back(token[id].back());
                    token[id].pop_back();
                }
            }

            if (ready){
                auto t = item.f(in);
            }
        }
    }
}
