#include "evaluatewindow.h"
#include "ui_evaluatewindow.h"

EvaluateWindow::EvaluateWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EvaluateWindow)
{
    ui->setupUi(this);
}

EvaluateWindow::~EvaluateWindow()
{
    delete ui;
}

void EvaluateWindow::on_pushEvaluation_clicked()
{
    int i = ui->comboBox->currentIndex();
    qDebug()<<"评价为："<<i;


    emit sendEvaluate(i);


}
