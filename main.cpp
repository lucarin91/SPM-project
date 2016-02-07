#include <iostream>
#include "GraphRepository.h"
#include "Interpreter.h"

using namespace std;

int main() {


    GraphRepository gr;
    gr.add("test",{Statement([](t_in in_ptr)->t_out{
                                auto &in = static_cast<Token_value<int>&> (*in_ptr[0]);
                                return shared_ptr<Token_value<int>>(new Token_value<int>(2,in.value*2));
                            }, {1}, 2)});

    Interpreter in(gr);

    in.start("test", [](Interpreter& in){
        for (int i=0;i<10;i++){
            in.add_token(shared_ptr<Token>(new Token_value<int>(1, 2)));
        }
    },[](shared_ptr<Token> t){
        cout << static_cast<Token_value<int>&> (*t).value << endl;
    });

    /*FlowInstruction mc;

    shared_ptr<Token_value<int>> in1 (new Token_value<int> (5));
    shared_ptr<Token_value<int>> in2 (new Token_value<int> (2));
    shared_ptr<Token_value<int>> out1 (new Token_value<int> ());

    shared_ptr<Token_value<int>> out2 (new Token_value<int> ());

    mc.add([](t_in in_ptr, t_out out_ptr) {
        auto &in = static_cast<Token_value<int>&> (*in_ptr[0]);
        auto &out = static_cast<Token_value<int>&> (*out_ptr);
        out.set(in.value*2);
    }, {out1}, out2);

    mc.add([](t_in in_ptr, t_out out_ptr) {
        auto &in1 = static_cast<Token_value<int>&> (*in_ptr[0]);
        auto &in2 = static_cast<Token_value<int>&> (*in_ptr[1]);
        auto &out = static_cast<Token_value<int>&> (*out_ptr);
        out.set(in1.value + in2.value);
    }, {in1, in2}, out1);

    t_in res = mc.start();

    for (auto &item : res){
        auto &t = static_cast<Token_value<int>&> (*item);
        cout << "token" << t.id << " value " << t.value << endl;
    }*/

    return 0;
}