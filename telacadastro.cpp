#include "telacadastro.h"
#include "database.h"
#include "ui_telacadastro.h"
#include <QMessageBox>
#include <QLineEdit>

//Bibliotecas necessárias para o SQLite
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDir>

TelaCadastro::TelaCadastro(QWidget *parent)
    : QDialog(parent)
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

    if (Database::instance()->cadastrarUsuario(nomeCadastro, senhaCadastro)) {
        QMessageBox::information(this, "Cadastro", "Usuário cadastrado com sucesso!");
        accept(); // Fecha a janela de diálogo
    } else {
        QMessageBox::critical(this, "Cadastro", "Erro: O usuário já pode existir ou a senha é inválida.");
        ui->leCadastroUsuario->clear();
        ui->leCadastroSenha->clear();
    }
}

// Volta para a Tela Inicial
void TelaCadastro::on_btnVoltar_clicked()
{
    reject();
}

