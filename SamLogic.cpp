#include "SamLogic.h"

SamLogic::SamLogic() {
    this->cells = nullptr;
    bVictory = false;
}

SamLogic::SamLogic(CellType** board) {
    this->cells = new CellType * [ROWS];
    for (int i = 0; i < ROWS; i++) {
        cells[i] = new CellType[COLS];
        for (int j = 0; j < COLS; j++)
            cells[i][j] = board[i][j];
    }
}

void SamLogic::setCells() {
    this->cells = new CellType * [ROWS];
    for (int i = 0; i < ROWS; i++) {
        cells[i] = new CellType[COLS];
        for (int j = 0; j < COLS; j++)
            cells[i][j] = CELLTYPE_EMPTY;
    }
}

int SamLogic::stepsBackTop() const {
    return stepsBack.top();
}

void SamLogic::stepsBackPop() {
    stepsBack.pop();
}

bool SamLogic::stepsBackIsEmpty() const {
    return stepsBack.isEmpty();
}

void SamLogic::stepsBackPush(int step) {
    stepsBack.push(step);
}

void SamLogic::stepsBackReserve(int count) {
    stepsBack.reserve(count);
}

void SamLogic::stepsBackClear() {
    stepsBack.clear();
}


int SamLogic::stepsForwardTop() const {
    return stepsForward.top();
}

void SamLogic::stepsForwardPop() {
    stepsForward.pop();
}

bool SamLogic::stepsForwardIsEmpty() const {
    return stepsForward.isEmpty();
}

void SamLogic::stepsForwardPush(int step) {
    stepsForward.push(step);
}

void SamLogic::stepsForwardReserve(int count) {
    stepsForward.reserve(count);
}

void SamLogic::stepsForwardClear() {
    stepsForward.clear();
}

void SamLogic::SetCell(int xpos, CellType ct) {
    for (int i = ROWS - 1; i >= 0; i--) {
        if (cells[i][xpos] == CELLTYPE_EMPTY) {
            cells[i][xpos] = ct;
            return;
        }
    }
}

void SamLogic::setBVictory(bool victory) {
    bVictory = victory;
}

void SamLogic::ClearCell(int xpos) {
    int i;
    for (i = 0; cells[i][xpos] == CELLTYPE_EMPTY; i++) {}

    cells[i][xpos] = CELLTYPE_EMPTY;
}

bool SamLogic::CheckLegal(int xpos) {
    if (xpos > COLS - 1 || xpos < 0)
        return false;
    if (cells[0][xpos] == CELLTYPE_EMPTY) return true;
    return false;
}

int SamLogic::IsRowMade(unsigned row) {
    int numX = 0, numO = 0;
    for (int i = 0; i < COLS; i++) {
        if (cells[row][i] == CELLTYPE_O) {
            numO++;
            if (numO == WIN_CONDITION) {
                bVictory = true;
                return 2;
            }
            numX = 0;
        }
        else if (cells[row][i] == CELLTYPE_X) {
            numX++;
            if (numX == WIN_CONDITION) {
                bVictory = true;
                return 1;
            }
            numO = 0;
        }
        else {
            numO = 0;
            numX = 0;
        }
    }
    return 0;
}

int SamLogic::IsColumnMade(unsigned col) {
    int numX = 0, numO = 0;
    for (int i = 0; i < ROWS; i++) {
        if (cells[i][col] == CELLTYPE_O) {
            numO++;
            if (numO == WIN_CONDITION) {
                bVictory = true;
                return 2;
            }
            numX = 0;
        }
        else if (cells[i][col] == CELLTYPE_X) {
            numX++;
            if (numX == WIN_CONDITION) {
                bVictory = true;
                return 1;
            }
            numO = 0;
        }
        else {
            numO = 0;
            numX = 0;
        }
    }
    return 0;
}

