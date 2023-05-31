#include "libraries.h"
#include "header.h"

int main() {
    Vector<Studentas> studentai;
    int kiek_nd;
    char pasirinkimas, pasirinkimas2, skaityti;
    bool is_naujo = false, is_naujo2 = false;

    auto sPrograma = std::chrono::high_resolution_clock::now();
    do {
        cout << "-----------------------------------------------------------------------" << endl;
        cout << "Duomenis skaityti is failo? (Y/N): ";
        cin >> skaityti;

        if(skaityti == 'Y' || skaityti == 'y') {
            char generuoti;

            do {
                cout << endl << "Sugeneruoti faila? (Y/N): ";
                cin >> generuoti;

                if(generuoti == 'Y' || generuoti == 'y') {
                    int kiek_studentu, kiek_nd2;
                    string failasGen;

                    cout << "Iveskite studentu kieki: ";
                    cin >> kiek_studentu;

                    cout << "Iveskite namu darbu rezultatu kieki: ";
                    cin >> kiek_nd2;

                    cout << "Iveskite sugeneruoto failo pavadinima: ";
                    cin >> failasGen; cout << endl;

                    cout << "Failas [" << failasGen << "] generuojamas... ";
                    generatorius(failasGen, kiek_studentu, kiek_nd2);

                    cout << "-----------------------------------------------------------------------" << endl;

                    break;
                } else if(generuoti == 'N' || generuoti == 'n') {
                    break;
                } else {
                    cout << endl << "Tokio pasirinkimo [" << generuoti << "] nera.";

                    continue;
                }
            } while(true);

            auto sPrograma = std::chrono::high_resolution_clock::now();
            failo_skaitymas(studentai);

            cout << "-----------------------------------------------------------------------" << endl;

            break;
        } else if (skaityti == 'N' || skaityti == 'n') {
            do {
                string vardas, pavarde;

                cout << "-----------------------------------------------------------------------" << endl;

                cout << "Iveskite studento varda: ";
                cin >> vardas;
                cout << "Iveskite studento pavarde: ";
                cin >> pavarde; cout << endl;

                cout << "Generuoti mokinio rezultatus atsitiktinai? (Y/N): ";
                cin >> pasirinkimas2;

                if(pasirinkimas2 == 'Y' || pasirinkimas2 == 'y') {
                    atsitiktiniai_rez(vardas, pavarde, kiek_nd, studentai);
                } else if (pasirinkimas2 == 'N' || pasirinkimas2 == 'n') {
                    rasomi_rez(vardas, pavarde, is_naujo2, studentai);
                } else {
                    cout << "Tokio pasirinkimo [" << pasirinkimas2 << "] nera." << endl;

                    is_naujo = true;
                    continue;
                }

                cout << "-----------------------------------------------------------------------";
                
                do {
                    cout << "Ar norite ivesti nauja studenta? (Y/N): ";
                    cin >> pasirinkimas;

                    if(pasirinkimas != 'N' && pasirinkimas != 'n' && pasirinkimas != 'Y' && pasirinkimas != 'y') {
                        cout << "Tokio pasirinkimo [" << pasirinkimas << "] nera." << endl;
                    } else {break;}
                } while(true);

                is_naujo = false;
            } while(is_naujo || pasirinkimas == 'Y' || pasirinkimas == 'y');
        }
    } while(is_naujo);  

    galutinis(studentai);
    sort(studentai.begin(), studentai.end(), [](const Studentas& s1, const Studentas& s2) {
        return s1.getVardas() < s2.getVardas();
    });
    auto ePrograma = std::chrono::system_clock::now();
    std::chrono::duration<double> dPrograma = ePrograma - sPrograma;
    isvesti(studentai);

    cout << endl << "-----------------------------------------------------------------------" << endl;

    cout << "Programos veikimas uztruko " << dPrograma.count() << "s." << endl;

    return 0;
}