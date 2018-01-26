//Adam Griswold : Version 1.0
//Adam Griswold : Version 1.5
//Purpose: Version 1.0 : 12/1/2017 : Sets up initial widget location and button triggers and page transitions. Basic timer is set up for occasional fish movement
//         Version 1.5 : 12/4/2017 : Added classes for Bubbles, Floating Bubbles, Food and more UI interfaces
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QApplication>
#include <QProcess>
#include <iostream>
#include <string>
#include <QMouseEvent>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    //setting up window with form
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    setWindowTitle(tr("TankDisplay"));
    setMouseTracking(true);

    //background bubbling sound
    sound_fx = new QMediaPlayer();
    sound_music = new QMediaPlayer();

    sound_fx->setMedia(QUrl("qrc:/sound/click.mp3"));

    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/sound/tankSound.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    sound_music->setPlaylist(playlist);
    sound_music->play();

    //Bubbles for splash screen
    splash_floater1 = new FloatingBubbles();
    splash_floater2 = new FloatingBubbles();
    splash_floater3 = new FloatingBubbles();
    splash_floater4 = new FloatingBubbles();
    splash_floater5 = new FloatingBubbles();
    splash_floater6 = new FloatingBubbles();

    //Fish and Bubbles and Food and Pillars for tank screen
    mainFish = new Fish(this->width(),this->height());
    bubble1 = new Bubbles();
    bubble2 = new Bubbles();
    single_bubble1 = new FloatingBubbles();

    food = new FishFood();

    pillar1 = new Pillar();
    pillar2 = new Pillar();

    feeding_button1 = new QPushButton();

    //mouse coordinates
    mouse_cord.setX(0);
    mouse_cord.setY(0);

    //assigning label to bubbles for splash screen
    splash_floater1->set_bubble(findChild<QLabel*>("spash_floater1"));
    splash_floater2->set_bubble(findChild<QLabel*>("spash_floater2"));
    splash_floater3->set_bubble(findChild<QLabel*>("spash_floater3"));
    splash_floater4->set_bubble(findChild<QLabel*>("spash_floater4"));
    splash_floater5->set_bubble(findChild<QLabel*>("spash_floater5"));
    splash_floater6->set_bubble(findChild<QLabel*>("spash_floater6"));
    //assinging label to fish and bubbles for tank screen
    bubble1->set_bubble(findChild<QLabel*>("bubbles1"));
    bubble2->set_bubble(findChild<QLabel*>("bubbles2"));
    single_bubble1->set_bubble(findChild<QLabel*>("single_bubble1"));

    food->set_food(findChild<QLabel*>("food1"));

    pillar1->set_label(findChild<QLabel*>("pillar1"));
    pillar2->set_label(findChild<QLabel*>("pillar2"));

    feeding_button1 = (findChild<QPushButton*>("feeding_button"));

    mainFish->set_fish(findChild<QLabel*>("Fish"));
    mainFish->sprite_setup();
    mainFish->brain_setup();
    /*tank = findChild<QPushButton*>("tank_button");
    tank->setStyleSheet("background-color: transparent; ");*/

    //setting up pile
    pile[0] = pillar1;
    pile[1] = pillar2;
    pile[2] = food;

    for(int i = 0; i < 3; i++){
        pile[i]->set_depth(rand()%10);
    }
    pile[0]->set_depth(5);

    //timer: starting move events
    //animations_timer cycles fish sprite, can be included with the moving animation
    //new_bubbles_timer
    QTimer *timer = new QTimer(this);
    QTimer *animations_timer = new QTimer(this);
    QTimer *feeding_timer = new QTimer(this);
    //QTimer *new_bubbles_timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(movement_logic()));
    connect(animations_timer, SIGNAL(timeout()), this, SLOT(next_frame()));
    connect(feeding_timer, SIGNAL(timeout()), this, SLOT(feeding_check()));
    //connect(new_bubbles_timer, SIGNAL(timeout()), this, SLOT(next_frame()));
    timer->start(10);
    animations_timer->start(500);
    feeding_timer->start(1000);
    //new_bubbles_timer->start(100);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::movement_logic(){
    //splash screen
    if(ui->stackedWidget->currentIndex() == 0){
        /*if(findChild<QLabel*>("spash_floater1") != 0){
            splash_floater1->float_up();
        }
        if(findChild<QLabel*>("spash_floater2") != 0){
            splash_floater2->float_up();
        }
        if(findChild<QLabel*>("spash_floater3") != 0){
            splash_floater3->float_up();
        }
        if(findChild<QLabel*>("spash_floater4") != 0){
            splash_floater4->float_up();
        }
        if(findChild<QLabel*>("spash_floater5") != 0){
            splash_floater5->float_up();
        }
        if(findChild<QLabel*>("spash_floater6") != 0){
            splash_floater6->float_up();
        }*/
        splash_floater1->float_up();
        splash_floater2->float_up();
        splash_floater3->float_up();
        splash_floater4->float_up();
        splash_floater5->float_up();
        splash_floater6->float_up();
    }
    //tank screen
    else if(ui->stackedWidget->currentIndex() == 1 ){
        /*if(findChild<QLabel*>("single_bubble1") != 0){
            single_bubble1->float_up();
        }*/
        mainFish->logic(pile);
        if(mainFish->eat_food(pile)){
            food->eaten();
            sound_fx->setMedia(QUrl("qrc:/sound/munch.mp3"));
            sound_fx->play();
        }
        /*if(ui->stackedWidget->currentIndex() == 1 && mainFish->get_brain().getState() == Move){
            Fish *test_fish = new Fish(mainFish);
            enum Move_Type direction;
            test_fish->swim();
            direction = (test_fish->get_brain()).getDirection();
            if(test_fish->no_over_lap(pile)){
                if(direction == Left || direction == UpLeft || direction == DownLeft){
                    mainFish->set_left(true);
                }
                else if(direction == Right || direction == UpRight || direction == DownRight){
                    mainFish->set_left(false);
                } else {
                    mainFish->set_left(mainFish->get_face_left());
                }
                mainFish->get_brain().set_direction(direction);
                mainFish->swim(direction);
                if(mainFish->eat_food(food)){
                    food->eaten();
                    sound_fx->setMedia(QUrl("qrc:/sound/munch.mp3"));
                    sound_fx->play();
                }
            }
            test_fish->~Fish();
            //mainFish->swim(DownRight);
        }*/
        single_bubble1->float_up();
        if(food->no_over_lap(pile)){
            food->sink();
        }
    }
}

