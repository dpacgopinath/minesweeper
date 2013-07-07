#include "cellClass.h"
#include "stdio.h"

#include <QPushButton>
#include <QMessageBox>

cellClass::cellClass()
{
    button=new QPushButton;
    value=0;
    flag=false;
    bomb=false;
    open=false;
    button->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
}

void cellClass::refreshCell()
{
//    QMessageBox::information(this,"a","in refresh cell");
    button->setIcon(QIcon());
    button->setFlat(false);
    button->setText("");
    value=0;
    flag=false;
    bomb=false;
    open=false;
    button->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
}
