#include "telacadastro.h"
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

    if (validacaoCadastro(nomeCadastro,senhaCadastro)) {
        QMessageBox::information(this, "Sucesso", "Usuário e Senha cadastrados!");
        qDebug() << "Nome e senha foram cadastrados...";
        close();
        ui->leCadastroUsuario->clear();
        ui->leCadastroUsuario->clear();

    } else {
        QMessageBox::critical(this, "Erro", "Erro ao cadastrar o usuário!");
        ui->leCadastroUsuario->clear();
        ui->leCadastroUsuario->clear();
    }

}

void TelaCadastro::on_btnVoltar_clicked()
{
    close();
}

bool TelaCadastro::validacaoCadastro(const QString &nomeCadastro, QString &senhaCadastro){
    if (!nomeCadastro.isEmpty() && !senhaCadastro.isEmpty()){
        return true;
    } else{
        return false;
    }
}
