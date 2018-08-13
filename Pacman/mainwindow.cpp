#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /// INITIALIZATION

    dirAngle = 0;
    x = 100;
    y = 100;

    image = new QImage();//(iWidth, iHeight, QImage::Format_ARGB32);
    image->load("1.png");

    imagePac = new QImage();//(iWidth, iHeight, QImage::Format_ARGB32);
    imagePac->load("pacR.png");
    *imagePac = imagePac->scaled(50,50);

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerTick()) );

    for(int i = 0; i < 50; i++)
        for(int j = 0; j < 50; j++)
        {
            if (qAlpha(imagePac->pixel(i,j)) > 0)
                image->setPixel(i + x, j + y, imagePac->pixel(i,j));
        }


    ui->label->setPixmap(QPixmap::fromImage(*image));
}

MainWindow::~MainWindow()
{
    delete timer;
    delete imagePac;
    delete image;
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "event  " << event->key();
    if(event->key()==16777235)
    {
        imagePac->load("pacU.png");
        *imagePac = imagePac->scaled(50,50);
        dirAngle = 90;
    }
    if(event->key()==16777237)
    {
        imagePac->load("pacD.png");
        *imagePac = imagePac->scaled(50,50);
        dirAngle = 270;
    }
    if(event->key()==16777234)
    {
        imagePac->load("pacL.png");
        *imagePac = imagePac->scaled(50,50);
        dirAngle = 180;
    }
    if(event->key()==16777236)
    {
        imagePac->load("pacR.png");
        *imagePac = imagePac->scaled(50,50);
        dirAngle = 0;
    }

}

void MainWindow::timerTick()
{

    for(int i = 0; i < 50; i++)
        for(int j = 0; j < 50; j++)
        {
            if (qAlpha(imagePac->pixel(i,j)) > 0)
                image->setPixel(i + x, j + y, 0xff000000);
        }

    y = y - 1 * int(sin(dirAngle * M_PI / 180));
    x = x + 1 * int(cos(dirAngle * M_PI / 180));

    if (x < 0 || x >= 550)
    {
       x = x - 1 * int(cos(dirAngle * M_PI / 180));
       return;
    }
    if (y < 0 || y >= 550)
    {
       y = y + 1 * int(sin(dirAngle * M_PI / 180));
       return;
    }
    //qDebug() << sin(dirAngle * M_PI / 180) << "   " << cos(dirAngle * M_PI / 180);

    for(int i = 0; i < 50; i++)
        for(int j = 0; j < 50; j++)
        {
            if (qAlpha(imagePac->pixel(i,j)) > 0)
                image->setPixel(i + x, j + y, imagePac->pixel(i,j));
        }

    //qDebug() << dirAngle;

    ui->label->setPixmap(QPixmap::fromImage(*image));
}

void MainWindow::on_pushButton_clicked()
{
    if(timer->isActive())
        timer->stop();
    else
        timer->start(10);
}


void MainWindow::on_lineEdit_editingFinished()
{
    dirAngle = ui->lineEdit->text().toInt();
}
