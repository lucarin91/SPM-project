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
    static bool _print;

public:
    static void println(const stringstream& in);

    static void setSync(bool v){_sync = v;}
    static void setPrint(bool v){_print = v;}
};


#endif //SPM_PROJECT_SYNCCOUT_H
