#include "telaeditar.h"
#include "ui_telaeditar.h"

TelaEditar::TelaEditar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TelaEditar)
    , rmAluno(-1)
{
    ui->setupUi(this);


}

TelaEditar::~TelaEditar()
{
    delete ui;
}

void TelaEditar::on_btnAlterarDados_clicked()
{

}

