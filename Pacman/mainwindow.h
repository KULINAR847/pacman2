#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QPixmap>
#include <QRgb>
#include <QTimer>
#include <QString>
#include <QDebug>
#include <QKeyEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QImage *image;  // scene

    // pacman coordinates
    int x;
    int y;
    QImage *imagePac;  // pacman image

    QTimer *timer;
    int dirAngle; // direction angle

private:
    Ui::MainWindow *ui;

private slots:
    void keyPressEvent(QKeyEvent *event);
    void timerTick();
    void on_pushButton_clicked();
    void on_lineEdit_editingFinished();
};

#endif // MAINWINDOW_H
