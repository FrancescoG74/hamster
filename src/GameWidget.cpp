#include "../include/GameWidget.h"
#include <QPainter>
#include <QKeyEvent>
#include <QApplication>
#include <QMessageBox>


GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent), m_hamster(0, 0)
{
    // La posizione iniziale verrà aggiornata dopo il primo paintEvent
    setFocusPolicy(Qt::StrongFocus);
    m_timer.setInterval(16); // ~60 FPS
    connect(&m_timer, &QTimer::timeout, this, &GameWidget::gameLoop);
    m_timer.start();

    // Posiziona l'hamster centrato nella cella di ingresso (colonna 0, riga 1)
    int cell_size = 48; // fallback iniziale
    int x_offset = 0;
    int y_offset = 0;
    int hamster_w = 40;
    int hamster_h = 40;
    int start_x = x_offset + 0 * cell_size + (cell_size - hamster_w) / 2;
    int start_y = y_offset + 1 * cell_size + (cell_size - hamster_h) / 2;
    m_hamster.setPosition(start_x, start_y);

    // Musica di sottofondo (disabilitata temporaneamente)
    /*
    m_player = new QMediaPlayer(this);
    m_audioOutput = new QAudioOutput(this);
    m_player->setAudioOutput(m_audioOutput);
    m_player->setSource(QUrl::fromLocalFile("music.mp3"));
    m_audioOutput->setVolume(50); // volume 0-100
    m_player->setLoops(QMediaPlayer::Infinite);
    m_player->play();
    */
}


void GameWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    // Calcola la dimensione delle celle in base alla finestra
    int cell_size, x_offset, y_offset;
    m_maze.draw(painter, width(), height(), cell_size, x_offset, y_offset);
    m_lastCellSize = cell_size;
    m_lastXOffset = x_offset;
    m_lastYOffset = y_offset;
    // Disegna hamster sopra il labirinto
    m_hamster.draw(painter);
}

void GameWidget::keyPressEvent(QKeyEvent *event)
{
    int dx = 0, dy = 0;
    switch (event->key()) {
    case Qt::Key_Left:  dx = -10; break;
    case Qt::Key_Right: dx = 10; break;
    case Qt::Key_Up:    dy = -10; break;
    case Qt::Key_Down:  dy = 10; break;
    case Qt::Key_Escape:
        QApplication::quit();
        return;
    case Qt::Key_Q:
        if (!(event->modifiers() & Qt::ControlModifier)) { // plain 'q'
            QApplication::quit();
            return;
        }
        break;
    default:
        QWidget::keyPressEvent(event);
        return;
    }
    QPoint pos = m_hamster.position();
    int cell_size = m_lastCellSize;
    int x_offset = m_lastXOffset;
    int y_offset = m_lastYOffset;
    int new_x = pos.x() + dx;
    int new_y = pos.y() + dy;
    // Dimensioni hamster
    const int hamster_w = 40;
    const int hamster_h = 40;
    // Limiti finestra
    int max_x = width() - hamster_w;
    int max_y = height() - hamster_h;
    if (new_x < 0) new_x = 0;
    if (new_y < 0) new_y = 0;
    if (new_x > max_x) new_x = max_x;
    if (new_y > max_y) new_y = max_y;

    // Collisione con muri del labirinto
    // Prendiamo il centro dell'hamster per il controllo
    int center_x = new_x + hamster_w / 2;
    int center_y = new_y + hamster_h / 2;
    int maze_col = (center_x - x_offset) / cell_size;
    int maze_row = (center_y - y_offset) / cell_size;
    bool can_move = !m_maze.isWall(maze_row, maze_col);
    if (can_move) {
        m_hamster.setPosition(new_x, new_y);
        update();
        // Logica di vittoria: uscita in (Maze::ROWS-2, Maze::COLS-1)
        if (maze_row == Maze::ROWS-2 && maze_col == Maze::COLS-1) {
            QMessageBox::information(this, "Vittoria!", "Hai raggiunto l'uscita!");
            // Ricrea il labirinto e riposiziona l'hamster all'ingresso
            m_maze = Maze();
            // Calcola posizione di partenza come in costruttore
            int cell_size = m_lastCellSize;
            int x_offset = m_lastXOffset;
            int y_offset = m_lastYOffset;
            int hamster_w = 40;
            int hamster_h = 40;
            int start_x = x_offset + 0 * cell_size + (cell_size - hamster_w) / 2;
            int start_y = y_offset + 1 * cell_size + (cell_size - hamster_h) / 2;
            m_hamster.setPosition(start_x, start_y);
            update();
        }
    }
}

void GameWidget::gameLoop()
{
    // Placeholder for game logic (e.g., collision, animation)
    update();
}
