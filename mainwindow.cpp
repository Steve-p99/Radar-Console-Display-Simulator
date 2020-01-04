#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mywidget.h"
#include <math.h>
#include <iostream>
#include <QGeoCoordinate>
#include <QGeoPath>
#include <QDoubleValidator>

int c=0,d=0,h=260;
QLabel *nz=NULL,*na=NULL,*nz1=NULL,*na1=NULL;
#define pi 3.14159265358979323846

double ox=0,oy=0;
QGeoCoordinate *qown=new QGeoCoordinate();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: SeaShell;");
    v = new View(this);
    connect(v, SIGNAL(valueChanged(int)),this, SLOT(updatepaint(int)));
    ui->pushButton->hide();
    ui->horizontalSpacer_8->changeSize(0,0);
    ui->openGLWidget->setGeometry(100, 180, 600, 390);
    ui->openGLWidget->setStyleSheet("background-color: transparent;");
    ui->openGLWidget->hide();
    v->hide();
    scene = new QGraphicsScene(this);

    QString ss = QString::number(radar);
    ui->lineEdit_5->setText(ss);
    impl=NULL;
    impel=NULL;

    QBrush blackBrush(Qt::black);
    QBrush blueBrush(Qt::blue);
    QPen outPen(Qt::green);
    outPen.setWidth(1.3);
    QPen outlinePen(Qt::white);
    outlinePen.setWidth(2);
    QBrush yellBrush(Qt::darkGray);
    QBrush yBrush(Qt::yellow);
    QPen oPen(Qt::green);
    oPen.setWidth(.5);
    v->setBackgroundBrush(yellBrush);
    ellipse = scene->addEllipse(20,20 , 480, 480, outlinePen, blackBrush);
    lin1 = scene->addLine(260,20,260,500,outlinePen);
    lin2 = scene->addLine(20,260,500,260,outlinePen);

    ss = QString::number(radar*0.539957);
    rscale = scene->addSimpleText("Range Scale is : "+ss+"nmi");
    rscale->setBrush(yBrush);
    rscale->setPos(0,2*h - 10);
    //QPen ens(Qt::red,1);
   //6 rscale->setPen(ens);

    ang = scene->addSimpleText("N");
    ang->setBrush(yBrush);
    ang->setPos(h-5,0);
    QPen en(Qt::red,1.5);
    ang->setPen(en);
    for(int i=-90;i<269;i=i+3)
    {
        if(i%30==0 && i%90!=0)
        {
            lin1 = scene->addLine(((h-20)*cos((pi*i)/180))+h,((h-20)*sin((pi*i)/180))+h,h,h,oPen);
            lin1->setOpacity(0.5);
        }
        if(i%15==0 && i!=-90)
        {
            lin1 = scene->addLine(((h-20)*cos((pi*i)/180))+h,((h-20)*sin((pi*i)/180))+h,((h-35)*cos((pi*i)/180))+h,((h-35)*sin((pi*i)/180))+h,outlinePen);
            QString s = QString::number(i+90);
            ang = scene->addSimpleText(s);
            ang->setBrush(yBrush);
            ang->setPos(((h-5)*cos((pi*i)/180))+h-15,((h-5)*sin((pi*i)/180))+h-10);
            ang->setPen(outPen);
        }
        else{
            QPen penHLines(Qt::white);
            lin1 = scene->addLine(((h-20)*cos((pi*i)/180))+h,((h-20)*sin((pi*i)/180))+h,((h-27)*cos((pi*i)/180))+h,((h-27)*sin((pi*i)/180))+h,penHLines);
        }
    }
    for(int i=1;i<=4;i++)
    {
        ellipse = scene->addEllipse(h-((h-20)*i)/5,h-((h-20)*i)/5,((h-20)*i*2)/5,((h-20)*i*2)/5,oPen);
        ellipse->setOpacity(0.5);
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_lineEdit_editingFinished()
{
    if(nz)
        nz->hide();
    QString arg=ui->lineEdit->text();
    double a = arg.split(" ")[0].toDouble();
    if(!(a>=-90 && a<=90))
    {
        QLabel *n=new QLabel(this);
        // n->setAlignment(Qt::AlignBottom | Qt::AlignRight);
        n->setStyleSheet("QLabel { color : red; }");
        n->move(100,140);
        n->setText("Enter valid Latitude");
        n->adjustSize();
        n->show();
        nz=n;
    }
    else
    {
        qown->setLatitude(a);
    }
}
void MainWindow::on_lineEdit_3_editingFinished()
{
    if(nz)
        nz->hide();
    QString arg=ui->lineEdit_3->text();
    double a = arg.split(" ")[0].toDouble();
    if(!(a>=-180 && a<=180))
    {
        QLabel *n=new QLabel(this);
        // n->setAlignment(Qt::AlignBottom | Qt::AlignRight);
        n->setStyleSheet("QLabel { color : red; }");
        n->move(100,140);
        n->setText("Enter valid Longitude ");
        n->adjustSize();
        n->show();
        nz=n;
    }
    else
    {
        qown->setLongitude(a);
    }
}
void MainWindow::on_toolButton_clicked()
{
   // ui->graphicsView->setGeometry(800,0,550,550);

    if(!(ui->lineEdit_5->text().isEmpty())&&!(ui->lineEdit->text().isEmpty())&&!(ui->lineEdit_3->text().isEmpty()))
    {
        //ui->openGLWidget->setStyleSheet("background-color:black;");
        this->setWindowState(Qt::WindowMaximized);
        //        this->setFixedHeight(870);
        //        this->setFixedWidth(1400);
        c++;
        QSize size = this->size();
        int hei = 870;
        int win = 800;
        int gw=win-200;
        int gh=hei-500;
        //    ui->openGLWidget->setStyleSheet("background-color:black;");
        if(c==1)
        {
            QString ss = QString::number(srada*0.539957);
            rscale->setText("Range Scale is : "+ss+"nmi");
      v->setGeometry(800,20,550,550);
            v->setScene(scene);
              v->setAlignment(Qt::AlignCenter);
            ui->openGLWidget->show();
            v->show();
            ui->label->hide();
            ui->label_4->hide();
            ui->lineEdit->hide();
            ui->lineEdit_3->hide();
            ui->horizontalSpacer_3->changeSize(0,0);
            ui->horizontalSpacer_4->changeSize(0,0);
            ui->horizontalSpacer_13->changeSize(100,10);
            ui->horizontalSpacer_12->changeSize(100,10);
            QPainter painter(ui->openGLWidget);
            QPen penHines(Qt::white);
            penHines.setWidth(1);
            painter.setPen(penHines);
            painter.drawLine((win-200)/2,0,(win-200)/2,((hei-500)));
            painter.drawLine(0,(hei-500)/2,(win-200),((hei-500))/2);
            painter.drawEllipse((gw/2)-(gh/2)+15,15,gh-30,gh-30);
        }
        if(c==2){
            ui->pushButton->show();
            ui->horizontalSpacer_8->changeSize(300,20);
            ui->label_6->setText("Track ID : ");
            ui->lineEdit_5->clear();
            //  painter.setBrush(background());
            QPainter painter(ui->openGLWidget);
            QPen penHines(Qt::white);
            penHines.setWidth(1);
            painter.setPen(penHines);
            painter.drawLine((win-200)/2,0,(win-200)/2,((hei-500)+20));
            painter.drawLine(0,(hei-500)/2,(win-200),((hei-500))/2);
            painter.drawEllipse((gw/2)-(gh/2)+15,15,gh-30,gh-30);

            //painter.drawEllipse((gw/2)-(gh/2),0,gh,gh);
            QLabel *n=new QLabel(ui->openGLWidget);
            // n->setAlignment(Qt::AlignBottom | Qt::AlignRight);
            n->setStyleSheet("QLabel { color : yellow; }");
            n->move((gw/2)-15,-3);
            n->setText("N");
            n->show();
            for(int i=-90;i<269;i=i+3)
            {
                int cx,cy;
                cx=(((gh/2)-2)*cos((pi*i)/180))+(gw/2);
                cy=(((gh/2)-2)*sin((pi*i)/180))+(gh/2);
                if(i%15==0 && i!=-90)
                {
                    QPen penHLines(Qt::white);
                    penHLines.setWidth(2);
                    painter.setPen(penHLines);
                    painter.drawLine((((gh/2)-15)*cos((pi*i)/180))+(gw/2),(((gh/2)-15)*sin((pi*i)/180))+(gh/2),(((gh/2)-28)*cos((pi*i)/180))+(gw/2),(((gh/2)-28)*sin((pi*i)/180))+(gh/2));
                    QLabel *n1=new QLabel(ui->openGLWidget);
                    // n->setAlignment(Qt::AlignBottom | Qt::AlignRight);
                    n1->setStyleSheet("QLabel { color : cyan; }");
                    n1->move(cx-15,cy-10);
                    QString s = QString::number(i+90);
                    n1->setText(s);
                    if(i+90!=15)
                        n1->show();
                }
                else{
                    QPen penHLines(Qt::white);
                    painter.setPen(penHLines);
                    painter.drawLine((((gh/2)-15)*cos((pi*i)/180))+(gw/2),(((gh/2)-15)*sin((pi*i)/180))+(gh/2),(((gh/2)-24)*cos((pi*i)/180))+(gw/2),(((gh/2)-24)*sin((pi*i)/180))+(gh/2));
                }
            }
            for(int i=0;i<=5;i++)
            {
                int cx,cy;
                cy=(gh/2)-(i*((gh/10)-3));
                cx=gw/2;
                QLabel *n1=new QLabel(ui->openGLWidget);
                // n->setAlignment(Qt::AlignBottom | Qt::AlignRight);
                n1->setStyleSheet("QLabel { color : yellow; }");
                n1->move(cx,cy-11);
                QString s = QString::number(i*radar/5);
                n1->setText("-"+s+"km");
                n1->show();
            }
            ui->toolButton->hide();
            ui->horizontalSpacer_7->changeSize(85,0);
        }
    }
}
void MainWindow::on_toolButton_2_clicked()
{
}
void MainWindow::on_pushButton_clicked()
{
    QPainter painter(ui->openGLWidget);
    //    QSize size = this->size();
    int hei = 870;
    int win = 800;
    int gw=win-200;
    int gh=hei-500;
    if(nz)
    {
        nz->hide();
    }
    if(na)
    {
        na->hide();
    }
    if(nz1||na1)
    {
        nz1->hide();
        na1->hide();
    }
    if(!(ui->lineEdit_4->text().isEmpty()) && !(ui->lineEdit_2->text().isEmpty()) && c>=2)
    {
        int id = ui->lineEdit_5->text().toInt();
        if(hash.contains(id))
        {
            int i = hash[id].path->size();
            QGeoCoordinate *qold = new QGeoCoordinate(hash[id].path->coordinateAt(i-1));
            QString arg1=ui->lineEdit_4->text();
            QString arg2=ui->lineEdit_2->text();
            double a1 = arg1.split(" ")[0].toDouble();
            double a2 = arg2.split(" ")[0].toDouble();
            QGeoCoordinate *qcord = new QGeoCoordinate(a1,a2);
            double ndist = qown->distanceTo(*qcord);
            if(ndist/1000<=radar)
            {
                if(ndist/1000<=srada)
                {
                    double dist=qold->distanceTo(*qcord);
                    QLabel *n2=new QLabel(this);
                    n2->setStyleSheet("QLabel { color : red; }");
                    n2->move(100,140);
                    QString s = QString::number(dist/1000);
                    n2->setText("The Object has travelled "+s+"km");
                    n2->adjustSize();
                    n2->show();
                    nz1=n2;
                    QLabel *n3=new QLabel(this);
                    n3->setStyleSheet("QLabel { color : red; }");
                    n3->move(400,140);
                    double degs = qold->azimuthTo(*qcord);
                    s = QString::number(degs);
                    n3->setText("The Travelling Direction is "+s+" Degrees");
                    n3->adjustSize();
                    n3->show();
                    na1=n3;
                    double cx1 = (gw/2)+((gh-30)*((a2 - qown->longitude())*111.320*cos((a1*pi)/180))/(2*radar));
                    double cy1 = (gh/2)-((gh-30)*(110.574*(a1 - qown->latitude()))/(2*radar));
                    double cx2 = (gw/2)+((gh-30)*((qold->longitude() - qown->longitude())*111.320*cos((a1*pi)/180))/(2*radar));
                    double cy2 = (gh/2)-((gh-30)*(110.574*(qold->latitude() - qown->latitude()))/(2*radar));

                    QPen penHLines(Qt::white, 1, Qt::DotLine);
                    painter.setPen(penHLines);
                    painter.drawLine(cx2,cy2,cx1,cy1);

                    if(impl ){
                        scene->removeItem(impl);
                    }
                    //int zz=(lim*111);
                    hash[id].path->addCoordinate(*qcord);
                    QLabel *n4=new QLabel(this);
                    n4->setStyleSheet("QLabel { color : red; }");
                    n4->move(100,160);
                    QString s1 = QString::number(dist/1000);
                    n4->setText("The Object is "+s1+"km far away");
                    n4->adjustSize();
                    n4->show();
                    nz=n4;

                    QLabel *n5=new QLabel(this);
                    n5->setStyleSheet("QLabel { color : red; }");
                    n5->move(400,160);
                    double deg = qown->azimuthTo(*qcord);
                    s = QString::number(deg);
                    n5->setText("The Bearing is "+s+" Degrees");
                    n5->adjustSize();
                    n5->show();
                    na=n5;

                    double cx = (gw/2)+((gh-30)*((a2 - qown->longitude())*111.320*cos((a1*pi)/180))/(2*radar));
                    double cy = (gh/2)-((gh-30)*(110.574*(a1 - qown->latitude()))/(2*radar));

                    double hx = h+((h-20)*((a2 - qown->longitude())*111.320*cos((a1*pi)/180))/srada);
                    double hy = h-((h-20)*(110.574*(a1 - qown->latitude()))/srada);

                    QLabel *n1=new QLabel(ui->openGLWidget);
                    // n->setAlignment(Qt::AlignBottom | Qt::AlignRight);
                    n1->setStyleSheet("QLabel { color : yellow; }");
                    n1->move((int)cx-5,(int)cy-8);
                    n1->setAutoFillBackground(false);
                    n1->setText("*");
                    n1->show();
                    QPen penLines(Qt::white, 1, Qt::DashDotLine);
                    painter.setPen(penLines);
                    painter.drawLine(gw/2,gh/2,cx,cy);
                    impl = scene->addLine(h,h,hx,hy,penLines);
                    int zval = impl->zValue();
                    QBrush blueBrush(Qt::blue);
                    QPen outlinePen(Qt::magenta,2);

                    hash[id].item1->setPos(hx-(hash[id].it.width())/2,hy-(hash[id].it.height())/2);
                    hash[id].item1->setZValue(zval+1);
                    hash[id].item1->setTransformOriginPoint(hash[id].it.rect().center());
                    hash[id].item1->setRotation(degs);
                    hash[id].item1->show();
                }
                else
                {
                    double dist=qold->distanceTo(*qcord);
                    QLabel *n2=new QLabel(this);
                    n2->setStyleSheet("QLabel { color : red; }");
                    n2->move(100,140);
                    QString s = QString::number(dist/1000);
                    n2->setText("The Object has travelled "+s+"km");
                    n2->adjustSize();
                    n2->show();
                    nz1=n2;
                    QLabel *n3=new QLabel(this);
                    n3->setStyleSheet("QLabel { color : red; }");
                    n3->move(400,140);
                    double degs = qold->azimuthTo(*qcord);
                    s = QString::number(degs);
                    n3->setText("The Travelling Direction is "+s+" Degrees");
                    n3->adjustSize();
                    n3->show();
                    na1=n3;
                    double cx1 = (gw/2)+((gh-30)*((a2 - qown->longitude())*111.320*cos((a1*pi)/180))/(2*radar));
                    double cy1 = (gh/2)-((gh-30)*(110.574*(a1 - qown->latitude()))/(2*radar));
                    double cx2 = (gw/2)+((gh-30)*((qold->longitude() - qown->longitude())*111.320*cos((a1*pi)/180))/(2*radar));
                    double cy2 = (gh/2)-((gh-30)*(110.574*(qold->latitude() - qown->latitude()))/(2*radar));

                    QPen penHLines(Qt::white, 1, Qt::DotLine);
                    painter.setPen(penHLines);
                    painter.drawLine(cx2,cy2,cx1,cy1);

                    if(impl ){
                        scene->removeItem(impl);
                        impl=NULL;
                    }
                    //int zz=(lim*111);
                    hash[id].path->addCoordinate(*qcord);
                    QLabel *n4=new QLabel(this);
                    n4->setStyleSheet("QLabel { color : red; }");
                    n4->move(100,160);
                    QString s1 = QString::number(dist/1000);
                    n4->setText("The Object is "+s1+"km far away");
                    n4->adjustSize();
                    n4->show();
                    nz=n4;

                    QLabel *n5=new QLabel(this);
                    n5->setStyleSheet("QLabel { color : red; }");
                    n5->move(400,160);
                    double deg = qown->azimuthTo(*qcord);
                    s = QString::number(deg);
                    n5->setText("The Bearing is "+s+" Degrees");
                    n5->adjustSize();
                    n5->show();
                    na=n5;

                    double cx = (gw/2)+((gh-30)*((a2 - qown->longitude())*111.320*cos((a1*pi)/180))/(2*radar));
                    double cy = (gh/2)-((gh-30)*(110.574*(a1 - qown->latitude()))/(2*radar));

                    double hx = h+((h-20)*((a2 - qown->longitude())*111.320*cos((a1*pi)/180))/radar);
                    double hy = h-((h-20)*(110.574*(a1 - qown->latitude()))/radar);

                    QLabel *n1=new QLabel(ui->openGLWidget);
                    // n->setAlignment(Qt::AlignBottom | Qt::AlignRight);
                    n1->setStyleSheet("QLabel { color : yellow; }");
                    n1->move((int)cx-5,(int)cy-8);
                    n1->setAutoFillBackground(false);
                    n1->setText("*");
                    n1->show();
                    QPen penLines(Qt::white, 1, Qt::DashDotLine);
                    painter.setPen(penLines);
                    painter.drawLine(gw/2,gh/2,cx,cy);
                    //impl = scene->addLine(h,h,hx,hy,penLines);
                    //int zval = impl->zValue();
                    QBrush blueBrush(Qt::blue);
                    QPen outlinePen(Qt::magenta,2);

                    hash[id].item1->setPos(hx-(hash[id].it.width())/2,hy-(hash[id].it.height())/2);
                    //hash[id].item1->setZValue(zval+1);
                    hash[id].item1->setTransformOriginPoint(hash[id].it.rect().center());
                    hash[id].item1->setRotation(degs);
                    hash[id].item1->hide();
                }

            }
            else
            {
                QLabel *n=new QLabel(this);
                n->setStyleSheet("QLabel { color : red; }");
                n->move(100,140);
                n->setText("The Latitude and Longitude exceed the radar range");
                n->adjustSize();
                n->show();
                nz=n;
            }
        }
        else
        {
            ui->pushButton->setText("Update Object Location");
            QString arg1=ui->lineEdit_4->text();
            QString arg2=ui->lineEdit_2->text();
            double a1 = arg1.split(" ")[0].toDouble();
            double a2 = arg2.split(" ")[0].toDouble();
            QGeoCoordinate *qcord = new QGeoCoordinate(a1,a2);

            double dist=qown->distanceTo(*qcord);
            if(dist/1000>radar)
            {
                QLabel *n=new QLabel(this);
                n->setStyleSheet("QLabel { color : red; }");
                n->move(100,140);
                n->setText("The Latitude and Longitude exceed the radar range");
                n->adjustSize();
                n->show();
                nz=n;
            }
            else{
                if(impl ){
                    scene->removeItem(impl);
                    impl=NULL;
                }
                if(dist/1000<=srada)
                {
                    hash[id].path->addCoordinate(*qcord);
                    hash[id].item1 = scene->addPixmap(hash[id].it);
                    QLabel *n2=new QLabel(this);
                    n2->setStyleSheet("QLabel { color : red; }");
                    n2->move(100,160);
                    QString s = QString::number(dist/1000);
                    n2->setText("The Object is "+s+"km far away");
                    n2->adjustSize();
                    n2->show();
                    nz=n2;

                    QLabel *n3=new QLabel(this);
                    n3->setStyleSheet("QLabel { color : red; }");
                    n3->move(400,160);
                    double deg = qown->azimuthTo(*qcord);
                    s = QString::number(deg);
                    n3->setText("The Bearing is "+s+" Degrees");
                    n3->adjustSize();
                    n3->show();
                    na=n3;

                    double cx = (gw/2)+((gh-30)*((a2 - qown->longitude())*111.320*cos((a1*pi)/180))/(2*radar));
                    double cy = (gh/2)-((gh-30)*(110.574*(a1 - qown->latitude()))/(2*radar));

                    double hx = h+((h-20)*((a2 - qown->longitude())*111.320*cos((a1*pi)/180))/srada);
                    double hy = h-((h-20)*(110.574*(a1 - qown->latitude()))/srada);

                    QLabel *n1=new QLabel(ui->openGLWidget);
                    // n->setAlignment(Qt::AlignBottom | Qt::AlignRight);
                    n1->setStyleSheet("QLabel { color : yellow; }");
                    n1->move((int)cx-5,(int)cy-8);
                    n1->setAutoFillBackground(false);
                    n1->setText("*");
                    n1->show();
                    QPen penHLines(Qt::white, 1, Qt::DashDotLine);
                    painter.setPen(penHLines);
                    painter.drawLine(gw/2,gh/2,cx,cy);
                    impl = scene->addLine(h,h,hx,hy,penHLines);
                    int zval = impl->zValue();
                    QBrush blueBrush(Qt::blue);
                    QPen outlinePen(Qt::magenta,2);
                    hash[id].item1->setPos(hx-(hash[id].it.width())/2,hy-(hash[id].it.height())/2);
                    hash[id].item1->setZValue(zval+1);
                    hash[id].item1->show();
                }
                else
                {
                    hash[id].path->addCoordinate(*qcord);
                    hash[id].item1 = scene->addPixmap(hash[id].it);
                    QLabel *n2=new QLabel(this);
                    n2->setStyleSheet("QLabel { color : red; }");
                    n2->move(100,160);
                    QString s = QString::number(dist/1000);
                    n2->setText("The Object is "+s+"km far away");
                    n2->adjustSize();
                    n2->show();
                    nz=n2;

                    QLabel *n3=new QLabel(this);
                    n3->setStyleSheet("QLabel { color : red; }");
                    n3->move(400,160);
                    double deg = qown->azimuthTo(*qcord);
                    s = QString::number(deg);
                    n3->setText("The Bearing is "+s+" Degrees");
                    n3->adjustSize();
                    n3->show();
                    na=n3;

                    double cx = (gw/2)+((gh-30)*((a2 - qown->longitude())*111.320*cos((a1*pi)/180))/(2*radar));
                    double cy = (gh/2)-((gh-30)*(110.574*(a1 - qown->latitude()))/(2*radar));

                    double hx = h+((h-20)*((a2 - qown->longitude())*111.320*cos((a1*pi)/180))/radar);
                    double hy = h-((h-20)*(110.574*(a1 - qown->latitude()))/radar);

                    QLabel *n1=new QLabel(ui->openGLWidget);
                    // n->setAlignment(Qt::AlignBottom | Qt::AlignRight);
                    n1->setStyleSheet("QLabel { color : yellow; }");
                    n1->move((int)cx-5,(int)cy-8);
                    n1->setAutoFillBackground(false);
                    n1->setText("*");
                    n1->show();
                    QPen penHLines(Qt::white, 1, Qt::DashDotLine);
                    painter.setPen(penHLines);
                    painter.drawLine(gw/2,gh/2,cx,cy);
                    //impl = scene->addLine(h,h,hx,hy,penHLines);
                    //int zval = impl->zValue();
                    QBrush blueBrush(Qt::blue);
                    QPen outlinePen(Qt::magenta,2);
                    hash[id].item1->setPos(hx-(hash[id].it.width())/2,hy-(hash[id].it.height())/2);
                    //hash[id].item1->setZValue(zval+1);
                    hash[id].item1->hide();
                }
                //int zz=(lim*111);

            }
        }
    }
    else if (!(ui->lineEdit_6->text().isEmpty()) && !(ui->lineEdit_7->text().isEmpty()) && c>=2)
    {
        int id = ui->lineEdit_5->text().toInt();
        if(hash.contains(id))
        {
            int i = hash[id].path->size();
            QGeoCoordinate *qold = new QGeoCoordinate(hash[id].path->coordinateAt(i-1));
            QString arg1=ui->lineEdit_6->text();
            QString arg2=ui->lineEdit_7->text();
            double a1 = arg1.split(" ")[0].toDouble();
            double a2 = arg2.split(" ")[0].toDouble();
            QGeoCoordinate qcord = qown->atDistanceAndAzimuth(a1*1000,a2);
            double ndist = a1*1000;
            if(ndist/1000<=radar)
            {
                a1=qcord.latitude();
                a2=qcord.longitude();
                double dist=qold->distanceTo(qcord);
                QLabel *n2=new QLabel(this);
                n2->setStyleSheet("QLabel { color : red; }");
                n2->move(100,140);
                QString s = QString::number(dist/1000);
                n2->setText("The Object has travelled "+s+"km");
                n2->adjustSize();
                n2->show();
                nz1=n2;
                QLabel *n3=new QLabel(this);
                n3->setStyleSheet("QLabel { color : red; }");
                n3->move(400,140);
                double degs = qold->azimuthTo(qcord);
                s = QString::number(degs);
                n3->setText("The Travelling Direction is "+s+" Degrees");
                n3->adjustSize();
                n3->show();
                na1=n3;
                double cx1 = (gw/2)+((gh-30)*((a2 - qown->longitude())*111.320*cos((a1*pi)/180))/(2*radar));
                double cy1 = (gh/2)-((gh-30)*(110.574*(a1 - qown->latitude()))/(2*radar));
                double cx2 = (gw/2)+((gh-30)*((qold->longitude() - qown->longitude())*111.320*cos((a1*pi)/180))/(2*radar));
                double cy2 = (gh/2)-((gh-30)*(110.574*(qold->latitude() - qown->latitude()))/(2*radar));

                QPen penHLines(Qt::white, 1, Qt::DotLine);
                painter.setPen(penHLines);
                painter.drawLine(cx2,cy2,cx1,cy1);

                if(impl ){
                    scene->removeItem(impl);
                    impl=NULL;
                }
                //int zz=(lim*111);
                hash[id].path->addCoordinate(qcord);
                QLabel *n4=new QLabel(this);
                n4->setStyleSheet("QLabel { color : red; }");
                n4->move(100,160);
                QString s1 = QString::number(qcord.latitude());
                n4->setText("The Object's Latitude is "+s1);
                n4->adjustSize();
                n4->show();
                nz=n4;

                QLabel *n5=new QLabel(this);
                n5->setStyleSheet("QLabel { color : red; }");
                n5->move(400,160);
                s = QString::number(qcord.longitude());
                n5->setText("The Object's Longitude is "+s);
                n5->adjustSize();
                n5->show();
                na=n5;

                double cx = (gw/2)+((gh-30)*((a2 - qown->longitude())*111.320*cos((a1*pi)/180))/(2*radar));
                double cy = (gh/2)-((gh-30)*(110.574*(a1 - qown->latitude()))/(2*radar));

                double hx = h+((h-20)*((a2 - qown->longitude())*111.320*cos((a1*pi)/180))/srada);
                double hy = h-((h-20)*(110.574*(a1 - qown->latitude()))/srada);

                QLabel *n1=new QLabel(ui->openGLWidget);
                // n->setAlignment(Qt::AlignBottom | Qt::AlignRight);
                n1->setStyleSheet("QLabel { color : yellow; }");
                n1->move((int)cx-5,(int)cy-8);
                n1->setAutoFillBackground(false);
                n1->setText("*");
                n1->show();
                QPen penLines(Qt::white, 1, Qt::DashDotLine);
                painter.setPen(penLines);
                painter.drawLine(gw/2,gh/2,cx,cy);
                if(ndist/1000<=srada)
                {
                    impl = scene->addLine(h,h,hx,hy,penLines);
                    int zval = impl->zValue();
                    QBrush blueBrush(Qt::blue);
                    QPen outlinePen(Qt::magenta,2);
                    //impel = scene->addEllipse(hx-1,hy-1 , 2, 2, outlinePen, blueBrush);
                    // QGraphicsPixmapItem item(QPixmap(":/new/Icons/Icon"));
                    // scene->addItem((QGraphicsItem*)&item);
                    // item1->setTransform(QTransform().rotate(deg), true);

                    hash[id].item1->setPos(hx-(hash[id].it.width())/2,hy-(hash[id].it.height())/2);
                    hash[id].item1->setZValue(zval+1);
                    hash[id].item1->setTransformOriginPoint(hash[id].it.rect().center());
                    hash[id].item1->setRotation(degs);
                    hash[id].item1->show();
                }
                else
                {
                    //impl = scene->addLine(h,h,hx,hy,penLines);
                    //int zval = impl->zValue();
                    QBrush blueBrush(Qt::blue);
                    QPen outlinePen(Qt::magenta,2);
                    //impel = scene->addEllipse(hx-1,hy-1 , 2, 2, outlinePen, blueBrush);
                    // QGraphicsPixmapItem item(QPixmap(":/new/Icons/Icon"));
                    // scene->addItem((QGraphicsItem*)&item);
                    // item1->setTransform(QTransform().rotate(deg), true);

                    hash[id].item1->setPos(hx-(hash[id].it.width())/2,hy-(hash[id].it.height())/2);
                    //hash[id].item1->setZValue(zval+1);
                    hash[id].item1->setTransformOriginPoint(hash[id].it.rect().center());
                    hash[id].item1->setRotation(degs);
                    hash[id].item1->hide();
                }
            }
            else
            {
                QLabel *n=new QLabel(this);
                n->setStyleSheet("QLabel { color : red; }");
                n->move(100,140);
                n->setText("The Latitude and Longitude exceed the radar range");
                n->adjustSize();
                n->show();
                nz=n;
            }
        }
        else
        {
            ui->pushButton->setText("Update Object Location");
            QString arg1=ui->lineEdit_6->text();
            QString arg2=ui->lineEdit_7->text();
            double a1 = arg1.split(" ")[0].toDouble();
            double a2 = arg2.split(" ")[0].toDouble();
            QGeoCoordinate qcord = qown->atDistanceAndAzimuth(a1*1000,a2);

            hash[id].path->addCoordinate(qcord);
            hash[id].item1 = scene->addPixmap(hash[id].it);
            a1=qcord.latitude();
            a2=qcord.longitude();

            double dist=qown->distanceTo(qcord);
            if(dist/1000>radar)
            {
                QLabel *n=new QLabel(this);
                n->setStyleSheet("QLabel { color : red; }");
                n->move(100,140);
                n->setText("The Latitude and Longitude exceed the radar range");
                n->adjustSize();
                n->show();
                nz=n;
            }
            else{
                if(impl ){
                    scene->removeItem(impl);
                    impl=NULL;
                }
                //int zz=(lim*111);
                hash[id].path->addCoordinate(qcord);
                QLabel *n2=new QLabel(this);
                n2->setStyleSheet("QLabel { color : red; }");
                n2->move(100,160);
                QString s1 = QString::number(qcord.latitude());
                n2->setText("The Object's Latitude is "+s1);
                n2->adjustSize();
                n2->show();
                nz=n2;

                QLabel *n3=new QLabel(this);
                n3->setStyleSheet("QLabel { color : red; }");
                n3->move(400,160);
                s1 = QString::number(qcord.longitude());
                n3->setText("The Object's Longitude is "+s1);

                n3->adjustSize();
                n3->show();
                na=n3;

                double cx = (gw/2)+((gh-30)*((a2 - qown->longitude())*111.320*cos((a1*pi)/180))/(2*radar));
                double cy = (gh/2)-((gh-30)*(110.574*(a1 - qown->latitude()))/(2*radar));

                double hx = h+((h-20)*((a2 - qown->longitude())*111.320*cos((a1*pi)/180))/srada);
                double hy = h-((h-20)*(110.574*(a1 - qown->latitude()))/srada);

                QLabel *n1=new QLabel(ui->openGLWidget);
                // n->setAlignment(Qt::AlignBottom | Qt::AlignRight);
                n1->setStyleSheet("QLabel { color : yellow; }");
                n1->move((int)cx-5,(int)cy-8);
                n1->setAutoFillBackground(false);
                n1->setText("*");
                n1->show();
                QPen penHLines(Qt::white, 1, Qt::DashDotLine);
                painter.setPen(penHLines);
                painter.drawLine(gw/2,gh/2,cx,cy);
                if(dist/1000<=srada)
                {
                    impl = scene->addLine(h,h,hx,hy,penHLines);
                    int zval = impl->zValue();
                    QBrush blueBrush(Qt::blue);
                    QPen outlinePen(Qt::magenta,2);
                    hash[id].item1->setPos(hx-(hash[id].it.width())/2,hy-(hash[id].it.height())/2);
                    hash[id].item1->setZValue(zval+1);
                    hash[id].item1->show();
                }
                else
                {
                    //impl = scene->addLine(h,h,hx,hy,penHLines);
                    //int zval = impl->zValue();
                    QBrush blueBrush(Qt::blue);
                    QPen outlinePen(Qt::magenta,2);
                    hash[id].item1->setPos(hx-(hash[id].it.width())/2,hy-(hash[id].it.height())/2);
                    //hash[id].item1->setZValue(zval+1);
                    hash[id].item1->hide();
                }

            }
        }
    }
    else
    {   //d=0;
        QLabel *n=new QLabel(this);
        n->setStyleSheet("QLabel { color : red; }");
        n->move(100,160);
        n->setText("Enter the Latitude and Longitude ");
        n->adjustSize();
        n->show();
        nz=n;
    }
    ui->lineEdit_2->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
}
//QGeoCoordinate QGeoCoordinate::atDistanceAndAzimuth(qreal distance, qreal azimuth, qreal distanceUp = 0.0) const
void MainWindow::on_lineEdit_4_editingFinished()
{
}
void MainWindow::on_lineEdit_5_editingFinished()
{
    if(nz)
        nz->hide();
    QString arg=ui->lineEdit_5->text();
    double a = arg.split(" ")[0].toDouble();
    if(a==0)
    {
        ui->lineEdit_5->clear();
    }
    if(!(a>0 && a<=5000) && c<2)
    {
        QLabel *n=new QLabel(this);
        // n->setAlignment(Qt::AlignBottom | Qt::AlignRight);
        n->setStyleSheet("QLabel { color : red; }");
        n->move(100,140);
        n->setText("Enter valid radar range ");
        n->adjustSize();
        n->show();
        nz=n;
    }
    else if(c<2)
    {
        srada=a;
        radar=a;
    }
    else if(c==2)
    {
        int i = a;
        if((ui->lineEdit_5->text().isEmpty()))
        {
            QLabel *n=new QLabel(this);
            // n->setAlignment(Qt::AlignBottom | Qt::AlignRight);
            n->setStyleSheet("QLabel { color : red; }");
            n->move(100,140);
            n->setText("Enter valid Track ID ");
            n->adjustSize();
            n->show();
            nz=n;
        }
        else
            ui->lineEdit_5->setText(QString::number(i));
    }
}
void MainWindow::updatepaint(int i)
{
    if(srada>=50 && srada<=radar)
    {
        if(i>0)
        {
            int mile = radar*0.539957;
            mile=(mile%2==0)?mile:mile-1;
            if(srada+3.704>=radar)
                srada=mile*1.852;
            else
                srada+=3.704;
        }
        else
        {
            if(srada-3.704<=51.856)
                srada=51.856;
            else
                srada-=3.704;
        }
        QHashIterator<int,obj> i(hash);
          while (i.hasNext())
          {
              i.next();
//              hash[i.key()].it = hash[i.key()].it.scaled(hash[i.key()].it.width()*0.95,hash[i.key()].it.height()*0.95);
              int ss = hash[i.key()].path->size();
              QGeoCoordinate *qcord = new QGeoCoordinate(hash[i.key()].path->coordinateAt(ss-1));
              double ndist = qown->distanceTo(*qcord);
              if(ndist/1000<=srada)
              {
                  if(impl ){
                      scene->removeItem(impl);
                      impl=NULL;
                  }

                  double hx = h+((h-20)*((qcord->longitude() - qown->longitude())*111.320*cos((qcord->latitude()*pi)/180))/srada);
                  double hy = h-((h-20)*(110.574*(qcord->latitude() - qown->latitude()))/srada);

                  QBrush blueBrush(Qt::blue);
                  QPen outlinePen(Qt::magenta,2);

                  hash[i.key()].item1->show();
                  hash[i.key()].item1->setPos(hx-(hash[i.key()].it.width())/2,hy-(hash[i.key()].it.height())/2);
              }else{
                  hash[i.key()].item1->hide();
              }
          }
          QString ss = QString::number(srada*0.539957);
          rscale->setText("Range Scale is : "+ss+"nmi");
    }
}
