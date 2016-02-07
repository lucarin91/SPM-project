//
// Created by luca on 22/12/15.
//

#include "FlowInstruction.h"

// PUBLIC
void FlowInstruction::add(fun f, initializer_list<shared_ptr<Token>> in_list, shared_ptr<Token> out) {
    int stm_id = stm.size();

    t_in in_vec;
    bool all_ready = true;
    for (auto item : in_list){
        if (!item->ready) all_ready = false;

//      auto ptr = shared_ptr<Token>(&item);
        // auto t = Token(&item);
        in_vec.push_back(item);

        updateTokenMap(item);
        updateTokenToStm(item->id, stm_id);
    }


    stm.push_back(Statement(move(f), move(in_vec), out));


    if (all_ready) {
        ready_stm.insert(stm_id);
    }
    updateTokenMap(out);
}

t_in FlowInstruction::start(){
    while (ready_stm.size()!=0){
        int stm_id = *ready_stm.begin();
        ready_stm.erase(ready_stm.begin());

        t_in in = stm[stm_id].in;
        t_out out = stm[stm_id].out;
        stm[stm_id].f(in, out);
        stm[stm_id].fired = true;

        auto got = token_to_stm.find(out->id);
        if (got != token_to_stm.end())
            for (auto& id : got->second){
                if (checkInputToken(stm[id].in) && !stm[id].fired){
                    ready_stm.insert(id);
                }
            }

    }
    t_in res;
    for (auto &item : token){
        auto got = token_to_stm.find(item.first);
        if (got==token_to_stm.end())
            res.push_back(item.second);
    }
    return res;
}

// PRIVATE
int FlowInstruction::_ID = 1;

void FlowInstruction::updateTokenMap(shared_ptr<Token> p) {
    auto got = token.find(p->id);
    if (got == token.end() || (got != token.end() && !got->second->ready && p->ready))
        token[p->id] = p;
}

void FlowInstruction::updateTokenToStm(int token_id, int stm_id){
    auto got = token_to_stm.find(token_id);
    if (got == token_to_stm.end()){
        auto v = vector<int>();
        v.push_back(stm_id);
        token_to_stm[token_id] = move(v);
    }else{
        got->second.push_back(stm_id);
    }
}


bool FlowInstruction::checkInputToken(t_in& v){
    bool all_ready = true;
    for (auto& p : v){
        if (!p->ready){
            all_ready = false;
            break;
        }
    }
    return all_ready;
}
