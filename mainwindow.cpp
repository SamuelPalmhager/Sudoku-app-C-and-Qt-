#include "mainwindow.h"
#include "welcomewindow.h"
#include "./ui_mainwindow.h"
#include "Sudoku.h"

#include <iostream>
#include <QPushButton>
#include <string>
#include <vector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), 
    sudoku()
{

    welcomeWindow *welcome = new welcomeWindow(this);
    connect(welcome, &welcomeWindow::startgame, this, &MainWindow::startnewgame); 
    welcome->show();

    ui->setupUi(this);
    connect(ui->Solvebutton, &QPushButton::released, this, &MainWindow::onSolveClicked);
    //connect(ui->NewBoardButton, &QPushButton::released, this, &MainWindow::OnNewBoardClicked);
    connect(ui->clearButton, &QPushButton::released, this, &MainWindow::onClearClicked);
    connect(ui->hintButton, &QPushButton::released, this, &MainWindow::onHintClicked);
    connect(ui->saveButton, &QPushButton::released, this, &MainWindow::onSaveClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startnewgame(int diff, int hints){
    std::cout << "Diff: " << diff << " Hints: " << hints << std::endl;
    OnNewBoardClicked(diff, hints);
};


void MainWindow::onSolveClicked(){
    std::vector<std::vector<int>> board(9, std::vector<int>(9, 0));
    for (size_t row = 0; row < 9; row++)
    {
        for (size_t col = 0; col < 9; col++)
        {
            QString widgetname = QString{"CELL%1%2"}.arg(row).arg(col); 
            QLineEdit* cell = this->findChild<QLineEdit*>(widgetname);
            if (!cell) {
            std::cerr << "Cell not found: " << widgetname.toStdString() << std::endl;
            return;
            }
            board[row][col] = cell->text().toInt();
            std::cout << "Pushed back " << cell->text().toInt();
        }
    }

    sudoku.refsudokuSolver(board);
    sudoku.board = board;
    //std::cout << sudoku << std::endl;

    for (size_t row = 0; row < 9; row++)
    {
        for (size_t col = 0; col < 9; col++)
        {
            QString widgetname = QString{"CELL%1%2"}.arg(row).arg(col); 
            QLineEdit* cell = this->findChild<QLineEdit*>(widgetname);
            if (!cell) {
            std::cerr << "Cell not found: " << widgetname.toStdString() << std::endl;
            return;
            }
            cell->clear();
            cell->setText(QString{"%1"}.arg(board[row][col]));
        }
    }
};

void MainWindow::OnNewBoardClicked(int diff=0, int hints=0){
    sudoku.populateBoard(sudoku.board);
    sudoku.generateBoard(sudoku.board, diff);
    sudoku.maxHints = hints;
    sudoku.difficulty = diff;
    ui->hintButton->setDisabled(false);
    ui->hintText->clear();
    for (size_t i = 0; i < 9; i++)
    {
        for (size_t j = 0; j < 9; j++)
        {
            QString widgetname = QString{"CELL%1%2"}.arg(i).arg(j);
            QLineEdit* cell = this->findChild<QLineEdit*>(widgetname);
            if (!cell) {
            std::cerr << "Cell not found: " << widgetname.toStdString() << std::endl;
            return;
            }
            if(sudoku.board[i][j]==0){
                cell->clear();
                cell->setText(QString{""});
                continue;
            }
            cell->clear();
            cell->setText(QString{"%1"}.arg(sudoku.board[i][j]));
        }
    }
};

void MainWindow::onClearClicked(){
    for (size_t i = 0; i < 9; i++)
        {
        for (size_t j = 0; j < 9; j++)
        {
            QString widgetname = QString{"CELL%1%2"}.arg(i).arg(j);
            QLineEdit* cell = this->findChild<QLineEdit*>(widgetname);
            if (!cell) {
            std::cerr << "Cell not found: " << widgetname.toStdString() << std::endl;
            return;
            }

            cell->clear();
        }
     
    }
}

void MainWindow::onHintClicked(){
    std::vector<std::vector<int>> board {};
       for (size_t i = 0; i < 9; i++)
        {
        for (size_t j = 0; j < 9; j++)
        {
            QString widgetname = QString{"CELL%1%2"}.arg(i).arg(j);
            QLineEdit* cell = this->findChild<QLineEdit*>(widgetname);
            
            if (!cell) {
            std::cerr << "Cell not found: " << widgetname.toStdString() << std::endl;
            return;
            }
            if(cell->text()==QString{""}){
                sudoku.board[i][j]=0;
                continue;    
            };
            std::cout << "Pushed back " << cell->text().toInt() << std::endl;
            sudoku.board[i][j]=cell->text().toInt();
        }
    }
    std::cout << "Created board" << std::endl;
    //std::cout << sudoku << std::endl;

    std::vector<int> hint {sudoku.hint(sudoku.board)};

    if(hint.empty()){
        ui->hintText->setText(QString{"YOU HAVE USED UP YOUR HINTS CHEATER "});
        ui->hintButton->setDisabled(true);
    }else{
        QString text = QString{"%1%2%3"}.arg(hint.at(0)).arg(hint.at(1)).arg(hint.at(2));
        ui->hintText->setText(QString{"There CAN be a %1 in row %2 and col %3"}.arg(hint.at(2)).arg(hint.at(0)).arg(hint.at(1)));
    } 
};

void MainWindow::onSaveClicked(){
    for (size_t i = 0; i < 9; i++)
        {
        for (size_t j = 0; j < 9; j++)
        {
            QString widgetname = QString{"CELL%1%2"}.arg(i).arg(j);
            QLineEdit* cell = this->findChild<QLineEdit*>(widgetname);

            if (!cell) {
            std::cerr << "Cell not found: " << widgetname.toStdString() << std::endl;
            }

            if(cell->text()==QString{""}){
                sudoku.board[i][j]=0;
                std::cout << "Pushed back " << 0 << std::endl;
                continue;    
            };
            std::cout << "Pushed back " << cell->text().toInt() << std::endl;
            sudoku.board[i][j]=cell->text().toInt();
        }
    }
    sudoku.saveBoard(sudoku.board);
}

bool MainWindow::saveBoard(){
    for (size_t i = 0; i < 9; i++)
        {
        for (size_t j = 0; j < 9; j++)
        {
            QString widgetname = QString{"CELL%1%2"}.arg(i).arg(j);
            QLineEdit* cell = this->findChild<QLineEdit*>(widgetname);

            if (!cell) {
            std::cerr << "Cell not found: " << widgetname.toStdString() << std::endl;
            return false;
            }

            if(cell->text()==QString{""}){
                sudoku.board[i][j]=0;
                std::cout << "Pushed back " << 0 << std::endl;
                continue;    
            };
            std::cout << "Pushed back " << cell->text().toInt() << std::endl;
            sudoku.board[i][j]=cell->text().toInt();
        }
    }
    return true;
}