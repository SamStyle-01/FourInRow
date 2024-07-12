#include "AlphaBetaTree.h"
#include "pch.h"

// Для работы дерева мы создаём начальный родительский узел, который после сам
// рекурсивно создаст всю оставшуюся необходимую по глубине часть дерева.
AlphaBetaTree::AlphaBetaTree(SamLogic* cells, CellType cellType, QVector<int> PossibleSteps) {
    parent = new AlphaBetaNode(cells, 0, cellType, true, -1, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), PossibleSteps);
    this->PossibleSteps = PossibleSteps;
}

AlphaBetaNode::AlphaBetaNode(SamLogic* cells_, int generation, CellType cellType, bool maximize_it, int column,
                             int alpha, int beta, QVector<int> PossibleSteps) {
    this->generation = generation;
    this->maximize_it = maximize_it;
    this->alpha = alpha;
    this->beta = beta;
    this->column = column;
    this->cells = new SamLogic(cells_);
    this->cellType = cellType;
    this->value = maximize_it ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();

    // Если мы находимся на родительском узле дерева, то мы хотим распараллелить создание (обычно 7) дочерних узлов, чтобы создалось по итогу
    // 7 потоков, которые сильно бы оптимизировали программу.
    if (!cells->CheckEndCondition()) {
        this->children.reserve(PossibleSteps.size());
        QVector<SamLogic*> steps;
        QVector<int> cols;
        steps.reserve(PossibleSteps.size());
        cols.reserve(PossibleSteps.size());

        for (int i = 0; i < PossibleSteps.size(); i++) {
            if (cells->CheckLegal(PossibleSteps[i])) {
                cells->SetCell(PossibleSteps[i], this->cellType);
                steps.push_back(new SamLogic(cells));
                cells->ClearCell(PossibleSteps[i]);
                cols.append(PossibleSteps[i]);
            }
        }

        QThread* threads = new QThread[steps.size()];

        for (int i = 0; i < cols.size(); i++)
            this->children.push_back(nullptr);

        for (qsizetype i = 0; i < cols.size(); i++) {
            QObject::connect(&threads[i], &QThread::started, [this, &steps, generation, cellType, &cols, i](){
                AlphaBetaNode* child = new AlphaBetaNode(steps[i], generation + 1,
                                                         cellType == CellType::CELLTYPE_O ? CellType::CELLTYPE_X : CellType::CELLTYPE_O,
                                                         !this->maximize_it, cols[i], this->alpha, this->beta);
                this->children[i] = child;

                QThread::currentThread()->quit();
            });
            threads[i].start();
        }

        for (qsizetype i = 0; i < cols.size(); i++) {
            threads[i].wait();
        }

        for (qsizetype i = 0; i < steps.size(); i++)
            delete steps[i];
        delete[] threads;

        for (qsizetype i = 0; i < this->children.size(); i++) {
            if (maximize_it) {
                this->value = std::max(this->value, children[i]->value);
                this->alpha = std::max(this->alpha, this->value);
            } else {
                this->value = std::min(this->value, children[i]->value);
                this->beta = std::min(this->beta, this->value);
            }

            if (this->beta <= this->alpha) {
                break;
            }
        }
    }
    else {
        QPair<int, int> est = this->cells->getEstimation();
        value = (cellType == CELLTYPE_X) ? est.first - est.second : est.second - est.first;
    }
}

AlphaBetaNode::AlphaBetaNode(SamLogic* cells_, int generation, CellType cellType, bool maximize_it, int column, int alpha, int beta) {
    this->generation = generation;
    this->maximize_it = maximize_it;
    this->alpha = alpha;
    this->beta = beta;
    this->column = column;
    this->cells = new SamLogic(cells_);
    this->cellType = cellType;
    this->value = maximize_it ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();

    if (this->generation < 6 && !cells->CheckEndCondition()) {
        for (int i = 0; i < COLS; i++) {
            if (cells->CheckLegal(i)) {
                cells->SetCell(i, this->cellType);
                AlphaBetaNode* child = new AlphaBetaNode(cells, generation + 1,
                                                         cellType == CellType::CELLTYPE_O ? CellType::CELLTYPE_X : CellType::CELLTYPE_O,
                                                         !this->maximize_it, i, this->alpha, this->beta);
                children.push_back(child);
                cells->ClearCell(i);

                if (maximize_it) {
                    this->value = std::max(this->value, child->value);
                    this->alpha = std::max(this->alpha, this->value);
                } else {
                    this->value = std::min(this->value, child->value);
                    this->beta = std::min(this->beta, this->value);
                }

                if (this->beta <= this->alpha) {
                    break;
                }
            }
        }
    } else {
        QPair<int, int> est = this->cells->getEstimation();
        value = (cellType == CELLTYPE_X) ? est.first - est.second : est.second - est.first;
    }
}

// Удаляем родительский узел, который потом рекурсивно удалит остальные.
AlphaBetaTree::~AlphaBetaTree() {
    delete parent;
}

// Здесь происходит рекурсивное удаление узлов дерева.
AlphaBetaNode::~AlphaBetaNode() {
    for (qsizetype i = 0; i < children.size(); i++) {
        delete children[i];
    }
    delete cells;
}

// Рассчитываем все оценки дерева и получаем следующий ход.
int AlphaBetaTree::getNextMove() {
    int index_max = 0;
    for (qsizetype i = 0; i < parent->children.size(); i++) {
        if (parent->children[i]->value > parent->children[index_max]->value) {
            index_max = i;
        }
    }

    for (int i = 0; i < 10; i++) {
        int finalMove = rand() % parent->children.size();
        if (parent->children[index_max]->value - parent->children[finalMove]->value <= 10) {
            if (!(rand() % 3))
                index_max = finalMove;
            break;
        }
    }

    return parent->children[index_max]->column;
}
