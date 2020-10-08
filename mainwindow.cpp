#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    this->ui->pBtnConfirm_1->setDisabled(true);
//    this->ui->pBtn_confirm_2->setDisabled(true);
//    this->ui->pBtnClip->setDisabled(true);
//    this->ui->pBtn_rtn->setDisabled(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

QString getTime(){
    QString  data_time = QDateTime::currentDateTime().toString("hh:mm:ss ");
    return data_time;
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(!this->curPolygon)
    {
        if(this->polygons.size()==2)
        {
            return;
        }
        Polygon* newPolygon;
        if(this->polygons.size()==0)
        {
            newPolygon=new Polygon(MAIN);
        }else{
            newPolygon=new Polygon(CUT);
        }
        newPolygon->addPoint(QPointF(event->x(),event->y()));
        this->polygons.push_back(newPolygon);
        this->curPolygon=newPolygon;
    }else
    {
        this->curPolygon->addPoint(QPointF(event->x(),event->y()));
    }
    // this->activePoint=QPointF(event->x(),event->y());
    qDebug()<<event->x()<<" "<<event->y()<<endl;
    update();
}

void MainWindow::paintEvent(QPaintEvent *)
{
   QPainter painter(this);
   if(this->nowStatus!=CLIP)
   {
       for(auto i:this->polygons)
       {
           i->drawPolygon(painter);
       }
   }else{
       if(this->resPolygon){
           this->resPolygon->drawClippedPath(painter);
       }
   }
}

void MainWindow::on_pBtnCloseLoop_clicked()
{
    qDebug()<<"yes?";
    if(this->curPolygon)
    {
        this->curPolygon->closeLoop();
    }
    update();
}

void MainWindow::on_pBtnFinish_clicked()
{
    if(this->polygons.size()==1)
    {
        this->mainPolygon=curPolygon;
        this->ui->txt_1->append(getTime()+"绘制已完成！");
    }else if(this->polygons.size()==2)
    {
        this->cutPolygon=curPolygon;
        this->ui->txt_2->append(getTime()+"绘制已完成！");
        this->ui->pBtn_confirm_2->setDisabled(false);
        this->ui->pBtnClip->setDisabled(false);
        this->ui->pBtnFinish->setDisabled(true);
        this->ui->pBtnCloseLoop->setDisabled(true);
    }
    this->curPolygon=NULL;
}

void MainWindow::on_pBtnConfirm_1_clicked()
{
    this->mainPolygon=this->polygons[0];
    this->cutPolygon=this->polygons[1];
    this->mainPolygon->changeRank();
    this->cutPolygon->changeRank();
    this->ui->pBtnConfirm_1->setDisabled(true);
    this->ui->pBtn_confirm_2->setDisabled(false);
    this->ui->txt_1->append(getTime()+"当前1号多边形为红色");
    this->ui->txt_2->append(getTime()+"当前2号多边形为黑色");
    update();
}

void MainWindow::on_pBtn_confirm_2_clicked()
{
    this->mainPolygon=this->polygons[1];
    this->cutPolygon=this->polygons[0];
    this->mainPolygon->changeRank();
    this->cutPolygon->changeRank();
    this->ui->pBtnConfirm_1->setDisabled(false);
    this->ui->pBtn_confirm_2->setDisabled(true);
    this->ui->txt_1->append(getTime()+"当前1号多边形为黑色");
    this->ui->txt_2->append(getTime()+"当前2号多边形为红色");
    update();
}

void MainWindow::on_pBtnClip_clicked()
{
//    // -- unit test --
//    this->mainPolygon=new Polygon;
//    this->curPolygon=this->mainPolygon;
//    this->mainPolygon->addPoint(QPointF(221,142));
//    this->mainPolygon->addPoint(QPointF(82,350));
//    this->mainPolygon->addPoint(QPointF(456,356));
//    this->on_pBtnCloseLoop_clicked();
//    this->on_pBtnFinish_clicked();

//    this->cutPolygon=new Polygon;
//    this->cutPolygon->changeRank();
//    this->curPolygon=this->cutPolygon;
//    this->cutPolygon->addPoint(QPointF(88,203));
//     this->cutPolygon->addPoint(QPointF(130,330));
//    this->cutPolygon->addPoint(QPointF(248,394));
//    this->cutPolygon->addPoint(QPointF(384,205));
//    this->on_pBtnCloseLoop_clicked();
//    this->on_pBtnFinish_clicked();
//    this->polygons.push_back(this->mainPolygon);
//    this->polygons.push_back(this->cutPolygon);
//    qDebug()<<"construct test polygon over!"<<endl;
//    // -- unit test --


    this->resPolygon=&logic.perform(*this->mainPolygon,*this->cutPolygon);
    this->nowStatus=CLIP;
    this->ui->label->append(getTime()+"裁剪完成！");
    this->ui->pBtnClip->setDisabled(true);
    this->ui->pBtn_rtn->setDisabled(false);
    update();
}

void MainWindow::on_pBtn_rtn_clicked()
{
    this->nowStatus=DRAW;
    this->mainPolygon->clearPoints();
    this->cutPolygon->clearPoints();
    this->ui->pBtnClip->setDisabled(false);
    this->ui->pBtn_rtn->setDisabled(true);
    update();
}
