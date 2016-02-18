#include <iostream>
#include <math.h>

using namespace std;

int main(int argc, char *argv[]) {
    double res1,res2,res3,res4;
    int n = argc>2?stoi(argv[2]):10000;
    for (int i = 0; i < (argc > 1 ? stoi(argv[1]) : 100); i++) {
        res1 = i + i;
        for (int j = 0; j < n; j++) {
            res1 = sin(res1);
        }
        res2 = res1;
        for (int j = 0; j < n; j++) {
           res2 = sin(res2);
        }
        res3 = res2;
        for (int j = 0; j < n; j++) {
            res3 = sin(res3);
        }
        res4 = res3;
        for (int j = 0; j < n; j++) {
            res4 = sin(res4);
        }
#ifndef NO_PRINT
        cout << "drainer: " << "token: " << i << " value: " << res4 << endl;
#endif
    }
    return res4;
}