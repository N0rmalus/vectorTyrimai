#include "header.h"

void failo_skaitymas(Vector<Studentas>& studentai) {
    string failas;
    do {
        cout << "Failu sarasas: ";
        system("ls *.txt");
        cout << "Pasirinkite faila: ";
        cin >> failas;

        ifstream skaito(failas);
        if(skaito.is_open()) {
            cout << endl << "Failas [" << failas << "] skaitomas... ";

            auto sSkaitymas = std::chrono::high_resolution_clock::now();
            string line;

            getline(skaito, line);

            size_t expectedStudentCount = 10000000; 
            studentai.reserve(expectedStudentCount);

            while (getline(skaito, line)) {
                string vardasF, pavardeF;
                vector<int> nd_rezultataiF;
                int egzamino_rezultatasF;

                istringstream iss(line);
                iss >> vardasF >> pavardeF;

                int rezultatas;
                while (iss >> rezultatas) {
                    nd_rezultataiF.push_back(rezultatas);
                }
                egzamino_rezultatasF = nd_rezultataiF.back();
                nd_rezultataiF.pop_back();

                Studentas naujas_studentas(vardasF, pavardeF, nd_rezultataiF, egzamino_rezultatasF, 0, 0);
                studentai.push_back(naujas_studentas);
            }
            skaito.close();
            auto eSkaitymas = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> dSkaitymas = eSkaitymas - sSkaitymas;
            cout << "Baigta per " << dSkaitymas.count() << "s." << endl;

            break;
        } else {
            cout << endl << "Tokio failo [" << failas << "] nera." << endl;

            continue;
        }
    } while (true);
}

