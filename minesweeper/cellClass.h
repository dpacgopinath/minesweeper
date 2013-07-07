#ifndef CELLCLASS_H
#define CELLCLASS_H

#include <QPushButton>
#include <QMainWindow>
#include <QMouseEvent>

#define MAXSIZE -2

class cellClass : public QMainWindow
{
public:
    cellClass();
    QPushButton * button;
    void refreshCell();

    int value;
    bool flag;
    bool bomb;
    bool open;

};
#endif // CELLCLASS_H
