#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <cstdio>
#include "Users.h"

using namespace std;

struct Znajomy {
    int id = 0;
    int idUzytkownika;
    string imie, nazwisko, telefon, email, adres;
};

//struct Uzytkownik {
//    string login;
//    string haslo;
//    int id;
//};

void zapisUseraDoPliku(int iloscUzytkownikow, vector<Uzytkownik>& uzytkownicy) {
    fstream plik;
    plik.open("Users.txt",ios::out);
    for(int i = 0; i < iloscUzytkownikow; i++) {
        plik << uzytkownicy[i].id << "|";
        plik << uzytkownicy[i].login <<  "|";
        plik << uzytkownicy[i].haslo <<  "|" << endl;
    }

    cout << "Zapisano pomyslnie!";

    Sleep(1000);
    plik.close();
}

bool sprawdzCzyWolnyLogin(vector<Uzytkownik>& uzytkownicy, string login, int iloscUzytkownikow) {
    bool czyWolnyLogin = true;
    for (int i = 0; i < iloscUzytkownikow; i++) {
        if (uzytkownicy[i].login == login)
            czyWolnyLogin = false;
    }
    return czyWolnyLogin;
}

void nowyUzytownik(vector<Uzytkownik>& uzytkownicy, int& iloscUzytkownikow) {
    string login, haslo;
    int id = iloscUzytkownikow;
    char decyzja;

    while(true) {
        cout << "wpisz nazwe uzytkownika: ";
        cin >> login;
        if (sprawdzCzyWolnyLogin(uzytkownicy, login, iloscUzytkownikow) == true) {
            cout << "wpisz haslo: ";
            cin >> haslo;

            uzytkownicy.push_back(Uzytkownik (login, haslo, id));
//            uzytkownicy[id].login = login;
//            uzytkownicy[id].haslo = haslo;
//            uzytkownicy[id].id = id;
            iloscUzytkownikow += 1;
            zapisUseraDoPliku(iloscUzytkownikow, uzytkownicy);
            cout << "utworzono pomyslnie" << endl << endl;

            return;
        } else
            cout << "Uzytkownik o takiej nazwie juz istnieje, wrocic do menu? (t/n)" << endl;
        decyzja = getch();
        decyzja = tolower(decyzja);
        if (decyzja == 't')
            return;
        else
            continue;
    }
}

int logowanie(vector<Uzytkownik>& uzytkownicy, int iloscUzytkownikow) {

    string login, haslo;
    int idZalogowanegoUzytkownika;
    char czyWyjsc;
    while(true) {
        cout << "wpisz login: ";
        cin >> login;

        for (int i = 0; i <= iloscUzytkownikow; i++) {
            if (uzytkownicy[i].login == login) {
                for (int iloscProb = 2; iloscProb >= 0; iloscProb--) {
                    cout << "wpisz haslo: ";
                    cin >> haslo;

                    if (uzytkownicy[i].haslo == haslo) {
                        idZalogowanegoUzytkownika = uzytkownicy[i].id;
                        cout << "zalogowano pomyslnie" << endl;
                        return idZalogowanegoUzytkownika;
                    } else {
                        if (iloscProb > 0) {
                            cout << "Nieprawidlowe haslo, pozostalo " << iloscProb << " prob" << endl;
                            continue;
                        } else {
                            cout << "3 razy wpisano bledne haslo, poczekaj, nastapi powrot do menu" << endl;
                            Sleep(5000);
                            return -1;
                        }
                    }
                }
            }
        }
        cout << "nie ma takiego uzytkownika" << endl;
        cout << "wyjsc do menu? (t/n): ";
        czyWyjsc = getch();
        cout << endl << endl;
        if (czyWyjsc == 't') {
            return -1;
        }
        //else continue;
    }
    return false;
}

