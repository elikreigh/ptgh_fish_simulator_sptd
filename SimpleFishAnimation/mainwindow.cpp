//Adam Griswold : Version 1.0
//Purpose: Sets up initial widget location and button triggers and page transitions
//         Basic timer is set up for occasional fish movement
//Date: 12/1/2017
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QApplication>
#include <QProcess>
#include <iostream>
#include <string>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){

    //setting up window with form
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    setWindowTitle(tr("TankDisplay"));

    //assinging label to fish & Pixmap to label
    mainFish->set_fish(findChild<QLabel*>("Fish"));

    //starting move events
    //anitimer cycles fish sprite, can be included with the moving animation
    QTimer *timer = new QTimer(this);
    //QTimer *anitimer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move_fish()));
    //connect(anitimer, SIGNAL(timeout()), this, SLOT(next_frame()));
    timer->start(10);
    //anitimer->start(300);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::move_fish(){
    //Placeholder bouncing
    if(ui->stackedWidget->currentIndex() == 1 && mainFish->get_left()){
        mainFish->swim(-3,0);
        if(mainFish->get_x() < 10){
            mainFish->set_left(false);
        }
    }
    else if(ui->stackedWidget->currentIndex() == 1 && !mainFish->get_left()){
        mainFish->swim(3,0);
        if(mainFish->get_x() > 1060){
            mainFish->set_left(true);
        }
    }
}

void MainWindow::next_frame(){
    if(ui->stackedWidget->currentIndex() == 1){
        mainFish->cycle_sprite();
    }
}

/*Startup Screen Inputs*/
void MainWindow::on_start_button_clicked(){
    ui->stackedWidget->setCurrentIndex(1);
}

/*Main Screen Inputs*/
void MainWindow::on_to_settings_button_clicked(){
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_feeding_button_clicked(){

}

void MainWindow::on_kill_button_clicked(){
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}

/*Settings Screen Inputs*/
void MainWindow::on_to_tank_button_clicked(){
    ui->stackedWidget->setCurrentIndex(1);
}
//position numbers: 0 - 99
void MainWindow::on_music_slider_sliderMoved(int position)
{
    QLabel *tag = findChild<QLabel*>("label_3");
    QString s;
    s.setNum(position);
    tag->setText(s);
}

/*General Window Inputs*/
void MainWindow::on_exit_button_clicked(){
    this->close();
}
