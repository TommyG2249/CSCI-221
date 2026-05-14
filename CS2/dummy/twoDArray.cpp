#include <vector>
#include <string>
#include <utility>
#include <iostream>
using namespace std;

int main(int argc, char* argv[3]) {
    if (argc < 3) {
        cout << "Usage: " << argv[0] << " <board width> <board height>" << endl;
        return 1;
    }

    pair<int, int> boardMax = {stoi(argv[1]), stoi(argv[2])};

    int boardY = boardMax.first-2;
    int boardX = boardMax.second-2;

    vector<vector<string>> boardItems;
    boardItems.resize(boardY);
    for (int i = 0; i < boardY; i++) {
        boardItems[i].resize(boardX);
    }
    for (int i = 0; i < boardY; i++) {
        for (int j = 0; j < boardX; j++) {
            boardItems[i][j] = "~";
        }
    }

    for (int i = 0; i < boardY; i++) {
        for (int j = 0; j < boardX; j++) {
            cout << boardItems[i][j] << " ";
        }
        cout << endl;
    }
}