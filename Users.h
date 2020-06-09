#include <vector>
#include <iostream>;

using namespace std;

class Uzytkownik{
public:
    string login;
    string haslo;
    int id;

public:
    Uzytkownik(string, string, int);
    ~Uzytkownik();
    void nowyUzytownik(vector<Uzytkownik>& uzytkownicy, int& iloscUzytkownikow);
    bool sprawdzCzyWolnyLogin(vector<Uzytkownik>& uzytkownicy, string login, int iloscUzytkownikow);
    int logowanie(vector<Uzytkownik>& uzytkownicy, int iloscUzytkownikow);
    void zapisUseraDoPliku(int iloscUzytkownikow, vector<Uzytkownik>& uzytkownicy);
};

