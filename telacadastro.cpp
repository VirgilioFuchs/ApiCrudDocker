#include "telacadastro.h"
#include "ui_telacadastro.h"
#include <QMessageBox>
#include <QLineEdit>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QDir>
#include <qcryptographichash.h>

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

    if(nomeCadastro.isEmpty() && senhaCadastro.isEmpty()){
        QMessageBox::warning(this, "AVISO", "Preencha todos os campos!");
        return;
    }

}

// Volta para a Tela Inicial
void TelaCadastro::on_btnVoltar_clicked()
{
    reject();
}

void TelaCadastro::onCadastroReply(QNetworkReply *resposta)
{

}
