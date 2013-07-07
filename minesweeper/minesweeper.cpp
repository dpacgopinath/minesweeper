#include "minesweeper.h"
#include "ui_minesweeper.h"
#include "cellClass.h"

#include <QPushButton>
#include <QMessageBox>
#include <QMouseEvent>

#define BOMB 0
#define FLAG 1


minesweeper::minesweeper(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::minesweeper)
{    
    ui->setupUi(this);
    size= 16;
    bombNumber=40;
    flagNumber=0;
    firstClick=true;
    runTimer=false;

    QTimer* timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateTime()));
    timer->start(1000);

    ui->gridLayout->setSpacing(0);
    ui->lcdNumberFlag->display(bombNumber-flagNumber);

    for(int a=0;a<30;a++)
        for(int b=0;b<30;b++)
            cell[a][b]= new cellClass;

    for(int a=0;a<size;a++)
        for(int b=0;b<size;b++)
        {
            ui->gridLayout->addWidget(cell[a][b]->button,a,b);
            cell[a][b]->button->setObjectName(QString::number(a)+'\t'+QString::number(b));
            cell[a][b]->button->installEventFilter(this);
        }

    generateField();
}

int minesweeper::countNumber(int x,int y, int index)
{
    int count=0;

    if(cell[x][y]->bomb && index==BOMB)
    {
        count=-1;
        return count;
    }

    for(int a=-1;a<2;a++)
        for(int b=-1;b<2;b++)
            if(x+a>=0 && x+a<size && y+b>=0 && y+b<size)
            {
                if(index==BOMB)
                {if(cell[x+a][y+b]->value==-1)
                    count++;}
                else if(index==FLAG)
                {if(cell[x+a][y+b]->flag)
                    count++;}
            }

    return count;
}

void minesweeper::generateField()
{
    for(int a=0;a<bombNumber;a++)
    {
        int xrand=rand()%size;
        int yrand=rand()%size;

        if(cell[xrand][yrand]->value==-1)
        {    a--;
            continue;
        }
        cell[xrand][yrand]->value=-1;
        cell[xrand][yrand]->bomb=true;
    }

    for(int a=0;a<size;a++)
        for(int b=0;b<size;b++)
            cell[a][b]->value=countNumber(a,b,BOMB);
}

void minesweeper::newGame()
{
    flagNumber=0;
    firstClick= true;
    runTimer=false;
    ui->lcdNumberFlag->display(bombNumber-flagNumber);
    ui->lcdNumberTime->display(0);

    for(int a=0;a<size;a++)
        for(int b=0;b<size;b++)
        {
            cell[a][b]->refreshCell();
//            cell[a][b]->button->setIcon(image);
//            cell[a][b]->button->setIconSize(cell[a][b]->button->size());

        }


    for(int a=0;a<size;a++)
    {
        for(int b=0;b<size;b++)
        {

            ui->gridLayout->addWidget(cell[a][b]->button,a,b);
            cell[a][b]->button->setObjectName(QString::number(a)+'\t'+QString::number(b));
            cell[a][b]->button->installEventFilter(this);

        }
    }
    generateField();
}

void minesweeper::whenLClicked(int a, int b)
{
    if(firstClick)
    {
        firstClick=false;
        runTimer=true;
    }

    if(!cell[a][b]->flag && !cell[a][b]->open)
    {
        if(cell[a][b]->value==-1)
        {
            QPixmap pixmap("images/bomb.png");
            QIcon image(pixmap);
            cell[a][b]->button->setIcon(image);
            cell[a][b]->button->setIconSize(cell[a][b]->button->size());
            //timer->stop();
            runTimer=false;
            for(int ax=0;ax<size;ax++)
            {
                for(int by=0;by<size;by++)
                {
                    if(cell[ax][by]->value==-1)
                    {
                        cell[ax][by]->button->setIcon(image);
                        cell[ax][by]->button->setIconSize(cell[ax][by]->button->size());
                        //cell[ax][by]->button->setPalette();;

                    }
                }
            }
            QMessageBox::information(this,"Fail!","You have stepped on a mine. You're dead meat!");

            newGame();
            return;
        }

        QString string = QString::number(cell[a][b]->value);
        if(cell[a][b]->value==0||cell[a][b]->value==-1)
            string ="";
        cell[a][b]->button->setText(string);
        cell[a][b]->button->setFlat(true);
        cell[a][b]->open=true;


        if(cell[a][b]->value==0)
            clearNeighbours(a,b);



    }
}

void minesweeper::whenRClicked(int a, int b)
{
    if(!cell[a][b]->flag&&!cell[a][b]->open)
    {
        flagNumber++;        
        ui->lcdNumberFlag->display(bombNumber-flagNumber);
        QPixmap pixmap("images/flag.png");
        QIcon image(pixmap);
        cell[a][b]->button->setIcon(image);
        cell[a][b]->button->setIconSize(cell[a][b]->button->size());
        cell[a][b]->flag=true;
    }
    else if(!cell[a][b]->open)
    {
        flagNumber--;
        ui->lcdNumberFlag->display(bombNumber-flagNumber);
        cell[a][b]->button->setIcon(QIcon());
        cell[a][b]->flag=false;
    }
}

void minesweeper::whenLRClicked(int x, int y)
{
    int flagCount=countNumber(x,y,FLAG);
    if(flagCount==cell[x][y]->value)
        for(int a=-1;a<2;a++)
            for(int b=-1;b<2;b++)
                if(x+a>=0 && x+a<size && y+b>=0 && y+b<size)
                    whenLClicked(x+a,y+b);



}

void minesweeper::clearNeighbours(int x, int y)
{
    for(int a=-1;a<2;a++)
        for(int b=-1;b<2;b++)
            if(x+a>=0 && x+a<size && y+b>=0 && y+b<size)
                whenLClicked(x+a,y+b);
}

bool minesweeper::checkFinish()
{
    if(flagNumber==bombNumber)
    {
        for(int a=0;a<size;a++)
            for(int b=0;b<size;b++)
                if(cell[a][b]->bomb&& !cell[a][b]->flag)
                    return false;
        return true;
    }
    return false;

}

bool minesweeper::eventFilter(QObject * object, QEvent*event)
{
    if(event->type()==QEvent::MouseButtonPress)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*> (event);
        QString index=object->objectName();
        QStringList indexList= index.split('\t');
        int x = indexList[0].toInt();
        int y = indexList[1].toInt();

        if(mouseEvent->button()==Qt::LeftButton)
            whenLClicked(x,y);
        else if(mouseEvent->button()==Qt::RightButton)
            whenRClicked(x,y);
        else
            whenLRClicked(x,y);
        if(checkFinish())
        {
            //timer->blockSignals(true);
            //timer->stop();
            runTimer=false;
            QMessageBox::information(this,"Success!","You have diffused all the mines in "+QString::number(ui->lcdNumberTime->value())+"s. Well done!",0,0);
            newGame();
        }
        return true;

    }
    return false;
}

void minesweeper::updateTime()
{
    if(runTimer)
    ui->lcdNumberTime->display(ui->lcdNumberTime->value()+1);
}

void minesweeper::slotHelp()
{
    QMessageBox::information(this,"Help","What is minesweeper?<br>How to play"
                             "<br>For more information click <a href = \"http://en.wikipedia.org/wiki/Self-help\">here</a>",1,0);
}


minesweeper::~minesweeper()
{
    delete ui;
}
