#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    stopLoading = false;
    isLoaded = false;

    col1Checked = false;
    col2Checked = false;
    col3Checked = false;
    col4Checked = false;

    circleChartAvl = false;
    barChartAvl = false;

    sputterChartAvl = false;

    row = 1;
    col = 1;
    pos = 0;

    m = 0;
    presentRows = 20;

    tempStr = "";
    tempStr2 ="";

    col1_checkBox = new QCheckBox(parent);
    col2_checkBox = new QCheckBox(parent);
    col3_checkBox = new QCheckBox(parent);
    col4_checkBox = new QCheckBox(parent);

    ui->col1_checkBox->setChecked(false);
    ui->col2_checkBox->setChecked(false);
    ui->col3_checkBox->setChecked(false);
    ui->col4_checkBox->setChecked(false);

    apply_Btn = new QPushButton(parent);
    barChart_Btn = new QPushButton(parent);
    showData_Btn= new QPushButton(parent);
    circleChart_Btn = new QPushButton(parent);
    lineChart_Btn = new QPushButton(parent);
    clear_Btn = new QPushButton(parent);
    load_Btn = new QPushButton(parent);

    ui->apply_Btn->setEnabled(false);
    ui->barChart_Btn->setEnabled(false);
    ui->showData_Btn->setEnabled(false);
    ui->circleChart_Btn->setEnabled(false);
    ui->lineChart_Btn->setEnabled(false);
    ui->clear_Btn->setEnabled(false);
    ui->load_Btn->setEnabled(true);

    tableWidget = new QTableWidget(parent);
    tableWidget->setRowCount(20);
    tableWidget->setColumnCount(4);
    tableHorizontalHeader<<"Kolumna 1"<<"Kolumna 2"<<"Kolumna 3"<<"Kolumna 4";
    tableVerticalHeader<<"Wiersz 1"<<"Wiersz 2"<<"Wiersz 3"<<"Wiersz 4"
                       <<"Wiersz 5"<<"Wiersz 6"<<"Wiersz 7"<<"Wiersz 8"
                       <<"Wiersz 9"<<"Wiersz 10"<<"Wiersz 11"<<"Wiersz 12"
                       <<"Wiersz 13"<<"Wiersz 14"<<"Wiersz 15"<<"Wiersz 16"
                       <<"Wiersz 17"<<"Wiersz 18"<<"Wiersz 19"<<"Wiersz 20";
    ui->tableWidget->setHorizontalHeaderLabels(tableHorizontalHeader);
    ui->tableWidget->setVerticalHeaderLabels(tableVerticalHeader);
    ui->tableWidget->verticalHeader()->setVisible(true);
    ui->tableWidget->horizontalHeader()->setVisible(true);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setShowGrid(true);
    ui->tableWidget->setStyleSheet("QTableView {selection-background-color: blue;}");
   // tableWidget->setGeometry(QApplication::desktop()->screenGeometry());

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_load_Btn_clicked()
{



    fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                        "/home",
                                                        tr("XML files (*.xlsx)"));

    usableFileName = "";

    for(int i=0, j=0; i < fileName.length(); i++)
    {
        usableFileName[j] = fileName[i];
        if(fileName[i] == '/')
        {
            usableFileName[j] = '\\';
            usableFileName[j+1] = '\\';
            j++;
        }
        else
        {
            usableFileName[j] = fileName[i];
        }
        j++;
    }

    stopLoading = false;

    excel     = new QAxObject("Excel.Application");
    workbooks = excel->querySubObject("Workbooks");
    workbook  = workbooks->querySubObject("Open(const QString&)", usableFileName);
    if (!workbook)
    {
        isLoaded = false;
        QMessageBox::information(this, "", "Nie udalo sie zaladowac workbook");
    }
    else
    {
        sheets = workbook->querySubObject("Worksheets");
        if (!sheets)
        {
            isLoaded = false;
            QMessageBox::information(this, "", "Nie udalo sie zaladowac worksheets");
        }
        else
        {
            sheet = sheets->querySubObject("Item(int)", 1);
            excel->setProperty("EnableEvents", false);
            excel->dynamicCall("SetVisible(bool)", false);
            isLoaded = true;
        }
    }


    if(isLoaded) {
        ui->barChart_Btn->setEnabled(false);
        ui->showData_Btn->setEnabled(true);
        ui->circleChart_Btn->setEnabled(false);
        ui->lineChart_Btn->setEnabled(false);
        ui->clear_Btn->setEnabled(true);
        ui->load_Btn->setEnabled(false);
        ui->apply_Btn->setEnabled(true);


        while((col <= ui->tableWidget->columnCount()) && (stopLoading == false))
        {

            while((row <= ui->tableWidget->rowCount()) && (row <= presentRows))
            {
                tempStr = sheet->querySubObject("Cells(int,int)",row,col)->dynamicCall("Value()").toString();

                //qDebug(qUtf8Printable(sheet->querySubObject("Cells(int,int)",row,col)->dynamicCall("Value()").toString()));
                //qDebug(qUtf8Printable(QString::number(pos)));

                if(row == 1 && (col >= 1))
                {

                   //qDebug(qUtf8Printable(QString::number(row)));
                   //qDebug(qUtf8Printable(tempStr));
                   if(tempStr == "")
                   {
                       stopLoading = true;
                       col = 1;
                       row = 1;
                       pos = 0;
                       presentRows = 20;
                       dataVector.clear();
                       tempStr = "";
                       QMessageBox::information(this, "", "Wprowadzone dane sa zapisane w nieprawidlowy sposob");
                       ui->barChart_Btn->setEnabled(false);
                       ui->showData_Btn->setEnabled(false);
                       ui->circleChart_Btn->setEnabled(false);
                       ui->lineChart_Btn->setEnabled(false);
                       ui->clear_Btn->setEnabled(true);
                       ui->load_Btn->setEnabled(false);
                       ui->apply_Btn->setEnabled(false);
                   }
                   for (int j = 0; j < tempStr.size(); j++)
                   {
                        if(tempStr[j].isDigit())
                        {
                            stopLoading = true;
                            col = 1;
                            row = 1;
                            pos = 0;
                            presentRows = 20;
                            dataVector.clear();
                            tempStr = "";
                            QMessageBox::information(this, "", "Wprowadzone dane sa zapisane w nieprawidlowy sposob");
                            ui->barChart_Btn->setEnabled(false);
                            ui->showData_Btn->setEnabled(false);
                            ui->circleChart_Btn->setEnabled(false);
                            ui->lineChart_Btn->setEnabled(false);
                            ui->clear_Btn->setEnabled(true);
                            ui->apply_Btn->setEnabled(false);
                            ui->load_Btn->setEnabled(false);
                            //workbook->dynamicCall("Close()");
                           // excel->dynamicCall("Quit()");
                            break;

                        }
                        else
                        {
                            //nic nie rob
                        }
                   }

                }

                if((row > 1) && (col == 1))
                {
                    if(tempStr == "")
                    {
                        //qDebug(qUtf8Printable(tempStr));
                        break;
                    }
                }

                if(row > 1 && col > 1)
                {

                 //  qDebug(qUtf8Printable(QString::number(row)));
                 //  qDebug(qUtf8Printable(tempStr));

                   for (int j = 0; j < tempStr.size(); j++)
                   {
                        if(tempStr[j].isDigit())
                        {
                            //nic nie rob
                        }
                        else
                        {
                            stopLoading = true;
                            col = 1;
                            row = 1;
                            pos = 0;
                            presentRows = 20;
                            dataVector.clear();
                            tempStr = "";
                            QMessageBox::information(this, "", "Wprowadzone dane sa zapisane w nieprawidlowy sposob");
                            ui->barChart_Btn->setEnabled(false);
                            ui->showData_Btn->setEnabled(false);
                            ui->circleChart_Btn->setEnabled(false);
                            ui->lineChart_Btn->setEnabled(false);
                            ui->clear_Btn->setEnabled(true);
                            ui->apply_Btn->setEnabled(false);
                            ui->load_Btn->setEnabled(false);
                           // delete excel;
                            //workbook->dynamicCall("Close (Boolean)", false);
                            //excel->dynamicCall("Quit()");
                            break;
                        }
                   }

                }

                if(tempStr == "")
                {
                    dataVector.insert(pos, "0");
                }
                else {
                    dataVector.insert(pos, sheet->querySubObject("Cells(int,int)",row,col)->dynamicCall("Value()").toString());
                }
                pos++;
                row++;
            }

            if(col == 1) {
                presentRows = row - 1;
               qDebug(qUtf8Printable(QString::number(presentRows)));
            }

            col++;
            row = 1;
        }
    }
}

