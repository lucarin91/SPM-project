#include <iostream>
#include "MacroDataFlow.h"

using namespace std;

int main() {

    MacroDataFlow mc;

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
    }

    return 0;
}