int odczytajPlikUzytkownicy(vector<Uzytkownik>& uzytkownicy) {
    ifstream plik;
    string linia, login, haslo;
    int id;
    string atrybut;
    int iloscUzytkownikow = 0;
    int pozycja = 0;

    plik.open("Users.txt", ios::in);
    if (plik.good() == false) {
        plik.open("Users.txt", ios::out);
    }
    while (getline(plik,linia)) {
        if (linia == "")
            continue;
        stringstream liniaSS (linia);

        while(getline(liniaSS, atrybut, '|' )) {
            switch (pozycja) {
            case 0:
                id = stoi(atrybut);
                break;
            case 1:
                login = atrybut;
                break;
            case 2:
                haslo = atrybut;
                break;
            }

            pozycja++;
        }
        uzytkownicy.push_back(Uzytkownik (login, haslo, id));
        iloscUzytkownikow++;
        pozycja = 0;
    }
    plik.close();
    return iloscUzytkownikow;
}

void zmienHaslo(int idZalogowanegoUzytkownika, vector<Uzytkownik>& uzytkownicy, int iloscUzytkownikow) {
    string noweHaslo;
    cout << "wpisz nowe haslo, (jesli chcesz wrocic do menu wcisnij 'n' i enter): ";
    cin >> noweHaslo;

    if (noweHaslo == "n") {
        cout << "powrot do menu, zmiana nie powiodla sie" << endl;
        return;
    } else {
        for (int i = 0; i < iloscUzytkownikow; i++) {
            if (uzytkownicy[i].id == idZalogowanegoUzytkownika) {
                uzytkownicy[i].haslo = noweHaslo;
                zapisUseraDoPliku(iloscUzytkownikow, uzytkownicy);
                cout << "Haslo zmieniono pomyslnie!" << endl;
                Sleep(1000);
                return;
            }
        }
        return;
    }
    return;
}

bool sprawdzCzyIstniejeZnajomy(string imie, string nazwisko, int iloscZnajomych, vector<Znajomy>& znajomi) {
    bool czyZnajomyIstnieje = false;
    for (int i = 0; i < iloscZnajomych; i++) {
        if( znajomi[i].imie == imie && znajomi[i].nazwisko == nazwisko ) {
            czyZnajomyIstnieje = true;
            char czyDodacZnajomego;
            cout << imie << " " << nazwisko << " juz jest w kontaktach, dodac mimo to? (t/n)" << endl;
            czyDodacZnajomego = getch();
            czyDodacZnajomego = tolower(czyDodacZnajomego);
            if (czyDodacZnajomego == 't') {
                czyZnajomyIstnieje = false;
            }
        }
    }
    return czyZnajomyIstnieje;
}

bool sprawdzCzyIstniejeID(vector<Znajomy>& znajomi, int iloscZnajomych, int id, int& pozycjaZnajomegoWWektorze) {

    bool czyIstnieje = false;
    char czyWyjsc;

    while (czyIstnieje == false) {
        cout << "Wpisz ID znajomego: ";
        cin >> id;
        for (int i = 0; i < iloscZnajomych; i++) {
            pozycjaZnajomegoWWektorze = i;
            if( znajomi[i].id == id) {
                czyIstnieje = true;
                break;
            }
        }
        if (czyIstnieje == true)
            break;
        else {
            cout << "znajomy o id: " << id << " nie istnieje\n";
            cout << "Wyjsc do menu?(t/n)\n";
            czyWyjsc = getch();
            czyWyjsc = tolower(czyWyjsc);
            if (czyWyjsc == 't')
                return czyIstnieje;
            else {
                system("cls");
                continue;
            }
        }
    }
    return czyIstnieje;
}

