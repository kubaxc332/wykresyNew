#include "wykreskolowy.h"
#include "mainwindow.h"
#include "ui_wykreskolowy.h"

wykresKolowy::wykresKolowy(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::wykresKolowy)
{
    ui->setupUi(this);

     mainLayout = new QGridLayout;


     series0 = new QPieSeries();
     series1 = new QPieSeries();
     series2 = new QPieSeries();

     for(int j = 0; j < presentRows ; j++)
     {
        series0->append(dataVector[j+1], dataVector[j+1+(presentRows)].toInt());
        series1->append(dataVector[j+1], dataVector[j+1+(2*presentRows)].toInt());
        series2->append(dataVector[j+1], dataVector[j+1+(3*presentRows)].toInt());
     }

     m = 0;

    if(col2Avl)
    {
         chart_0 = new QChart();
         chart_0->addSeries(series0);
         chart_0->setTitle("Wykres " + dataVector[presentRows]);
         chart_0->legend()->show();

         chartView_0 = new QChartView(chart_0);
         chartView_0->setRenderHint(QPainter::Antialiasing);
         mainLayout->addWidget(chartView_0, 0, m);
     }

     if(col3Avl)
     {
         ++m;
         chart_1 = new QChart();
         chart_1->addSeries(series1);
         chart_1->setTitle("Wykres " + dataVector[2*presentRows]);
         chart_1->legend()->show();

         chartView_1 = new QChartView(chart_1);
         chartView_1->setRenderHint(QPainter::Antialiasing);
         mainLayout->addWidget(chartView_1, 0, m);
     }

     if(col4Avl)
     {
         ++m;
         chart_2 = new QChart();
         chart_2->addSeries(series2);
         chart_2->setTitle("Wykres " + dataVector[3*presentRows]);
         chart_2->legend()->show();

         chartView_2 = new QChartView(chart_2);
         chartView_2->setRenderHint(QPainter::Antialiasing);
         mainLayout->addWidget(chartView_2, 0, m);
     }

     setLayout(mainLayout);

     setWindowTitle(tr("Wykres kolowy"));
}

wykresKolowy::~wykresKolowy()
{
    delete ui;
}
