#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QList>
#include <QGraphicsScene>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    const int VECTOR_SIZE = 50;
    Ui::Dialog *ui;
    QGraphicsScene* scene;
    std::vector<std::tuple<QRect,int>> v;
    std::vector<QGraphicsRectItem*> vp;
    QList<QGraphicsItem*> bars;
    QPushButton* shuffle_button;
    QPushButton* sort_button;

    void create_table();
    void update_scene();

private slots:
    void shuffle();
    void selection_sort();
};
#endif // DIALOG_H
