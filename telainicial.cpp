#include "telainicial.h"
#include "./ui_telainicial.h"
#include "telacadastro.h"
#include "database.h"
#include <QMessageBox>
#include <QLineEdit>

//Bibliotecas necessárias para o SQLite
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDir>


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
    QString nome = ui->leUsuario->text();
    QString senha = ui->leSenha->text();

    if (Database::instance()->validarLogin(nome, senha)) {
        QMessageBox::information(this, "Login", "Login realizado com sucesso!");
        close();
    } else {
        QMessageBox::warning(this, "Login", "Usuário ou senha incorretos.");
        ui->leUsuario->clear();
        ui->leSenha->clear();
    }
}

// Abre a Tela Cadastro
void TelaInicial::on_btnCadastrar_clicked()
{
    TelaCadastro telaCadastro(this);
    telaCadastro.exec();
}