void MainWindow::on_barChart_Btn_clicked()
{
    wykres wykres;
    wykres.setModal(true);
    wykres.exec();
}

void MainWindow::on_circleChart_Btn_clicked()
{
     wykresKolowy wykres;
     wykres.setModal(true);
     wykres.exec();
}

void MainWindow::on_lineChart_Btn_clicked()
{
    wykresliniowy wykres;
    wykres.setModal(true);
    wykres.exec();
}

void MainWindow::on_clear_Btn_clicked()
{
    ui->barChart_Btn->setEnabled(false);
    ui->showData_Btn->setEnabled(false);
    ui->circleChart_Btn->setEnabled(false);
    ui->lineChart_Btn->setEnabled(false);
    ui->clear_Btn->setEnabled(false);
    ui->load_Btn->setEnabled(true);
    ui->apply_Btn->setEnabled(false);

    ui->col1_checkBox->setChecked(false);
    ui->col2_checkBox->setChecked(false);
    ui->col3_checkBox->setChecked(false);
    ui->col4_checkBox->setChecked(false);

    circleChartAvl = false;
    barChartAvl = false;
    sputterChartAvl = false;


    tempStr="";
    tempStr2="";

    stopLoading = false;
    isLoaded = false;
    row = 1;
    col = 1;
    pos = 0;
    m = 0;
    presentRows = 20;
    dataVector.clear();
    for(int i = 0; i < ui->tableWidget->columnCount(); i++)
    {
        for(int j = 0; j < ui->tableWidget->rowCount(); j++)
        {
            ui->tableWidget->setItem(j,i, new QTableWidgetItem(""));
            m++;
        }
    }
   // workbook->dynamicCall("Close()");
   // excel->dynamicCall("Quit()");
    delete excel;
}