void zapisKontaktuDoPlikuPoEdycji(int iloscZnajomych, vector<Znajomy>& znajomi, int idZalogowanegoUzytkownika) {
    fstream plik, kopiaPlik;
    plik.open("kontakty.txt",ios::in);
    kopiaPlik.open("kopiaKontakty.txt",ios::out);
    string linia;
    string atrybut;
    int pozycja = 0;
    int id, idUzytkownika;
    string imie, nazwisko, telefon, email, adres;

    while (getline(plik,linia)) {
        if (linia == "")
            continue;
        stringstream liniaSS (linia);

        while(getline(liniaSS, atrybut, '|' )) {
            switch (pozycja) {
            case 0:
                id = stoi(atrybut);
                break;
            case 1:
                idUzytkownika = stoi(atrybut);
                break;
            case 2:
                imie = atrybut;
                break;
            case 3:
                nazwisko = atrybut;
                break;
            case 4:
                telefon = atrybut;
                break;
            case 5:
                email = atrybut;
                break;
            case 6:
                adres = atrybut;
                break;
            }
            pozycja++;
        }
        if(idUzytkownika != idZalogowanegoUzytkownika) {
            kopiaPlik << id << "|";
            kopiaPlik << idUzytkownika << "|";
            kopiaPlik << imie <<  "|";
            kopiaPlik << nazwisko <<  "|";
            kopiaPlik << telefon <<  "|";
            kopiaPlik << email <<  "|";
            kopiaPlik << adres <<  "|" << endl;
        }

        else {
            for(int i = 0; i < iloscZnajomych; i++) {
                if(znajomi[i].id == id) {
                    kopiaPlik << znajomi[i].id << "|";
                    kopiaPlik << znajomi[i].idUzytkownika << "|";
                    kopiaPlik << znajomi[i].imie <<  "|";
                    kopiaPlik << znajomi[i].nazwisko <<  "|";
                    kopiaPlik << znajomi[i].telefon <<  "|";
                    kopiaPlik << znajomi[i].email <<  "|";
                    kopiaPlik << znajomi[i].adres <<  "|" << endl;
                }
            }
        }
        pozycja = 0;
    }
    plik.close();
    kopiaPlik.close();
    remove("kontakty.txt");
    rename("kopiaKontakty.txt", "kontakty.txt");
}

void zapisKontaktuDoPliku(int iloscZnajomych, vector<Znajomy>& znajomi, int idZalogowanegoUzytkownika) {
    fstream plik;
    plik.open("kontakty.txt",ios::out | ios::app);

    plik << znajomi[iloscZnajomych].id << "|";
    plik << znajomi[iloscZnajomych].idUzytkownika << "|";
    plik << znajomi[iloscZnajomych].imie <<  "|";
    plik << znajomi[iloscZnajomych].nazwisko <<  "|";
    plik << znajomi[iloscZnajomych].telefon <<  "|";
    plik << znajomi[iloscZnajomych].email <<  "|";
    plik << znajomi[iloscZnajomych].adres <<  "|" << endl;
    plik.close();
}

int dodajKontakt (int iloscZnajomych, vector<Znajomy>& znajomi, int idOstatniegoZnajomego, int idZalogowanegoUzytkownika) {
    string imie, nazwisko, email, adres, telefon;
    cout << "podaj imie i nazwisko: ";
    cin >> imie >> nazwisko;


    if (sprawdzCzyIstniejeZnajomy(imie, nazwisko, iloscZnajomych, znajomi) == false ) {
        znajomi.push_back(Znajomy());
        if (idOstatniegoZnajomego == 0) {
            znajomi[iloscZnajomych].id = 1;
        } else {
            znajomi[iloscZnajomych].id = idOstatniegoZnajomego + 1;
        }

        znajomi[iloscZnajomych].idUzytkownika = idZalogowanegoUzytkownika;
        znajomi[iloscZnajomych].imie = imie;
        znajomi[iloscZnajomych].nazwisko = nazwisko;

        cout << "podaj adres: ";
        cin.sync();
        getline(cin, adres);
        cin.sync();
        znajomi[iloscZnajomych].adres = adres;

        cout << "podaj nr telefonu: ";
        getline(cin, telefon);
        cin.sync();
        znajomi[iloscZnajomych].telefon = telefon;

        cout << "podaj adres e-mail: ";
        cin >> email;
        znajomi[iloscZnajomych].email = email;

        zapisKontaktuDoPliku(iloscZnajomych, znajomi, idZalogowanegoUzytkownika);

        cout << "zapisano kontakt" << endl;
    } else {
        return 0;
    }

    return 1;
}

