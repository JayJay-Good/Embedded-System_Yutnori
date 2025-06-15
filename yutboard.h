#ifndef YUTBOARD_H
#define YUTBOARD_H

#include <QWidget>
#include <QPoint>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QKeyEvent>

class YutGame;

class yutboard : public QWidget
{
    Q_OBJECT

public:
    explicit yutboard(QWidget *parent = nullptr);
    void setGame(YutGame *game);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    QPoint getScreenPos(int locId);
    YutGame *m_game;
    QPoint boardPoints[31]; // 충분히 크게 잡아둠
    bool m_started = false;
    QRect m_startButton;

};

#endif // YUTBOARD_H
