#include <string>
#include <iostream>
#include "cell.h"
using namespace std;

bool init_test(cell celly) {
    if (celly.isMine() || celly.isFlagged() || celly.isRevealed() || celly.getMines() != 0) {
        return false;
    }
    return true;
}

string fullCellTest() {
    // debug arr key
    // arr[0] revealed bool
    // arr[1] flagged bool
    // arr[2] isMine bool
    // arr[3] mines int
    
    // test conds:
    // init
    // reveal
    // make mine: also interacts with mine count
    // flag method: revelaed and unrevealed
    // unflag method
    // update mine: interacts with mine
    
    // variable def
    cell celly;
    string result = "";
    int arr[4];
    
    // init test
    if (!init_test(celly)) {
        result += "init_error";
        return result;
    }
    
    // behavior arr init
    celly.debugArr(arr);
    
    // reveal test
    celly.reveal();
    celly.debugArr(arr);
    if (arr[0] != 1) {
        result += "reveal_error";
        return result;
    }
    celly.undoReveal();
    celly.debugArr(arr);
    
    // flag test
    celly.flag();
    celly.debugArr(arr);
    if (arr[1] != 1) {
        result += "flag_error";
        return result;
    }
    
    // unflag test
    celly.unflag();
    celly.debugArr(arr);
    if (arr[1] != 0) {
        result += "unflag_error";
        return result;
    }
    
    // unflag flag dependency
    celly.unflag();
    celly.debugArr(arr);
    if (arr[1] != 0) {
        result += "unflag_error_flag";
        return result;
    }
    
    // flag reveal dependency
    celly.reveal();
    celly.flag();
    celly.debugArr(arr);
    if (arr[1] != 0) {
        result += "flag_error_reveal";
        return result;
    }
    celly.undoReveal();
    celly.undoFlag();
    
    // make mine test
    celly.makeMine();
    celly.debugArr(arr);
    if (arr[2] != 1) {
        result += "mine_error";
        return result;
    }
    if (arr[3] != -1) {
        result += "mine_error_mineCount";
        return result;
    }
    
    // mine count test
    celly.updateMines(100);
    celly.debugArr(arr);
    if (arr[3] != -1) {
        result += "updateMines_error_mine";
        return result;
    }
    celly.undoMine();
    celly.updateMines(100);
    celly.debugArr(arr);
    if (arr[3] != 100) {
        result += "updateMines_error";
        return result;
    }
    
    if (arr[0] != 0 || arr[1] != 0 || arr[2] != 0 || arr[3] != 100) {
        result += "unspecified_error";
        return result;
    } 
    result += "success!";
    return result;
}

int main() {
    cout << fullCellTest() << endl;
    return 0;
}