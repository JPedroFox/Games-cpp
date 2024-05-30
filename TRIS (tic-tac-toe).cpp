
//	J.Pedro Gregorio Barros 
//	2023-2024

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

#define DIM 3    

void stampaTitolo() {
    cout << "__/\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\____/\\\\\\\\\\\\\\\\\\______/\\\\\\\\\\\\\\\\\\\\\\_____/\\\\\\\\\\\\\\\\\\\\\\___" << endl;
    cout << " _\\///////\\\\\\/////___/\\\\\\///////\\\\\\___\\/////\\\\\\///____/\\\\\\/////////\\\\\\_" << endl;
    cout << "  _______\\/\\\\\\_______\\/\\\\\\_____\\/\\\\\\_______\\/\\\\\\______\\//\\\\\\______\\///__" << endl;
    cout << "   _______\\/\\\\\\_______\\/\\\\\\\\\\\\\\\\\\\\\\/________\\/\\\\\\_______\\////\\\\\\_________" << endl;
    cout << "    _______\\/\\\\\\_______\\/\\\\\\//////\\\\\\________\\/\\\\\\__________\\////\\\\\\______" << endl;
    cout << "     _______\\/\\\\\\_______\\/\\\\\\____\\//\\\\\\_______\\/\\\\\\_____________\\////\\\\\\___" << endl;
    cout << "      _______\\/\\\\\\_______\\/\\\\\\_____\\//\\\\\\______\\/\\\\\\______/\\\\\\______\\//\\\\\\__" << endl;
    cout << "       _______\\/\\\\\\_______\\/\\\\\\______\\//\\\\\\__/\\\\\\\\\\\\\\\\\\\\\\_\\///\\\\\\\\\\\\\\\\\\\\\\/___" << endl;
    cout << "        _______\\///________\\///________\\///__\\///////////____\\///////////_____" << endl << endl;
}

void azzera(char tris[][DIM], int n) {
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            tris[r][c] = ' ';
        }
    }
}

bool verifica(char tris[][DIM], int n) {
    for (int i = 0; i < n; ++i) {
        if ((tris[i][0] == tris[i][1] && tris[i][1] == tris[i][2] && tris[i][0] != ' ') || 
            (tris[0][i] == tris[1][i] && tris[1][i] == tris[2][i] && tris[0][i] != ' ')) {
            cout << "Giocatore " << (tris[i][i] == 'X' ? 1 : 2) << " ha vinto!" << endl;
            return false;
        }
    }

    if ((tris[0][0] == tris[1][1] && tris[1][1] == tris[2][2] && tris[0][0] != ' ') || 
        (tris[0][2] == tris[1][1] && tris[1][1] == tris[2][0] && tris[0][2] != ' ')) {
        cout << "Giocatore " << (tris[1][1] == 'X' ? 1 : 2) << " ha vinto!" << endl;
        return false;
    }

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            if (tris[r][c] == ' ') {
                return true;
            }
        }
    }

    cout << "PAREGGIO!" << endl;
    return false;
}

void stampaTris(char tris[][DIM]) {
    cout << setw(6) << "a" << setw(4) << "b" << setw(4) << "c" << endl << endl;
    for (int i = 0; i < DIM; ++i) {
        cout << setw(2) << (i + 1) << "  ";
        for (int j = 0; j < DIM; ++j) {
            cout << setw(2) << tris[i][j];
            if (j < DIM - 1) cout << " |";
        }
        cout << endl;
        if (i < DIM - 1) cout << "    -----------" << endl;
    }
    cout << endl;
}

bool mossaVincente(char tris[][DIM], int r, int c, char giocatore) {
    tris[r][c] = giocatore;
    bool win = !verifica(tris, DIM);
    tris[r][c] = ' ';
    return win;
}

