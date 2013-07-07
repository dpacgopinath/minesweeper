#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include "cellClass.h"


namespace Ui {
    class minesweeper;
}


class minesweeper : public QMainWindow
{
    Q_OBJECT

public:
    explicit minesweeper(QWidget *parent = 0);
    cellClass *cell[30][30];
    int size;
    int bombNumber;
    int flagNumber;
    bool firstClick;
    QTimer* timer;
    bool runTimer;

    bool eventFilter(QObject *, QEvent * );
    void generateField();
    void whenLClicked(int, int);
    void whenRClicked(int, int);
    void whenLRClicked(int, int);
    void clearNeighbours(int, int);
    bool checkFinish();

     ~minesweeper();


public slots:
    void slotHelp();
    void newGame();
    void updateTime();

private:
    int countNumber(int, int, int);
    Ui::minesweeper *ui;
};


#endif // MINESWEEPER_H
