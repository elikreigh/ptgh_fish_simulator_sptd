#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtUiTools>
#include <QVBoxLayout>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "fish.h"
#include "bubbles.h"
#include "floatingbubbles.h"
#include "fishfood.h"
#include "pillar.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void movement_logic();
    void on_start_button_clicked();
    void on_to_settings_button_clicked();
    void on_to_tank_button_clicked();
    void on_exit_button_clicked();
    void on_kill_button_clicked();
    void on_feeding_button_clicked();
    void on_controls_button_clicked();
    void on_credits_button_clicked();
    void on_controls_to_settings_button_clicked();
    void on_credits_to_settings_button_clicked();
    void on_tank_button_clicked();

    void next_frame();
    void spawn_bubbles();

    void on_music_slider_sliderMoved(int position);
    void on_sfx_slider_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
    //Sound
    QMediaPlayer *sound_fx;
    QMediaPlayer *sound_music;
    //Bubbles for splash screen
    FloatingBubbles *splash_floater1;
    FloatingBubbles *splash_floater2;
    FloatingBubbles *splash_floater3;
    FloatingBubbles *splash_floater4;
    FloatingBubbles *splash_floater5;
    FloatingBubbles *splash_floater6;
    //Fish and Bubbles and Food for tank screen
    Fish *mainFish;
    Bubbles *bubble1;
    Bubbles *bubble2;
    FloatingBubbles *single_bubble1;
    FishFood *food;
    Pillar *pillar1;
    Pillar *pillar2;

    QPushButton *tank;
    //label layout
    QVBoxLayout *main_layout;

    Pillar *pile[2];
};

#endif // MAINWINDOW_H