void wyswietlKontakty(vector<Znajomy>& znajomi, int iloscZnajomych) {
    if (iloscZnajomych == 0)
        cout << "Nie masz zapisanych kontaktow" << endl;
    else {
        cout << "Oto lista twoich kontaktow: " << endl << endl;
        for (int i = 0; i < iloscZnajomych; i++) {
            cout << znajomi[i].id << ". " << znajomi[i].imie << " " << znajomi[i].nazwisko << endl;
        }
        cout << endl;
    }
}

bool wyswietlDaneZnajomego(vector<Znajomy>& znajomi, int iloscZnajomych, string imie, string nazwisko) {
    bool czyZnajomyIstnieje = false;
    for (int i = 0; i < iloscZnajomych; i++) {
        if (znajomi[i].imie == imie || znajomi[i].nazwisko == nazwisko) {
            cout << znajomi[i].id << ". " << znajomi[i].imie << " " << znajomi[i].nazwisko << "   adres: " << znajomi[i].adres << "   tel.: " << znajomi[i].telefon << "   e-mail: " << znajomi[i].email << endl;
            czyZnajomyIstnieje = true;
        }
    }
    return czyZnajomyIstnieje;
}

void wyszukajZnajomego(vector<Znajomy>& znajomi, int iloscZnajomych, char wybor) {

    string imie = "";
    string nazwisko = "";
    bool czyZnajomyIstnieje = false;

    switch (wybor) {
    case '1':
        cout << "wpisz imie: ";
        cin >> imie;
        cout << endl;
        czyZnajomyIstnieje = wyswietlDaneZnajomego(znajomi, iloscZnajomych, imie, nazwisko);
        cout << endl;
        break;

    case '2':
        cout << "wpisz nazwisko: ";
        cin >> nazwisko;
        cout << endl;
        czyZnajomyIstnieje = wyswietlDaneZnajomego(znajomi, iloscZnajomych, imie, nazwisko);
        cout << endl;
        break;
    }

    if (czyZnajomyIstnieje == false)
        cout << "Nie ma takiego znajomego." << endl << endl;
}


int odczytajPlikKontakty(vector<Znajomy>& znajomi, int idZalogowanegoUzytkownika, int& idOstatniegoZnajomego) {
    ifstream plik;
    string linia;
    string atrybut;
    int iloscZnajomych = 0;
    int pozycja = 0;
    int id, idUzytkownika;
    string imie, nazwisko, telefon, email, adres;


    plik.open("kontakty.txt", ios::in);
    if (plik.good() == false) {
        plik.open("kontakty.txt", ios::out);
    }
    while (getline(plik,linia)) {
        if (linia == "")
            continue;
        stringstream liniaSS (linia);

        while(getline(liniaSS, atrybut, '|' )) {
            switch (pozycja) {
            case 0:
                id = stoi(atrybut);
                break;
            case 1:
                idUzytkownika = stoi(atrybut);
                break;
            case 2:
                imie = atrybut;
                break;
            case 3:
                nazwisko = atrybut;
                break;
            case 4:
                telefon = atrybut;
                break;
            case 5:
                email = atrybut;
                break;
            case 6:
                adres = atrybut;
                break;
            }
            pozycja++;
        }
        if (idUzytkownika == idZalogowanegoUzytkownika ) {
            znajomi.push_back(Znajomy());
            znajomi[iloscZnajomych].id = id;
            znajomi[iloscZnajomych].idUzytkownika = idZalogowanegoUzytkownika;
            znajomi[iloscZnajomych].imie = imie;
            znajomi[iloscZnajomych].nazwisko = nazwisko;
            znajomi[iloscZnajomych].telefon = telefon;
            znajomi[iloscZnajomych].email = email;
            znajomi[iloscZnajomych].adres = adres;
            iloscZnajomych++;
        }
        idOstatniegoZnajomego = id;
        pozycja = 0;
    }
    plik.close();
    return iloscZnajomych;
}


