#include <iostream>
using namespace std;

string schluessel;
char alphabet [27] = "abcdefghijklmnopqrstuvwxyz";
char tabelle [5][5];
int geheimtext [200];

string schluesselErmitteln ();
void tabelleErstellen(string schl);
void verschluesseln();
void entschluesselVorgang();
string entschluesseln(int geheim[]);
void testAusgabe();
void geheimAusgeben();


int main() {
    int c = 0;
    bool running = true;
    //Geheimtext muss unterscheidbar von leeren Stellen sein. Leere Stelle = 9
    for (int i = 0; i < 200; ++i) {
        geheimtext[i] = 9;
    }
    while (running){
        cout << "Willkommen Polybios Chiffre Programm." << endl;
        cout << "---------------------------------------" << endl;
        cout << "0: Text verschlüsseln" << endl;
        cout << "1: Text entschlüsseln" << endl;
        cout << "2: Geheimtext ausgeben" << endl;
        cout << "3: Test Ausgabe (Dev)" << endl;
        cout << "4: Programm beenden" << endl;
        cout << "---------------------------------------" << endl;
        cout << "Bitte wählen Sie eine Option: ";
        cin >> c;

        switch (c) {
            case 0:
                verschluesseln();
                break;
            case 1:
                entschluesselVorgang();
                break;
            case 2:
                geheimAusgeben();
                break;
            case 3:
                testAusgabe();
                break;
            case 4:
                running = false;
                break;
        }
    }
    return 0;
}

string schluesselErmitteln(){
    input:
    string tempschluessel;
    cout << "Bitte geben Sie den Schlüssel ein." << endl;
    cout << "Der Schlüssel darf nur aus Maximal 25 Buchstaben bestehen und kein Zeichen doppelt" << endl;

    cout << "Eingabe: ";
    cin >> tempschluessel;

    //Überprüfen ob Schlüssel gültig
    for (int i = 0; i < tempschluessel.length(); ++i) {
        if(i == 26){
            cout << "Der Schlüssel ist größer als 25 Zeichen!" << endl;
            goto input;
        }
        else if(i != 0){
            for (int j = 0; j < tempschluessel.length(); ++j) {
                if(i != j && tempschluessel[i]==tempschluessel[j]) {
                    cout << "Der Schlüssel hat doppelte Buchstaben!" << endl;
                    goto input;
                }
            }
        }
    }
    cout << "Der Schlüssel " << tempschluessel << " wurde eingelesen." << endl;
    return tempschluessel;

}

void tabelleErstellen (string schl){
   char alphabetneu [27];
   bool schlfertig = false;
   int s = 0;
   int a = 0;
   int b = 0;
   bool same = false;
   //Alphabet ohne Schlüssel erstellen
    for (int i = 0; i < 27; ++i) {
        for (int j = 0; j < schl.length(); ++j) {
            if (schl[j] != alphabet[i] && alphabet[i] != 'j'){
                alphabetneu[b] = alphabet[i];
            }
            else{
                same = true;
                break;
            }
        }
        if (!same){
            b++;
        }
        same = false;
    }
    //Schlüssel einfügen
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
           if (schl[s] != 0 && !schlfertig){
               tabelle[i][j] = schl[s];
               s++;
           }
           else if (schl[s] == 0){
               schlfertig = true;
              break;
           }
        }
    }
    //Auffüllen
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (tabelle[i][j] == 0){
                tabelle[i][j] = alphabetneu[a];
                a++;
            }
        }
    }
}

void verschluesseln(){
    string klartext;
    int a = 0;
    int b = 0;

    schluessel = schluesselErmitteln();
    tabelleErstellen(schluessel);

    //Nachricht eingeben
    cout << "Bitte geben Sie die Nachricht in Kleinbuchstaben und ohne Leerzeichen ein: ";
    cin >> klartext;
    cout << endl;

    //Verschlüsseln
    verschluesslenp:
    if (klartext[b] == 'j'){
        klartext[b] = 'i';
    }
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (klartext[b] == tabelle[i][j] && klartext[b] != 0){
                if(klartext[b] != ' ' && a <= 200){
                    geheimtext[a] = i;
                    geheimtext[a+1] = j;
                    a += 2;
                    b++;
                    goto verschluesslenp;
                }
            }
        }

    }

    //Geheimtext ausgeben
    geheimAusgeben();
}

void entschluesselVorgang(){
    int c = 0;

    cout << "Möchten Sie eine eigene Nachricht entschlüsseln (0) oder Die Nachricht aus dem Speicher entschlüsseln (1)" << endl;
    cout << "[0|1]: ";
    cin >> c;
    switch (c) {
        case 0:
            int geheimtextInput [200];

            cout << "Bitte geben Sie den zu entschlüsselnen Text ein. Um die Eingabe abzuschließen, drücken Sie bitte 9: " << endl;
            for (int i = 0; i < 200; ++i) {
                cin >> geheimtextInput[i];
                if (geheimtextInput[i] == 9){
                    goto exit;
                }
            }
            exit:
            cout << "Die Nachricht ist: " << endl;
            cout << entschluesseln(geheimtextInput) << endl;
            break;
        case 1:
            cout << "Die Nachricht ist: " << endl;
            cout << entschluesseln(geheimtext) << endl;
            break;
    }


}

string entschluesseln(int geheim []){
    string klartext ;
    int a = 0;
    int b = 0;


    schluessel = schluesselErmitteln();
    tabelleErstellen(schluessel);


    //Entschlüsseln
    for (int i = 0; i < 200; i += 2) {
        if (geheim[i] != 9){
            klartext.resize(a+1);
            klartext[a] = tabelle[geheim[i]][geheim[i+1]];
            a++;
        }
    }
    return klartext;
}

void testAusgabe(){
    cout << "Die Tabelle:";
    for (int i = 0; i < 5; ++i) {
        cout << endl;
        for (int j = 0; j < 5; ++j) {
            cout << tabelle[i][j] << "\t";
        }
    }
    cout << endl;
    cout << "Geheimtext: " << endl;
    for (int i = 0; i < 200; ++i) {
        cout << geheimtext[i];
    }
}

void geheimAusgeben(){
    cout << "Ihre verschlüsselte Nachricht lautet: " << endl;
    for (int i = 0; i < 200; ++i) {
        if (geheimtext[i] != 9){
            cout << geheimtext[i];
        }
        else if(geheimtext[0] == 9){
            cout << "Sie haben noch keinen Text verschlüsselt. Bitte wählen Sie Option 0" << endl;
            break;
        }
    }
    cout << endl;
}