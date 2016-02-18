#include <iostream>
#include <sstream>
#include <memory>
#include "GraphRepository.h"
#include "InterpreterFactory.h"
#include "Helper.h"

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

    double sumTS = 0;
    double prev = Helper::gettime();
    function<void(shared_ptr<Token>)> drain = [&sumTS,&prev](shared_ptr <Token> t) {
        auto now = Helper::gettime();
        sumTS = now - prev;
        prev = now;

        auto &tv = static_cast<Token_value<double> &> (*t);
#ifndef NO_PRINT
        stringstream msg;
        msg << "drainer: " << "token: " << tv.id << " value: " << tv.value;
        SyncCout::println(msg);
#endif
    };

    double sumTA = 0;
    int N = (argc>2?stoi(argv[2]):100);
    for (int i = 0; i < N; i++) {
        auto start = Helper::gettime();
        sumTA += Helper::gettime() - start;

        inFactory.start("test", {shared_ptr<Token>(new Token_value<int>(1, i)),
                                 shared_ptr<Token>(new Token_value<int>(2, i))}, drain);

    }

    inFactory.wait();

    Helper::printtime(sumTA/N,sumTS/N);
    return 0;
}