//
// Created by luca on 17/02/2016.
//

#ifndef SPM_PROJECT_HELPER_H
#define SPM_PROJECT_HELPER_H

#include <iostream>
#include <sys/time.h>
#include <iomanip>

using namespace std;
namespace Helper {
    static double gettime(){
        struct timeval t;
        gettimeofday(&t, NULL);
        return (double) t.tv_sec + t.tv_usec * 1e-6;
    };

    static void printtime(double ta, double ts){
        cout << fixed << setprecision( 10 ) << ta <<":"<< ts << ":" << endl;
    }
};


#endif //SPM_PROJECT_HELPER_H
