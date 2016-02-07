//
// Created by luca on 07/02/2016.
//

#ifndef SPM_PROJECT_INTERPRETER_H
#define SPM_PROJECT_INTERPRETER_H

#include "GraphRepository.h"

using namespace std;
class Interpreter;

typedef function<void(Interpreter&)> Streamer;
typedef function<void(shared_ptr<Token>)> Drainer;

class Interpreter {
    Interpreter(Interpreter const &) = delete;

    Interpreter(Interpreter &) = delete;

    Interpreter &operator=(Interpreter const &) = delete;

    GraphRepository &_gr;

    unordered_map<int, vector<shared_ptr<Token>>> token;
    //unordered_map<int, vector<int>> token_to_stm;
    //unordered_set<int> ready_stm;

    void _start(const Graph &g);
public:
    Interpreter(GraphRepository &g) : _gr(g) {}

    void start(string,Streamer,Drainer);
    void add_token(shared_ptr<Token>);


};



#endif //SPM_PROJECT_INTERPRETER_H
