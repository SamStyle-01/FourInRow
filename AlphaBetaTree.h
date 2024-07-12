#ifndef ALPHABETATREE_H
#define ALPHABETATREE_H

#include "pch.h"
#include "SamLogic.h"

extern int ROWS;        // Количество ячеек в ряду доски.
extern int COLS;        // Количество ячеек в столбце доски.

struct AlphaBetaNode {
    AlphaBetaNode(SamLogic* cells_, int generation, CellType cellType, bool maximize_it, int column, int alpha, int beta, QVector<int> PossibleSteps);
    AlphaBetaNode(SamLogic* cells_, int generation, CellType cellType, bool maximize_it, int column, int alpha, int beta);
    ~AlphaBetaNode();
    SamLogic* cells;
    int alpha, beta, value;                     // Значения Альфа, Бета и оценка текущего состояния доски.
    QVector<AlphaBetaNode*> children;           // Дочерние узлы относительно данного.
    CellType cellType;                          // Фигура игрока. Их 2 вида. Скажем, есть белые и есть чёрные.
    int generation;                             // Глубина узла дерева.
    int column;                                 // Колонка игровой доски, ход в которую узел просчитывает.

    bool maximize_it;                           // Параметр для Альфа-Бета отсечения. Мы смотрим, максимизируем ли мы сейчас Бета или минимизируем Альфа.
};

class AlphaBetaTree {
public:
    AlphaBetaTree(SamLogic* cells, CellType cellType, QVector<int> PossibleSteps);
    int getNextMove();
    ~AlphaBetaTree();
    AlphaBetaNode* parent;                      // Родительский узел дерева, откуда начинаем построение всех остальных узлов.
    QVector<int> PossibleSteps;
};

#endif
