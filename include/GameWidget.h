#include <QMediaPlayer>
#include <QAudioOutput>
#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "Hamster.h"
#include "Maze.h"

class GameWidget : public QWidget {
//    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
private slots:
    void gameLoop();
private:
    QTimer m_timer;
    Hamster m_hamster;
    Maze m_maze;
    int m_lastCellSize = 48;
    int m_lastXOffset = 0;
    int m_lastYOffset = 0;
    QMediaPlayer *m_player = nullptr;
    QAudioOutput *m_audioOutput = nullptr;
};

#endif // GAMEWIDGET_H
