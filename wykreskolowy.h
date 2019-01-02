#ifndef WYKRESKOLOWY_H
#define WYKRESKOLOWY_H

#include <QDialog>
#include <QtCharts>
#include <QtWidgets>
#include "globals.h"

namespace Ui {
class wykresKolowy;
}

class wykresKolowy : public QDialog
{
    Q_OBJECT

public:
    explicit wykresKolowy(QWidget *parent = nullptr);
    ~wykresKolowy();

private:
    int m;

    QGridLayout *mainLayout;
    QChartView *chartView_0, *chartView_1, *chartView_2;
    QPieSeries *series0, *series1, *series2;
    QPieSlice *slice;
    QChart *chart_0, *chart_1, *chart_2;
    Ui::wykresKolowy *ui;
};

#endif // WYKRESKOLOWY_H
