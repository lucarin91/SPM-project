//
// Created by luca on 12/02/2016.
//

#include "SyncCout.h"

mutex SyncCout::_m;
bool SyncCout::_sync = true;
bool SyncCout::_print = true;

void SyncCout::println(const stringstream &in) {
    if (_print) {
        if (_sync) _m.lock();
        cout << in.str() << endl << flush;
        if (_sync) _m.unlock();
    }
}
