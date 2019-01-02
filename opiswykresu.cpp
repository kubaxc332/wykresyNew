#include "opiswykresu.h"
#include "ui_opiswykresu.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

opisWykresu::opisWykresu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::opisWykresu)
{
    ui->setupUi(this);
}

opisWykresu::~opisWykresu()
{
    delete ui;
}

void opisWykresu::on_SaveBtn_clicked()
{

    QString filename = QFileDialog::getSaveFileName(this,"Zapisz jako");
    if( filename.isEmpty())
        return;

    QFile file(filename);


    if( !file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
        return;

    QTextStream out(&file);
    out << ui->textEdit->toPlainText() << "\n";

    file.close();
}

void opisWykresu::on_OpenBtn_clicked()
{
    QString  fileContent;

    QString filename = QFileDialog::getOpenFileName(this,"Otwórz plik");

    if(filename.isEmpty())
    return;

    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    QString line = in.readLine();

    while(!line.isNull())
    {
         fileContent.append(line);
        line = in.readLine();
    }

    file.close();

    ui->textEdit->clear();
    ui->textEdit->setPlainText(fileContent);
}



void opisWykresu::on_selectBtn_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,"Wybierz plik");
    if( filename.isEmpty())
        return;
    ui->sourceLineEdit->setText(filename);
}

void opisWykresu::on_CopyBtn_clicked()
{
    QString srcFileName = ui->sourceLineEdit->text();
    QString destFileName = ui->destLineEdit->text();

    if( srcFileName.isEmpty() || destFileName.isEmpty())
        return;

    QFile file(srcFileName);
    if( file.copy(destFileName))
    {
        QMessageBox::information(this,"Udało się!","Kopiowanie pliku powiodło się");
    }else
    {
        QMessageBox::information(this,"Błąd!","Kopiowanie pliku nie powiodło się");
    }
}
