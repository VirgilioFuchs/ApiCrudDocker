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
    conexao = new QNetworkAccessManager(this);
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


    QUrl url("http://127.0.0.1:8080/register");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=utf-8");

    QJsonObject json;
    json["nome"] = nomeCadastro;
    json["senha"] = senhaCadastro;

    QJsonDocument docJson(json);
    QByteArray data = docJson.toJson();

    conexao->post(request,data);

    connect(conexao, &QNetworkAccessManager::finished, this, &TelaCadastro::onCadastroReply);
}

// Volta para a Tela Inicial
void TelaCadastro::on_btnVoltar_clicked()
{
    reject();
}

void TelaCadastro::onCadastroReply(QNetworkReply *resposta)
{
    if(resposta->error()) {
        QMessageBox::critical(this, "Erro", "Erro ao Cadastrar!" + resposta->errorString());
        resposta->deleteLater();
        return;
    }

    QByteArray respostaData = resposta->readAll();
    QString resp = QString::fromUtf8(respostaData);

    if (resp.contains("Usuário Cadastrado com sucesso!", Qt::CaseInsensitive)) {
        QMessageBox::information(this, "Sucesso!", "Cadastro realizado com sucesso!");
        ui->leCadastroUsuario->clear();
        ui->leCadastroSenha->clear();
        accept();
    } else {
        QMessageBox::critical(this, "ERRO!", "Resposta Inesperada: " + resp);
    }

    resposta->deleteLater();
}
