#include "dialog.h"
#include "ui_dialog.h"

#include <iostream>
#include <QApplication>
#include <QPushButton>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);

    shuffle_button = new QPushButton("shuffle", this);
    shuffle_button->setGeometry(0,0,50,20);
    shuffle_button->setAutoDefault(false);
    connect(shuffle_button, SIGNAL (clicked()), this, SLOT (shuffle()));

    sort_button = new QPushButton("selection sort", this);
    sort_button->setGeometry(50,0,50,20);
    sort_button->setAutoDefault(false);
    connect(sort_button, SIGNAL (clicked()), this, SLOT (selection_sort()));

    create_table();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::create_table()
{
    QBrush blackbrush(Qt::black);
    QPen blackpen(Qt::black);

    scene->clear();
    v.clear();
    vp.clear();

    srand(time(NULL));
    for (int i = 0; i < VECTOR_SIZE; ++i)
    {
        int w = (this->width()-50)/VECTOR_SIZE;
        int h = rand()%280+1;
        int val = h;

        int xpos = i*w;
        int ypos = (this->height()) - h;

        QRect temp(xpos,ypos,w,h);
        v.push_back(std::tuple<QRect,int>(temp,val));
        vp.push_back(scene->addRect(std::get<0>(v[i]),blackpen, blackbrush));
    }
}

void Dialog::update_scene()
{
    QBrush blackbrush(Qt::black);
    QPen blackpen(Qt::black);

    scene->clear();
    for(int i = 0; i < VECTOR_SIZE;++i)
    {
        scene->addRect(std::get<0>(v[i]), blackpen, blackbrush);
    }
    ui->graphicsView->setScene(scene);
}

/*
 * slots
 */
void Dialog::shuffle()
{
    create_table();
}

void Dialog::selection_sort()
{
    std::cout << "sorting..." << std::endl;

    for(int i = 0; i < VECTOR_SIZE; ++i)
    {
        scene->clear();
        int min = i;
        for(int j = i+1; j < VECTOR_SIZE; ++j){
            if(std::get<1>(v[min])>std::get<1>(v[j])){
                min = j;
            }
        }
        std::tuple<QRect,int> previous = v[i];
        QGraphicsRectItem* handlep = vp[i];

        v[i] = v[min];
        vp[i] = vp[min];

        v[min] = previous;
        vp[min] = handlep;
        update_scene();
    }
    std::cout << "...done" << std::endl;

//    for(int i = 0; i < VECTOR_SIZE; ++i){
//        std::cout << std::get<0>(v[i]).height()<< " ";
//    }
//    std::cout << std::endl;
}

