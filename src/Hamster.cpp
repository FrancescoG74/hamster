#include "../include/Hamster.h"

Hamster::Hamster(int x, int y)
    : m_pos(x, y), m_bodyColor(200, 150, 80), m_headColor(220, 180, 100)
{
}

void Hamster::setPosition(int x, int y)
{
    m_pos = QPoint(x, y);
}

QPoint Hamster::position() const
{
    return m_pos;
}

void Hamster::draw(QPainter &painter) const
{
    int m_x = m_pos.x();
    int m_y = m_pos.y();
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(m_bodyColor); // brown body
    painter.drawEllipse(m_x, m_y + 10, 40, 30); // body

    painter.setBrush(m_headColor);
    painter.drawEllipse(m_x + 5, m_y, 30, 30); // head

    painter.setBrush(m_bodyColor);
    painter.drawEllipse(m_x + 5, m_y - 5, 10, 10); // left ear
    painter.drawEllipse(m_x + 25, m_y - 5, 10, 10); // right ear

    painter.setBrush(Qt::white);
    painter.drawEllipse(m_x + 13, m_y + 10, 6, 6); // left eye white
    painter.drawEllipse(m_x + 21, m_y + 10, 6, 6); // right eye white
    painter.setBrush(Qt::black);
    painter.drawEllipse(m_x + 15, m_y + 13, 2, 2); // left pupil
    painter.drawEllipse(m_x + 23, m_y + 13, 2, 2); // right pupil

    painter.setBrush(Qt::black);
    painter.drawEllipse(m_x + 19, m_y + 20, 4, 3); // nose

    painter.setPen(QPen(Qt::black, 1));
    painter.drawLine(m_x + 10, m_y + 22, m_x, m_y + 20); // left whisker 1
    painter.drawLine(m_x + 10, m_y + 25, m_x, m_y + 28); // left whisker 2
    painter.drawLine(m_x + 30, m_y + 22, m_x + 40, m_y + 20); // right whisker 1
    painter.drawLine(m_x + 30, m_y + 25, m_x + 40, m_y + 28); // right whisker 2
}
