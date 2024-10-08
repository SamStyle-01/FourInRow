#include "SamCellsView.h"

int ROWS = 8, COLS = 7, WIN_CONDITION = 4, NUM_PICTURES = 35;

SamCellsView::SamCellsView(QWidget *parent) : QWidget{parent}, SamLogic() {
    this->cells = nullptr;
    bVictory = false;

    index = -1;
    web_index = -1;

    this->setStyleSheet("background-color: rgba(100, 150, 150, 200); border: 2px solid rgba(200, 150, 100, 150); border-radius: 65px;");

    playersCells = new QPixmap*[NUM_PICTURES];
    for (int i = 0; i < NUM_PICTURES; i++) {
        playersCells[i] = new QPixmap("./skins/player" + QString::number(i + 1) + ".png");
    }

    emptyCell = new QPixmap("./skins/emptyCell.png");

    fieldLayout = new QGridLayout();

    this->viewCells = nullptr;
    this->cols = nullptr;

    line = new SamWinLine(this);
    line->setAttribute(Qt::WA_TransparentForMouseEvents);
    line->setStyleSheet("background-color: none; border: none;");

    this->setLayout(fieldLayout);
}

SamCellsView::SamCellsView(bool t) {
    Q_UNUSED(t);
}

CellType** SamCellsView::getCells() {
    CellType** newCells = new CellType*[ROWS];
    for (int i = 0; i < ROWS; i++) {
        newCells[i] = new CellType[COLS];
        for (int j = 0; j < COLS; j++) {
            newCells[i][j] = cells[i][j];
        }
    }
    return newCells;
}

bool SamCellsView::oneOnBoard() const {
    int figures = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (cells[i][j] != CellType::CELLTYPE_EMPTY) figures++;
        }
    }

    return (figures == 1);
}

void SamCellsView::setCells() {
    this->cells = new CellType * [ROWS];
    for (int i = 0; i < ROWS; i++) {
        cells[i] = new CellType[COLS];
        for (int j = 0; j < COLS; j++)
            cells[i][j] = CELLTYPE_EMPTY;
    }

    this->cols = new SamRow*[COLS];
    for (int i = 0; i < COLS; i++) {
        cols[i] = new SamRow(this, i, reinterpret_cast<SamGame*>(this->parent()));
        cols[i]->setStyleSheet("background-color: none; border: none; border-radius: 5px;");
    }

    viewCells = new QLabel*[ROWS * COLS];
    for (int i = 0; i < ROWS * COLS; i++) {
        viewCells[i] = new QLabel(this);
        viewCells[i]->setAttribute(Qt::WA_TransparentForMouseEvents);
        viewCells[i]->setMaximumSize(56, 56);
        viewCells[i]->setScaledContents(true);
        viewCells[i]->setPixmap(*emptyCell);
        viewCells[i]->setStyleSheet("background-color: none; border: none;");
    }

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            fieldLayout->addWidget(viewCells[COLS * i + j], i, j);
        }
    }

    for (int i = 0; i < COLS; i++) {
        fieldLayout->addWidget(cols[i], 0, i, ROWS, 1);
    }
}

void SamCellsView::Show() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (cells[i][j] == CELLTYPE_EMPTY) {
                viewCells[COLS * i + j]->setPixmap(*emptyCell);
            }
            else if (cells[i][j] == CELLTYPE_O) {
                viewCells[COLS * i + j]->setPixmap(*playersCells[skin2]);
            }
            else if (cells[i][j] == CELLTYPE_X) {
                viewCells[COLS * i + j]->setPixmap(*playersCells[skin1]);
            }
        }
    }
    line->raise();
    line->update();
}

bool SamCellsView::IsRowMade(unsigned row) {
    int numX = 0, numO = 0;
    for (int i = 0; i < COLS; i++) {
        if (cells[row][i] == CELLTYPE_O) {
            numO++;
            if (numO == WIN_CONDITION) {
                bVictory = true;
                int add = 0;
                for (; i + add + 1 < COLS && cells[row][i + add + 1] == CELLTYPE_O; add++);
                fieldLayout->addWidget(line, row, i - 3, 1, 4 + add);
                line->Activate(LineState::ROW);
                return true;
            }
            numX = 0;
        }
        else if (cells[row][i] == CELLTYPE_X) {
            numX++;
            if (numX == WIN_CONDITION) {
                bVictory = true;
                int add = 0;
                for (; i + add + 1 < COLS && cells[row][i + add + 1] == CELLTYPE_X; add++);
                fieldLayout->addWidget(line, row, i - 3, 1, 4 + add);
                line->Activate(LineState::ROW);
                return true;
            }
            numO = 0;
        }
        else {
            numO = 0;
            numX = 0;
        }
    }
    return false;
}

