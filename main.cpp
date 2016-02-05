#include <iostream>
#include "MacroDataFlow.h"

using namespace std;

int main() {

    MacroDataFlow mc;

    shared_ptr<Token_value<int>> in1 (new Token_value<int> (5));
    shared_ptr<Token_value<int>> in2 (new Token_value<int> (2));
    shared_ptr<Token_value<int>> out (new Token_value<int> ());

    fun f = [](t_in in_ptr, t_out out_ptr) {
        auto &in1 = static_cast<Token_value<int>&> (*in_ptr[0]);
        auto &in2 = static_cast<Token_value<int>&> (*in_ptr[1]);
        auto &out = static_cast<Token_value<int>&> (*out_ptr);
        out.set(in1.value + in2.value);
    };

    mc.add(f, {in1, in2}, out);

    t_in res = mc.start();

    for (auto &item : res){
        auto &t = static_cast<Token_value<int>&> (*item);
        cout << "token" << t.id << " value " << t.value << endl;
    }

    return 0;
}