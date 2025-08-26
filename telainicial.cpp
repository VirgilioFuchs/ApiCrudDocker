#include "telainicial.h"
#include "./ui_telainicial.h"
#include "telacadastro.h"
#include <QMessageBox>
#include <QLineEdit>


TelaInicial::TelaInicial(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TelaInicial)
{
    ui->setupUi(this);
}

TelaInicial::~TelaInicial()
{
    delete ui;
}


void TelaInicial::on_btnLogin_clicked()
{
    // QString nome = ui->leUsuario->text();
    // QString senha = ui->leSenha->text();

    //     // Condição de Login
    //     if(){
    //         QMessageBox::information(this, "Login", "Login efetuado com sucesso!");
    //         ui->leUsuario->clear();
    //         ui->leSenha->clear();
    //         close();
    //     } else {
    //         QMessageBox::critical(this, "Erro!", "Usuário ou Senha estão incorretos!");
    //         ui->leUsuario->clear();
    //         ui->leSenha->clear();
    //     }

}


void TelaInicial::on_btnCadastrar_clicked()
{
    //Recebe do enviarDados e armazena no receberDadosCadastro
    TelaCadastro *telaCadastro = new TelaCadastro(this);
    // connect(telaCadastro, &TelaCadastro::enviarDados, this, &TelaInicial::receberDadosCadastro);
    telaCadastro->show();
}