void mossaCPU(char tris[][DIM]) {
    // Controllo per una mossa vincente
    for (int r = 0; r < DIM; ++r) {
        for (int c = 0; c < DIM; ++c) {
            if (tris[r][c] == ' ' && mossaVincente(tris, r, c, 'O')) {
                tris[r][c] = 'O';
                return;
            }
        }
    }

    // Controllo per bloccare la mossa vincente dell'avversario
    for (int r = 0; r < DIM; ++r) {
        for (int c = 0; c < DIM; ++c) {
            if (tris[r][c] == ' ' && mossaVincente(tris, r, c, 'X')) {
                tris[r][c] = 'O';
                return;
            }
        }
    }

    // Altrimenti, prendere il centro se disponibile
    if (tris[1][1] == ' ') {
        tris[1][1] = 'O';
        return;
    }

    // Altrimenti, prendere qualsiasi angolo disponibile
    if (tris[0][0] == ' ') {
        tris[0][0] = 'O';
        return;
    }
    if (tris[0][2] == ' ') {
        tris[0][2] = 'O';
        return;
    }
    if (tris[2][0] == ' ') {
        tris[2][0] = 'O';
        return;
    }
    if (tris[2][2] == ' ') {
        tris[2][2] = 'O';
        return;
    }

    // Altrimenti, prendere qualsiasi spazio rimanente
    for (int r = 0; r < DIM; ++r) {
        for (int c = 0; c < DIM; ++c) {
            if (tris[r][c] == ' ') {
                tris[r][c] = 'O';
                return;
            }
        }
    }
}

int main() {
    char tris[DIM][DIM];
    int giocatore = 1;
    int mossaR, mossaC;
    char mossaCL;
    bool fine = true;
    int tipoGioco;

    srand(time(NULL));

    azzera(tris, DIM);
    
    stampaTitolo();
    cout << "Inserire (1) per due giocatori o (2) per giocatore contro CPU: " << endl;
    cin >> tipoGioco;
    
	// Controllo che tipoGioco sia 1 o 2
	while (tipoGioco != 1 && tipoGioco != 2) {
		system("cls");
		stampaTitolo();
	    cout << "SCELTA NON VALIDA!"<< endl << "Inserire (1) per due giocatori o (2) per giocatore contro CPU:" << endl;
	    cin >> tipoGioco;
	}
	
	system("cls");
	
    do {
        stampaTris(tris);

        if (tipoGioco == 2 && giocatore == 2) {
            mossaCPU(tris);
            giocatore = 1;
        } else {
            bool riprova;
            do {
			    riprova = false;
			    cout << "Giocatore " << giocatore << " selezionare mossa (riga colonna): " << endl;
			    string input;
			    cin >> input;
			
			    if (input.length() != 2 || !isdigit(input[0]) || !isalpha(input[1])) {
			        cout << endl << "MOSSA INVALIDA: Inserire una riga numerica (1-" << DIM << ") e una colonna lettera (a-" << char('a' + DIM - 1) << ")!" << endl << "RIPROVA" << endl << endl;
			        riprova = true;
			    } else {
			        mossaR = input[0] - '0';
			        mossaCL = input[1];
			
			        if (mossaR < 1 || mossaR > DIM || mossaCL < 'a' || mossaCL > 'a' + DIM - 1 || tris[mossaR - 1][mossaCL - 'a'] != ' ') {
			            cout << endl << "MOSSA INVALIDA: Inserire una riga numerica (1-" << DIM << ") e una colonna lettera (a-" << char('a' + DIM - 1) << ")!" << endl << "RIPROVA" << endl << endl;
			            riprova = true;
			        }
			    }
			} while (riprova);
			
			mossaR--;  // Adatto mossaR per l'uso nell'array
			mossaC = mossaCL - 'a';  // Adatto mossaCL per l'uso nell'array

            tris[mossaR][mossaC] = (giocatore == 1) ? 'X' : 'O';
            giocatore = (giocatore == 1) ? 2 : 1;
        }

        system("cls");

        fine = verifica(tris, DIM);

    } while (fine);

    cout << endl << endl;

    stampaTris(tris);

    return 0;
}
