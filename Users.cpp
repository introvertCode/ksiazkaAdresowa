#include <iostream>
#include "Users.h"
#include <vector>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <stdio.h>
#include <cstdio>

using namespace std;

Uzytkownik::Uzytkownik(string l, string h, int i){
login = l;
haslo = h;
id = i;
}
Uzytkownik::~Uzytkownik(){};

bool Uzytkownik::sprawdzCzyWolnyLogin(vector<Uzytkownik>& uzytkownicy, string login, int iloscUzytkownikow) {
    bool czyWolnyLogin = true;
    for (int i = 0; i < iloscUzytkownikow; i++) {
        if (uzytkownicy[i].login == login)
            czyWolnyLogin = false;
    }
    return czyWolnyLogin;
}

void Uzytkownik::zapisUseraDoPliku(int iloscUzytkownikow, vector<Uzytkownik>& uzytkownicy) {
    fstream plik;
    plik.open("Users.txt",ios::out);
    for(int i = 0; i < iloscUzytkownikow; i++) {
        plik << uzytkownicy[i].id << "|";
        plik << uzytkownicy[i].login <<  "|";
        plik << uzytkownicy[i].haslo <<  "|" << endl;
    }

    //cout << "Zapisano pomyslnie!";

    Sleep(1000);
    plik.close();
}

void Uzytkownik::nowyUzytownik(vector<Uzytkownik>& uzytkownicy, int& iloscUzytkownikow) {
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

int Uzytkownik::logowanie(vector<Uzytkownik>& uzytkownicy, int iloscUzytkownikow) {

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
    }
    return false;
}
