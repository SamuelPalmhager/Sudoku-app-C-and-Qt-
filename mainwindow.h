#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Sudoku.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Sudoku sudoku;
    Ui::MainWindow *ui;

private slots: 
    void onSolveClicked();
    void OnNewBoardClicked(int, int);
    void onClearClicked();
    void onHintClicked();
    void startnewgame(int, int);
    void onSaveClicked();
    bool saveBoard();
};
#endif // MAINWINDOW_H
