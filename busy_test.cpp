#include <iostream>
#include <sstream>
#include <memory>
#include "GraphRepository.h"
#include "InterpreterFactory.h"
#include "Helper.h"

using namespace std;

int main(int argc, char* argv[]) {

    int n = argc>3?stoi(argv[3]):10000;
    shared_ptr<GraphRepository> gr (new GraphRepository());
    gr->add("test", {

            Statement([&n](t_in in_ptr) -> t_out {
                auto &in = static_cast<T_value<double> &> (*in_ptr[0]);
                shared_ptr<T_value<double>> res(new T_value<double>(in.value * 2));
                for (int i=0;i<n/10;i++){
                    res->set(sin(res->value));
                }
                return res;
            }, {3}, 4),

            Statement([&n](t_in in_ptr) -> t_out {
                auto &in = static_cast<T_value<double> &> (*in_ptr[0]);
                shared_ptr<T_value<double>> res(new T_value<double>(in.value * 3));
                for (int i=0;i<n*10;i++){
                    res->set(sin(res->value));
                }
                return res;
            }, {3}, 5),

            Statement([&n](t_in in_ptr) -> t_out {
                auto &in1 = static_cast<T_value<int> &> (*in_ptr[0]);
                auto &in2 = static_cast<T_value<int> &> (*in_ptr[1]);
                shared_ptr<T_value<double>> res(new T_value<double>(in1.value + in2.value));
                for (int i=0;i<n;i++){
                    res->set(sin(res->value));
                }
                return res;
            }, {1, 2}, 3),

            Statement([](t_in in_ptr) -> t_out {
                auto &in1 = static_cast<T_value<double> &> (*in_ptr[0]);
                auto &in2 = static_cast<T_value<double> &> (*in_ptr[1]);
                shared_ptr<T_value<double>> res(new T_value<double>(in1.value * in2.value));
                for (int i=0;i<10000;i++){
                    res->set(sin(res->value));
                }
                return res;
            }, {4, 5}, 6)
    });


    InterpreterFactory inFactory(gr,
                                 (argc>1?stoi(argv[1]):0)
#ifdef MULTY_QUEUE
                                 ,QueueType::MULTY
#endif
                                 );


    function<void(shared_ptr<Token>)> drain = [](shared_ptr <Token> t) {
        auto &tv = static_cast<T_value<double> &> (*t);
#ifndef NO_PRINT
        stringstream msg;
        msg << "drainer: " << "token: " << tv.type << " value: " << tv.value;
        SyncCout::println(msg);
#endif
    };


    int N = (argc>2?stoi(argv[2]):100);
    for (int i = 0; i < N; i++) {
        inFactory.start("test", {shared_ptr<Token>(new T_value<int>(1, i)),
                                 shared_ptr<Token>(new T_value<int>(2, i))}, drain);
    }

    inFactory.wait();
    return 0;
}