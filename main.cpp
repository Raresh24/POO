#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

/*

    Programul gestioneaza evidenta studentilor, a disciplinelor si a notelor obtinute de studenti.

    Date de intrare:
    - fisierul "studenti.txt", care contine pentru fiecare student:
      id, nume, grupa
    - fisierul "discipline.txt", care contine pentru fiecare disciplina:
      cod, denumire, numar de credite
    - fisierul "note.txt", care contine pentru fiecare nota:
      id student, cod disciplina, valoarea notei

    Pe baza acestor date, utilizatorul poate vizualiza lista studentilor
    si a disciplinelor, poate analiza situatia scolara a unui student,
    poate calcula mediile (simpla si ponderata in functie de credite)
    si poate identifica studenti integralisti sau restantieri.

    In plus, programul permite adaugarea de noi studenti, discipline
    si note, precum si actualizarea unei note existente daca aceasta
    este reintrodusa.

    La final, se determina si se afiseaza seful de promotie,
    adica studentul cu cea mai mare medie ponderata.

    Clase folosite:
    - Student
    - Disciplina
    - Nota
    - Catalog
*/

class Student {
    int id;
    string nume, grupa;
public:
    // constructor
    Student(int id = 0, string n = "", string g = "") : id(id), nume(n), grupa(g) {}

    // constructor de copiere
    Student(const Student& s) {
        id = s.id;
        nume = s.nume;
        grupa = s.grupa;
    }

    // operator =
    Student& operator=(const Student& s) {
        if (this != &s) {
            id = s.id;
            nume = s.nume;
            grupa = s.grupa;
        }
        return *this;
    }

    // destructor
    ~Student() {}

    // getteri
    int getId() const { return id; }
    string getNume() const { return nume; }
    string getGrupa() const { return grupa; }

    // afisare obiect
    friend ostream& operator<<(ostream& out, const Student& s) {
        return out << "ID:" << s.id << " Nume:" << s.nume << " Grupa:" << s.grupa;
    }
};

class Disciplina {
    int cod, credite;
    string den;
public:

    Disciplina(int c = 0, string d = "", int cr = 0) : cod(c), credite(cr), den(d) {}


    Disciplina(const Disciplina& x) {
        cod = x.cod;
        den = x.den;
        credite = x.credite;
    }


    Disciplina& operator=(const Disciplina& x) {
        if (this != &x) {
            cod = x.cod;
            den = x.den;
            credite = x.credite;
        }
        return *this;
    }


    ~Disciplina() {}

    int getCod() const { return cod; }
    int getCredite() const { return credite; }
    string getDen() const { return den; }


    friend ostream& operator<<(ostream& out, const Disciplina& d) {
        return out << "Cod:" << d.cod << " Disciplina:" << d.den << " Credite:" << d.credite;
    }
};

class Nota {
    int idS, codD;
    float val;
public:

    Nota(int s = 0, int d = 0, float v = 0) : idS(s), codD(d), val(v) {}


    Nota(const Nota& x) {
        idS = x.idS;
        codD = x.codD;
        val = x.val;
    }


    Nota& operator=(const Nota& x) {
        if (this != &x) {
            idS = x.idS;
            codD = x.codD;
            val = x.val;
        }
        return *this;
    }


    ~Nota() {}

    int getIdS() const { return idS; }
    int getCodD() const { return codD; }
    float getVal() const { return val; }

    // setter folosit la actualizarea notei
    void setVal(float v) { val = v; }

    friend ostream& operator<<(ostream& out, const Nota& n) {
        return out << "StudentID:" << n.idS
                   << " DisciplinaCod:" << n.codD
                   << " Nota:" << n.val;
    }
};

class Catalog {
    vector<Student> st;
    vector<Disciplina> d;
    vector<Nota> n;

    // cautare student dupa id
    int findS(int id) const {
        for (int i = 0; i < st.size(); i++)
            if (st[i].getId() == id) return i;
        return -1;
    }

    // cautare disciplina dupa cod
    int findD(int cod) const {
        for (int i = 0; i < d.size(); i++)
            if (d[i].getCod() == cod) return i;
        return -1;
    }

    // cautare nota existenta
    int findN(int id, int cod) const {
        for (int i = 0; i < n.size(); i++)
            if (n[i].getIdS() == id && n[i].getCodD() == cod)
                return i;
        return -1;
    }

public:
    // incarcare date din fisiere
    void load() {
        st.clear();
        d.clear();
        n.clear();

        ifstream f1("studenti.txt"), f2("discipline.txt"), f3("note.txt");

        int id, cod, cr, sid, cd;
        float v;
        string nume, gr, den;

        // citire studenti
        while (f1 >> id >> nume >> gr)
            st.push_back(Student(id, nume, gr));

        // citire discipline
        while (f2 >> cod >> den >> cr)
            d.push_back(Disciplina(cod, den, cr));

        // citire note cu validare
        while (f3 >> sid >> cd >> v)
            addNota(Nota(sid, cd, v));
    }

