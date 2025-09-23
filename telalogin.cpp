#include "telalogin.h"
#include "./ui_telalogin.h"
#include "telacadastro.h"
#include "telamenu.h"
#include <QMessageBox>
#include <QLineEdit>

#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>
#include <QDebug>
#include <QDir>
#include <qcryptographichash.h>


TelaInicial::TelaInicial(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TelaInicial)
{
    ui->setupUi(this);
    conexao= new QNetworkAccessManager(this);
}

TelaInicial::~TelaInicial()
{
    delete ui;
}

QString TelaInicial::getJwtToken() const
{
    return jwtToken;
}

void TelaInicial::on_btnLogin_clicked()
{
    QString nome = ui->leUsuario->text();
    QString senha = ui->leSenha->text();

    if (nome.isEmpty() || senha.isEmpty()) {
        QMessageBox::warning(this, "AVISO!", "Preencha todos os campos!");
        return;
    }

    QUrl url("http://127.0.0.1:8080/login");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject loginData;
    loginData["nome"] = nome;
    loginData["senha"] = senha;

    QJsonDocument docJson(loginData);
    resposta = conexao->post(request,docJson.toJson());

    connect(resposta, &QNetworkReply::finished, this, &TelaInicial::onLoginFinalizado);
}

// Abre a Tela Cadastro
void TelaInicial::on_btnCadastrar_clicked()
{
    TelaCadastro telaCadastro(this);
    telaCadastro.exec();
}

void TelaInicial::onLoginFinalizado()
{
    if(resposta->error() == QNetworkReply::NoError) {
        QByteArray resp = resposta->readAll();
        QJsonDocument json = QJsonDocument::fromJson(resp);
        jwtToken = json["token"].toString();

        QMessageBox::information(this, "Sucesso!", "Seja bem vindo ao nosso sistema!");
        TelaMenu *telaMenu = new TelaMenu(nullptr);
        telaMenu->setTelaLogin(this);
        telaMenu->show();
        this->hide();
        ui->leUsuario->clear();
        ui->leSenha->clear();
    } else {
        QMessageBox::critical(this, "Erro!", "Credenciais do usuário inválida!");
        ui->leUsuario->clear();
        ui->leSenha->clear();
    }
}
