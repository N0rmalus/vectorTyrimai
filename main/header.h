#include "libraries.h"

// Abstract base class Human
class Zmogas {
    protected:
        string vardas;
        string pavarde;

    public:
        Zmogas(const string& vardas, const string& pavarde)
            : vardas(vardas), pavarde(pavarde) {}

        // Getteriai
        string getVardas() const { return vardas; }
        string getPavarde() const { return pavarde; }

        // Virtuali Funkcija
        virtual void rasoInfo(ofstream& raso) const = 0;

        // Destruktorius
        virtual ~Zmogas() {}
};

// Derived class Student from Human
class Studentas : public Zmogas {
    private:
        vector<int> nd_rezultatai;
        int egzamino_rezultatas;
        double galutinis_vid, galutinis_med;

    public:
        // R05 -----
        Studentas(const string& vardas, const string& pavarde, const vector<int>& nd_rezultatai,
                int egzamino_rezultatas, double galutinis_vid, double galutinis_med)
            : Zmogas(vardas, pavarde), nd_rezultatai(nd_rezultatai), egzamino_rezultatas(egzamino_rezultatas),
            galutinis_vid(galutinis_vid), galutinis_med(galutinis_med) {}
        Studentas(const Studentas& other)
            : Zmogas(other), nd_rezultatai(other.nd_rezultatai), egzamino_rezultatas(other.egzamino_rezultatas),
            galutinis_vid(other.galutinis_vid), galutinis_med(other.galutinis_med) {}
        Studentas(Studentas&& other) noexcept
            : Zmogas(move(other)), nd_rezultatai(move(other.nd_rezultatai)),
            egzamino_rezultatas(other.egzamino_rezultatas), galutinis_vid(other.galutinis_vid),
            galutinis_med(other.galutinis_med) {}
        
        Studentas& operator=(const Studentas& other) {
            if(this != &other) {
                Zmogas::operator=(other);
                nd_rezultatai = other.nd_rezultatai;
                egzamino_rezultatas = other.egzamino_rezultatas;
                galutinis_vid = other.galutinis_vid;
                galutinis_med = other.galutinis_med;
            }
            return *this;
        } Studentas& operator=(Studentas&& other) noexcept {
            if(this != &other) {
                Zmogas::operator=(move(other));
                nd_rezultatai = move(other.nd_rezultatai);
                egzamino_rezultatas = other.egzamino_rezultatas;
                galutinis_vid = other.galutinis_vid;
                galutinis_med = other.galutinis_med;
            }
            return *this;
        }

        // Setteriai
        void setNdRezultatai(const vector<int>& nd_rezultatai) { this->nd_rezultatai = nd_rezultatai; }
        void setEgzaminoRezultatas(int egzamino_rezultatas) { this->egzamino_rezultatas = egzamino_rezultatas; }
        void setGalutinisVid(double galutinis_vid) { this->galutinis_vid = galutinis_vid; }
        void setGalutinisMed(double galutinis_med) { this->galutinis_med = galutinis_med; }

        // Getteriai
        vector<int> getNdRezultatai() const { return nd_rezultatai; }
        int getEgzaminoRezultatas() const { return egzamino_rezultatas; }
        double getGalutinisVid() const { return galutinis_vid; }
        double getGalutinisMed() const { return galutinis_med; }

        // Perrašyta printInfo funkcija iš bazinės klasės
        void rasoInfo(ofstream& raso) const override {
            raso << "Vardas: " << vardas << endl;
            raso << "Pavarde: " << pavarde << endl;
            raso << "ND rezultatai: ";
            for (int rezultatas : nd_rezultatai)
                raso << rezultatas << " ";
            raso << endl << "Egzamino rezultatas: " << egzamino_rezultatas << endl;
            raso << "Galutinis (Vid.): " << galutinis_vid << endl;
            raso << "Galutinis (Med.): " << galutinis_med << endl;
            raso << "--------" << endl;
        }

        // Destruktorius
        ~Studentas() {}
};

template <class T>
class Vector {
    public:
        typedef T* iterator; 
        typedef const T* const_iterator; 
        typedef size_t size_type;
        typedef T value_type;

        Vector() { create(); }
        explicit Vector(size_type n, const T& val = T{}) { create(n, val); }
        Vector(const Vector& v) {create(v.begin(), v.end()); }
        Vector(const std::vector<T>& other) {
            create(other.begin(), other.end());
        }
        ~Vector() { uncreate(); }

