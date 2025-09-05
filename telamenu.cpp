#include "telamenu.h"
#include "ui_telamenu.h"

TelaMenu::TelaMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TelaMenu)
{
    ui->setupUi(this);
}

TelaMenu::~TelaMenu()
{
    delete ui;
}

void TelaMenu::on_btnPesquisar_clicked()
{

}


void TelaMenu::on_btnAdicionar_clicked()
{

}


void TelaMenu::on_btnEditar_clicked()
{

}


void TelaMenu::on_btnExcluir_clicked()
{

}

