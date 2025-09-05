#include "telainicial.h"
#include "./ui_telainicial.h"
#include "telacadastro.h"
#include <QMessageBox>
#include <QLineEdit>

//Bibliotecas necessárias para o SQLite
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDir>
#include <qcryptographichash.h>


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

    QByteArray senhaHash = QCryptographicHash::hash(senha.toUtf8(), QCryptographicHash::Sha256).toHex();

    QSqlQuery query;
    query.prepare("SELECT id FROM usuarios WHERE nome = :nome AND senha = :senha");
    query.bindValue(":nome", nome);
    query.bindValue(":senha", QString(senhaHash));

    if(query.exec() && query.next()) {
        QMessageBox::information(this, "Sucesso", "Bem vindo ao nosso sistema!");
        close();
    } else {
        QMessageBox::critical(this, "Erro", "Nome ou senha inválidos ou inexistesnte!");
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
