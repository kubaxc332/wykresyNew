//#include "mainwindow.h"
#include "logowanie.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>


QString readTextFile(QString path)
{
    QFile file(path);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        return in.readAll();
    }

    return "";
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
   // w.show();
    QString css = readTextFile(":/style/style/style.css");

            if( css.length() > 0)
            {
                a.setStyleSheet(css);
            }

    logowanie w;
    w.show();


    return a.exec();
}