void MainWindow::next_frame(){
    if(ui->stackedWidget->currentIndex() == 0){
        /*if(findChild<QLabel*>("spash_floater1") != 0){
            splash_floater1->cycle_sprite();
        }
        if(findChild<QLabel*>("spash_floater2") != 0){
            splash_floater2->cycle_sprite();
        }
        if(findChild<QLabel*>("spash_floater3") != 0){
            splash_floater3->cycle_sprite();
        }
        if(findChild<QLabel*>("spash_floater4") != 0){
            splash_floater4->cycle_sprite();
        }
        if(findChild<QLabel*>("spash_floater5") != 0){
            splash_floater5->cycle_sprite();
        }
        if(findChild<QLabel*>("spash_floater6") != 0){
            splash_floater6->cycle_sprite();
        }*/
        splash_floater1->cycle_sprite();
        splash_floater2->cycle_sprite();
        splash_floater3->cycle_sprite();
        splash_floater4->cycle_sprite();
        splash_floater5->cycle_sprite();
        splash_floater6->cycle_sprite();
    }
    else if(ui->stackedWidget->currentIndex() == 1){
        mainFish->cycle_sprite();
        bubble1->cycle_sprite();
        bubble2->cycle_sprite();
        /*if(findChild<QLabel*>("single_bubble1") != 0){
            single_bubble1->cycle_sprite();
        }*/
        single_bubble1->cycle_sprite();
        food->cycle_sprite();
    }
}

