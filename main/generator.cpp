#include "header.h"

void generatorius(string failas, int kiek_studentu, int kiek_nd) {
    auto sGeneravimas = std::chrono::high_resolution_clock::now();
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 10), sdist(1, kiek_studentu);

    ofstream failasO(failas);

    std::stringstream buffer;

    buffer << setw(15) << left << "Vardas" << setw(15) << left << "Pavarde";
    for(int i = 1; i <= kiek_nd; i++) {
        buffer << setw(10) << right << ("ND" + to_string(i));
    }
    buffer << setw(10) << right << "Egz." << endl;

    for(int i = 1; i <= kiek_studentu; i++) {
        buffer << setw(15) << left << ("Vardas" + to_string(sdist(mt))) << setw(15) << left << ("Pavarde" + to_string(sdist(mt)));
        for (int j = 1; j <= kiek_nd; j++) {
            buffer << setw(10) << right << dist(mt);
        }
        buffer << setw(10) << right << dist(mt) << endl;

        if (i % 1000 == 0) {
            failasO << buffer.str();
            buffer.str(""); 
        }
    }

    failasO << buffer.str();
    auto eGeneravimas = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> dGeneravimas = eGeneravimas - sGeneravimas;
    cout << "Baigta per " << dGeneravimas.count() << "s." << endl;

    failasO.close();
}