void edytujDaneZnajomego(vector<Znajomy>& znajomi, int iloscZnajomych) {
    int id;
    char wybor;
    string noweImie, noweNazwisko, nowyTelefon, nowyEmail, nowyAdres;
    bool czyIstnieje = false;
    int pozycjaZnajomegoWWektorze = 0;

    czyIstnieje = sprawdzCzyIstniejeID(znajomi, iloscZnajomych, id, pozycjaZnajomegoWWektorze);
    if (czyIstnieje == false)
        return;

    do {
        cout << "Co chcesz zmienic: "<<endl;
        cout << "1 - imie\n";
        cout << "2 - nazwisko\n";
        cout << "3 - numer telefonu\n";
        cout << "4 - email\n";
        cout << "5 - adres\n";
        cout << "6 - powrot do menu\n";

        cout << "wybor: ";
        cin >> wybor;
        switch(wybor) {
        case '1': {
            cout << "Wpisz nowe imie: ";
            cin >> noweImie;
            znajomi[pozycjaZnajomegoWWektorze].imie = noweImie;
            break;
        }
        case '2': {
            cout << "Wpisz nowe nazwisko: ";
            cin >> noweNazwisko;
            znajomi[pozycjaZnajomegoWWektorze].nazwisko = noweNazwisko;
            break;
        }
        case '3': {
            cout << "Wpisz nowy numer telefonu: ";
            cin.sync();
            getline(cin,nowyTelefon);
            cin.sync();
            znajomi[pozycjaZnajomegoWWektorze].telefon = nowyTelefon;
            break;
        }
        case '4': {
            cout << "Wpisz nowy email: ";
            cin >> nowyEmail;
            znajomi[pozycjaZnajomegoWWektorze].email = nowyEmail;
            break;
        }
        case '5': {
            cout << "Wpisz nowy adres: ";
            cin.sync();
            getline(cin,nowyAdres);
            cin.sync();
            znajomi[pozycjaZnajomegoWWektorze].adres = nowyAdres;
            break;
        }
        case '6':
            return;
            break;
        }
        cout << "Zmieniono pomyslnie" << endl;
        Sleep(1000);
        system("cls");
    } while (true);
}


int usunZnajomego(vector<Znajomy>& znajomi, int iloscZnajomych) {
    int id;
    char czyUsunac;
    string noweImie, noweNazwisko, nowyTelefon, nowyEmail, nowyAdres;
    bool czyIstnieje = false;
    int pozycjaZnajomegoWWektorze = 0;

    czyIstnieje = sprawdzCzyIstniejeID(znajomi, iloscZnajomych, id, pozycjaZnajomegoWWektorze);
    if (czyIstnieje == false)
        return 0;

    cout << "Czy na pewno chcesz usunac " << znajomi[pozycjaZnajomegoWWektorze].imie << " " << znajomi[pozycjaZnajomegoWWektorze].nazwisko << "? (t/n)\n";
    czyUsunac = getch();
    czyUsunac = tolower(czyUsunac);
    if (czyUsunac == 't') {
        znajomi.erase(znajomi.begin() + pozycjaZnajomegoWWektorze);
        cout << "Usunieto pomyslnie!" << endl;
        return 1;
    }
    return 0;

}



