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
        for (int i=0;i<4;i++){
            in.add_token(shared_ptr<Token>(new Token_value<int>(1, i)));
        }
    },[](shared_ptr<Token> t){
        cout << static_cast<Token_value<int>&> (*t).value << endl;
    });

    return 0;
}