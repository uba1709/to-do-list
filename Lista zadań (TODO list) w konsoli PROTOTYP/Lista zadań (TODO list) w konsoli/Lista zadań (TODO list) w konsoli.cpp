#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <filesystem>
#include <Windows.h>
using namespace std;
namespace fs = std::filesystem;

string dodaj_zadanie, pokaz_wszystkie_zadania, usun_zadanie, powturzenie, filename, folderName = "dane";
vector<string> zadania;
int wybur, zapisanie;

void dodajZadanie() {  
    /*cout << "Podaj zadanie do dodania: ";
    cin >> dodaj_zadanie;
    zadania.push_back(dodaj_zadanie);
    cout << "---------------" << endl;
    cout << "" << endl;*/

    cout << "Podaj zadanie do dodania: ";
    cin.ignore(); // usuwa pozostałości po poprzednim 'cin'
    getline(cin, dodaj_zadanie);
    zadania.push_back(dodaj_zadanie);
    cout << "---------------" << endl;
    cout << "" << endl;
}
void pokazWszystkieZadania() {
    cout << "Pokaz wszystkie zadania { ";
    for (const string& name : zadania) {
        cout << name << ", ";
    }cout << "}" << endl;
    cout << "" << endl;
}
void usunZadanie() {
    cout << "Pokaz wszystkie zadania do wykonania { ";

    for (const string& name : zadania) {
        cout << name << ", ";
    }cout << "}" << endl;
	cout << "" << endl;

    cout << "Podaj zadanie do usuniecia: ";
    cin.ignore();
    getline(cin, usun_zadanie);
    zadania.erase(remove(zadania.begin(), zadania.end(), usun_zadanie), zadania.end());
    for (const string& name : zadania) {
        cout << name << ", ";
    }
	cout << "" << endl;
}
void menuZPlikami() {
    cout << "Wybierz plik do zapisu: " << endl;
    cout << "" << endl;
    cout << "1. Zapisz jako plik" << endl;
    cout << "2. Wczytaj z pliku" << endl;
    cout << "3. Usun dane" << endl;
	cout << "4. Pokaz wszystkie zapisane pliki" << endl;
    cout << "5. Zakoncz" << endl;
    cout << "wybierz: ";
    cin >> zapisanie;
    cout << "---------------" << endl;
}
void zapiszDoPliku() {
    if (!fs::exists(folderName)) {
        fs::create_directory(folderName);
    }

    cout << "Podaj nazwę pliku (bez rozszerzenia): ";
    //cin >> filename;
    cin.ignore();
    getline(cin, filename);


    string filePath = folderName + "/" + filename + ".txt";
    ofstream file(filePath);
    if (file.is_open()) {
        for (const string& wiersz : zadania) {
            file << wiersz << endl;
        }
        file.close();
        cout << "Dane zostały zapisane do pliku: " << filePath << endl;
    }
    else {
        cerr << "Nie udało się otworzyć pliku do zapisu.\n";
		cout << "" << endl;
    }
}
void wczytajZPliku(){
    cout << "Podaj nazwę pliku do odczytu (bez rozszerzenia) "<< endl;
    cout << "Podaj nazwe: ";
    //cin >> filename;
    cin.ignore();
    getline(cin, filename);

    cout << "" << endl;

    string filePath = folderName + "/" + filename + ".txt";
    ifstream odczytPliku(filePath);
    string linia;

    if (odczytPliku.is_open()) {
        zadania.clear();
        while (getline(odczytPliku, linia)) {
            if (!linia.empty()) zadania.push_back(linia);
        }
        odczytPliku.close();
        cout << "Dane sa wczytane z pliku: " << filePath << endl;
    }
    else {
        cerr << "Błąd: nie można otworzyć pliku do odczytu." << endl;
    }
    cout << "" << endl;
}
void usunDane() {
    string folder = "dane";
    vector<string> pliki;

    if (!fs::exists(folder)) {
        cout << "Folder '" << folder << "' nie istnieje." << endl;
        return;
    }

    cout << "Pliki w folderze '" << folder << "':" << endl;
    int index = 0;
    for (const auto& entry : fs::directory_iterator(folder)) {
        if (entry.is_regular_file()) {
            string nazwa = entry.path().filename().string();
            pliki.push_back(nazwa);
            cout << index + 1 << ". " << nazwa << endl;
            index++;
        }
    }

    if (pliki.empty()) {
        cout << "Brak plików do usunięcia." << endl;
        return;
    }

    int wybor;
    cout << "Podaj numer pliku do usunięcia: "<< endl;
    cout << "wybor: ";
    cin >> wybor;

    if (wybor < 1 || wybor > pliki.size()) {
        cout << "Nieprawidłowy numer!" << endl;
        return;
    }

    string sciezka = folder + "/" + pliki[wybor - 1];

    try {
        fs::remove(sciezka);
        cout << "Plik '" << pliki[wybor - 1] << "' zostal usunięty." << endl;
    }
    catch (const fs::filesystem_error& e) {
        cerr << "Błąd usuwania pliku: " << e.what() << endl;
    }
}
void pokazPliki() {
    if (!fs::exists(folderName)) {
        cout << "Folder nie istnieje." << endl;
        return;
    }

    cout << "Pliki w folderze '" << folderName << "':" << endl;
    cout << "" << endl;
    for (const auto& entry : fs::directory_iterator(folderName)) {
        if (entry.is_regular_file()) {
            cout << "- " << entry.path().filename().string() << endl;
        }
    }
    cout << "---------------" << endl;
}
void Koniec() {
    cout << "" << endl;
    cout << "Program wykonany poprawnie" << endl;
    cout << "Dziekuje za skorzystanie z programu" << endl;
    cout << "Aby wylaczyc program wcisnij enter" << endl;
    cout << "---------------" << endl;
}
void Error() {
    cout << "" << endl;
    cout << "Niepoprawny wybor, sprubuju ponownie" << endl;
}

int main(){

    cout << "--- Lista zadan ---" << endl;
    cout << "" << endl;
    while (true) {
        cout << "1. Dodaj zadanie" << endl;
        cout << "2. Pokaz wszystkie zadania" << endl;
        cout << "3. Usun zadanie" << endl;
        cout << "4. Pokaz pliki folderu" << endl;
        cout << "5. Zakoncz" << endl;
        cout << "---------------" << endl;
        cout << "Wybierz opcje: ";
        cin >> wybur;
        cout << "---------------" << endl;
        switch (wybur) {
        case 1:
            cout << "" << endl;
            dodajZadanie();
            break;
        case 2:
            cout << "" << endl;
            pokazWszystkieZadania();
            break;
        case 3:
            cout << "" << endl;
            usunZadanie();
            break;
        case 4:
            cout << "" << endl;
            menuZPlikami();
                switch (zapisanie) {
                case 1:
                    cout << "" << endl;
                    zapiszDoPliku();
                    break;
                case 2:
                    cout << "" << endl;
                    wczytajZPliku();
                    break;
                case 3:
                    cout << "" << endl;
                    usunDane();
                    break;
                case 4:
					cout << "" << endl;
					pokazPliki();
					break;
                case 5:
                    cout << "" << endl;
                    Koniec();
                    return 0;
                default:
                    cout << "" << endl;
                    Error();
                break;}
            break;
        case 5:
            Koniec();
            return 0;
        default:
            Error();
            break;
        }
    }
    return 0;
}

