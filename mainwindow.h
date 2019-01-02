#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QAxObject>
#include <QDebug>
#include <QMessageBox>

#include "wykreskolowy.h"
#include "wykres.h"
#include "wykresliniowy.h"
#include "eksplorator.h"
#include "opisWykresu.h"
#include "globals.h"

class QPushButton;
class QAxObject;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_load_Btn_clicked();

    void on_barChart_Btn_clicked();

    void on_showData_Btn_clicked();

    void on_circleChart_Btn_clicked();

    void on_lineChart_Btn_clicked();

    void on_clear_Btn_clicked();



    void on_apply_Btn_clicked();

    void on_actionZako_cz_triggered();
    void quitApp();

    void on_actionEksplorator_plik_w_triggered();

    void on_actionDodaj_opis_triggered();

private:
    void checkForCharts();
    void checkForPermission();

    bool isLoaded;
    bool stopLoading;
    bool col1Checked, col2Checked, col3Checked, col4Checked;


    int row, col, pos;
    int m;


    QString tempStr, tempStr2;
    QString fileName, usableFileName;

    QStringList tableVerticalHeader;
    QStringList tableHorizontalHeader;

    QTableWidget *tableWidget;

    QPushButton *apply_Btn;
    QPushButton *barChart_Btn;
    QPushButton *showData_Btn;
    QPushButton *circleChart_Btn;
    QPushButton *lineChart_Btn;
    QPushButton *load_Btn;
    QPushButton *clear_Btn;

    QCheckBox *col1_checkBox;
    QCheckBox *col2_checkBox;
    QCheckBox *col3_checkBox;
    QCheckBox *col4_checkBox;

    QAxObject* excel ;
    QAxObject* workbooks;
    QAxObject* workbook;
    QAxObject* sheets;
    QAxObject* sheet;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
