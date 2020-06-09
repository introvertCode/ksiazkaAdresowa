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
//{
//
//}

//void Uzytkownik::zapisUseraDoPliku(int iloscUzytkownikow, vector<Uzytkownik> uzytkownicy) {
//    fstream plik;
//    plik.open("Users.txt",ios::out);
//    for(int i = 0; i < iloscUzytkownikow; i++) {
//        plik << uzytkownicy[i].id << "|";
//        plik << uzytkownicy[i].login <<  "|";
//        plik << uzytkownicy[i].haslo <<  "|" << endl;
//    }
//    plik.close();
//}


//bool Uzytkownik::sprawdzCzyWolnyLogin(vector<Uzytkownik> uzytkownicy, string login, int iloscUzytkownikow) {
//    bool czyWolnyLogin = true;
//    for (int i = 0; i < iloscUzytkownikow; i++) {
//        if (uzytkownicy[i].login == login)
//            czyWolnyLogin = false;
//    }
//    return czyWolnyLogin;
//}