int main() {

    vector<Uzytkownik> uzytkownicy;
    int idZalogowanegoUzytkownika = -1;
    int iloscUzytkownikow = odczytajPlikUzytkownicy(uzytkownicy);
    bool PokazMenuLogowania = true;

    vector<Znajomy> znajomi;
    int nowyZnajomy = 0;
    char wybor;
    char wyszukajPoImieniu = '1';
    char wyszukajPoNazwisku = '2';
    int idOstatniegoZnajomego = 0;

    while(1) {
        if(PokazMenuLogowania) {
            system("cls");
            cout << "   --MENU--   " << endl;
            cout << "1. zaloguj sie" << endl;
            cout << "2. utworz konto" << endl;
            cout << "3. wyjdz" << endl << endl;

            cout << "ilosc uzytkownikow: " << iloscUzytkownikow << endl << endl;

            // cout << "ilosc uzytkownikow: " << iloscUzytkownikow <<endl;
            char wybor;

            cin >> wybor;

            switch (wybor) {
            case '1':
                if (iloscUzytkownikow == 0) {
                    cout << "brak uzytkownikow" << endl;
                    Sleep(1000);
                    continue;
                } else {
                    idZalogowanegoUzytkownika = logowanie(uzytkownicy, iloscUzytkownikow);
                    Sleep(1000);
                    if (idZalogowanegoUzytkownika >= 0) {
                        PokazMenuLogowania = false;
                    }
                    continue;
                }
                break;
            case '2':
                nowyUzytownik(uzytkownicy, iloscUzytkownikow);
                system("pause");
                continue;
                break;
            case '3':
                return 0;
                break;
            }
        }

        int iloscZnajomych = odczytajPlikKontakty(znajomi, idZalogowanegoUzytkownika, idOstatniegoZnajomego);


        system("cls");

        cout << "Program ksiazka adresowa" << endl << endl;
        cout << ".......MENU......." << endl;
        cout << "1. Dodaj znajomego" << endl;
        cout << "2. Wyswietl wszystkich znajomych" << endl;
        cout << "3. Wyszukaj po imieniu" << endl;
        cout << "4. Wyszukaj po nazwisku" << endl;
        cout << "5. Usun znajomego" << endl;
        cout << "6. Edytuj dane znajomego" << endl;
        cout << "7. Wyloguj sie" << endl;
        cout << "8. Zmiana hasla" << endl;
        cout << "9. Wyjscie" << endl;
        cout << "<====================================>" << endl;

        // cout <<"id Ostatniego: " << idOstatniegoZnajomego<<endl;

        cin >> wybor;

        cout << endl;

        switch (wybor) {
        case '1':
            nowyZnajomy = dodajKontakt(iloscZnajomych, znajomi, idOstatniegoZnajomego, idZalogowanegoUzytkownika);
            iloscZnajomych += nowyZnajomy;
            idOstatniegoZnajomego += nowyZnajomy;
            system("pause");
            break;
        case '2':
            wyswietlKontakty(znajomi, iloscZnajomych);
            system("pause");
            break;
        case '3':
            wyszukajZnajomego(znajomi, iloscZnajomych, wyszukajPoImieniu);
            system("pause");
            break;
        case '4':
            wyszukajZnajomego(znajomi, iloscZnajomych, wyszukajPoNazwisku);
            system("pause");
            break;
        case '5':
            iloscZnajomych -= usunZnajomego(znajomi, iloscZnajomych);
            zapisKontaktuDoPlikuPoEdycji(iloscZnajomych, znajomi, idZalogowanegoUzytkownika);
            system("pause");
            break;
        case '6':
            edytujDaneZnajomego(znajomi, iloscZnajomych);
            zapisKontaktuDoPlikuPoEdycji(iloscZnajomych, znajomi, idZalogowanegoUzytkownika);
            system("pause");
            break;
        case '7':
            PokazMenuLogowania = true;
            znajomi.clear();
            Sleep(1000);
            continue;
            break;
        case '8':
            zmienHaslo(idZalogowanegoUzytkownika, uzytkownicy, iloscUzytkownikow);
            system("pause");
            break;
        case '9':
            return 0;
            break;
        }
    }
    return 0;
}

