#include "mainwindow.h"     
#include "welcomewindow.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QWidget>
#include <QPushbutton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();

    for (const QString &locale : uiLanguages) {
        const QString baseName = "SUDOKU_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }


    MainWindow w;
    w.setWindowTitle("Sudoku app");

    w.show();
    return a.exec();
}
