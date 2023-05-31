#include "vectorFunc.h"

int main() {
    unsigned int sz = 10000;  // 100000, 1000000, 10000000, 100000000
    unsigned int n = 5;

    for(int i = 0; i < n; i++) {
        // Pradėti std::vector užpildymo laiko matavimą
        auto sStdVector = std::chrono::high_resolution_clock::now();
        vector<int> v1;

        v1.resize(sz);
        for (int i = 1; i <= sz; ++i)
            v1.push_back(i);
        auto eStdVector = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> dStdVector = eStdVector - sStdVector;

        cout << "std::vector uzpildymas su " << sz << " elementu truko - " << dStdVector.count() << " s." << endl;

        // Pradėti class Vector užpildymo laiko matavimą
        auto sVector = std::chrono::high_resolution_clock::now();
        Vector<int> v2;

        v2.resize(sz);
        for (int i = 1; i <= sz; ++i)
            v2.push_back(i);
        auto eVector = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> dVector = eVector - sVector;

        cout << "class Vector uzpildymas su " << sz << " elementu truko - " << dVector.count() << " s." << endl << endl;

        v1.clear();
        v2.clear();
        sz *= 10;
    }
    
    return 0;
}