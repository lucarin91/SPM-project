#include <iostream>
#include <math.h>

using namespace std;

int main(int argc, char *argv[]) {
    double res;
    for (int i = 0; i < (argc > 2 ? stoi(argv[2]) : 100); i++) {
        res = i + i;
        for (int j = 0; j < 10000; j++) {
            res = sin(res);
        }
       /* for (int j = 0; j < 10000; j++) {
            res = sin(res);
        }*/
        for (int j = 0; j < 10000; j++) {
            res = sin(res);
        }
        for (int j = 0; j < 10000; j++) {
            res = sin(res);
        }
#ifndef NO_PRINT
        cout << "drainer: " << "token: " << i << " value: " << res << endl;
#endif
    }
    return res;
}