#include <iostream>
#include "MacroDataFlow.h"

using namespace std;

int main() {

    MacroDataFlow mc;

    Token_value<int> in1(5);
    Token_value<int> in2(2);
    Token_value<int> out;

    fun f = [](t_in in_ptr, t_out out_ptr) {
        auto &in1 = static_cast<Token_value<int>&> (*in_ptr[0]);
        auto &in2 = static_cast<Token_value<int>&> (*in_ptr[1]);
        auto &out = static_cast<Token_value<int>&> (*out_ptr);
        out.set(in1.value + in2.value);
    };

    mc.add(f, {shared_ptr<Token>(&in1), shared_ptr<Token>(&in2)}, shared_ptr<Token>(&out));

    t_in res = mc.start();

    return 0;
}