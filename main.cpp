#include <iostream>
#include "GraphRepository.h"
#include "Interpreter.h"

using namespace std;

int main() {

    GraphRepository gr;
    gr.add("test", {
            Statement([](t_in in_ptr) -> t_out {
                auto &in = static_cast<Token_value<int> &> (*in_ptr[0]);
                return shared_ptr<Token_value<int>>(new Token_value<int>(4, in.value * 2));
            }, {3}, 4),

            Statement([](t_in in_ptr) -> t_out {
                auto &in = static_cast<Token_value<int> &> (*in_ptr[0]);
                return shared_ptr<Token_value<int>>(new Token_value<int>(5, in.value * 3));
            }, {3}, 5),

            Statement([](t_in in_ptr) -> t_out {
                auto &in1 = static_cast<Token_value<int> &> (*in_ptr[0]);
                auto &in2 = static_cast<Token_value<int> &> (*in_ptr[1]);
                return shared_ptr<Token_value<int>>(new Token_value<int>(3, in1.value + in2.value));
            }, {1, 2}, 3)
    });

    InterpreterFactory inFactory(gr);

    function<void(shared_ptr<Token>)> drain = [](shared_ptr <Token> t) {
        cout << static_cast<Token_value<int> &> (*t).value << endl << flush;
    };
    
    for (int i = 0; i < 1; i++) {
        inFactory.start("test", {shared_ptr<Token>(new Token_value<int>(1, i)),
                                 shared_ptr<Token>(new Token_value<int>(2, i))}, drain);
    }
    return 0;
}