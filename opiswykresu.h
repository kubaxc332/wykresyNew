#ifndef OPISWYKRESU_H
#define OPISWYKRESU_H

#include <QWidget>

namespace Ui {
class opisWykresu;
}

class opisWykresu : public QWidget
{
    Q_OBJECT

public:
    explicit opisWykresu(QWidget *parent = nullptr);
    ~opisWykresu();

private slots:
    void on_SaveBtn_clicked();

    void on_OpenBtn_clicked();

    void on_selectBtn_clicked();

    void on_CopyBtn_clicked();

private:
    Ui::opisWykresu *ui;
};

#endif // OPISWYKRESU_H
