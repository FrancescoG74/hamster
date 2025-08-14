#ifndef HAMSTER_H
#define HAMSTER_H

#include <QPoint>
#include <QColor>
#include <QPainter>

class Hamster {
public:
    Hamster(int x = 100, int y = 100);
    void setPosition(int x, int y);
    QPoint position() const;
    void draw(QPainter &painter) const;
private:
    QPoint m_pos;
    QColor m_bodyColor;
    QColor m_headColor;
};

#endif // HAMSTER_H
