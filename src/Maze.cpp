#include "Maze.h"
#include <vector>
#include <stack>
#include <random>
#include <ctime>

Maze::Maze() {
    // Maze generation: DFS backtracking
    for (int r = 0; r < ROWS; ++r)
        for (int c = 0; c < COLS; ++c)
            m_data[r][c] = 1;

    std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
    std::vector<std::pair<int, int>> directions = {{0,2},{0,-2},{2,0},{-2,0}};
    std::stack<std::pair<int,int>> stack;
    int start_r = 1, start_c = 0; // ingresso
    m_data[start_r][start_c] = 0;
    stack.push({start_r, start_c});

    while (!stack.empty()) {
        auto [r, c] = stack.top();
        stack.pop();
        std::vector<std::pair<int,int>> neighbors;
        for (auto [dr, dc] : directions) {
            int nr = r + dr, nc = c + dc;
            if (nr > 0 && nr < ROWS-1 && nc > 0 && nc < COLS-1 && m_data[nr][nc] == 1) {
                neighbors.push_back({nr, nc});
            }
        }
        std::shuffle(neighbors.begin(), neighbors.end(), rng);
        for (auto [nr, nc] : neighbors) {
            if (m_data[nr][nc] == 1) {
                m_data[nr][nc] = 0;
                m_data[r + (nr-r)/2][c + (nc-c)/2] = 0;
                stack.push({nr, nc});
            }
        }
    }
    // ingresso
    m_data[1][0] = 0;
    // uscita
    m_data[ROWS-2][COLS-1] = 0;
}

void Maze::draw(QPainter &painter, int widgetWidth, int widgetHeight, int &cellSize, int &xOffset, int &yOffset) const {
    int cell_w = widgetWidth / COLS;
    int cell_h = widgetHeight / ROWS;
    cellSize = qMin(cell_w, cell_h);
    xOffset = (widgetWidth - (cellSize * COLS)) / 2;
    yOffset = (widgetHeight - (cellSize * ROWS)) / 2;
    painter.setPen(Qt::NoPen);
    // Disegna muri
    painter.setBrush(Qt::darkBlue);
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            if (m_data[row][col] == 1) {
                painter.drawRect(xOffset + col * cellSize, yOffset + row * cellSize, cellSize, cellSize);
            }
        }
    }
    // Evidenzia ingresso (colonna 0, riga 1)
    painter.setBrush(Qt::green);
    painter.drawRect(xOffset + 0 * cellSize, yOffset + 1 * cellSize, cellSize, cellSize);
    // Evidenzia uscita (colonna COLS-1, riga ROWS-2)
    painter.setBrush(Qt::red);
    painter.drawRect(xOffset + (COLS-1) * cellSize, yOffset + (ROWS-2) * cellSize, cellSize, cellSize);
}

bool Maze::isWall(int row, int col) const {
    if (row < 0 || row >= ROWS || col < 0 || col >= COLS) return true;
    return m_data[row][col] == 1;
}
