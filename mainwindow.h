#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QColor>
#include <QRandomGenerator>
#include <iostream>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsSimpleTextItem>
#include <QHash>
#include<QGeoPath>
#include<QValidator>
#include <QGraphicsPixmapItem>
#include <QWheelEvent>
#include <QKeyEvent>
#include<QHashIterator>
class MainWindow;
namespace Ui {
class MainWindow;
}
//class MainWindow;
/*void change(MainWindow tis,int i)
{
    if(tis.radar<500 && tis.radar>50)
    {
        if(i<0)
        {
            tis.radar*=0.95;
            tis.updatepaint();
        }
        else
        {
            tis.radar*=1.05;
            tis.updatepaint();
        }
    }
}*/

class View : public QGraphicsView
{
    Q_OBJECT
public:
    explicit View(QWidget *parent = 0) :
        QGraphicsView(parent)
    {
        setDragMode(QGraphicsView::ScrollHandDrag);
        //    QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem(QPixmap(":/images/my_image.png"));
        //    pixmapItem->setTransformationMode(Qt::SmoothTransformation);
    }
signals:
    void valueChanged(int i);
public Q_SLOTS:
    void isasignal(int i)
    {
        emit valueChanged(i);
    }
    void wheelEvent(QWheelEvent *event)
    {
        if(event->delta() > 0)
            isasignal(1);
        else
            isasignal(-1);
    }

    void keyPressEvent(QKeyEvent *event)
    {
        if(event->key() == Qt::Key_Left)
        {
            setTransformationAnchor(QGraphicsView::AnchorViewCenter);
            rotate(-.5);
        }
        else if(event->key() == Qt::Key_Right)
            rotate(.5);
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QPixmap *it;
    QGraphicsPixmapItem *item1;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_lineEdit_editingFinished();

    void on_lineEdit_3_editingFinished();

    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

    void on_pushButton_clicked();

    void on_lineEdit_4_editingFinished();

    void on_lineEdit_5_editingFinished();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    View *v;
    QGraphicsEllipseItem *ellipse , *impel;
    QGraphicsRectItem *rectangle;
    QGraphicsTextItem *texts;
    QGraphicsLineItem *lin1,*lin2,*impl;
    QGraphicsSimpleTextItem *ang,*rscale;
    QDoubleValidator *validator;
    QGraphicsView *vv;
    double radar=500;
    double srada=radar;

    struct obj
    {
        QGeoPath *path =new QGeoPath();
        QPixmap *its  = new QPixmap(":/new/Icons/Icon");
        QPixmap it = its->scaled(30,30);
        QGraphicsPixmapItem *item1;
    };
    QHash<int,obj> hash;
public slots:
    void updatepaint(int i);

    /*protected Q_SLOTS:
  void wheelEvent(QWheelEvent *event)
  {
    if(event->delta() > 0)
    {
        QHashIterator<int,obj> i(hash);
          while (i.hasNext()) {
              i.next();
              hash[i.key()].it = hash[i.key()].it.scaled(hash[i.key()].it.width()*0.95,hash[i.key()].it.height()*0.95);
          }
    }
    else
    {
        QHashIterator<int,obj> i(hash);
          while (i.hasNext()) {
              i.next();
              hash[i.key()].it = hash[i.key()].it.scaled(hash[i.key()].it.width()*1.05,hash[i.key()].it.height()*1.05);
          }
    }
  }*/
};

#endif // MAINWINDOW_H
