#include "telaeditar.h"
#include "ui_telaeditar.h"
#include <qmessagebox.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkRequest>

TelaEditar::TelaEditar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TelaEditar)
    , idAluno(-1)
{
    ui->setupUi(this);
    conexao = new QNetworkAccessManager(this);
}

void TelaEditar::dadosAlunos(int rmAluno,
                             const QString &nomeAluno,
                             const QDate &dataNascimentoAluno,
                             const QString &sexoAluno,
                             const QString &cpfAluno,
                             const QString &rgAluno,
                             const QString &nomeResponsavel,
                             const QString &telefoneResponsavel)
{
    idAluno = rmAluno;

    ui->leRmAluno->setText(QString::number(rmAluno));
    ui->leNomeAluno->setText(nomeAluno);
    ui->deDataNascimento->setDate(dataNascimentoAluno);
    ui->leCPFAluno->setText(cpfAluno);
    ui->leRGAluno->setText(rgAluno);
    ui->leNomeResponsavel->setText(nomeResponsavel);
    ui->leTelefoneResponsavel->setText(telefoneResponsavel);

    if(sexoAluno == "M") {
        ui->rbMasculino->setChecked(true);
    } else if(sexoAluno == "F") {
        ui->rbFeminino->setChecked(true);
    }
}

TelaEditar::~TelaEditar()
{
    delete ui;
}

void TelaEditar::on_btnAlterarDados_clicked()
{
    QString nomeAluno = ui->leNomeAluno->text();
    QString dataNascimentoAluno = ui->deDataNascimento->date().toString("yyyy-MM-dd");
    QString nomeResponsavel = ui->leNomeResponsavel->text();
    QString telefoneResponsavel = ui->leTelefoneResponsavel->text();

    QString sexoAluno;
    if(ui->rbMasculino->isChecked()) sexoAluno = "M";
    else if(ui->rbFeminino->isChecked()) sexoAluno = "F";
    else QMessageBox::critical(this, "Erro!", "Erro ao identificar o sexo do aluno!");

    QString urlString = QString("http://127.0.0.1:8080/alunos/%1").arg(idAluno);
    QNetworkRequest request((QUrl(urlString)));

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=utf-8");
    request.setRawHeader("Authorization", ("Bearer " + jwtToken).toUtf8());

    QJsonObject json;
    json["nomeAluno"] = nomeAluno;
    json["dataNascimento"] = dataNascimentoAluno;
    json["sexoAluno"] = sexoAluno;
    json["nomeResponsavel"] = nomeResponsavel;
    json["telefoneResponsavel"] = telefoneResponsavel;

    QJsonDocument docJson(json);
    QByteArray data = docJson.toJson();

    connect(conexao, &QNetworkAccessManager::finished, this, &TelaEditar::onUpdateReply);
    conexao->put(request, data);
}

void TelaEditar::onUpdateReply(QNetworkReply *resposta)
{
    // Garante que o sinal não seja processado novamente
    disconnect(conexao, &QNetworkAccessManager::finished, this, &TelaEditar::onUpdateReply);

    if (resposta->error()) {
        QMessageBox::critical(this, "Erro de Rede", "Erro ao atualizar! " + resposta->errorString());
        resposta->deleteLater();
        return;
    }

    QByteArray respostaData = resposta->readAll();
    QString resp = QString::fromUtf8(respostaData);

    if (resp.contains("Aluno e Responsavel atualizados com sucesso!", Qt::CaseInsensitive)) {
        QMessageBox::information(this, "Sucesso!", "Dados alterados com sucesso!");
        emit dadosInseridos();
        this->close();
    } else {
        QMessageBox::critical(this, "ERRO!", "Resposta Inesperada: " + resp);
    }
    resposta->deleteLater();
}


void TelaEditar::on_btnVoltar_clicked()
{
    this->close();
}

