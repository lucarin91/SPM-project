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
            Statement([](t_in in_ptr) -> t_out {
                auto &in = static_cast<T_value<int> &> (*in_ptr[0]);
                return shared_ptr<T_value<int>>(new T_value<int>(in.value * 2));
            }, {3}, 4),

            Statement([](t_in in_ptr) -> t_out {
                auto &in = static_cast<T_value<int> &> (*in_ptr[0]);
                return shared_ptr<T_value<int>>(new T_value<int>(in.value * 3));
            }, {3}, 5),

            Statement([](t_in in_ptr) -> t_out {
                auto &in1 = static_cast<T_value<int> &> (*in_ptr[0]);
                auto &in2 = static_cast<T_value<int> &> (*in_ptr[1]);
                return shared_ptr<T_value<int>>(new T_value<int>(in1.value + in2.value));
            }, {1, 2}, 3)
    });

    InterpreterFactory inFactory(gr,
                                 (argc>1?stoi(argv[1]):0)
#ifdef MULTY_QUEUE
            ,QueueType::MULTY
#endif
    );

    function<void(shared_ptr<Token>)> drain = [](shared_ptr <Token> t) {
        auto &tv = static_cast<T_value<int> &> (*t);
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