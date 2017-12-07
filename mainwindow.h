#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtUiTools>
#include "fish.h"

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
    void move_fish();
    void on_start_button_clicked();
    void on_to_settings_button_clicked();
    void on_to_tank_button_clicked();
    void on_exit_button_clicked();
    void on_kill_button_clicked();
    void on_feeding_button_clicked();
    void next_frame();

    void on_music_slider_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
    Fish *mainFish;
};

#endif // MAINWINDOW_H
