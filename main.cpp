#include <iostream>
#include <sstream>
#include <memory>
#include "Helper.h"
#include "GraphRepository.h"
#include "InterpreterFactory.h"

using namespace std;

int main(int argc, char* argv[]) {

    shared_ptr<GraphRepository> gr (new GraphRepository());
    gr->add("test", {
//            Statement([](t_in in_ptr) -> t_out {
//                auto &in = static_cast<Token_value<int> &> (*in_ptr[0]);
//                return shared_ptr<Token_value<int>>(new Token_value<int>(in.value * 2));
//            }, {3}, 4),
//
//            Statement([](t_in in_ptr) -> t_out {
//                auto &in = static_cast<Token_value<int> &> (*in_ptr[0]);
//                return shared_ptr<Token_value<int>>(new Token_value<int>(in.value * 3));
//            }, {3}, 5),

            Statement([](t_in in_ptr) -> t_out {
                auto *in1 = static_cast<Token_value<int> *> (in_ptr[0]);
                auto *in2 = static_cast<Token_value<int> *> (in_ptr[1]);
                return new Token_value<int>(in1->value + in2->value);
            }, {1, 2}, 3)
    });

    InterpreterFactory inFactory(gr,(argc>1?stoi(argv[1]):0));
    //cout << "N thread " << inFactory.n_thread << endl;

    double sumTS = 0;
    double prev = Helper::gettime();
    function<void(Token*)> drain = [&prev,&sumTS](Token* t) {
        auto now = Helper::gettime();
        sumTS = now - prev;
        prev = now;

        auto *tv = static_cast<Token_value<int> *> (t);
#ifndef NO_PRINT
        stringstream msg;
        msg << "drainer: " << "token: " << tv->id << " value: " << tv->value;
        SyncCout::println(msg);
#endif
    };


    double sumTA = 0;
    int N = (argc>2?stoi(argv[2]):100);

    for (int i = 0; i < N; i++) {
        auto start = Helper::gettime();
        sumTA += Helper::gettime() - start;

        inFactory.start("test", {Token_value<int>(1, i),
                                 Token_value<int>(2, i)}, drain);


    }

    inFactory.wait();

    Helper::printtime(sumTA/N,sumTS/N*2);
    return 0;
}