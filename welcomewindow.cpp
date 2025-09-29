#include "welcomewindow.h"
#include "./ui_welcomewindow.h"
#include <iostream>

welcomeWindow::welcomeWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::welcomeWindow)
{
    ui->setupUi(this);

    connect(ui->newGameButton, &QPushButton::released, this, &welcomeWindow::startgamebuttonclicked);
}

welcomeWindow::~welcomeWindow()
{
    std::cout << "Welcome destructed" << std::endl;
    delete ui;
}

void welcomeWindow::startgamebuttonclicked(){
    int difficulty = (1 + ui->difficultyBox->currentIndex())*20;
    int hints = ui->hintsBox->value();
    std::cout << "Start button clicked" << std::endl;
    emit startgame(difficulty, hints);
    close();
};