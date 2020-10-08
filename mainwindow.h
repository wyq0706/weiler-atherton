#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QDateTime>
#include <QPainter>
#include <QPointF>
#include <QDebug>

#include <polygon.h>
#include <weileratherton.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void mouseReleaseEvent(QMouseEvent *event);

    void paintEvent(QPaintEvent *);

private slots:
    void on_pBtnCloseLoop_clicked();

    void on_pBtnFinish_clicked();

    void on_pBtnConfirm_1_clicked();

    void on_pBtn_confirm_2_clicked();

    void on_pBtnClip_clicked();

    void on_pBtn_rtn_clicked();

private:
    Ui::MainWindow *ui;
    QPointF activePoint;
    std::vector<Polygon*> polygons;
    Polygon* curPolygon=NULL;

    Polygon* mainPolygon=NULL;
    Polygon* cutPolygon=NULL;
    Polygon* resPolygon=NULL;

    WeilerAtherton logic;
    mainStatus nowStatus;
};
#endif // MAINWINDOW_H
