//
// Created by luca on 22/12/15.
//

#include "MacroDataFlow.h"

// PUBLIC
void MacroDataFlow::add(fun f, vector<shared_ptr<Token>> in, shared_ptr<Token> out) {
    stm.emplace(f, in, out);

    for (auto p : in) {
        updateMap(p);
    }

    updateMap(*out);
}

t_vec MacroDataFlow::start(){

}

// PRIVATE
void MacroDataFlow::updateMap(Token &p) {
    auto got = token.find(p.id);
    if (got != token.end() && !got->second.ready && p.ready) {
        token[p.id] = p;
    }
}