void atsitiktiniai_rez(string vardas, string pavarde, int kiek_nd, Vector<Studentas>& studentai) {
    int nd_rezultatas, egzamino_rezultatas;
    vector<int> nd_rezultatai;

    cout << "-----------------------------------------------------------------------" << endl;
    do {
        try {
            cout << "Iveskite [" << vardas << " " << pavarde << "] namu darbu rezultatu kieki, kuris bus atsitiktinai sugeneruotas: ";
            cin >> kiek_nd; cout << endl;
            if(cin.fail()) {
                throw invalid_argument("Klaida: ivestas neteisingas simbolis.");
            } else {break;}
        } catch(const invalid_argument& e) {
            cout << e.what() << endl;
            cin.clear(); 
            cin.ignore();
        }
    } while(true);

    // Generuojami atsitiktiniai namų darbų bei egzamino rezultatai
    std::mt19937 mt(1729);
    std::uniform_int_distribution<int> dist(1, 10);
    for(int i = 0; i < kiek_nd; i++) {
        nd_rezultatas = dist(mt);
        nd_rezultatai.push_back(nd_rezultatas);
        cout << "Atsitiktinis [" << vardas << " " << pavarde << "] namu darbu rezultatas: " << nd_rezultatas << endl;
    }
    egzamino_rezultatas = dist(mt);
    cout << endl << "Atsitiktinis [" << vardas << " " << pavarde << "] egzamino rezultatas: " << egzamino_rezultatas << endl;

    Studentas student(vardas, pavarde, nd_rezultatai, egzamino_rezultatas, 0, 0);
    studentai.push_back(student);
}
void rasomi_rez(string vardas, string pavarde, bool is_naujo2, Vector<Studentas>& studentai) {
    int nd_rezultatas, egzamino_rezultatas;
    vector<int> nd_rezultatai;

    cout << "-----------------------------------------------------------------------" << endl;
    do {
        try {
            cout << "Iveskite [" << vardas << " " << pavarde << "] namu darbo rezultata intervale [1; 10] (arba 0, jei daugiau nenorite vesti): ";
            cin >> nd_rezultatas;

            if(cin.fail()) {
                throw invalid_argument("Klaida: ivestas neteisingas simbolis.");
            } if(nd_rezultatas != 0 && nd_rezultatas > 0 && nd_rezultatas <= 10) {
                nd_rezultatai.push_back(nd_rezultatas);
            } else if(nd_rezultatas < 0 || nd_rezultatas > 10) {
                cout << "Klaida: pazymys turi buti intervale [1; 10]." << endl;

                continue;
            } else if(nd_rezultatas == 0) {break;}  
        } catch(const invalid_argument& e) {
            cout << e.what() << endl;
            cin.clear(); 
            cin.ignore();

            is_naujo2 = true;
        }
    } while (nd_rezultatas != 0 || is_naujo2 != false);

    do {
        try {
            cout << endl << "Iveskite [" << vardas << " " << pavarde << "] egzamino rezultata intervale [1; 10]: ";
            cin >> egzamino_rezultatas;
            
            if(cin.fail()) {
                throw invalid_argument("Klaida: ivestas neteisingas simbolis.");
            }
        } catch(const invalid_argument& e) {
            cout << e.what() << endl;
            cin.clear(); 
            cin.ignore();
        } if(egzamino_rezultatas > 0 && egzamino_rezultatas <= 10) {
            Studentas student(vardas, pavarde, nd_rezultatai, egzamino_rezultatas, 0, 0);
            studentai.push_back(student);

            break;
        } else if(egzamino_rezultatas < 1 && egzamino_rezultatas > 10) {
            cout << "Klaida: rezultatas turi buti intervale [1; 10]." << endl;

            continue;
        }
    } while(true);  
}
void galutinis(Vector<Studentas>& studentai) {
    for (Studentas& s : studentai) {
        const Vector<int>& nd_rezultatai = s.getNdRezultatai();
        int dydis = nd_rezultatai.size();

        double vidurkis = 0;
        double mediana = 0;
        if (dydis > 0) {
            // Galutinio balo apskaičiavimas su rezultatų vidurkiu
            double sum = accumulate(nd_rezultatai.begin(), nd_rezultatai.end(), 0.0);
            vidurkis = sum / dydis;

            // Galutinio balo apskaičiavimas su rezultatų mediana
            Vector<int> sorted_nd_rezultatai = nd_rezultatai;
            Vector<int>::iterator nth = sorted_nd_rezultatai.nth_element(sorted_nd_rezultatai.begin(), sorted_nd_rezultatai.begin() + dydis / 2, sorted_nd_rezultatai.end());

            if (dydis % 2 == 0) {
                Vector<int>::iterator nth = sorted_nd_rezultatai.nth_element(sorted_nd_rezultatai.begin(), sorted_nd_rezultatai.begin() + dydis / 2 - 1, sorted_nd_rezultatai.end());
                mediana = (double)(sorted_nd_rezultatai[dydis / 2 - 1] + sorted_nd_rezultatai[dydis / 2]) / 2;
            } else {
                mediana = sorted_nd_rezultatai[dydis / 2];
            }
        }

        double galutinis_med = 0.4 * mediana + 0.6 * s.getEgzaminoRezultatas();
        double galutinis_vid = 0.4 * vidurkis + 0.6 * s.getEgzaminoRezultatas();

        s.setGalutinisMed(galutinis_med);
        s.setGalutinisVid(galutinis_vid);
    }
}
void isvesti(Vector<Studentas>& studentai) {
    vector<Studentas> win;
    vector<Studentas> loss;
    int strategija;

    ofstream raso("operatorius.txt");
    ofstream rasoL("luzeriai.txt");
    ofstream rasoW("neluzeriai.txt");
    rasoL << setw(15) << left << "Pavarde" << setw(15) << left << "Vardas" << setw(20) << left << "Galutinis (Vid.)" << "Galutinis (Med.)" << endl;
    rasoW << setw(15) << left << "Pavarde" << setw(15) << left << "Vardas" << setw(20) << left << "Galutinis (Vid.)" << "Galutinis (Med.)" << endl;
    rasoL << "--------------------------------------------------------------------" << endl;
    rasoW << "--------------------------------------------------------------------" << endl;

    cout << "Kokia rusiavimo strategija norite naudoti? (1 / 2): ";
    cin >> strategija; cout << endl;

    // Duomenų išvedimas
    // for (const auto& s : studentai)
    //     s.rasoInfo(raso);

    // Mokinių duomenų išrašymas
    switch (strategija) {
        case 1: {
            win.reserve(studentai.size());
            loss.reserve(studentai.size());

            cout << "Studentai rusiuojami... ";

            auto sRusiavimas = std::chrono::high_resolution_clock::now();
            for (const auto& s : studentai) {
                const vector<int>& nd_rezultatai = s.getNdRezultatai();
                double galutinisVid = s.getGalutinisVid();
                double galutinisMed = s.getGalutinisMed();

                if (nd_rezultatai.empty() || galutinisVid <= 0 || galutinisMed <= 0) {
                    continue;
                }

                if (galutinisVid < 5.0 && galutinisMed < 5.0) {
                    loss.push_back(std::move(s));
                } else {
                    win.push_back(std::move(s));
                }
            }
            auto eRusiavimas = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> dRusiavimas = eRusiavimas - sRusiavimas;
            cout << "Baigta per " << dRusiavimas.count() << "s.";

            cout << endl << "Duomenys spausdinami i faila... ";
            auto sSpausdinimas = std::chrono::high_resolution_clock::now();
            for(auto& l : loss) {
                rasoL << setw(15) << left << l.getPavarde() << setw(15) << left << l.getVardas() << setw(20) << left << fixed << setprecision(2) << l.getGalutinisVid() << fixed << setprecision(2) << l.getGalutinisMed() << endl;
            } for(auto& w : win) {
                rasoW << setw(15) << left << w.getPavarde() << setw(15) << left << w.getVardas() << setw(20) << left << fixed << setprecision(2) << w.getGalutinisVid() << fixed << setprecision(2) << w.getGalutinisMed() << endl;
            }
            auto eSpausdinimas = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> dSpausdinimas = eSpausdinimas - sSpausdinimas;
            cout << "Baigta per " << dSpausdinimas.count() << "s.";

            rasoL.close();
            rasoW.close();
            break;
        }
        case 2: {
            win.reserve(studentai.size());
            loss.reserve(studentai.size());

            cout << "Studentai rusiuojami... ";
            auto sRusiavimas = std::chrono::high_resolution_clock::now();
            for (const auto& s : studentai) {
                const vector<int>& nd_rezultatai = s.getNdRezultatai();
                double galutinisVid = s.getGalutinisVid();
                double galutinisMed = s.getGalutinisMed();

                if (nd_rezultatai.empty() || galutinisVid <= 0 || galutinisMed <= 0 ||
                    (galutinisVid < 5.0 && galutinisMed < 5.0)) {
                    loss.push_back(std::move(s));
                }
            }

            // vector<Studentas>::iterator newEnd = remove_if(studentai.begin(), studentai.end(), [](const auto& s) {
            //     const vector<int>& nd_rezultatai = s.getNdRezultatai();
            //     double galutinisVid = s.getGalutinisVid();
            //     double galutinisMed = s.getGalutinisMed();
            //             return nd_rezultatai.empty() || galutinisVid <= 0 || galutinisMed <= 0 ||
            //         (galutinisVid < 5.0 && galutinisMed < 5.0);
            // });
            // studentai.erase(newEnd, studentai.end());
            auto eRusiavimas = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> dRusiavimas = eRusiavimas - sRusiavimas;
            cout << "Baigta per " << dRusiavimas.count() << "s.";

            cout << endl << "Duomenys spausdinami i faila... ";
            auto sSpausdinimas = std::chrono::high_resolution_clock::now();
            for(auto& l : loss) {
                rasoL << setw(15) << left << l.getPavarde() << setw(15) << left << l.getVardas() << setw(20) << left << fixed << setprecision(2) << l.getGalutinisVid() << fixed << setprecision(2) << l.getGalutinisMed() << endl;
            } for(auto& s : studentai) {
                rasoW << setw(15) << left << s.getPavarde() << setw(15) << left << s.getVardas() << setw(20) << left << fixed << setprecision(2) << s.getGalutinisVid() << fixed << setprecision(2) << s.getGalutinisMed() << endl;
            }
            auto eSpausdinimas = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> dSpausdinimas = eSpausdinimas - sSpausdinimas;
            cout << "Baigta per " << dSpausdinimas.count() << "s.";

            rasoL.close();
            rasoW.close();
            break;
        }
        default: {
            cout << "Tokio pasirinkimo nera. Tesiama su pirma strategija." << endl;

            win.reserve(studentai.size());
            loss.reserve(studentai.size());

            cout << "Studentai rusiuojami... ";

            auto sRusiavimas = std::chrono::high_resolution_clock::now();
            for (const auto& s : studentai) {
                const vector<int>& nd_rezultatai = s.getNdRezultatai();
                double galutinisVid = s.getGalutinisVid();
                double galutinisMed = s.getGalutinisMed();

                if (nd_rezultatai.empty() || galutinisVid <= 0 || galutinisMed <= 0) {
                    continue;
                }

                if (galutinisVid < 5.0 && galutinisMed < 5.0) {
                    loss.push_back(std::move(s));
                } else {
                    win.push_back(std::move(s));
                }
            }
            auto eRusiavimas = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> dRusiavimas = eRusiavimas - sRusiavimas;
            cout << "Baigta per " << dRusiavimas.count() << "s.";

            cout << endl << "Duomenys spausdinami i faila... ";
            auto sSpausdinimas = std::chrono::high_resolution_clock::now();
            for(auto& l : loss) {
                rasoL << setw(15) << left << l.getPavarde() << setw(15) << left << l.getVardas() << setw(20) << left << fixed << setprecision(2) << l.getGalutinisVid() << fixed << setprecision(2) << l.getGalutinisMed() << endl;
            } for(auto& w : win) {
                rasoW << setw(15) << left << w.getPavarde() << setw(15) << left << w.getVardas() << setw(20) << left << fixed << setprecision(2) << w.getGalutinisVid() << fixed << setprecision(2) << w.getGalutinisMed() << endl;
            }
            auto eSpausdinimas = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> dSpausdinimas = eSpausdinimas - sSpausdinimas;
            cout << "Baigta per " << dSpausdinimas.count() << "s.";

            rasoL.close();
            rasoW.close();
            break;
        }
    }
}