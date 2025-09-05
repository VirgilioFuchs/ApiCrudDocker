#include "telaalterar.h"
#include "ui_telaalterar.h"

TelaAlterar::TelaAlterar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TelaAlterar)
{
    ui->setupUi(this);
}

TelaAlterar::~TelaAlterar()
{
    delete ui;
}

void TelaAlterar::on_pushButton_clicked()
{

}

