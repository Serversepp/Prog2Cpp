#include <iostream>
#include <string>
#include <list>
#include <map>
#include <fstream>

using namespace std; // damit man nicht std::string schreiben muss

class Artikel{
    private:
        int artnr;
        string name;
        double preis;
    public:
        Artikel(int artnr, string name, double preis){this->artnr=artnr;this->name=name;this->preis=preis;}
        void setartnr(int artnr){this->artnr=artnr;}
        void setpreis(int preis){this->preis=preis;}
        void setname(string name){this->name=name;}

    int getArtnr() const {
        return artnr;
    }

    const string &getName() const {
        return name;
    }

    double getPreis() const {
        return preis;
    }

    Artikel() {

    }
};

class verkaufte_Artikel{
private:
    int artnr;
    int menge;
public:
    void setartnr(int artnr){this->artnr=artnr;}
    void setmenge(int menge){this->menge=menge;}

    verkaufte_Artikel(const Artikel artikel) {
        artnr = artikel.getArtnr();
        menge = 1;
    }
};
class Kasse{
private:
    map<int, Artikel> ArtikelMap;
    list<verkaufte_Artikel> verkaufteArtikel;

public:
    Kasse();
    int eingabe();
    void Artikelanlegen();
    void Artikelverkaufen();
    double Umsatz();
    void Artikelspeichern();
    void Artikellisten();
    void Artikellesen();

};

int Kasse::eingabe() {
    printf("1: Artikel anlegen\n2: Artikel verkaufen\n3: Artikel in Datei speichern\n4: Artikel von Datei lesen\n"
           "5: Umsätze anzeigen\n6: Artikel listen\n7: Artikel lesen \n9999: Ende\n");
    int eingabe;
    scanf("%i", &eingabe);
    return eingabe;
}

void Kasse::Artikelanlegen() {
    int artnr;
    int preis;
    string name;
    cout << "Geben sie die Artikel nummer ein" <<endl;
    scanf("%i", &artnr);
    cout << "Geben sie den Artikel Namen ein" <<endl;
    scanf("%s", &name);
    cout << "Geben sie die Artikel nummer ein" <<endl;
    cin >> preis;
    this->ArtikelMap.emplace(this->ArtikelMap.size()+1, Artikel(artnr,name, preis));
}

void Kasse::Artikelverkaufen() {
    /*for (auto iter = ArtikelMap.begin(); iter != ArtikelMap.end(); iter++){
    }*/
    for (const auto &item : ArtikelMap) {
        this->verkaufteArtikel.insert(verkaufteArtikel.end(),verkaufte_Artikel(item.second));
    }
}
double Kasse::Umsatz() {
    int cntr = 0;
    double umsatz;
    for (const auto &i : this->verkaufteArtikel){
        umsatz += i*ArtikelMap.find(1)->second.getPreis();
    }
    return umsatz;
}

void Kasse::Artikellisten() {
    for (const auto &item : ArtikelMap) {
        cout << "Name = " << item.second.getName() << " Preis = " << item.second.getPreis() << " mit Artnr:  "<< item.second.getArtnr() << endl;
    }
}
void Kasse::Artikelspeichern() {
    fstream f;
    f.open("art.txt", ios::out);
    for (const auto &item : ArtikelMap) {
        f << "Name = " << item.second.getName() << " Preis = " << item.second.getPreis() << " mit Artnr:  "<< item.second.getArtnr() << endl;
    }
}
void Kasse::Artikellesen() {
    ifstream f("art.txt");
    int artnr;
    string name;
    int preis;

    if(!f) exit(-1);
    while(!f.eof()){
        f >> artnr;
        f >> name;
        f >> preis;
        this->ArtikelMap.emplace(this->ArtikelMap.size()+1, Artikel(artnr,name, preis));
    }

}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