bool SamCellsView::IsColumnMade(unsigned col) {
    int numX = 0, numO = 0;
    for (int i = 0; i < ROWS; i++) {
        if (cells[i][col] == CELLTYPE_O) {
            numO++;
            if (numO == WIN_CONDITION) {
                bVictory = true;
                fieldLayout->addWidget(line, i - 3, col, 4, 1);
                line->Activate(LineState::COL);
                return true;
            }
            numX = 0;
        }
        else if (cells[i][col] == CELLTYPE_X) {
            numX++;
            if (numX == WIN_CONDITION) {
                bVictory = true;
                fieldLayout->addWidget(line, i - 3, col, 4, 1);
                line->Activate(LineState::COL);
                return true;
            }
            numO = 0;
        }
        else {
            numO = 0;
            numX = 0;
        }
    }
    return false;
}

bool SamCellsView::checkMainDiags() {
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

            if ((numX == WIN_CONDITION) || (numO == WIN_CONDITION)) {
                bVictory = true;
                int add = 0;
                for (; j + add + 1 < COLS && i2 + add + 1 < ROWS && cells[i2 + add + 1][j + add + 1] == cells[i2][j]; add++);
                fieldLayout->addWidget(line, i2 - 3, j - 3, 4 + add, 4 + add);
                line->Activate(LineState::DIAG_RIGHT);
                return true;
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

            if ((numX == WIN_CONDITION) || (numO == WIN_CONDITION)) {
                bVictory = true;
                int add = 0;
                for (; i + add + 1 < ROWS && j2 + add + 1 < COLS && cells[i + add + 1][j2 + add + 1] == cells[i][j2]; add++);
                fieldLayout->addWidget(line, i - 3, j2 - 3, 4 + add, 4 + add);
                line->Activate(LineState::DIAG_RIGHT);
                return true;
            }
        }

        numX = numO = 0;
    }

    return false;
}

bool SamCellsView::checkSideDiags() {
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

            if ((numX == WIN_CONDITION) || (numO == WIN_CONDITION)) {
                bVictory = true;
                int add = 0;
                for (; j - add - 1 >= 0 && i2 + add + 1 < ROWS && cells[i2 + add + 1][j - add - 1] == cells[i2][j]; add++);
                fieldLayout->addWidget(line, i2 - 3, j - add, 4 + add, 4 + add);
                line->Activate(LineState::DIAG_LEFT);
                return true;
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

            if ((numX == WIN_CONDITION) || (numO == WIN_CONDITION)) {
                bVictory = true;
                int add = 0;
                for (; i + add + 1 < ROWS && j2 - add - 1 >= 0 && cells[i + add + 1][j2 - add - 1] == cells[i][j2]; add++);
                fieldLayout->addWidget(line, i - 3, j2 - add, 4 + add, 4 + add);
                line->Activate(LineState::DIAG_LEFT);
                return true;
            }
        }

        numX = numO = 0;
    }

    return false;

}

bool SamCellsView::IsBoardFull() {
    for (int j = 0; j < COLS; j++)
        if (cells[0][j] == CELLTYPE_EMPTY) return false;

    return true;
}

bool SamCellsView::CheckEndCondition() {
    for (int i = 0; i < ROWS; i++)
        if (IsRowMade(i))
            return true;
    for (int i = 0; i < COLS; i++)
        if (IsColumnMade(i))
            return true;

    if (checkMainDiags() || checkSideDiags() || IsBoardFull())
        return true;

    return false;
}

void SamCellsView::InitIt(SamCellsView* board) {
    this->cells = new CellType * [ROWS];
    for (int i = 0; i < ROWS; i++) {
        cells[i] = new CellType[COLS];
        for (int j = 0; j < COLS; j++)
            cells[i][j] = board->cells[i][j];
    }
    this->viewCells = nullptr;
    this->cols = nullptr;
    this->line = nullptr;
    this->playersCells = nullptr;
}

void SamCellsView::ClearStart() {
    for (int i = 0; i < ROWS; i++) {
        delete[] cells[i];
    }
    delete[] cells;
    cells = nullptr;

    for (int i = 0; i < COLS * ROWS; i++) {
        delete viewCells[i];
    }
    delete[] viewCells;
    viewCells = nullptr;

    for (int i = 0; i < COLS; i++) {
        delete cols[i];
    }
    delete[] cols;
    cols = nullptr;

    this->bVictory = false;

    line->DisActivate();
    fieldLayout->removeWidget(line);

    stepsBack.clear();
    stepsForward.clear();
}

SamCellsView::~SamCellsView() {
    if (viewCells != nullptr) {
        for (int i = 0; i < ROWS * COLS; i++) {
            delete viewCells[i];
        }
        delete[] viewCells;

        for (int i = 0; i < COLS; i++) {
            delete cols[i];
        }
        delete[] cols;

        for (int i = 0; i < NUM_PICTURES; i++) {
            delete playersCells[i];
        }

        delete[] playersCells;
        delete emptyCell;
        delete line;
        delete fieldLayout;
    }

}
