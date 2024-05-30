
//	J.Pedro Gregorio Barros 
//	2023-2024

#include <iostream>
#include <ctime>
#include <iomanip>

using namespace std;

#define DIM 6
#define GIOCATORE1 'X'
#define GIOCATORE2 'O'

void stampaTitolo() {
    cout << ":::::::::: ::::::::  :::::::::  :::::::::     :::              :::" << endl;
    cout << ":+:       :+:    :+: :+:    :+:      :+:    :+: :+:           :+:" << endl;
    cout << "+:+       +:+    +:+ +:+    +:+     +:+    +:+   +:+         +:+ +:+" << endl;
    cout << ":#::+::#  +#+    +:+ +#++:++#:     +#+    +#++:++#++:       +#+  +:+" << endl;
    cout << "+#+       +#+    +#+ +#+    +#+   +#+     +#+     +#+      +#+#+#+#+#+" << endl;
    cout << "#+#       #+#    #+# #+#    #+#  #+#      #+#     #+#            #+#" << endl;
    cout << "###        ########  ###    ### ######### ###     ###            ###" << endl << endl;
}

void azzera(char forza[][DIM]) {
    for (int r = 0; r < DIM; ++r) {
        for (int c = 0; c < DIM; ++c) {
            forza[r][c] = ' ';
        }
    }
}

bool verificaVittoria(char forza[][DIM], char giocatore) {
    // Controllo righe
    for (int r = 0; r < DIM; ++r) {
        for (int c = 0; c <= DIM - 4; ++c) {
            if (forza[r][c] == giocatore &&
                forza[r][c+1] == giocatore &&
                forza[r][c+2] == giocatore &&
                forza[r][c+3] == giocatore) {
                return true;
            }
        }
    }

    // Controllo colonne
    for (int r = 0; r <= DIM - 4; ++r) {
        for (int c = 0; c < DIM; ++c) {
            if (forza[r][c] == giocatore &&
                forza[r+1][c] == giocatore &&
                forza[r+2][c] == giocatore &&
                forza[r+3][c] == giocatore) {
                return true;
            }
        }
    }

    // Controllo diagonali
    for (int r = 0; r <= DIM - 4; ++r) {
        for (int c = 0; c <= DIM - 4; ++c) {
            if (forza[r][c] == giocatore &&
                forza[r+1][c+1] == giocatore &&
                forza[r+2][c+2] == giocatore &&
                forza[r+3][c+3] == giocatore) {
                return true;
            }
            if (forza[r][c+3] == giocatore &&
                forza[r+1][c+2] == giocatore &&
                forza[r+2][c+1] == giocatore &&
                forza[r+3][c] == giocatore) {
                return true;
            }
        }
    }

    return false;
}

bool mossaValida(char forza[][DIM], int mossa) {
    return mossa >= 0 && mossa < DIM && forza[0][mossa] == ' ';
}

void stampaForza(char forza[][DIM]) {
    cout << endl;
	for (int r = 0; r < DIM; ++r) {
        cout << "   ";
		for (int c = 0; c < DIM; ++c) {
            cout << setw(2) << "| " << forza[r][c] << " ";
        }
        cout << "|" << endl;
    }
    cout << "   -------------------------" << endl;
    cout << "     1   2   3   4   5   6" << endl << endl;
}

int main() {
    char forza[DIM][DIM];
    int giocata = 0;
    int tipoGioco;
    int player = 1;

    srand(time(NULL));

    azzera(forza);
    
	stampaTitolo();
    cout << "Inserire (1) per due giocatori o (2) per giocatore contro CPU:" << endl;
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
        stampaForza(forza);

        int mossa;
        if (tipoGioco == 2 && player == 2) {
            do {
                mossa = rand() % DIM;
            } while (!mossaValida(forza, mossa));
        } else {
            do {
                cout << "Giocatore " << player << " seleziona mossa (1-6): ";
                cin >> mossa;
                mossa--; // converti a indice base 0
            } while (!mossaValida(forza, mossa));
        }

        int riga = 0;
        while (riga < DIM && forza[riga][mossa] == ' ') {
            riga++;
        }

        if (player == 1) {
            forza[riga-1][mossa] = GIOCATORE1;
            player = 2;
        } else {
            forza[riga-1][mossa] = GIOCATORE2;
            player = 1;
        }

        giocata++;

        system("cls");

        if (verificaVittoria(forza, GIOCATORE1)) {
            cout << "Giocatore 1 ha vinto!" << endl;
            stampaForza(forza);
            break;
        } else if (verificaVittoria(forza, GIOCATORE2)) {
            cout << "Giocatore 2 ha vinto!" << endl;
            stampaForza(forza);
            break;
        } else if (giocata == DIM * DIM) {
            cout << "PAREGGIO!" << endl;
            stampaForza(forza);
            break;
        }

    } while (true);

    return 0;
}