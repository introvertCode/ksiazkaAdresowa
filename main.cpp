#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <vector>


using namespace std;

struct znajomy {
    int id = 0;
    string imie, nazwisko, telefon, email, adres;
};

bool sprawdzCzyIstniejeZnajomy(string imie, string nazwisko, int iloscZnajomych, vector<znajomy>& znajomi) {
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

bool sprawdzCzyIstniejeID(vector<znajomy>& znajomi, int iloscZnajomych, int id, int& pozycjaZnajomegoWWektorze) {

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

void zapisKontaktuDoPliku(int iloscZnajomych, vector<znajomy>& znajomi) {
    fstream plik;
    plik.open("kontakty.txt",ios::out);
    for(int i = 0; i < iloscZnajomych; i++) {

        plik << znajomi[i].id << "|";
        plik << znajomi[i].imie <<  "|";
        plik << znajomi[i].nazwisko <<  "|";
        plik << znajomi[i].telefon <<  "|";
        plik << znajomi[i].email <<  "|";
        plik << znajomi[i].adres <<  "|" << endl;
    }
    plik.close();
}

int dodajKontakt (int iloscZnajomych, vector<znajomy>& znajomi) {
    string imie, nazwisko, email, adres, telefon;
    cout << "podaj imie i nazwisko: ";
    cin >> imie >> nazwisko;


    if (sprawdzCzyIstniejeZnajomy(imie, nazwisko, iloscZnajomych, znajomi) == false ) {
        znajomi.push_back(znajomy());
        if (iloscZnajomych == 0) {
            znajomi[iloscZnajomych].id = 1;
        } else {
            znajomi[iloscZnajomych].id = znajomi[iloscZnajomych-1].id + 1;
        }
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

        cout << "zapisano kontakt" << endl;
    } else {
        return 0;
    }

    return 1;
}

void wyswietlKontakty(vector<znajomy>& znajomi, int iloscZnajomych) {
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

bool wyswietlDaneZnajomego(vector<znajomy>& znajomi, int iloscZnajomych, string imie, string nazwisko) {
    bool czyZnajomyIstnieje = false;
    for (int i = 0; i < iloscZnajomych; i++) {
        if (znajomi[i].imie == imie || znajomi[i].nazwisko == nazwisko) {
            cout << znajomi[i].id << ". " << znajomi[i].imie << " " << znajomi[i].nazwisko << "   adres: " << znajomi[i].adres << "   tel.: " << znajomi[i].telefon << "   e-mail: " << znajomi[i].email << endl;
            czyZnajomyIstnieje = true;
        }
    }
    return czyZnajomyIstnieje;
}

void wyszukajZnajomego(vector<znajomy>& znajomi, int iloscZnajomych, char wybor) {

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

int OdczytajPlik(vector<znajomy>& znajomi) {
    ifstream plik;
    string linia;
    string atrybut;
    int iloscZnajomych = 0;
    int pozycja = 0;


    plik.open("kontakty.txt", ios::in);
    if (plik.good() == false) {
        plik.open("kontakty.txt", ios::out);
    }
    while (getline(plik,linia)) {
        if (linia == "")
            continue;
        stringstream liniaSS (linia);

        znajomi.push_back(znajomy());
        while(getline(liniaSS, atrybut, '|' )) {
            switch (pozycja) {
            case 0:
                znajomi[iloscZnajomych].id = stoi(atrybut);
                break;
            case 1:
                znajomi[iloscZnajomych].imie = atrybut;
                break;
            case 2:
                znajomi[iloscZnajomych].nazwisko = atrybut;
                break;
            case 3:
                znajomi[iloscZnajomych].telefon = atrybut;
                break;
            case 4:
                znajomi[iloscZnajomych].email = atrybut;
                break;
            case 5:
                znajomi[iloscZnajomych].adres = atrybut;
                break;
            }
            pozycja++;
        }
        iloscZnajomych++;
        pozycja = 0;
    }
    plik.close();
    return iloscZnajomych;
}

void edytujDaneZnajomego(vector<znajomy>& znajomi, int iloscZnajomych) {
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


int usunZnajomego(vector<znajomy>& znajomi, int iloscZnajomych) {
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
    vector<znajomy> znajomi;
    int nowyZnajomy = 0;
    char wybor;
    char wyszukajPoImieniu = '1';
    char wyszukajPoNazwisku = '2';

    int iloscZnajomych = OdczytajPlik(znajomi);

    while(1) {
        system("cls");

        cout << "Program ksiazka adresowa" << endl << endl;
        cout << ".......MENU......." << endl;
        cout << "1. Dodaj znajomego" << endl;
        cout << "2. Wyswietl wszystkich znajomych" << endl;
        cout << "3. Wyszukaj po imieniu" << endl;
        cout << "4. Wyszukaj po nazwisku" << endl;
        cout << "5. Usun znajomego" << endl;
        cout << "6. Edytuj dane znajomego" << endl;
        cout << "9. Wyjscie" << endl;
        cout << "<====================================>" << endl;

        cin >> wybor;
        //cout<< iloscZnajomych<<endl;
        cout << endl;

        switch (wybor) {
        case '1':
            nowyZnajomy = dodajKontakt(iloscZnajomych, znajomi);
            iloscZnajomych += nowyZnajomy;
            zapisKontaktuDoPliku(iloscZnajomych, znajomi);
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
            zapisKontaktuDoPliku(iloscZnajomych, znajomi);
            system("pause");
            break;
        case '6':
            edytujDaneZnajomego(znajomi, iloscZnajomych);
            zapisKontaktuDoPliku(iloscZnajomych, znajomi);
            system("pause");
            break;
        case '9':
            return 0;
            break;
        }
    }
    return 0;
}

