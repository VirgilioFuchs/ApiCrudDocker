#include "telacadastro.h"
#include "ui_telacadastro.h"
#include <QMessageBox>
#include <QLineEdit>

TelaCadastro::TelaCadastro(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TelaCadastro)
{
    ui->setupUi(this);
}

TelaCadastro::~TelaCadastro()
{
    delete ui;
}

void TelaCadastro::on_btnCadastrar_clicked()
{
    QString nomeCadastro = ui->leCadastroUsuario->text();
    QString senhaCadastro = ui->leCadastroSenha->text();

    if(!nomeCadastro.isEmpty() && !senhaCadastro.isEmpty()){
        QMessageBox::information(this, "Sucesso!", "Cadastro realizado com sucesso!");
        emit enviarDados(nomeCadastro,senhaCadastro);
        close();
    } else {
        QMessageBox::critical(this, "Erro!", "Falha ao tentar cadastrar no sistema!");
        ui->leCadastroUsuario->clear();
        ui->leCadastroSenha->clear();
    }
}

void TelaCadastro::on_btnVoltar_clicked()
{
    close();
}