/*Mouse Tracking*/
void MainWindow::mousePressEvent(QMouseEvent *event){
    qDebug() << "Before Click Event";
    if(ui->stackedWidget->currentIndex() == 1){
        sound_fx->setMedia(QUrl("qrc:/sound/tap.mp3"));
        sound_fx->play();
        mouse_cord = event->pos();
        mainFish->frighten(mouse_cord);
        qDebug() << "After Click Event";
        /*enum Move_Type direction;
        if(mainFish->get_x() < mouse_cord.x() && mainFish->get_y() < mouse_cord.y()){
            direction = UpLeft;
        }
        else if(mainFish->get_x() == mouse_cord.x() && mainFish->get_y() > mouse_cord.y()){
            direction = Up;
        }
        else if(mainFish->get_x() > mouse_cord.x() && mainFish->get_y() > mouse_cord.y()){
            direction = UpRight;
        }
        else if(mainFish->get_x() > mouse_cord.x() && mainFish->get_y() == mouse_cord.y()){
            direction = Right;
        }
        else if(mainFish->get_x() < mouse_cord.x() && mainFish->get_y() < mouse_cord.y()){
            direction = DownRight;
        }
        else if(mainFish->get_x() == mouse_cord.x() && mainFish->get_y() < mouse_cord.y()){
            direction = Down;
        }
        else if(mainFish->get_x() > mouse_cord.x() && mainFish->get_y() < mouse_cord.y()){
            direction = DownLeft;
        }
        else if(mainFish->get_x() < mouse_cord.x() && mainFish->get_y() == mouse_cord.y()){
            direction = Left;
        }

        Fish *test_fish = new Fish(mainFish);
        test_fish->test_swim(direction);
        if(test_fish->no_over_lap(pile)){
            if(direction == Left || direction == UpLeft || direction == DownLeft){
                mainFish->set_left(true);
            }
            else if(direction == Right || direction == UpRight || direction == DownRight){
                mainFish->set_left(false);
            } else {
                mainFish->set_left(mainFish->get_face_left());
            }
            mainFish->get_brain().set_direction(direction);
            mainFish->swim(direction);
            if(mainFish->eat_food(food)){
                food->eaten();
                sound_fx->setMedia(QUrl("qrc:/sound/munch.mp3"));
                sound_fx->play();
            }

            mainFish->get_brain().set_state(Scared);
        }
        test_fish->~Fish();*/
    }
}

/*Startup Screen Inputs*/
void MainWindow::on_start_button_clicked(){
    sound_fx->setMedia(QUrl("qrc:/sound/click.mp3"));
    sound_fx->play();
    ui->stackedWidget->setCurrentIndex(1);
}

/*Main Screen Inputs*/
//feeding_check assures the user that the fish is not overly hungry.
//if the fish needs food, the feeding button will blink
void MainWindow::feeding_check(){
    static bool blink = false;
    if (mainFish->get_hunger() >= 1.0 && blink == false){
        feeding_button1->setStyleSheet((QString)"background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 grey, stop:1 black);\nfont: 75 auto 'MS Serif';\ncolor: white");
        feeding_button1->setGeometry(27, 27, 80, 28);
        blink = true;
    }
    else if (mainFish->get_hunger() >= 1.0 && blink == true){
        feeding_button1->setStyleSheet((QString)"background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 white, stop:1 grey);\nfont: 75 auto 'MS Serif';\ncolor: black");
        feeding_button1->setGeometry(30, 30, 75, 23);
        blink = false;
    }
}

