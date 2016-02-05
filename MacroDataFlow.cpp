//
// Created by luca on 22/12/15.
//

#include "MacroDataFlow.h"

// PUBLIC
void MacroDataFlow::add(fun f, initializer_list<shared_ptr<Token>> in_list, shared_ptr<Token> out) {
    int stm_id = stm.size();

    t_in in_vec = t_in(in_list.size());
    bool all_ready = true;
    for (auto &item : in_list){
        if (!item->ready) all_ready = false;

//      auto ptr = shared_ptr<Token>(&item);
        // auto t = Token(&item);
        in_vec.push_back(item);

        updateTokenMap(item);
        updateTokenToStm(item->id, stm_id);
    }


    stm.push_back(Statement(move(f), move(in_vec), out));


    if (all_ready) {
        ready_stm.emplace(&stm_id);
    }
    updateTokenMap(out);
}

t_in MacroDataFlow::start(){
    while (ready_stm.size()!=0){
        int stm_id = *ready_stm.begin();

        t_in in = stm[stm_id].in;
        t_out out = stm[stm_id].out;
        stm[stm_id].f(in, out);

        stm[stm_id].fired = true;

        auto v = token_to_stm[out->id];

        for (auto& id : v){
            if (checkInputToken(stm[id].in)){
                ready_stm.emplace(id);
            }
        }
    }
}

// PRIVATE
void MacroDataFlow::updateTokenMap(shared_ptr<Token> p) {
    auto got = token.find(p->id);
    if (got != token.end() && !got->second->ready && p->ready) {
        token[p->id] = p;
    }
}

void MacroDataFlow::updateTokenToStm(int token_id, int stm_id){
    auto got = token_to_stm.find(token_id);
    if (got == token_to_stm.end()){
        auto v = vector<int>(1);
        v.push_back(stm_id);
        token_to_stm[token_id] = move(v);
    }else{
        got->second.push_back(stm_id);
    }
}


bool MacroDataFlow::checkInputToken(t_in& v){
    bool all_ready = true;
    for (auto& p : v){
        if (!p->ready){
            all_ready = false;
            break;
        }
    }
    return all_ready;
}