int SamLogic::checkMainDiags() {
    int numX = 0, numO = 0;
    for (int i = 0; i < ROWS - 3; i++) {
        int i2 = i;
        for (int j = 0; j < COLS && i2 < ROWS; j++, i2++) {
            if (cells[i2][j] == CELLTYPE_O) {
                numO++;
                numX = 0;
            }
            else if (cells[i2][j] == CELLTYPE_X) {
                numX++;
                numO = 0;
            }
            else {
                numX = numO = 0;
            }

            if (numX == WIN_CONDITION) {
                bVictory = true;
                return 1;
            }
            else if (numO == WIN_CONDITION) {
                bVictory = true;
                return 2;
            }
        }

        numX = numO = 0;
    }

    for (int j = 1; j < COLS - 3; j++) {
        int j2 = j;
        for (int i = 0; i < ROWS && j2 < COLS; j2++, i++) {
            if (cells[i][j2] == CELLTYPE_O) {
                numO++;
                numX = 0;
            }
            else if (cells[i][j2] == CELLTYPE_X) {
                numX++;
                numO = 0;
            }
            else {
                numX = numO = 0;
            }

            if (numX == WIN_CONDITION) {
                bVictory = true;
                return 1;
            }
            else if (numO == WIN_CONDITION) {
                bVictory = true;
                return 2;
            }
        }

        numX = numO = 0;
    }

    return 0;
}

int SamLogic::checkSideDiags() {
    int numX = 0, numO = 0;
    for (int i = 0; i < ROWS - 3; i++) {
        int i2 = i;
        for (int j = COLS - 1; j >= 0 && i2 < ROWS; j--, i2++) {
            if (cells[i2][j] == CELLTYPE_O) {
                numO++;
                numX = 0;
            }
            else if (cells[i2][j] == CELLTYPE_X) {
                numX++;
                numO = 0;
            }
            else {
                numX = numO = 0;
            }

            if (numX == WIN_CONDITION) {
                bVictory = true;
                return 1;
            }
            else if (numO == WIN_CONDITION) {
                bVictory = true;
                return 2;
            }
        }

        numX = numO = 0;
    }

    for (int j = COLS - 4; j <= COLS - 1; j++) {
        int j2 = j;
        for (int i = 0; i < ROWS && j2 >= 0; j2--, i++) {
            if (cells[i][j2] == CELLTYPE_O) {
                numO++;
                numX = 0;
            }
            else if (cells[i][j2] == CELLTYPE_X) {
                numX++;
                numO = 0;
            }
            else {
                numX = numO = 0;
            }

            if (numX == WIN_CONDITION) {
                bVictory = true;
                return 1;
            }
            else if (numO == WIN_CONDITION) {
                bVictory = true;
                return 2;
            }
        }

        numX = numO = 0;
    }

    return 0;

}

bool SamLogic::IsBoardFull() {
    for (int j = 0; j < COLS; j++)
        if (cells[0][j] == CELLTYPE_EMPTY) return false;

    return true;
}

int SamLogic::CheckEndCondition() {
    int win = 0;
    for (int i = 0; i < ROWS; i++) {
        win = IsRowMade(i);
        if (win) return win;
    }

    for (int i = 0; i < COLS; i++){
        win = IsColumnMade(i);
        if (win) return win;
    }

    win = checkMainDiags();
    if (win) return win;

    win = checkSideDiags();
    if (win) return win;

    if (IsBoardFull()) return 3;

    return 0;
}

bool SamLogic::IsVictory() {
    return bVictory;
}


std::pair<int, int> SamLogic::GetSize() const {
    return std::make_pair(ROWS, COLS);
}

SamLogic::SamLogic(SamLogic* board) {
    this->cells = new CellType * [ROWS];
    for (int i = 0; i < ROWS; i++) {
        cells[i] = new CellType[COLS];
        for (int j = 0; j < COLS; j++)
            cells[i][j] = board->cells[i][j];
    }
}

void SamLogic::ClearStart() {
    for (int i = 0; i < ROWS; i++) {
        delete[] cells[i];
    }
    delete[] cells;

    this->bVictory = false;

    stepsBack.clear();
    stepsForward.clear();
}