        Vector& operator=(const Vector& rhs) {
            if(&rhs != this) {
                uncreate();
                create(rhs.begin(), rhs.end());
            }
            return *this;
        } 
        Vector& operator=(const std::vector<T>& other) {
            if (this != &other) {
                uncreate();
                create(other.begin(), other.end());
            }
            return *this;
        }

        size_type size() const { return avail - data; }
        // size_type capacity() const { return limit - data; }
        T& operator[](size_type i) { return data[i]; }
        const T& operator[](size_type i) const { return data[i]; }

        iterator begin() { return data; }
        const_iterator begin() const { return data; }
        iterator end() { return limit; }
        const_iterator end() const { return limit; }

        void push_back(const T& val) {
            if(avail == limit)
                grow();
            unchecked_append(val);
        } 
        void resize(size_type new_size, const T& val = T{}) {
            if(new_size < size()) {
                iterator new_limit = data + new_size;
                while(limit != new_limit)
                    alloc.destroy(--limit);
            }
            else if(new_size > size()) {
                if(new_size > capacity())
                    reserve(new_size);
                iterator new_limit = data + new_size;
                while (limit != new_limit)
                    unchecked_append(val);
            }
            limit = data + new_size;
        } 
        void reserve(size_type new_capacity) {
            if(new_capacity > capacity()) {
                iterator new_data = alloc.allocate(new_capacity);
                iterator new_avail = uninitialized_copy(data, avail, new_data);
                uncreate();
                data = new_data;
                avail = new_avail;
                limit = data + new_capacity;
            }
        } 
        void pop_back() {
            if(avail != data)
                alloc.destroy(--avail);
        }
        void clear() { uncreate();}
        bool empty() const { return data == avail; }
        size_type capacity() const { return limit - data; }
        
        iterator erase(iterator pos) {
            if(pos < begin() || pos >= end())
                throw std::out_of_range("Invalid iterator position");

            iterator new_end = pos;
            alloc.destroy(new_end++);
            while(new_end != end()) {
                *pos++ = *new_end++;
            }
            --avail;

            return pos;
        }
        iterator nth_element(iterator first, iterator nth, iterator last) {
            if (nth < first || nth >= last)
                throw std::out_of_range("Invalid iterator position");

            while (true) {
                iterator pivot = partition(first, last);
                if (pivot == nth)
                    return pivot;
                else if (pivot < nth)
                    first = pivot + 1;
                else
                    last = pivot;
            }
        }
    private:
        iterator data;
        iterator avail;
        iterator limit;

        allocator<T> alloc;

        iterator partition(iterator first, iterator last) {
            T& pivot = *first;
            iterator i = first + 1;
            iterator j = last - 1;

            while (true) {
                while (i < last && *i <= pivot)
                    ++i;
                while (j > first && *j >= pivot)
                    --j;

                if (i >= j)
                    break;

                std::swap(*i, *j);
            }

            std::swap(*first, *j);
            return j;
        }
        void create() {
            data = avail = limit = nullptr;
        }
        void create(size_type n, const T& val) {
            data = alloc.allocate(n);
            limit = avail = data + n;
            uninitialized_fill(data, limit, val);
        }
        void create(const_iterator i, const_iterator j) {
            data = alloc.allocate(j - i);
            limit = avail = uninitialized_copy(i,j,data);
        }
        void uncreate() {
            if (data) {
                iterator it = avail;
                while (it != data)
                    alloc.destroy(--it);
                alloc.deallocate(data, limit - data);
            }
            data = limit = avail = nullptr;
        }
        void grow() {
            size_type new_size = max(2 * (limit - data), ptrdiff_t(1));

            iterator new_data = alloc.allocate(new_size);
            iterator new_avail = uninitialized_copy(data, avail, new_data);

            uncreate();

            data = new_data;
            avail = new_avail;
            limit = data + new_size;
        }
        void unchecked_append(const T& val) {
            allocator_traits<allocator<T>>::construct(alloc, avail++, val);
        }

        template <typename InputIterator>
        void create(InputIterator first, InputIterator last) {
            size_type n = std::distance(first, last);
            data = alloc.allocate(n);
            limit = avail = std::uninitialized_copy(first, last, data);
        }
};

void generatorius(string failas, int kiek_studentu, int kiek_nd);
void failo_skaitymas(Vector<Studentas>& studentai);
void atsitiktiniai_rez(string vardas, string pavarde, int kiek_nd, Vector<Studentas>& studentai);
void rasomi_rez(string vardas, string pavarde, bool is_naujo2, Vector<Studentas>& studentai);
void galutinis(Vector<Studentas>& studentai);
void isvesti(Vector<Studentas>& studentai);
