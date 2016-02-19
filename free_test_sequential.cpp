#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    double res1,res2,res3,res4;
    for (int i = 0; i < (argc > 1 ? stoi(argv[1]) : 100); i++) {
        res1 = i + i;
        res2 = res1;
        res3 = res2;
        res4 = res3;
#ifndef NO_PRINT
        cout << "drainer: " << "token: " << i << " value: " << res4 << endl;
#endif
    }
    return res4;
}