QPair<int, int> SamLogic::getEstimation() {
    const int COEFF = 7;
    int player1 = 0, player2 = 0;

    if (CheckEndCondition() != 2) {
        for (int i = 0; i < COLS; i++) {
            if (CheckLegal(i)) {
                SetCell(i, CellType::CELLTYPE_X);
                if (CheckEndCondition() == 1) {
                    player1 += 500;
                }
                ClearCell(i);
            }
        }
    }

    if (CheckEndCondition() != 1) {
        for (int i = 0; i < COLS; i++) {
            if (CheckLegal(i)) {
                SetCell(i, CellType::CELLTYPE_O);
                if (CheckEndCondition() == 2) {
                    player2 += 500;
                }
                ClearCell(i);
            }
        }
    }

    if (CheckEndCondition() != 2) {
        for (int i = 0; i < COLS - 3; i++) {
            if (CheckLegal(i) && CheckLegal(i + 3)) {
                SetCell(i, CellType::CELLTYPE_X);
                SetCell(i + 3, CellType::CELLTYPE_X);
                if (CheckEndCondition() == 1) {
                    player1 += 500;
                }
                ClearCell(i);
                ClearCell(i + 3);
            }
        }
    }

    if (CheckEndCondition() != 1) {
        for (int i = 0; i < COLS - 3; i++) {
            if (CheckLegal(i) && CheckLegal(i + 3)) {
                SetCell(i, CellType::CELLTYPE_O);
                SetCell(i + 3, CellType::CELLTYPE_O);
                if (CheckEndCondition() == 2) {
                    player2 += 500;
                }
                ClearCell(i);
                ClearCell(i + 3);
            }
        }
    }

    if (CheckEndCondition() != 1) {
        for (int i = 0; i < COLS - 4; i++) {
            if (CheckLegal(i) && CheckLegal(i + 2) && CheckLegal(i + 4)) {
                SetCell(i, CellType::CELLTYPE_O);
                SetCell(i + 2, CellType::CELLTYPE_O);
                if (CheckEndCondition() == 2) {
                    ClearCell(i);

                    SetCell(i + 4, CellType::CELLTYPE_O);

                    if (CheckEndCondition() == 2) {
                        ClearCell(i + 4);
                        ClearCell(i + 2);

                        player2 += 300;
                    }
                    else {
                        ClearCell(i + 4);
                        ClearCell(i + 2);
                    }
                }
                else {
                    ClearCell(i);
                    ClearCell(i + 2);
                }
            }
        }
    }

    if (CheckEndCondition() != 2) {
        for (int i = 0; i < COLS - 4; i++) {
            if (CheckLegal(i) && CheckLegal(i + 2) && CheckLegal(i + 4)) {
                SetCell(i, CellType::CELLTYPE_X);
                SetCell(i + 2, CellType::CELLTYPE_X);
                if (CheckEndCondition() == 1) {
                    ClearCell(i);

                    SetCell(i + 4, CellType::CELLTYPE_X);

                    if (CheckEndCondition() == 1) {
                        ClearCell(i + 4);
                        ClearCell(i + 2);

                        player1 += 300;
                    }
                    else {
                        ClearCell(i + 4);
                        ClearCell(i + 2);
                    }
                }
                else {
                    ClearCell(i);
                    ClearCell(i + 2);
                }
            }
        }
    }

    for (int row = 0; row < ROWS; row++) {
        int numFriend = 0, numEnemy = 0, numEmpty = 0;
        int numFriendAgain = 0, numEnemyAgain = 0;
        for (int i = 0; i < COLS; i++) {
            if (cells[row][i] == CellType::CELLTYPE_X) {
                numFriend++;
                numFriendAgain++;
                if (numFriendAgain == WIN_CONDITION) {
                    player1 += 10000;
                }
                if (numEnemy) {
                    if (numEnemy + numEmpty >= 4) {
                        player2 += numEnemy * COEFF + numEmpty;
                    }
                    numEnemy = 0;
                    numEnemyAgain = 0;
                    numEmpty = 0;
                }
            }
            else if (cells[row][i] == CellType::CELLTYPE_O) {
                numEnemy++;
                numEnemyAgain++;
                if (numEnemyAgain == WIN_CONDITION) {
                    player2 += 10000;
                }
                if (numFriend) {
                    if (numFriend + numEmpty >= 4) {
                        player1 += numFriend * COEFF + numEmpty;
                    }
                    numFriend = 0;
                    numFriendAgain = 0;
                    numEmpty = 0;
                }
            }
            else {
                numEmpty++;
                numFriendAgain = 0;
                numEnemyAgain = 0;
            }
        }
        if (numFriend) {
            if (numFriend + numEmpty >= 4) {
                player1 += numFriend * COEFF + numEmpty;
            }
        }
        if (numEnemy) {
            if (numEnemy + numEmpty >= 4) {
                player2 += numEnemy * COEFF + numEmpty;
            }
        }
    }

    for (int col = 0; col < COLS; col++) {
        int numFriend = 0, numEnemy = 0, numEmpty = 0;
        int numFriendAgain = 0, numEnemyAgain = 0;
        for (int i = 0; i < ROWS; i++) {
            if (cells[i][col] == CellType::CELLTYPE_X) {
                numFriend++;
                numFriendAgain++;
                if (numFriendAgain == WIN_CONDITION) {
                    player1 += 10000;
                }
                if (numEnemy) {
                    if (numEnemy + numEmpty >= 4) {
                        player2 += numEnemy * COEFF + (numEmpty > 4 - numEnemy ? 4 - numEnemy : numEmpty);
                    }
                    numEnemy = 0;
                    numEnemyAgain = 0;
                    numEmpty = 0;
                }
            }
            else if (cells[i][col] == CellType::CELLTYPE_O) {
                numEnemy++;
                numEnemyAgain++;
                if (numEnemyAgain == WIN_CONDITION) {
                    player2 += 10000;
                }
                if (numFriend) {
                    if (numFriend + numEmpty >= 4) {
                        player1 += numFriend * COEFF + (numEmpty > 4 - numFriend ? 4 - numFriend : numEmpty);
                    }
                    numFriend = 0;
                    numFriendAgain = 0;
                    numEmpty = 0;
                }
            }
            else {
                numFriendAgain = 0;
                numEnemyAgain = 0;
                numEmpty++;
            }
        }
        if (numFriend) {
            if (numFriend + numEmpty >= 4) {
                player1 += numFriend * COEFF + numEmpty;
            }
        }
        if (numEnemy) {
            if (numEnemy + numEmpty >= 4) {
                player2 += numEnemy * COEFF + numEmpty;
            }
        }
    }

    int numFriend = 0, numEnemy = 0, numEmpty = 0;
    int numFriendAgain = 0, numEnemyAgain = 0;
    for (int i = 0; i < ROWS - 3; i++) {
        int i2 = i;
        for (int j = 0; j < COLS && i2 < ROWS; j++, i2++) {
            if (cells[i2][j] == CellType::CELLTYPE_X) {
                numFriend++;
                numFriendAgain++;
                if (numEnemy) {
                    if (numEnemy + numEmpty >= 4) {
                        player2 += numEnemy * COEFF + numEmpty;
                    }
                    numEnemy = 0;
                    numEnemyAgain = 0;
                    numEmpty = 0;
                }
            }
            else if (cells[i2][j] == CellType::CELLTYPE_O) {
                numEnemy++;
                numEnemyAgain++;
                if (numFriend) {
                    if (numFriend + numEmpty >= 4) {
                        player1 += numFriend * COEFF + numEmpty;
                    }
                    numFriend = 0;
                    numFriendAgain = 0;
                    numEmpty = 0;
                }
            }
            else {
                numEmpty++;
                numFriendAgain = 0;
                numEnemyAgain = 0;
            }

            if (numEnemyAgain == WIN_CONDITION) {
                player2 += 10000;
            }
            else if (numFriendAgain == WIN_CONDITION) {
                player1 += 10000;
            }
        }
        if (numFriend) {
            if (numFriend + numEmpty >= 4) {
                player1 += numFriend * COEFF + numEmpty;
            }
        }
        if (numEnemy) {
            if (numEnemy + numEmpty >= 4) {
                player2 += numEnemy * COEFF + numEmpty;
            }
        }
        numEnemy = numFriend = numEmpty = 0;
        numFriendAgain = numEnemyAgain = 0;
    }

    for (int j = 1; j < COLS - 3; j++) {
        int j2 = j;
        for (int i = 0; i < ROWS && j2 < COLS; j2++, i++) {
            if (cells[i][j2] == CellType::CELLTYPE_X) {
                numFriend++;
                numFriendAgain++;
                if (numEnemy) {
                    if (numEnemy + numEmpty >= 4) {
                        player2 += numEnemy * COEFF + numEmpty;
                    }
                    numEnemy = 0;
                    numEmpty = 0;
                    numEnemyAgain = 0;
                }
            }
            else if (cells[i][j2] == CellType::CELLTYPE_O) {
                numEnemy++;
                if (numFriend) {
                    if (numFriend + numEmpty >= 4) {
                        player1 += numFriend * COEFF + numEmpty;
                    }
                    numFriend = 0;
                    numFriendAgain = 0;
                    numEmpty = 0;
                }
            }
            else {
                numEmpty++;
                numFriendAgain = 0;
                numEnemyAgain = 0;
            }

            if (numEnemyAgain == WIN_CONDITION) {
                player2 += 10000;
            }
            else if (numFriendAgain == WIN_CONDITION) {
                player1 += 10000;
            }
        }
        if (numFriend) {
            if (numFriend + numEmpty >= 4) {
                player1 += numFriend * COEFF + numEmpty;
            }
        }
        if (numEnemy) {
            if (numEnemy + numEmpty >= 4) {
                player2 += numEnemy * COEFF + numEmpty;
            }
        }
        numEnemy = numFriend = numEmpty = 0;
        numFriendAgain = numEnemyAgain = 0;
    }

    numFriend = 0, numEnemy = 0, numEmpty = 0;
    numFriendAgain = 0, numEnemyAgain = 0;
    for (int i = 0; i < ROWS - 3; i++) {
        int i2 = i;
        for (int j = COLS - 1; j >= 0 && i2 < ROWS; j--, i2++) {
            if (cells[i2][j] == CellType::CELLTYPE_X) {
                numFriend++;
                numFriendAgain++;
                if (numEnemy) {
                    if (numEnemy + numEmpty >= 4) {
                        player2 += numEnemy * COEFF + numEmpty;
                    }
                    numEnemy = 0;
                    numEnemyAgain = 0;
                    numEmpty = 0;
                }
            }
            else if (cells[i2][j] == CellType::CELLTYPE_O) {
                numEnemy++;
                numEnemyAgain++;
                if (numFriend) {
                    if (numFriend + numEmpty >= 4) {
                        player1 += numFriend * COEFF + numEmpty;
                    }
                    numFriend = 0;
                    numFriendAgain = 0;
                    numEmpty = 0;
                }
            }
            else {
                numEmpty++;
                numFriendAgain = 0;
                numEnemyAgain = 0;
            }

            if (numEnemyAgain == WIN_CONDITION) {
                player2 += 10000;
            }
            else if (numFriendAgain == WIN_CONDITION) {
                player1 += 10000;
            }
        }
        if (numFriend) {
            if (numFriend + numEmpty >= 4) {
                player1 += numFriend * COEFF + numEmpty;
            }
        }
        if (numEnemy) {
            if (numEnemy + numEmpty >= 4) {
                player2 += numEnemy * COEFF + numEmpty;
            }
        }
        numEnemy = numFriend = numEmpty = 0;
        numFriendAgain = numEnemyAgain = 0;
    }

    for (int j = COLS - 4; j <= COLS - 1; j++) {
        int j2 = j;
        for (int i = 0; i < ROWS && j2 >= 0; j2--, i++) {
            if (cells[i][j2] == CELLTYPE_O) {
                numFriend++;
                numFriendAgain++;
                if (numEnemy) {
                    if (numEnemy + numEmpty >= 4) {
                        player2 += numEnemy * COEFF + numEmpty;
                    }
                    numEnemy = 0;
                    numEnemyAgain = 0;
                    numEmpty = 0;
                }
            }
            else if (cells[i][j2] == CELLTYPE_X) {
                numEnemy++;
                numEnemyAgain++;
                if (numFriend) {
                    if (numFriend + numEmpty >= 4) {
                        player1 += numFriend * COEFF + numEmpty;
                    }
                    numFriend = 0;
                    numFriendAgain = 0;
                    numEmpty = 0;
                }
            }
            else {
                numEmpty++;
                numFriendAgain = 0;
                numEnemyAgain = 0;
            }

            if (numEnemyAgain == WIN_CONDITION) {
                player2 += 10000;
            }
            else if (numFriendAgain == WIN_CONDITION) {
                player1 += 10000;
            }
        }
        if (numFriend) {
            if (numFriend + numEmpty >= 4) {
                player1 += numFriend * COEFF + numEmpty;
            }
        }
        if (numEnemy) {
            if (numEnemy + numEmpty >= 4) {
                player2 += numEnemy * COEFF + numEmpty;
            }
        }
        numEnemy = numFriend = numEmpty = 0;
        numFriendAgain = numEnemyAgain = 0;
    }

    return qMakePair(player1, player2);
}

SamLogic::~SamLogic() {
    if (cells != nullptr) {
        for (int i = 0; i < ROWS; i++) {
            delete[] cells[i];
        }
        delete[] cells;
    }
}
