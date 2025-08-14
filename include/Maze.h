#ifndef MAZE_H
#define MAZE_H

#include <QPainter>

class Maze {
public:
    static const int ROWS = 15;
    static const int COLS = 20;
    Maze();
    void draw(QPainter &painter, int widgetWidth, int widgetHeight, int &cellSize, int &xOffset, int &yOffset) const;
    bool isWall(int row, int col) const;
private:
    int m_data[ROWS][COLS];
};

#endif // MAZE_H
