#include <iostream>
#include <sstream>
#include <memory>
#include "GraphRepository.h"
#include "InterpreterFactory.h"

using namespace std;

int main(int argc, char* argv[]) {

    shared_ptr<GraphRepository> gr (new GraphRepository());
    gr->add("test", {

            Statement([](t_in in_ptr) -> t_out {
                auto &in = static_cast<Token_value<double> &> (*in_ptr[0]);
                shared_ptr<Token_value<double>> res(new Token_value<double>(in.value));
                return res;
            }, {3}, 4),

            Statement([](t_in in_ptr) -> t_out {
                auto &in = static_cast<Token_value<double> &> (*in_ptr[0]);
                shared_ptr<Token_value<double>> res(new Token_value<double>(in.value));
                return res;
            }, {3}, 5),

            Statement([](t_in in_ptr) -> t_out {
                auto &in1 = static_cast<Token_value<int> &> (*in_ptr[0]);
                auto &in2 = static_cast<Token_value<int> &> (*in_ptr[1]);
                shared_ptr<Token_value<double>> res(new Token_value<double>(in1.value + in2.value));
                return res;
            }, {1, 2}, 3),

            Statement([](t_in in_ptr) -> t_out {
                auto &in1 = static_cast<Token_value<double> &> (*in_ptr[0]);
                auto &in2 = static_cast<Token_value<double> &> (*in_ptr[1]);
                shared_ptr<Token_value<double>> res(new Token_value<double>(in1.value + in2.value));
                return res;
            }, {4, 5}, 6)

    });

    InterpreterFactory inFactory(gr,(argc>1?stoi(argv[1]):0));
    //cout << "N thread " << inFactory.n_thread << endl;

    function<void(shared_ptr<Token>)> drain = [](shared_ptr <Token> t) {
        auto &tv = static_cast<Token_value<double> &> (*t);
#ifndef NO_PRINT
        stringstream msg;
        msg << "drainer: " << "token: " << tv.id << " value: " << tv.value;
        SyncCout::println(msg);
#endif
    };

    for (int i = 0; i < (argc>2?stoi(argv[2]):100); i++) {
        inFactory.start("test", {shared_ptr<Token>(new Token_value<int>(1, 1)),
                                 shared_ptr<Token>(new Token_value<int>(2, 1))}, drain);
    }
    return 0;
}