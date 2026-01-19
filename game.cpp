#include <stdlib.h>
#include <stdexcept>
#include <iostream>

using namespace std;

const int LENGTH_Y = 6;
const int LENGTH_X = 7;

bool outOfRange(const int x, const int y) {
    if(x < 0 || x >= LENGTH_X) {
        return true;
    }
    if(y < 0 || y >= LENGTH_Y) {
        return true;
    }
    return false;
}

class Board {

private:
    char cells[LENGTH_Y][LENGTH_X];
        
public:
    Board() {
        for(int i = 0; i < LENGTH_Y; i++) {
            for (int j = 0; j < LENGTH_X; j++)
            {
                cells[i][j] = ' ';
            }
            
        }
    }
    Board(const char outerCells[LENGTH_Y][LENGTH_X]) {
        for(int i = 0; i < LENGTH_Y; i++) {
            for (int j = 0; j < LENGTH_X; j++)
            {
                cells[i][j] = outerCells[i][j];
            }
        }
    }
    
    void makeMove(const int x, const int y, const char ch) {
        
        if(outOfRange(x, y)) {
            throw invalid_argument("Coordinates out of range.");
        }

        if(at(x, y) != ' ') {
            throw invalid_argument("Cell already filled.");
        }
        
        if(y == (LENGTH_Y - 1)) {
            cells[y][x] = ch;
        } else {
            if(cells[y+1][x] != ' ') {
                //cout << "Checking column top: " << x << y + 1 << endl; 
                cells[y][x] = ch;
            } else {
                throw invalid_argument("Can place move only on top of the column.");
            }
        }
        
        
    }

    char at(const int x, const int y) const {
        return cells[y][x];
    }

    bool defineWinLine(const int startX, const int startY, 
        int xWalk, int yWalk, const char ch) const {

        if(outOfRange(startX, startY)) {
            throw invalid_argument("startx and starty out of range.");
        }

        int currentX = startX;
        int currentY = startY;

        int checkerCount = 1;

        if(at(startX, startY) != ch) {
            return false;
        }
        
        char currentChar = ch;
        bool directionSwitch = false;

        while(checkerCount < 4) {
            currentX += xWalk;
            currentY += yWalk;
            if(outOfRange(currentX, currentY) || at(currentX, currentY) != ch) {
                if(!directionSwitch) {
                    directionSwitch = true;
                    xWalk *= -1;
                    yWalk *= -1;
                    currentX = startX;
                    currentY = startY;
                    continue;
                } else {
                    break;
                }
            }
            cout << "At currentx: " << currentX << " currenty " << currentY << " " << at(currentX, currentY) << endl;
            cout << "Increnenting count at " << currentX << " " << currentY << endl;
            checkerCount++;
        }
        cout << "Count " <<  checkerCount << endl;
        return checkerCount >= 4;
        
        

    }
    char defineWin(const int x, const int y, char ch) const {
        
        return defineWinLine(x, y, 1, 0, ch)
            || defineWinLine(x, y, 0, 1, ch)
            || defineWinLine(x, y, 1, 1, ch)
            || defineWinLine(x, y, 1, -1, ch);
    }

};

int main() {
    cout << "Start..." << endl;
    char cells[LENGTH_Y][LENGTH_X] = {
        {' ', ' ', ' ', ' ', ' ', ' ', ' ' },
        {' ', ' ', ' ', ' ', ' ', ' ', ' ' },
        {' ', ' ', ' ', ' ', ' ', 'X', ' ' },
        {' ', ' ', ' ', ' ', 'X', '0', ' ' },
        {' ', ' ', ' ', 'X', '0', '0', ' ' },
        {' ', ' ', 'X', '0', '0', '0', ' ' }
    };
    Board board(cells);
    int lastx = 2;
    int lasty = 5;

    bool win = board.defineWin(lastx, lasty, 'X');
    cout << "Win: " << win << endl;
    return 0;
}