void MainWindow::on_showData_Btn_clicked()
{
    m = 0;
    for(int i = 0; i < ui->tableWidget->columnCount(); i++)
    {
        for(int j = 0; j < presentRows ; j++)
        {
            ui->tableWidget->setItem(j,i, new QTableWidgetItem(dataVector[m]));
            m++;
        }
    }



}

void MainWindow::checkForPermission()
{
    if(col1Checked)
    {
        if(col2Checked && col3Checked && col4Checked)
        {
            col2Avl = true;
            col3Avl = true;
            col4Avl = true;

            circleChartAvl = true;
            barChartAvl = true;
            sputterChartAvl = true;
        }
        if(col2Checked && !col3Checked && !col4Checked)
        {
            col2Avl = true;
            col3Avl = false;
            col4Avl = false;

            circleChartAvl = true;
            barChartAvl = false;
            sputterChartAvl = true;
        }
        if(!col2Checked && col3Checked && !col4Checked)
        {
            col2Avl = false;
            col3Avl = true;
            col4Avl = false;

            circleChartAvl = true;
            barChartAvl = false;
            sputterChartAvl = true;
        }
        if(!col2Checked && !col3Checked && col4Checked)
        {
            col2Avl = false;
            col3Avl = false;
            col4Avl = true;

            circleChartAvl = true;
            barChartAvl = false;
            sputterChartAvl = true;
        }
        if(!col2Checked && !col3Checked && !col4Checked)
        {
            col2Avl = false;
            col3Avl = false;
            col4Avl = false;

            circleChartAvl = false;
            barChartAvl = false;
            sputterChartAvl = false;
        }
        if(col2Checked && col3Checked && !col4Checked)
        {
            col2Avl = true;
            col3Avl = true;
            col4Avl = false;

            circleChartAvl = true;
            barChartAvl = true;
            sputterChartAvl = true;
        }
        if(col2Checked && !col3Checked && col4Checked)
        {
            col2Avl = true;
            col3Avl = false;
            col4Avl = true;

            circleChartAvl = true;
            barChartAvl = true;
            sputterChartAvl = true;
        }
        if(!col2Checked && col3Checked && col4Checked)
        {
            col2Avl = false;
            col3Avl = true;
            col4Avl = true;

            circleChartAvl = true;
            barChartAvl = true;
            sputterChartAvl = true;
        }

    }
    else
    {
        col2Avl = false;
        col3Avl = false;
        col4Avl = false;

        circleChartAvl = false;
        barChartAvl = false;
        sputterChartAvl = false;
    }
    checkForCharts();
}

void MainWindow::checkForCharts()
{
    if(circleChartAvl)
    {
        ui->circleChart_Btn->setEnabled(true);
    }
    else
    {
        ui->circleChart_Btn->setEnabled(false);
    }

    if(barChartAvl)
    {
        ui->barChart_Btn->setEnabled(true);
    }
    else
    {
        ui->barChart_Btn->setEnabled(false);
    }

    if(sputterChartAvl)
    {
        ui->lineChart_Btn->setEnabled(true);
    }
    else
    {
        ui->lineChart_Btn->setEnabled(false);
    }
}

void MainWindow::on_apply_Btn_clicked()
{
    if(ui->col1_checkBox->isChecked())
    {
        col1Checked = true;
    }
    else
    {
        col1Checked = false;
    }

    if(ui->col2_checkBox->isChecked())
    {
        col2Checked = true;
    }
    else
    {
        col2Checked = false;
    }

    if(ui->col3_checkBox->isChecked())
    {
        col3Checked = true;
    }
    else
    {
        col3Checked = false;
    }

    if(ui->col4_checkBox->isChecked())
    {
        col4Checked = true;
    }
    else
    {
        col4Checked = false;
    }

       checkForPermission();
}

void MainWindow::on_actionZako_cz_triggered()
{



            int ret = QMessageBox::critical(this,"Uwaga!","Czy chcesz zakończyć działanie aplikacji  ?",
                                            QMessageBox::Ok | QMessageBox::Cancel);


    if ( ret == QMessageBox::Ok)
            {
        statusBar()->showMessage("Aplikacja zostanie zamknięta w ciągu 4s...");
         QTimer::singleShot(4000,this,SLOT(quitApp()));
            }




}
void MainWindow::quitApp()
{
    QApplication::quit();
}

void MainWindow::on_actionEksplorator_plik_w_triggered()
{
    eksplorator eksplorator;
    eksplorator.setModal(true);
    eksplorator.exec();
}

void MainWindow::on_actionDodaj_opis_triggered()
{
    /*
      opisWykresu opis;
    opis.setModal(true);
    opis.exec();

    */
}
