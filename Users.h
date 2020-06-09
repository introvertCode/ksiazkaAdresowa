#include <vector>
#include <iostream>;

class Uzytkownik{
public:
    std::string login;
    std::string haslo;
    int id;

public:
    Uzytkownik(std::string, std::string, int);
    ~Uzytkownik();
//    void zapisUseraDoPliku(int, std::vector<Uzytkownik>);
    //bool sprawdzCzyWolnyLogin(std::vector<Uzytkownik>, std::string, int);
};

