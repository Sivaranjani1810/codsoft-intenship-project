
#include <iostream>
#include <string>
using namespace std;

class Board {
private:
    char grid[3][3];
    int filledCells;

public:
    Board() : filledCells(0) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                grid[i][j] = ' ';
            }
        }
    }

    void drawBoard() const {
        cout << "-------------" << endl;
        for (int i = 0; i < 3; i++) {
            cout << "| ";
            for (int j = 0; j < 3; j++) {
                cout << grid[i][j] << " | ";
            }
            cout << endl << "-------------" << endl;
        }
    }

    bool isValidMove(int row, int col) const {
        return (row >= 0 && row < 3 && col >= 0 && col < 3 && grid[row][col] == ' ');
    }

    void makeMove(int row, int col, char symbol) {
        if (isValidMove(row, col)) {
            grid[row][col] = symbol;
            filledCells++;
        }
    }

    bool checkWin(char symbol) const {
        for (int i = 0; i < 3; i++) {
            if (grid[i][0] == symbol && grid[i][1] == symbol && grid[i][2] == symbol) return true;
            if (grid[0][i] == symbol && grid[1][i] == symbol && grid[2][i] == symbol) return true;
        }
        if (grid[0][0] == symbol && grid[1][1] == symbol && grid[2][2] == symbol) return true;
        if (grid[0][2] == symbol && grid[1][1] == symbol && grid[2][0] == symbol) return true;
        return false;
    }

    bool isFull() const {
        return filledCells == 9;
    }
};

class TicTacToe {
private:
    Board board;
    char currentPlayer;

public:
    TicTacToe() : currentPlayer('X') {}

    void play() {
        int row, col;
        cout << "Welcome to Tic-Tac-Toe!" << endl;
        while (true) {
            board.drawBoard();
            cout << "Player " << currentPlayer << ", enter row (1-3) and column (1-3): ";
            cin >> row >> col;
            row--; col--;

            if (!board.isValidMove(row, col)) {
                cout << "Invalid move. Try again." << endl;
                continue;
            }

            board.makeMove(row, col, currentPlayer);

            if (board.checkWin(currentPlayer)) {
                board.drawBoard();
                cout << "Player " << currentPlayer << " wins!" << endl;
                break;
            }

            if (board.isFull()) {
                board.drawBoard();
                cout << "It's a draw!" << endl;
                break;
            }

            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }
};

int main() {
    char playAgain;
    do {
        TicTacToe game;
        game.play();
        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;
    } while (playAgain == 'y' || playAgain == 'Y');
    return 0;
}