void MainWindow::on_to_settings_button_clicked(){
    sound_fx->setMedia(QUrl("qrc:/sound/click.mp3"));
    sound_fx->play();
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_feeding_button_clicked(){
    sound_fx->setMedia(QUrl("qrc:/sound/click.mp3"));
    sound_fx->play();
    sound_fx->setMedia(QUrl("qrc:/sound/shaker.mp3"));
    sound_fx->play();
    /*QLabel *new_food = new QLabel("food1", ui->GameWindow, 0);
    new_food->setGeometry(100,100,100,100);*/
    food->show_food();
    mainFish->feeding();
}

void MainWindow::on_kill_button_clicked(){
    sound_fx->setMedia(QUrl("qrc:/sound/click.mp3"));
    sound_fx->play();
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}

/*Settings Screen Inputs*/
/*void MainWindow::on_to_tank_button_clicked(){
    sound_fx->setMedia(QUrl("qrc:/sound/click.mp3"));
    sound_fx->play();
    ui->stackedWidget->setCurrentIndex(1);
}*/

void MainWindow::on_credits_button_clicked(){
    sound_fx->setMedia(QUrl("qrc:/sound/click.mp3"));
    sound_fx->play();
    ui->stackedWidget->setCurrentIndex(3);

}
void MainWindow::on_controls_button_clicked(){
    sound_fx->setMedia(QUrl("qrc:/sound/click.mp3"));
    sound_fx->play();
    ui->stackedWidget->setCurrentIndex(4);

}
/*Credits Screen Inputs*/
void MainWindow::on_credits_to_settings_button_clicked(){
    sound_fx->setMedia(QUrl("qrc:/sound/click.mp3"));
    sound_fx->play();
    ui->stackedWidget->setCurrentIndex(2);
}
/*Contorls Screen Inputs*/
void MainWindow::on_controls_to_settings_button_clicked(){
    sound_fx->setMedia(QUrl("qrc:/sound/click.mp3"));
    sound_fx->play();
    ui->stackedWidget->setCurrentIndex(2);
}

//position numbers: 0 - 99
void MainWindow::on_music_slider_sliderMoved(int position){
    sound_music->setVolume((position));
    /*QLabel *tag = findChild<QLabel*>("label_3");
    QString s;
    s.setNum(position);
    tag->setText(s);*/
}

void MainWindow::on_sfx_slider_sliderMoved(int position){
    sound_fx->setVolume((position));
}

/*General Window Inputs*/
void MainWindow::on_exit_button_clicked(){
    this->close();
}

void MainWindow::spawn_bubbles(){
    /*if(findChild<QLabel*>("spash_floater1") == 0){
        QLabel *new_bubble = new QLabel(ui->centralWidget, 0);
        new_bubble->setGeometry(rand()%1000, 600, 31, 31);
        new_bubble->setPixmap(QPixmap("../Resources/BubbleBasic1.png"));
        new_bubble->setObjectName("splash_floater1");
        splash_floater1->set_bubble(findChild<QLabel*>("spash_floater1"));
    }
    if(findChild<QLabel*>("spash_floater2") == 0){
        QLabel *new_bubble = new QLabel(ui->centralWidget, 0);
        new_bubble->setGeometry(rand()%1000, 600, 31, 31);
        new_bubble->setPixmap(QPixmap("../Resources/BubbleBasic1.png"));
        new_bubble->setObjectName("splash_floater2");
        splash_floater2->set_bubble(findChild<QLabel*>("spash_floater2"));
    }
    if(findChild<QLabel*>("spash_floater3") == 0){
        QLabel *new_bubble = new QLabel(ui->centralWidget, 0);
        new_bubble->setObjectName(QString("splash_floater3"));
        new_bubble->setGeometry(rand()%1000, 600, 31, 31);
        new_bubble->setPixmap(QPixmap("../Resources/BubbleBasic1.png"));
        splash_floater3->set_bubble(new_bubble);
    }
    if(findChild<QLabel*>("spash_floater4") == 0){
        QLabel *new_bubble = new QLabel(ui->centralWidget, 0);
        new_bubble->setGeometry(rand()%1000, 600, 31, 31);
        new_bubble->setPixmap(QPixmap("../Resources/BubbleBasic1.png"));
        new_bubble->setObjectName("splash_floater4");
        splash_floater4->set_bubble(findChild<QLabel*>("spash_floater4"));
    }
    if(findChild<QLabel*>("spash_floater5") == 0){
        QLabel *new_bubble = new QLabel(ui->centralWidget, 0);
        new_bubble->setGeometry(rand()%1000, 600, 31, 31);
        new_bubble->setPixmap(QPixmap("../Resources/BubbleBasic1.png"));
        new_bubble->setObjectName("splash_floater5");
        splash_floater5->set_bubble(findChild<QLabel*>("spash_floater5"));
    }
    if(findChild<QLabel*>("spash_floater6") == 0){
        QLabel *new_bubble = new QLabel(ui->centralWidget, 0);
        new_bubble->setGeometry(rand()%1000, 600, 31, 31);
        new_bubble->setPixmap(QPixmap("../Resources/BubbleBasic1.png"));
        new_bubble->setObjectName("splash_floater6");
        splash_floater6->set_bubble(findChild<QLabel*>("spash_floater6"));
    }*/
}

