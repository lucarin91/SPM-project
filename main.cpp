#include <iostream>
#include "MacroDataFlow.h"

using namespace std;

int main() {
    cout << "Hello World!" << endl;

    MacroDataFlow mc;

    Token_value<int> in1(5);
    Token_value<int> in2(2);
    Token_value<int> out;

    fun f = [](t_in in_ptr, t_out out_ptr) {
        auto in1 = dynamic_cast<Token_value<int>> (*in_ptr[0]);
        auto in2 = dynamic_cast<Token_value<int>> (*in_ptr[1]);
        auto out = dynamic_cast<Token_value<int>> (*out_ptr);
        out.set(in1.value + in2.value);
    };

    mc.add(f, {in1, in2}, out);

    t_in res = mc.start();

    return 0;
}