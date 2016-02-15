//
// Created by luca on 12/02/2016.
//

#ifndef SPM_PROJECT_SYNCCOUT_H
#define SPM_PROJECT_SYNCCOUT_H
#include <iostream>
#include <sstream>
#include <mutex>

using namespace std;

class SyncCout {
    static mutex _m;
    static bool _sync;

public:
    static void println(const stringstream& in){
        if (_sync) _m.lock();
        cout << in.str() << endl << flush;
        if (_sync) _m.unlock();
    }

    static void setSync(bool v){
        _sync = v;
    }
};


#endif //SPM_PROJECT_SYNCCOUT_H
