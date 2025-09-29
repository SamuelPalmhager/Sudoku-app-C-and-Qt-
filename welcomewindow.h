#ifndef WELCOMEWINDOW_H
#define WELCOMEWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class welcomeWindow;
}
QT_END_NAMESPACE

class welcomeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit welcomeWindow(QWidget *parent = nullptr);
    ~welcomeWindow();
    void startgamebuttonclicked();

signals:
    void startgame(int, int);    
    
private:
    Ui::welcomeWindow *ui;
};
#endif // WELCOMEWINDOW_H