    // adaugare student
    void addStudent(const Student& x) {
        if (findS(x.getId()) == -1)
            st.push_back(x);
    }

    // adaugare disciplina
    void addDisciplina(const Disciplina& x) {
        if (findD(x.getCod()) == -1)
            d.push_back(x);
    }

    // adaugare sau actualizare nota
    void addNota(const Nota& x) {
        if (findS(x.getIdS()) == -1 || findD(x.getCodD()) == -1)
            return;

        if (x.getVal() < 1 || x.getVal() > 10)
            return;

        int p = findN(x.getIdS(), x.getCodD());
        if (p != -1)
            n[p].setVal(x.getVal());
        else
            n.push_back(x);
    }

    // afisare studenti
    void showStudents() const {
        cout << "\n--- STUDENTI ---\n";
        for (int i = 0; i < st.size(); i++)
            cout << st[i] << '\n';
    }

    // afisare discipline
    void showDiscipline() const {
        cout << "\n--- DISCIPLINE ---\n";
        for (int i = 0; i < d.size(); i++)
            cout << d[i] << '\n';
    }

    // afisare note
    void showNote() const {
        cout << "\n--- NOTE ---\n";
        for (int i = 0; i < n.size(); i++)
            cout << n[i] << '\n';
    }

    // situatie scolara a unui student
    void situatie(int id) const {
        int p = findS(id);

        if (p == -1) {
            cout << "Student inexistent.\n";
            return;
        }

        cout << "\n--- SITUATIE STUDENT ---\n";
        cout << st[p] << '\n';

        bool ok = false;

        for (int i = 0; i < n.size(); i++) {
            if (n[i].getIdS() == id) {
                int pd = findD(n[i].getCodD());
                if (pd != -1) {
                    cout << d[pd].getDen() << " -> " << n[i].getVal() << '\n';
                    ok = true;
                }
            }
        }

        if (!ok)
            cout << "Studentul nu are note.\n";

        cout << "Media simpla: " << media(id) << '\n';
        cout << "Media ponderata: " << mediaPonderata(id) << '\n';
    }

    // calcul medie simpla
    float media(int id) const {
        float s = 0;
        int k = 0;

        for (int i = 0; i < n.size(); i++)
            if (n[i].getIdS() == id) {
                s += n[i].getVal();
                k++;
            }

        if (k == 0) return 0;
        return s / k;
    }

    // calcul medie ponderata
    float mediaPonderata(int id) const {
        float suma = 0;
        int cred = 0;

        for (int i = 0; i < n.size(); i++) {
            if (n[i].getIdS() == id) {
                int pd = findD(n[i].getCodD());
                if (pd != -1) {
                    suma += n[i].getVal() * d[pd].getCredite();
                    cred += d[pd].getCredite();
                }
            }
        }

        if (cred == 0) return 0;
        return suma / cred;
    }

    // vf daca studentul are restante
    bool rest(int id) const {
        for (int i = 0; i < n.size(); i++)
            if (n[i].getIdS() == id && n[i].getVal() < 5)
                return true;
        return false;
    }

    // afisare integralisti
    void integralisti() const {
        cout << "\n--- INTEGRALISTI ---\n";

        for (int i = 0; i < st.size(); i++)
            if (media(st[i].getId()) > 0 && !rest(st[i].getId()))
                cout << st[i] << " | Medie: " << mediaPonderata(st[i].getId()) << '\n';
    }

    // afisare restantieri
    void restantieri() const {
        cout << "\n--- RESTANTIERI ---\n";

        for (int i = 0; i < st.size(); i++)
            if (rest(st[i].getId()))
                cout << st[i] << '\n';
    }

    // determinare sef de promotie
    void sefPromotie() const {
        int best = -1;
        float mBest = -1;

        for (int i = 0; i < st.size(); i++) {
            float m = mediaPonderata(st[i].getId());
            if (m > mBest) {
                mBest = m;
                best = i;
            }
        }

        cout << "\n--- SEF DE PROMOTIE ---\n";

        if (best == -1 || mBest <= 0)
            cout << "Nu exista date.\n";
        else
            cout << st[best] << " | Media: " << mBest << '\n';
    }
};

int main() {
    Catalog c;

    // incarcare date
    c.load();

    // apeluri principale
    c.showStudents();
    c.showDiscipline();
    c.showNote();
    c.situatie(1);
    c.integralisti();
    c.restantieri();
    c.sefPromotie();

    // exemple de adaugare
    c.addStudent(Student(6, "Mara", "132"));
    c.addDisciplina(Disciplina(105, "POO2", 5));
    c.addNota(Nota(6, 105, 10));

    cout << "\nDupa adaugari:\n";
    c.situatie(6);

    return 0;
}
